#include "workspace.h"

#include <QRandomGenerator>


#include <QDebug>


static QString pidGenerate(WorkspaceType wsType)
{
    QString pid;

    if(wsType == WS_Request) {
        pid = "R:";
    }
    else if (wsType == WS_Folder) {
        pid = "F:";
    }
    else if (wsType == WS_Workspace) {
        pid = "W:";
    }

    const QString pidCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    while(pid.size() < 8) {
        pid += pidCharacters[QRandomGenerator().global()->bounded(0, pidCharacters.length())];
    }

    return pid;
}


WorkspaceObject::WorkspaceObject(QObject *parent) : QObject(parent)
{

}
WorkspaceType WorkspaceObject::type() const
{
    return WS_BaseObject;
}

QString WorkspaceObject::pid() const
{
    return m_pid;
}
void WorkspaceObject::setPid(const QString &pid)
{
    m_pid = pid;
}

QString WorkspaceObject::name() const
{
    return m_name;
}
void WorkspaceObject::setName(const QString &name)
{
    m_name = name;
}


WorkspaceContainer::WorkspaceContainer(Workspace *parent) : WorkspaceObject(parent)
{
    m_parentWorkspace = parent;
}
WorkspaceType WorkspaceContainer::type() const
{
    return WS_Container;
}

Workspace *WorkspaceContainer::parentWorkspace() const
{
    return m_parentWorkspace;
}
WorkspaceFolder *WorkspaceContainer::parentFolder() const
{
    return m_parentFolder;
}


WorkspaceRequest::WorkspaceRequest(Workspace *parent) : WorkspaceContainer(parent)
{

}
WorkspaceType WorkspaceRequest::type() const
{
    return WS_Request;
}


WorkspaceFolder::WorkspaceFolder(Workspace *parent) : WorkspaceContainer(parent)
{

}
WorkspaceType WorkspaceFolder::type() const
{
    return WS_Folder;
}

QVector<WorkspaceFolder*> WorkspaceFolder::childFolders() const
{
    QVector<WorkspaceFolder*> children;
    for(const QString &pid : pidFolders) {
        children.append(parentWorkspace()->getFolder(pid));
    }
    return children;
}
QVector<WorkspaceRequest*> WorkspaceFolder::childRequests() const
{
    QVector<WorkspaceRequest*> children;
    for(const QString &pid : pidRequests) {
        children.append(parentWorkspace()->getRequest(pid));
    }
    return children;
}


Workspace::Workspace(QObject *parent) : WorkspaceObject(parent)
{
    setPid(pidGenerate(WS_Workspace));
    setName("New Workspace");
}
WorkspaceType Workspace::type() const
{
    return WS_Workspace;
}

bool Workspace::load(const QString &path)
{
    m_path = path;

    return true;
}
bool Workspace::create(const QString &path)
{
    m_path = path;

    return true;
}
void Workspace::reset()
{

}

QString Workspace::path() const
{
    return m_path;
}

QVector<WorkspaceFolder*> Workspace::folders() const
{
    return m_folders;
}
QVector<WorkspaceRequest*> Workspace::requests() const
{
    return m_requests;
}

WorkspaceFolder *Workspace::getFolder(const QString &pid) const
{
    for(WorkspaceFolder *folder : m_folders) {
        if (folder->pid() == pid) {
            return folder;
        }
    }
    return nullptr;
}
WorkspaceRequest *Workspace::getRequest(const QString &pid) const
{
    for(WorkspaceRequest *request : m_requests) {
        if (request->pid() == pid) {
            return request;
        }
    }
    return nullptr;
}

WorkspaceFolder *Workspace::createFolder(WorkspaceFolder *parentFolder)
{
    Q_UNUSED(parentFolder)

    WorkspaceFolder *folder = new WorkspaceFolder(this);
    folder->setPid(pidGenerate(folder->type()));

    QString name = "New Folder";
    QString append = "";
    int duplicates = 1;

    int i = 0;
    while(i < m_folders.size()) {
        WorkspaceFolder *f = m_folders.at(i++);
        if(f->name() == name + append) {
            append = " " + QString::number(duplicates++);
            i = 0;
        }
    }

    folder->setName(name + append);

    m_folders.append(folder);

    emit folderCreated(folder);

    return folder;
}
WorkspaceRequest *Workspace::createRequest(WorkspaceFolder *parentFolder)
{
    Q_UNUSED(parentFolder)

    WorkspaceRequest *request = new WorkspaceRequest(this);
    request->setPid(pidGenerate(request->type()));

    QString name = "New Request";
    QString append = "";
    int duplicates = 1;

    int i = 0;
    while(i < m_requests.size()) {
        WorkspaceRequest *r = m_requests.at(i++);
        if(r->name() == name + append) {
            append = " " + QString::number(duplicates++);
            i = 0;
        }
    }

    request->setName(name + append);

    m_requests.append(request);

    emit requestCreated(request);

    return request;
}

void Workspace::remove(WorkspaceFolder *folder)
{
    for(WorkspaceFolder *f : m_folders) {
        f->pidFolders.removeAll(folder->pid());
    }

    m_folders.removeAll(folder);

    emit folderRemoved(folder);
}
void Workspace::remove(WorkspaceRequest *request)
{
    for(WorkspaceFolder *f : m_folders) {
        f->pidRequests.removeAll(request->pid());
    }

    m_requests.removeAll(request);

    emit requestRemoved(request);
}
