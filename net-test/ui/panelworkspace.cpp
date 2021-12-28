#include "panelworkspace.h"

#include "treeviewworkspace.h"
#include "modelworkspace.h"

#include <QGridLayout>
#include <QMenu>


PanelWorkspace::PanelWorkspace(QWidget *parent) : QWidget(parent)
{
    m_treeviewWorkspace = new TreeViewWorkspace(this);
    m_modelWorkspace = new ModelWorkspace(this);
    m_treeviewWorkspace->setModel(m_modelWorkspace);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_treeviewWorkspace, 0, 0, 1, 1);
    gridMain->setColumnStretch(0, 1);
    gridMain->setRowStretch(0, 1);
    setLayout(gridMain);

    connect(m_treeviewWorkspace, &QTreeView::customContextMenuRequested, this, &PanelWorkspace::contextMenuTreeview);
}

void PanelWorkspace::setWorkspace(Workspace *workspace)
{
    m_workspace = workspace;
    m_modelWorkspace->setWorkspace(workspace);
}

void PanelWorkspace::newFolder()
{
    m_workspace->addFolder();
}
void PanelWorkspace::newRequest()
{
    m_workspace->addRequest();
}
void PanelWorkspace::editItem()
{

}
void PanelWorkspace::deleteItems()
{

}

void PanelWorkspace::contextMenuTreeview(const QPoint &point)
{
    QMenu *menuContext = new QMenu(this);

    QAction *actExpandItem = new QAction(menuContext);
    QAction *actCollapseItem = new QAction(menuContext);
    QAction *actExpandAll = new QAction(menuContext);
    QAction *actCollapseAll = new QAction(menuContext);
    QAction *actNewFolder = new QAction(menuContext);
    QAction *actNewRequest = new QAction(menuContext);
    QAction *actEditItem = new QAction(menuContext);
    QAction *actDeleteItems = new QAction(menuContext);

    actExpandItem->setText("Expand");
    actCollapseItem->setText("Collapse");
    actExpandAll->setText("Expand All");
    actCollapseAll->setText("Collapse All");
    actNewFolder->setText("New Folder");
    actNewRequest->setText("New Request");
    actEditItem->setText("Edit");
    actDeleteItems->setText("Delete");

    menuContext->addAction(actExpandItem);
    menuContext->addAction(actCollapseItem);
    menuContext->addSeparator();
    menuContext->addAction(actExpandAll);
    menuContext->addAction(actCollapseAll);
    menuContext->addSeparator();
    menuContext->addAction(actNewFolder);
    menuContext->addAction(actNewRequest);
    menuContext->addSeparator();
    menuContext->addAction(actEditItem);
    menuContext->addSeparator();
    menuContext->addAction(actDeleteItems);

    QModelIndex idxAt = m_treeviewWorkspace->indexAt(point);

    m_treeviewWorkspace->selectionModel()->setCurrentIndex(idxAt, QItemSelectionModel::ClearAndSelect);

    if(m_modelWorkspace->itemIsRequest(idxAt)) {
        actExpandItem->setDisabled(true);
        actCollapseItem->setDisabled(true);
    }
    else if(m_modelWorkspace->itemIsFolder(idxAt)) {

    }
    else {
        actExpandItem->setDisabled(true);
        actCollapseItem->setDisabled(true);
        actEditItem->setDisabled(true);
        actDeleteItems->setDisabled(true);
    }

    connect(actExpandItem, &QAction::triggered, this, [this](){m_treeviewWorkspace->expand(m_treeviewWorkspace->currentIndex());});
    connect(actCollapseItem, &QAction::triggered, this, [this](){m_treeviewWorkspace->collapse(m_treeviewWorkspace->currentIndex());});
    connect(actExpandAll, &QAction::triggered, this, [this](){m_treeviewWorkspace->expandAll();});
    connect(actCollapseAll, &QAction::triggered, this, [this](){m_treeviewWorkspace->collapseAll();});

    connect(actNewFolder, &QAction::triggered, this, &PanelWorkspace::newFolder);
    connect(actNewRequest, &QAction::triggered, this, &PanelWorkspace::newRequest);

    connect(actEditItem, &QAction::triggered, this, &PanelWorkspace::editItem);

    connect(actDeleteItems, &QAction::triggered, this, &PanelWorkspace::deleteItems);

    menuContext->exec(m_treeviewWorkspace->mapToGlobal(point));
    delete menuContext;
}
