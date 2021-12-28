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


struct KeyValueLine {
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
    void addLine(const QString &key = QString(), const QString &value = QString());
    void removeLine(const int &index);
    QHash<QString, QString> keyValueMap() const;

    void reset();

private:
    QLabel *m_lblTitle = nullptr;
    QPushButton *m_btnAddLine = nullptr;
    QVector<KeyValueLine*> m_keyValueLines;
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
    void setData(const QString &data);

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
    QString data() const;
    QHash<QString, QString> headers() const;
    QHash<QString, QString> query() const;

    void setMethod(const QString &method);
    void setUrl(const QString &url);
    void setData(const QString &data);
    void addHeader(const QString &key, const QString &value);
    void addQuery(const QString &key, const QString &value);
    void reset();

private:
    QComboBox *m_cbxMethod = nullptr;
    QLineEdit *m_boxUrl = nullptr;
    QPushButton *m_btnSend = nullptr;
    TabBody *m_tabBody = nullptr;
    TabHeaders *m_tabHeaders = nullptr;
    TabQuery *m_tabQuery = nullptr;
    QTabWidget *m_tabWidget = nullptr;

signals:
    void signalSendRequest();
};


#endif
