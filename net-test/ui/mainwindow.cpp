#include "mainwindow.h"

#include "panelworkspace.h"
#include "panelrequest.h"
#include "panelresponse.h"

#include <QGridLayout>
#include <QMenuBar>
#include <QSplitter>

#include <QStandardPaths>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>


#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initialize();
}
MainWindow::~MainWindow()
{
    delete m_networkAcessManager;
}

void MainWindow::initialize()
{
    initializeObjects();
    initializeLayout();
    initializeMenubar();
    loadSettings();
}
void MainWindow::initializeObjects()
{
    m_panelWorkspace = new PanelWorkspace(this);
    m_frameSplitter = new QSplitter(this);
    m_panelRequest = new PanelRequest(this);
    m_panelResponse = new PanelResponse(this);

    m_networkAcessManager = new QNetworkAccessManager(this);
    m_workspace = new Workspace(this);

    m_panelWorkspace->setWorkspace(m_workspace);

    connect(m_networkAcessManager, &QNetworkAccessManager::finished, this, &MainWindow::slotReceiveResponse);
    connect(m_panelRequest, &PanelRequest::signalSendRequest, this, &MainWindow::slotSendRequest);
}
void MainWindow::initializeLayout()
{
    m_frameSplitter->addWidget(m_panelRequest);
    m_frameSplitter->addWidget(m_panelResponse);
    m_frameSplitter->setOrientation(Qt::Vertical);
    m_frameSplitter->setCollapsible(0, false);
    m_frameSplitter->setCollapsible(1, false);

    QWidget *windowMain = new QWidget(this);
    QGridLayout *gridMain = new QGridLayout(windowMain);
    gridMain->addWidget(m_panelWorkspace, 0, 0, 1, 1);
    gridMain->addWidget(m_frameSplitter, 0, 1, 1, 1);
    gridMain->setColumnStretch(1, 1);
    gridMain->setRowStretch(0, 1);
    gridMain->setContentsMargins(20, 20, 20, 20);
    gridMain->setHorizontalSpacing(0);
    gridMain->setVerticalSpacing(0);
    windowMain->setLayout(gridMain);
    setCentralWidget(windowMain);
    setWindowIcon(QIcon(":/icons/generic.ico"));

    setMinimumHeight(500);
    setMinimumWidth(800);

    windowMain->setObjectName("WindowMain");
    windowMain->setStyleSheet("QWidget#WindowMain { background-color: #333333 }");
}
void MainWindow::initializeMenubar()
{
    QMenuBar *menuMain = menuBar();

    QAction *actSaveSettings = new QAction(menuMain);
    QAction *actLoadSettings = new QAction(menuMain);
    QAction *actReset = new QAction(menuMain);
    QAction *actWndExit = new QAction(menuMain);

    QAction *actHelpAbout = new QAction(menuMain);

    actSaveSettings->setText("Save");
    actLoadSettings->setText("Load");
    actReset->setText("Reset");
    actWndExit->setText("Exit");

    actHelpAbout->setText("About");

    QMenu *menuFile = new QMenu(menuMain);
    QMenu *menuHelp = new QMenu(menuMain);

    menuFile->setTitle("File");
    menuHelp->setTitle("Help");

    menuMain->addMenu(menuFile);
    menuFile->addAction(actSaveSettings);
    menuFile->addAction(actLoadSettings);
    menuFile->addSeparator();
    menuFile->addAction(actReset);
    menuFile->addSeparator();
    menuFile->addAction(actWndExit);

    menuMain->addMenu(menuHelp);
    menuHelp->addAction(actHelpAbout);

    connect(actSaveSettings, &QAction::triggered, this, &MainWindow::saveSettings);
    connect(actLoadSettings, &QAction::triggered, this, &MainWindow::loadSettings);
    connect(actReset, &QAction::triggered, this, &MainWindow::reset);
    connect(actWndExit, &QAction::triggered, this, [this](){window()->close();});
}

QString MainWindow::pathAppData() const
{
//    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    return "/home/matt/Desktop/net-ui-share";
}
QString MainWindow::pathSettings() const
{
    return pathAppData() + "/settings.json";
}

