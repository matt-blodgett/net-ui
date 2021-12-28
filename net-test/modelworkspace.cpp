#include "modelworkspace.h"
#include "modelworkspaceitem.h"

#include <QMimeData>
#include <QUrl>


#include <QDebug>


static void populateItem(ModelWorkspaceItem *item, WorkspaceContainer *container)
{
    item->setPid(container->pid());
    item->setLabel(container->name());

    if(container->type() == WS_Folder) {
        item->setType(ModelWorkspaceItem::FolderItem);
    }
    else if(container->type() == WS_Request) {
        item->setType(ModelWorkspaceItem::RequestItem);
    }
}
//static MFolderList allChildFolders(MFolder *parentFolder)
//{
//    MFolderList folders;
//    for(MFolder *childFolder : parentFolder->childFolders()) {
//        folders.append(childFolder);
//        for(MFolder *f : allChildFolders(childFolder)) {
//            folders.append(f);
//        }
//    }

//    return folders;
//}


ModelWorkspace::ModelWorkspace(QObject *parent) : QAbstractItemModel(parent)
{
    m_rootItem = new ModelWorkspaceItem();
    m_rootItem->setLabel("Requests");
}
ModelWorkspace::~ModelWorkspace()
{
    delete m_rootItem;
}

Qt::ItemFlags ModelWorkspace::flags(const QModelIndex &index) const
{
    Qt::ItemFlags idxFlags;

    if (index.isValid()) {
        idxFlags |= Qt::ItemIsEnabled;
        idxFlags |= Qt::ItemIsSelectable;
    }

//    if(index.isValid()) {
//        idxFlags |= Qt::ItemIsDropEnabled;
//        idxFlags |= Qt::ItemIsEnabled;
//        idxFlags |= Qt::ItemIsEditable;
//        idxFlags |= Qt::ItemIsSelectable;
//        idxFlags |= Qt::ItemIsDragEnabled;
//    }

    return idxFlags;
}
Qt::DropActions ModelWorkspace::supportedDragActions() const
{
//    return Qt::MoveAction;
    return Qt::IgnoreAction;
}
Qt::DropActions ModelWorkspace::supportedDropActions() const
{
//    return Qt::CopyAction | Qt::MoveAction;
    return Qt::IgnoreAction;
}

QStringList ModelWorkspace::mimeTypes() const
{
    QStringList mTypes;
//    mTypes << MPI3_MIME_TYPE_PIDS_CONTAINERS;
    return mTypes;
}
QMimeData *ModelWorkspace::mimeData(const QModelIndexList &indexes) const
{
    Q_UNUSED(indexes)

    QMimeData *mData = new QMimeData();

//    if(indexes.size() == 1) {
//        QByteArray pidBytes;
//        pidBytes.append(pidAt(indexes.at(0)).toStdString().c_str());
//        mData->setData(MPI3_MIME_TYPE_PIDS_CONTAINERS, pidBytes);
//    }

    return mData;
}

bool ModelWorkspace::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(data)
    Q_UNUSED(action)
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)
//    bool dataIsSonglist = data->hasFormat(MPI3_MIME_TYPE_PIDS_SONGS);
//    bool dataIsContainer = data->hasFormat(MPI3_MIME_TYPE_PIDS_CONTAINERS);
//    bool dataIsValidMediaFiles = data->hasUrls() ? Mpi3::Core::validMediaFiles(data->urls()) : false;
//    bool actionIsCopyAction = action == Qt::CopyAction;
//    bool actionIsMoveAction = action == Qt::MoveAction;

//    QModelIndex targetIndex = index(row, column, parent);
//    MContainer *targetContainer = m_mediaLibrary->getContainer(pidAt(targetIndex));

//    if(!targetContainer) {
//        return dataIsContainer || dataIsValidMediaFiles;
//    }
//    else if(targetContainer->type() == Mpi3::PlaylistElement) {
//        return actionIsCopyAction && (dataIsSonglist || dataIsValidMediaFiles);
//    }
//    else if(targetContainer->type() == Mpi3::FolderElement) {

//        if(actionIsMoveAction && dataIsContainer) {
//            QString pid = data->data(MPI3_MIME_TYPE_PIDS_CONTAINERS);

//            MFolder *dropFolder = m_mediaLibrary->getFolder(pid);
//            MPlaylist *dropPlaylist = m_mediaLibrary->getPlaylist(pid);

