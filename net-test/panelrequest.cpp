#include "panelrequest.h"


#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>


#include <QLabel>
#include <QTextEdit>


#include <QDebug>


TabKeyValues::TabKeyValues(QWidget *parent) : QWidget(parent)
{
    QLabel *lblKey = new QLabel(this);
    QLabel *lblValue = new QLabel(this);
    m_lblTitle = new QLabel(this);
    m_btnAddLine = new QPushButton(this);

    m_lblTitle->setText("Request Headers");
    lblKey->setText("Key");
    lblValue->setText("Value");
    m_btnAddLine->setText("ADD");

    connect(m_btnAddLine, &QPushButton::pressed, this, &TabKeyValues::lineAdd);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_lblTitle, 0, 0, 1, 3);
    gridMain->addWidget(lblKey, 1, 0, 1, 1);
    gridMain->addWidget(lblValue, 1, 1, 1, 1);
    gridMain->addWidget(m_btnAddLine, 2, 2, 1, 1);
    gridMain->setColumnStretch(0, 1);
    gridMain->setColumnStretch(1, 1);
    gridMain->setRowStretch(3, 1);
    setLayout(gridMain);

    lineAdd();
}

void TabKeyValues::setTitle(const QString &title)
{
    m_lblTitle->setText(title);
}
QHash<QString, QString> TabKeyValues::keyValueMap() const
{
    QHash<QString, QString> kvm;
    return kvm;
}

void TabKeyValues::lineAdd()
{
    Line *line = new Line();
    line->key = new QLineEdit(this);
    line->value = new QLineEdit(this);
    line->edit = new QPushButton(this);
    line->edit->setText("-");
    m_lines.append(line);

    connect(line->edit, &QPushButton::pressed, this, [=](){lineRemove(m_lines.indexOf(line));});

    QGridLayout *gridMain = static_cast<QGridLayout*>(layout());
    gridMain->removeWidget(m_btnAddLine);
    int gridRow = gridMain->rowCount() - 1;
    gridMain->addWidget(line->key, gridRow, 0, 1, 1);
    gridMain->addWidget(line->value, gridRow, 1, 1, 1);
    gridMain->addWidget(line->edit, gridRow, 2, 1, 1);
    gridMain->addWidget(m_btnAddLine, gridRow + 1, 2, 1, 1);

    for (int i = 0; i < gridMain->rowCount(); i++) {
        gridMain->setRowStretch(i, 0);
    }
    gridMain->setRowStretch(gridMain->rowCount(), 1);
}
void TabKeyValues::lineRemove(const int &index)
{
    if (index < 0 || index >= m_lines.length()) {
        return;
    }

    QGridLayout *gridMain = static_cast<QGridLayout*>(layout());
    Line *line = m_lines.takeAt(index);
    gridMain->removeWidget(line->key);
    gridMain->removeWidget(line->value);
    gridMain->removeWidget(line->edit);
    delete line->key;
    delete line->value;
    delete line->edit;
    delete line;

    for (int i = 0; i < gridMain->rowCount(); i++) {
        gridMain->setRowStretch(i, 0);
    }
    gridMain->setRowStretch(gridMain->rowCount(), 1);
}


TabHeaders::TabHeaders(QWidget *parent) : TabKeyValues(parent)
{
    setTitle("Request Headers");
}


TabQuery::TabQuery(QWidget *parent) : TabKeyValues(parent)
{
    setTitle("Query Parameters");
}


TabBody::TabBody(QWidget *parent) : QWidget(parent)
{
    QLabel *lblTitle = new QLabel(this);

    lblTitle->setText("Request Payload");

    QTextEdit *boxData = new QTextEdit(this);
//    boxData->setBaseSize(10, 10);
//    boxData->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
//    boxData->setMaximumHeight(20);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(lblTitle, 0, 0, 1, 1);
    gridMain->addWidget(boxData, 1, 0, 1, 1);

    gridMain->setRowStretch(1, 0);
    setLayout(gridMain);
}


PanelRequest::PanelRequest(QWidget *parent) : QWidget(parent)
{
    m_cbxMethod = new QComboBox(this);
    m_boxUrl = new QLineEdit(this);
    m_btnSend = new QPushButton(this);

    m_tabHeaders = new TabHeaders();
    m_tabQuery = new TabQuery();
    m_tabBody = new TabBody();
    m_tabWidget = new QTabWidget(this);

    m_tabWidget->addTab(m_tabHeaders, "Headers");
    m_tabWidget->addTab(m_tabQuery, "Query");
    m_tabWidget->addTab(m_tabBody, "Body");

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_cbxMethod, 0, 0, 1, 1);
    gridMain->addWidget(m_boxUrl, 0, 1, 1, 1);
    gridMain->addWidget(m_btnSend, 0, 2, 1, 1);
    gridMain->addWidget(m_tabWidget, 1, 0, 1, 3);
    gridMain->setColumnStretch(1, 1);
    gridMain->setContentsMargins(0, 0, 0, 0);
    gridMain->setHorizontalSpacing(2);
    gridMain->setVerticalSpacing(10);
    setLayout(gridMain);

    m_btnSend->setText("SEND");

    m_cbxMethod->addItems(PanelRequest::methodOptions());

    connect(m_btnSend, &QPushButton::pressed, this, &PanelRequest::signalSendRequest);
}

QStringList PanelRequest::methodOptions()
{
    QStringList methods = {"GET", "POST", "PUT", "PATCH", "DELETE"};
    return methods;
}

QString PanelRequest::method() const
{
    return m_cbxMethod->currentText();
}
QString PanelRequest::url() const
{
    return m_boxUrl->text();
}
QHash<QString, QString> PanelRequest::headers() const
{
    return m_tabHeaders->keyValueMap();
}
QHash<QString, QString> PanelRequest::queryParameters() const
{
    return m_tabQuery->keyValueMap();
}
QString PanelRequest::queryString() const
{
    return "";
}
QByteArray PanelRequest::data() const
{
    return QByteArray();
}

void PanelRequest::setMethod(const QString &method)
{
    m_cbxMethod->setCurrentText(method);
}
void PanelRequest::setUrl(const QString &url)
{
    m_boxUrl->setText(url);
}
