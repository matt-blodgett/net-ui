#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


QT_BEGIN_NAMESPACE
class QSplitter;
class QNetworkAccessManager;
class QNetworkReply;
QT_END_NAMESPACE


class PanelRequest;
class PanelResponse;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initialize();
    void initializeObjects();
    void initializeLayout();
    void initializeMenubar();

private:
    QSplitter *m_frameSplitter = nullptr;
    PanelRequest *m_panelRequest = nullptr;
    PanelResponse *m_panelResponse = nullptr;

private:
    QNetworkAccessManager *m_networkAcessManager = nullptr;

private slots:
    void slotSendRequest();
    void slotHandleResponse(QNetworkReply *networkReply);


    void test();
};


#endif