//            MFolder *targetFolder = static_cast<MFolder*>(targetContainer);
//            MPlaylist *targetPlaylist = static_cast<MPlaylist*>(targetContainer);

//            if(dropFolder && !targetFolder) {
//                return dropFolder->parentFolder() || !targetPlaylist;
//            }
//            else if(dropPlaylist && !targetFolder) {
//                return dropPlaylist->parentFolder() || !targetPlaylist;
//            }
//            else if(dropFolder && targetFolder) {
//                return dropFolder != targetFolder && !allChildFolders(dropFolder).contains(targetFolder);
//            }
//            else if(dropPlaylist && targetFolder) {
//                return dropPlaylist->parentFolder() != targetFolder;
//            }
//        }
//    }

    return false;
}
bool ModelWorkspace::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(data)
    Q_UNUSED(action)
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)
//    bool dataIsSonglist = data->hasFormat(MPI3_MIME_TYPE_PIDS_SONGS);
//    bool dataIsContainer = data->hasFormat(MPI3_MIME_TYPE_PIDS_CONTAINERS);
//    bool dataIsValidMediaFiles = data->hasUrls() ? Mpi3::Core::validMediaFiles(data->urls()) : false;
//    bool actionIsCopyAction = action == Qt::CopyAction;
//    bool actionIsMoveAction = action == Qt::MoveAction;

//    QModelIndex targetIndex = index(row, column, parent);
//    MContainer *targetContainer = m_mediaLibrary->getContainer(pidAt(targetIndex));

//    if(!targetContainer) {
//        if(actionIsMoveAction && dataIsContainer) {
//            QString pid = data->data(MPI3_MIME_TYPE_PIDS_CONTAINERS);
//            MContainer *dropContainer = m_mediaLibrary->getContainer(pid);

//            if(dropContainer && dropContainer->parentFolder()) {
//                m_mediaLibrary->edit(dropContainer, "parentFolder", QVariant());
//                return true;
//            }
//        }
//        else if(actionIsCopyAction && dataIsValidMediaFiles) {
//            for(const QUrl &url : data->urls()) {
//                MSongInfo songInfo;
//                if (songInfo.load(url.toString())) {
//                    m_mediaLibrary->newSong(songInfo.songInfoMap());
//                }
//            }
//            return true;
//        }
//    }
//    else if(targetContainer->type() == Mpi3::PlaylistElement) {
//        MPlaylist *targetPlaylist = static_cast<MPlaylist*>(targetContainer);

//        if(actionIsCopyAction && dataIsSonglist) {
//            QByteArray pidBytes = data->data(MPI3_MIME_TYPE_PIDS_SONGS);
//            QStringList pidStrings = Mpi3::Core::bytesToSongs(pidBytes);
//            QStringList pidStringsCombined = targetPlaylist->songsPidList();
//            pidStringsCombined.append(pidStrings);
//            m_mediaLibrary->edit(targetPlaylist, "songs", pidStringsCombined);
//            return true;
//        }
//        else if(actionIsCopyAction && dataIsValidMediaFiles) {
//            QStringList pidStrings;
//            for(const QUrl &url : data->urls()) {
//                MSongInfo songInfo;
//                if (songInfo.load(url.toString())) {
//                    MSong *song = m_mediaLibrary->newSong(songInfo.songInfoMap());
//                    pidStrings << song->pid();
//                }
//            }
//            QStringList pidStringsCombined = targetPlaylist->songsPidList();
//            pidStringsCombined.append(pidStrings);
//            m_mediaLibrary->edit(targetPlaylist, "songs", pidStringsCombined);
//            return true;
//        }
//    }
//    else if(targetContainer->type() == Mpi3::FolderElement) {
//        MFolder *targetFolder = static_cast<MFolder*>(targetContainer);

//        if(actionIsMoveAction && dataIsContainer) {
//            QString pid = data->data(MPI3_MIME_TYPE_PIDS_CONTAINERS);
//            MContainer *dropContainer = m_mediaLibrary->getContainer(pid);

//            if(dropContainer) {
//                m_mediaLibrary->edit(dropContainer, "parentFolder", targetFolder->pid());
//                return true;
//            }
//        }
//    }

    return false;
}

