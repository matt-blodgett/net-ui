#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QNetworkReply;
class QSplitter;
QT_END_NAMESPACE


#include "workspace.h"
class PanelWorkspace;
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
    QString pathAppData() const;
    QString pathSettings() const;

private:
    void loadSettings();
    void saveSettings();
    void reset();

private:
    PanelWorkspace *m_panelWorkspace = nullptr;
    QSplitter *m_frameSplitter = nullptr;
    PanelRequest *m_panelRequest = nullptr;
    PanelResponse *m_panelResponse = nullptr;

    QNetworkAccessManager *m_networkAcessManager = nullptr;

    Workspace *m_workspace = nullptr;

private slots:
    void slotSendRequest();
    void slotReceiveResponse(QNetworkReply *networkReply);

protected:
    void closeEvent(QCloseEvent *event);
};


#endif
