#pragma once

#ifndef PANELRESPONSE_H
#define PANELRESPONSE_H


#include <QWidget>


QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE


class PanelResponse : public QWidget
{
    Q_OBJECT

public:
    explicit PanelResponse(QWidget *parent = nullptr);

public:
    void setDisplayText(const QString &text);

private:
    QTextEdit *m_boxDisplay = nullptr;
};

#endif
