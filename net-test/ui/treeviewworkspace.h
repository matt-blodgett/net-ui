#pragma once

#ifndef TREEVIEWWORKSPACE_H
#define TREEVIEWWORKSPACE_H


#include <QTreeView>


class TreeViewWorkspace : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeViewWorkspace(QWidget *parent = nullptr);
};


#endif
