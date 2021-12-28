#pragma once

#ifndef MODELWORKSPACE_H
#define MODELWORKSPACE_H


#include <QAbstractItemModel>
#include <QIcon>

QT_BEGIN_NAMESPACE
class QMimeData;
QT_END_NAMESPACE


#include "workspace.h"


class ModelWorkspaceItem;


class ModelWorkspace : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ModelWorkspace(QObject *parent = nullptr);
    ~ModelWorkspace() override;

public:
    QIcon iconFolder;
    QIcon iconRequest;

public:
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;

    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;

    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    QModelIndex index(int row, int column, const QModelIndex &index = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<ModelWorkspaceItem*> allItems(ModelWorkspaceItem *parentItem = nullptr) const;
    ModelWorkspaceItem *getItem(const QModelIndex &index) const;
    ModelWorkspaceItem *getItem(const QString &pid) const;
    QModelIndex getIndex(const QString &pid) const;

public:
    QString pidAt(const QModelIndex &index) const;
    bool itemIsFolder(const QModelIndex &index) const;
    bool itemIsRequest(const QModelIndex &index) const;

public:
    void setWorkspace(Workspace *workspace);

private:
    ModelWorkspaceItem *m_rootItem = nullptr;
    Workspace *m_workspace = nullptr;

private:
    void containerCreated(WorkspaceContainer *container);
    void containerDeleted(WorkspaceContainer *container);
    void containerChanged(WorkspaceContainer *container);

private slots:
    void folderCreated(WorkspaceFolder *folder);
    void requestCreated(WorkspaceRequest *request);
    void folderRemoved(WorkspaceFolder *folder);
    void requestRemoved(WorkspaceRequest *request);
    void folderChanged(WorkspaceFolder *folder);
    void requestChanged(WorkspaceRequest *request);
//    void parentFolderChanged(MContainer *container);
};


#endif
