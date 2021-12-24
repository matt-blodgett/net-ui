#pragma once

#ifndef PANELREQUEST_H
#define PANELREQUEST_H


#include <QWidget>
#include <QVector>
#include <QHash>


QT_BEGIN_NAMESPACE
class QComboBox;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QLabel;
class QTextEdit;
QT_END_NAMESPACE


struct Line {
    QLineEdit *key = nullptr;
    QLineEdit *value = nullptr;
    QPushButton *edit = nullptr;
};


class TabKeyValues : public QWidget
{
    Q_OBJECT

public:
    explicit TabKeyValues(QWidget *parent = nullptr);

public:
    void setTitle(const QString &title);
    QHash<QString, QString> keyValueMap() const;

private:
    void lineAdd();
    void lineRemove(const int &index);
    QVector<Line*> m_lines;
    QLabel *m_lblTitle = nullptr;
    QPushButton *m_btnAddLine = nullptr;
};


class TabHeaders : public TabKeyValues
{
    Q_OBJECT

public:
    explicit TabHeaders(QWidget *parent = nullptr);

};


class TabQuery : public TabKeyValues
{
    Q_OBJECT

public:
    explicit TabQuery(QWidget *parent = nullptr);
};


class TabBody : public QWidget
{
    Q_OBJECT

public:
    explicit TabBody(QWidget *parent = nullptr);

public:
    QString data() const;

private:
    QTextEdit *m_boxData = nullptr;
};


class PanelRequest : public QWidget
{
    Q_OBJECT

public:
    explicit PanelRequest(QWidget *parent = nullptr);

public:
    static QStringList methodOptions();

public:
    QString method() const;
    QString url() const;
    QHash<QString, QString> headers() const;
    QHash<QString, QString> queryParameters() const;
    QString queryString() const;
    QByteArray data() const;

    void setMethod(const QString &method);
    void setUrl(const QString &url);

private:
    QComboBox *m_cbxMethod = nullptr;
    QLineEdit *m_boxUrl = nullptr;
    QPushButton *m_btnSend = nullptr;

    TabHeaders *m_tabHeaders = nullptr;
    TabQuery *m_tabQuery = nullptr;
    TabBody *m_tabBody = nullptr;
    QTabWidget *m_tabWidget = nullptr;

signals:
    void signalSendRequest();
};


#endif