QModelIndex ModelWorkspace::index(int row, int column, const QModelIndex &parent) const
{
    ModelWorkspaceItem *parentItem = getItem(parent);
    ModelWorkspaceItem *childItem = parentItem->child(row);

    if(childItem) {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}
QModelIndex ModelWorkspace::parent(const QModelIndex &index) const
{
    if(index.isValid()) {
        ModelWorkspaceItem *childItem = getItem(index);
        ModelWorkspaceItem *parentItem = childItem->parent();

        if(parentItem != m_rootItem) {
            return createIndex(parentItem->childNumber(), 0, parentItem);
        }
    }

    return QModelIndex();
}

int ModelWorkspace::rowCount(const QModelIndex &parent) const
{
    ModelWorkspaceItem *parentItem = getItem(parent);
    return parentItem->childCount();
}
int ModelWorkspace::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant ModelWorkspace::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.column() == 0) {
        if(role == Qt::DecorationRole) {
            ModelWorkspaceItem *item = getItem(index);
            if(item->type() == ModelWorkspaceItem::FolderItem) {
                return iconFolder;
            }
            else if(item->type() == ModelWorkspaceItem::RequestItem) {
                return iconRequest;
            }
        }
        else if(role == Qt::DisplayRole || role == Qt::EditRole) {
            ModelWorkspaceItem *item = getItem(index);
            return item->label();
        }
    }

    return QVariant();
}
bool ModelWorkspace::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)
//    if(role == Qt::EditRole) {
//        MModelItem *item = getItem(index);
//        MContainer *container = m_mediaLibrary->getContainer(item->pid());
//        m_mediaLibrary->edit(container, "name", value);
//        return true;
//    }

    return false;
}

QVariant ModelWorkspace::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0) {
        return m_rootItem->label();
    }

    return QVariant();
}

QList<ModelWorkspaceItem*> ModelWorkspace::allItems(ModelWorkspaceItem *parentItem) const
{
    if(!parentItem) {
        parentItem = m_rootItem;
    }

    QList<ModelWorkspaceItem*> childItems;
    for(int i = 0; i < parentItem->childCount(); i++) {
        ModelWorkspaceItem *childItem = parentItem->child(i);
        childItems.append(childItem);

        for(ModelWorkspaceItem *c : allItems(childItem)) {
            childItems.append(c);
        }
    }

    return childItems;
}
ModelWorkspaceItem *ModelWorkspace::getItem(const QModelIndex &index) const
{
    if(index.isValid()) {
        ModelWorkspaceItem *item = static_cast<ModelWorkspaceItem*>(index.internalPointer());
        if(item) {
            return item;
        }
    }

    return m_rootItem;
}
ModelWorkspaceItem *ModelWorkspace::getItem(const QString &pid) const
{
    for(ModelWorkspaceItem *item : allItems()) {
        if(item->pid() == pid) {
            return item;
        }
    }

    return m_rootItem;
}
QModelIndex ModelWorkspace::getIndex(const QString &pid) const
{
    for(QModelIndex idx : persistentIndexList()) {
        if(getItem(idx)->pid() == pid) {
            return idx;
        }
    }

    return QModelIndex();
}

QString ModelWorkspace::pidAt(const QModelIndex &index) const
{
    return getItem(index)->pid();
}
bool ModelWorkspace::itemIsFolder(const QModelIndex &index) const
{
    return getItem(index)->type() == ModelWorkspaceItem::FolderItem;
}
bool ModelWorkspace::itemIsRequest(const QModelIndex &index) const
{
    return getItem(index)->type() == ModelWorkspaceItem::RequestItem;
}