void MainWindow::loadSettings()
{
    if (!QDir(pathAppData()).exists()) {
        bool created = QDir().mkpath(pathAppData());
        if (created) {
            qDebug() << "created" << pathAppData();
        }
        else {
            qWarning() << "failed to save user settings" << pathSettings();
            return;
        }
    }

    QFile jsonFile(pathSettings());
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning() << "failed to load user settings" << pathSettings();
        return;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonRoot = jsonDocument.object();

    QJsonObject jsonWindow = jsonRoot["window"].toObject();
    int wnd_rootx = jsonWindow["x"].toInt(0);
    int wnd_rooty = jsonWindow["y"].toInt(0);
    int wnd_width = jsonWindow["width"].toInt(0);
    int wnd_height = jsonWindow["height"].toInt(0);
    bool wnd_maximized = jsonWindow["maximized"].toBool(false);

    if(wnd_maximized) {
        showMaximized();
    }
    else {
        move(wnd_rootx, wnd_rooty);
        resize(wnd_width, wnd_height);
    }


//    m_panelRequest->reset();

//    const QString &method = jsonRoot["method"].toString();
//    const QString &url = jsonRoot["url"].toString();
//    const QString &data = jsonRoot["data"].toString();

//    m_panelRequest->setMethod(method);
//    m_panelRequest->setUrl(url);
//    m_panelRequest->setData(data);
}
void MainWindow::saveSettings()
{
    if (!QDir(pathAppData()).exists()) {
        bool created = QDir().mkpath(pathAppData());
        if (created) {
            qDebug() << "created" << pathAppData();
        }
        else {
            qWarning() << "failed to save user settings" << pathSettings();
            return;
        }
    }

    QFile jsonFile(pathSettings());
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qWarning() << "failed to save user settings" << pathSettings();
        return;
    }

    QJsonObject jsonRoot;

    QJsonObject jsonWindow;
    jsonWindow["x"] = x();
    jsonWindow["y"] = y();
    jsonWindow["width"] = width();
    jsonWindow["height"] = height();
    jsonWindow["maximized"] = isMaximized();

    jsonRoot["window"] = jsonWindow;

    jsonFile.write(QJsonDocument(jsonRoot).toJson(QJsonDocument::JsonFormat::Indented));

    //    const QString &method = m_panelRequest->method();
    //    const QString &url = m_panelRequest->url();
    //    const QHash<QString, QString> &headers = m_panelRequest->headers();
    //    const QHash<QString, QString> &query = m_panelRequest->query();
    //    const QString &data = m_panelRequest->data();

}
void MainWindow::reset()
{
    QFile jsonFile(pathSettings());
    if (!jsonFile.remove()) {
        qWarning() << "error removing settings" << pathSettings();
    }

    m_panelRequest->reset();
    if (m_panelRequest->headers().size() == 0) {
        m_panelRequest->addHeader(QString(), QString());
    }
    if (m_panelRequest->query().size() == 0) {
        m_panelRequest->addQuery(QString(), QString());
    }
}

void MainWindow::slotSendRequest()
{
    m_panelResponse->setDisplayText("");

    const QString &method = m_panelRequest->method();
    const QString &url = m_panelRequest->url();
    const QHash<QString, QString> &headers = m_panelRequest->headers();
//    const QHash<QString, QString> &query = m_panelRequest->query();
    const QString &data = m_panelRequest->data();

    const QByteArray &payload = QByteArray(data.toStdString().c_str());

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QHash<QString, QString>::const_iterator i;
    for (i = headers.constBegin(); i != headers.constEnd(); ++i) {
        request.setRawHeader(QByteArray(i.key().toStdString().c_str()), QByteArray(i.value().toStdString().c_str()));
    }

    if (method == "GET") {
        m_networkAcessManager->get(request);
    }
    else if (method == "POST") {
        m_networkAcessManager->post(request, payload);
    }
    else if (method == "PUT") {
        m_networkAcessManager->put(request, payload);
    }
    else if (method == "PATCH") {
        m_networkAcessManager->sendCustomRequest(request, "PATCH", payload);
    }
    else if (method == "DELETE") {
        m_networkAcessManager->sendCustomRequest(request, "DELETE", payload);
    }
}
void MainWindow::slotReceiveResponse(QNetworkReply *networkReply)
{
    QStringList displayStream;

    QVariant statusCode = networkReply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute);

    displayStream << "URL: " << networkReply->url().toString();
    displayStream << "\n";

    displayStream << "STATUS: " << statusCode.toString();
    displayStream << "\n";

    displayStream << "DATA:";
    displayStream << "\n";

    if (networkReply->error() == QNetworkReply::NoError) {
        if (networkReply->isReadable()) {
            QByteArray bytes = networkReply->readAll();
            displayStream << QString::fromStdString(bytes.toStdString());
        }
    }
    else {
        QByteArray bytes = networkReply->readAll();
        displayStream << QString::fromStdString(bytes.toStdString());
    }

    QString displayText = displayStream.join("");
    m_panelResponse->setDisplayText(displayText);

    networkReply->deleteLater();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}


















