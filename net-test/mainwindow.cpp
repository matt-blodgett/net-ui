#include "mainwindow.h"

#include "panelrequest.h"
#include "panelresponse.h"

#include <QGridLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QSplitter>


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


#include <QDebug>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initialize();

    m_panelRequest->setMethod("GET");
    m_panelRequest->setUrl("http://qt-project.org");
}
MainWindow::~MainWindow()
{

}

void MainWindow::initialize()
{
    initializeObjects();
    initializeLayout();
    initializeMenubar();

}
void MainWindow::initializeObjects()
{
    m_frameSplitter = new QSplitter(this);
    m_panelRequest = new PanelRequest(this);
    m_panelResponse = new PanelResponse(this);

    m_networkAcessManager = new QNetworkAccessManager(this);

    connect(m_networkAcessManager, &QNetworkAccessManager::finished, this, &MainWindow::slotHandleResponse);
    connect(m_panelRequest, &PanelRequest::signalSendRequest, this, &MainWindow::slotSendRequest);
}
void MainWindow::initializeLayout()
{
    m_frameSplitter->addWidget(m_panelRequest);
    m_frameSplitter->addWidget(m_panelResponse);
    m_frameSplitter->setOrientation(Qt::Vertical);

    QWidget *windowMain = new QWidget(this);
    QGridLayout *gridMain = new QGridLayout(windowMain);
    gridMain->addWidget(m_frameSplitter, 0, 0, 1, 1);
    gridMain->setColumnStretch(0, 0);
    gridMain->setRowStretch(0, 1);
    gridMain->setContentsMargins(20, 20, 20, 20);
    gridMain->setHorizontalSpacing(0);
    gridMain->setVerticalSpacing(0);
    windowMain->setLayout(gridMain);
    setCentralWidget(windowMain);

    setMinimumHeight(500);
    setMinimumWidth(800);

    windowMain->setObjectName("WindowMain");
    windowMain->setStyleSheet("QWidget#WindowMain { background-color: #333333 }");
}
void MainWindow::initializeMenubar()
{
    QMenuBar *menuMain = menuBar();

    QAction *actWndExit = new QAction(menuMain);

    QAction *actHelpAbout = new QAction(menuMain);

    actWndExit->setText("Exit");

    actHelpAbout->setText("About");

    QMenu *menuFile = new QMenu(menuMain);
    QMenu *menuHelp = new QMenu(menuMain);

    menuFile->setTitle("File");
    menuHelp->setTitle("Help");

    menuMain->addMenu(menuFile);
    menuFile->addAction(actWndExit);

    menuMain->addMenu(menuHelp);
    menuHelp->addAction(actHelpAbout);

    connect(actWndExit, &QAction::triggered, this, [this](){window()->close();});

    // Testing
    QAction *actTest = new QAction(menuMain);
    actTest->setText("Test");
    connect(actTest, &QAction::triggered, this, &MainWindow::test);
    menuMain->addAction(actTest);
}

void MainWindow::slotSendRequest()
{
    m_panelResponse->setDisplayText("");

    const QString &method = m_panelRequest->method();
    const QUrl &url = m_panelRequest->url();
//    const QString &query = m_panelRequest->query();
    const QByteArray &data = m_panelRequest->data();

    QNetworkRequest request;
    request.setUrl(QUrl(url));
//    request.setRawHeader("User-Agent", "TestClient");

    if (method == "GET") {
        m_networkAcessManager->get(request);
    }
    else if (method == "POST") {
        m_networkAcessManager->post(request, data);
    }
    else if (method == "PUT") {
        m_networkAcessManager->put(request, data);
    }
    else if (method == "PATCH") {
        m_networkAcessManager->sendCustomRequest(request, "PATCH", data);
    }
    else if (method == "DELETE") {
        m_networkAcessManager->sendCustomRequest(request, "DELETE", data);
    }
}
void MainWindow::slotHandleResponse(QNetworkReply *networkReply)
{
    QStringList displayStream;

    displayStream << "URL: " << networkReply->url().toString();
    displayStream << "\n";

    displayStream << "STATUS: " << networkReply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toString();
    displayStream << "\n";

    displayStream << "DATA:";
    displayStream << "\n";

    if (networkReply->error() == QNetworkReply::NoError) {
        if (networkReply->isReadable()) {
            QByteArray bytes = networkReply->readAll();
            displayStream << QString::fromStdString(bytes.toStdString());
        }
    }

    QString displayText = displayStream.join("");
    m_panelResponse->setDisplayText(displayText);

    networkReply->deleteLater();
}



void MainWindow::test()
{
    qDebug() << "test";
}







void debugNetworkReply(QNetworkReply *networkReply)
{
//    url = QUrl("https://qt-project-org.herokuapp.com/")
//    status = QVariant(int, 200)
//    error = QNetworkReply::NoError
//    errorString = "Unknown error"
//    size = 0
//    true
//    true
//    false
//    1933
//    OpenMode( "ReadOnly" )
//    0
//    1933
    qDebug() << "url =" << networkReply->url();
    qDebug() << "status =" << networkReply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute);
    qDebug() << "error =" << networkReply->error();
    qDebug() << "errorString =" << networkReply->errorString();
    qDebug() << "size =" << networkReply->readBufferSize();

    if (networkReply->error() == QNetworkReply::NoError) {
        qDebug() << networkReply->isReadable();
        qDebug() << networkReply->isOpen();
        qDebug() << networkReply->isWritable();
        qDebug() << networkReply->size();
        qDebug() << networkReply->openMode();
        qDebug() << networkReply->readBufferSize();

        QByteArray bytes = networkReply->readAll();
        qDebug() << bytes.size();
    }

    networkReply->deleteLater();
}



