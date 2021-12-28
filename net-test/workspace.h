#pragma once

#ifndef WORKSPACE_H
#define WORKSPACE_H


#include <QObject>


enum WorkspaceType {
    WS_Object,
    WS_Container,
    WS_Request,
    WS_Folder,
    WS_Workspace
};


class WorkspaceObject;
class WorkspaceContainer;
class WorkspaceRequest;
class WorkspaceFolder;
class Workspace;


//typedef QVector<WorkspaceContainer*> WSContainerList;
//typedef QVector<WorkspaceRequest*> WSRequestList;
//typedef QVector<WorkspaceFolder*> WSFolderList;


class WorkspaceObject : public QObject
{
    Q_OBJECT

public:
    explicit WorkspaceObject(QObject *parent = nullptr);
    virtual WorkspaceType type() const;

public:
    QString pid() const;
    void setPid(const QString &pid);

    QString name() const;
    void setName(const QString &name);

private:
    QString m_pid;
    QString m_name;
};


class WorkspaceContainer : public WorkspaceObject
{
    Q_OBJECT

public:
    explicit WorkspaceContainer(Workspace *parent = nullptr);
    WorkspaceType type() const override;

public:
    Workspace *parentWorkspace() const;
    WorkspaceFolder *parentFolder() const;

private:
    Workspace *m_parentWorkspace = nullptr;
    WorkspaceFolder *m_parentFolder = nullptr;
};


class WorkspaceRequest : public WorkspaceContainer
{
    Q_OBJECT

public:
    explicit WorkspaceRequest(Workspace *parent = nullptr);
    WorkspaceType type() const override;
};


class WorkspaceFolder : public WorkspaceContainer
{
    Q_OBJECT

public:
    explicit WorkspaceFolder(Workspace *parent = nullptr);
    WorkspaceType type() const override;

public:
    QVector<WorkspaceFolder*> childFolders() const;
    QVector<WorkspaceRequest*> childRequests() const;

public:
    // should not be public
    QStringList pidFolders;
    QStringList pidRequests;
};


class Workspace : public WorkspaceObject
{
    Q_OBJECT

public:
    explicit Workspace(QObject *parent = nullptr);
    WorkspaceType type() const override;

public:
    bool load(const QString &path);
    bool create(const QString &path);
    void reset();

public:
    QString path() const;

private:
    QString m_path;

public:
    QVector<WorkspaceFolder*> folders() const;
    QVector<WorkspaceRequest*> requests() const;

    WorkspaceFolder *getFolder(const QString &pid) const;
    WorkspaceRequest *getRequest(const QString &pid) const;

    WorkspaceFolder *addFolder(WorkspaceFolder *parentFolder = nullptr);
    WorkspaceRequest *addRequest(WorkspaceFolder *parentFolder = nullptr);

    void remove(WorkspaceFolder *folder);
    void remove(WorkspaceRequest *request);

private:
    QVector<WorkspaceFolder*> m_folders;
    QVector<WorkspaceRequest*> m_requests;

signals:
    void folderCreated(WorkspaceFolder *folder);
    void requestCreated(WorkspaceRequest *request);

    void folderRemoved(WorkspaceFolder *folder);
    void requestRemoved(WorkspaceRequest *request);

    void folderChanged(WorkspaceFolder *folder);
    void requestChanged(WorkspaceRequest *request);
};


#endif
