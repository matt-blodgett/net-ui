#include "treeviewworkspace.h"

#include <QDropEvent>


#include <QDebug>


TreeViewWorkspace::TreeViewWorkspace(QWidget *parent) : QTreeView(parent)
{
    setAcceptDrops(false);
    setDragEnabled(false);
    viewport()->setAcceptDrops(false);
    setDragDropMode(QAbstractItemView::NoDragDrop);

    setExpandsOnDoubleClick(true);
    setFocusPolicy(Qt::NoFocus);
    setSelectionBehavior(QAbstractItemView::SelectRows);

//    setEditTriggers(QTreeView::SelectedClicked);
    setContextMenuPolicy(Qt::CustomContextMenu);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setAlternatingRowColors(false);
    setRootIsDecorated(true);
    setHeaderHidden(true);
    setSortingEnabled(false);
}
