#pragma once

#ifndef MODELWORKSPACEITEM_H
#define MODELWORKSPACEITEM_H


#include <QList>


class ModelWorkspaceItem
{

public:
    enum ItemType {
        EmptyItem,
        RootItem,
        FolderItem,
        RequestItem
    };

public:
    explicit ModelWorkspaceItem(ModelWorkspaceItem *parent = nullptr);
    ~ModelWorkspaceItem();

public:
    ModelWorkspaceItem *parent();
    ModelWorkspaceItem *child(int row);

    ModelWorkspaceItem::ItemType type() const;
    void setType(ModelWorkspaceItem::ItemType value);

    QString pid() const;
    void setPid(const QString &value);

    QString label() const;
    void setLabel(const QString &value);

    int childCount() const;
    int childNumber() const;

    bool insertChildren(int position, int count);
    bool removeChildren(int position, int count);

    bool move(ModelWorkspaceItem *parent, int position);

private:
    ModelWorkspaceItem *m_parentItem = nullptr;
    QList<ModelWorkspaceItem*> m_childItems;

    ModelWorkspaceItem::ItemType m_itemType = ModelWorkspaceItem::ItemType::EmptyItem;
    QString m_itemPid;
    QString m_itemLabel;
};


#endif