void ModelWorkspace::setWorkspace(Workspace *workspace)
{
    beginResetModel();

    m_rootItem->removeChildren(0, rowCount());

    if(m_workspace) {
        disconnect(m_workspace, nullptr, this, nullptr);
    }

    m_workspace = workspace;
//    connect(m_mediaLibrary, &Workspace::libraryReset, this, [this](){beginResetModel(); m_rootItem->removeChildren(0, rowCount()); endResetModel();});
    connect(m_workspace, &Workspace::folderCreated, this, &ModelWorkspace::folderCreated);
    connect(m_workspace, &Workspace::requestCreated, this, &ModelWorkspace::requestCreated);
    connect(m_workspace, &Workspace::folderRemoved, this, &ModelWorkspace::folderRemoved);
    connect(m_workspace, &Workspace::requestRemoved, this, &ModelWorkspace::requestRemoved);
    connect(m_workspace, &Workspace::folderChanged, this, &ModelWorkspace::folderChanged);
    connect(m_workspace, &Workspace::requestChanged, this, &ModelWorkspace::requestChanged);
//    connect(m_workspace, &MMediaLibrary::parentFolderChanged, this, &ModelWorkspace::parentFolderChanged);

    QVector<WorkspaceFolder*> parentFolders;
    QVector<WorkspaceFolder*> childFolders;

    for(WorkspaceFolder *folder : m_workspace->folders()) {
        if(folder->parentFolder()) {
            childFolders.append(folder);
        }
        else {
            parentFolders.append(folder);
        }
    }

    for(WorkspaceFolder *folder : parentFolders) {
        int position = m_rootItem->childCount();
        m_rootItem->insertChildren(position, 1);
        populateItem(m_rootItem->child(position), folder);
    }

    while(allItems().size() != m_workspace->folders().size()) {
        for(WorkspaceFolder *folder : childFolders) {
            ModelWorkspaceItem *item = getItem(folder->parentFolder()->pid());

            if(item != m_rootItem) {
                int position = item->childCount();
                item->insertChildren(position, 1);
                populateItem(item->child(position), folder);
            }
        }
    }

    for(WorkspaceRequest *request : m_workspace->requests()) {
        ModelWorkspaceItem *item = m_rootItem;

        if(request->parentFolder()) {
            item = getItem(request->parentFolder()->pid());
        }

        int position = item->childCount();
        item->insertChildren(position, 1);
        populateItem(item->child(position), request);
    }

    endResetModel();
}

void ModelWorkspace::containerCreated(WorkspaceContainer *container)
{
    ModelWorkspaceItem *parentItem = m_rootItem;
    QModelIndex parentIndex = QModelIndex();

    if(container->parentFolder()) {
        parentItem = getItem(container->parentFolder()->pid());
        parentIndex = getIndex(container->parentFolder()->pid());
    }

    int row = parentItem->childCount();
    if(container->type() == WS_Folder) {
        for(int i = 0; i < parentItem->childCount(); i++) {
            if(parentItem->child(i)->type() == ModelWorkspaceItem::RequestItem) {
                row = i;
                break;
            }
        }
    }

    beginInsertRows(parentIndex, row, row);
    parentItem->insertChildren(row, 1);
    populateItem(parentItem->child(row), container);
    endInsertRows();
}
void ModelWorkspace::containerDeleted(WorkspaceContainer *container)
{
    ModelWorkspaceItem *childItem = getItem(container->pid());

    if(childItem != m_rootItem) {
        QModelIndex idx = getIndex(container->pid());
        beginRemoveRows(idx.parent(), idx.row(), idx.row());
        childItem->parent()->removeChildren(childItem->childNumber(), 1);
        endRemoveRows();
    }
}
void ModelWorkspace::containerChanged(WorkspaceContainer *container)
{
    ModelWorkspaceItem *childItem = getItem(container->pid());

    if(childItem != m_rootItem) {
        QModelIndex idx = getIndex(container->pid());
        childItem->setLabel(container->name());

        QVector<int> roles = {Qt::DisplayRole};
        emit dataChanged(idx, idx, roles);
    }
}

void ModelWorkspace::folderCreated(WorkspaceFolder *folder)
{
    containerCreated(folder);
}
void ModelWorkspace::requestCreated(WorkspaceRequest *request)
{
    containerCreated(request);
}
void ModelWorkspace::folderRemoved(WorkspaceFolder *folder)
{
    containerDeleted(folder);
}
void ModelWorkspace::requestRemoved(WorkspaceRequest *request)
{
    containerDeleted(request);
}
void ModelWorkspace::folderChanged(WorkspaceFolder *folder)
{
    containerChanged(folder);
}
void ModelWorkspace::requestChanged(WorkspaceRequest *request)
{
    containerChanged(request);
}
//void ModelWorkspace::parentFolderChanged(MContainer *container)
//{
//    QModelIndex sourceIdx = getIndex(container->pid());
//    QModelIndex parentIdx = container->parentFolder() ? getIndex(container->parentFolder()->pid()) : QModelIndex();

//    MModelItem *sourceItem = getItem(sourceIdx);
//    MModelItem *parentItem = getItem(parentIdx);

//    int row = parentItem->childCount();
//    if(container->type() == Mpi3::FolderElement) {
//        for(int i = 0; i < parentItem->childCount(); i++) {
//            if(parentItem->child(i)->type() == MModelItem::PlaylistItem) {
//                row = i;
//                break;
//            }
//        }
//    }

//    beginMoveRows(sourceIdx, sourceIdx.row(), sourceIdx.row(), parentIdx, row);
//    sourceItem->move(parentItem, row);
//    endMoveRows();
//}
