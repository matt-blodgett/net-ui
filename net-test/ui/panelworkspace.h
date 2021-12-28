#pragma once

#ifndef PANELWORKSPACE_H
#define PANELWORKSPACE_H


#include <QWidget>


class Workspace;
class TreeViewWorkspace;
class ModelWorkspace;


class PanelWorkspace : public QWidget
{
    Q_OBJECT

public:
    explicit PanelWorkspace(QWidget *parent = nullptr);

public:
    void setWorkspace(Workspace *workspace);

    void newFolder();
    void newRequest();
    void editItem();
    void deleteItems();


private:
    Workspace *m_workspace = nullptr;

    TreeViewWorkspace *m_treeviewWorkspace = nullptr;
    ModelWorkspace *m_modelWorkspace = nullptr;

private slots:
    void contextMenuTreeview(const QPoint &point);

signals:

};

#endif
