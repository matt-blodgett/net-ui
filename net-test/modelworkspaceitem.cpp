#include "modelworkspaceitem.h"


ModelWorkspaceItem::ModelWorkspaceItem(ModelWorkspaceItem *parent)
{
    m_parentItem = parent;

    if(!m_parentItem) {
        m_itemType = ModelWorkspaceItem::RootItem;
    }
}

ModelWorkspaceItem::~ModelWorkspaceItem()
{
    qDeleteAll(m_childItems);
}

ModelWorkspaceItem *ModelWorkspaceItem::parent()
{
    return m_parentItem;
}
ModelWorkspaceItem *ModelWorkspaceItem::child(int row)
{
    return m_childItems.value(row);
}

ModelWorkspaceItem::ItemType ModelWorkspaceItem::type() const
{
    return m_itemType;
}
void ModelWorkspaceItem::setType(ModelWorkspaceItem::ItemType value)
{
    m_itemType = value;
}

QString ModelWorkspaceItem::pid() const
{
    return m_itemPid;
}
void ModelWorkspaceItem::setPid(const QString &value)
{
    m_itemPid = value;
}

QString ModelWorkspaceItem::label() const
{
    return m_itemLabel;
}
void ModelWorkspaceItem::setLabel(const QString &value)
{
    m_itemLabel = value;
}

int ModelWorkspaceItem::childCount() const
{
    return m_childItems.count();
}
int ModelWorkspaceItem::childNumber() const
{
    if(m_parentItem) {
        return m_parentItem->m_childItems.indexOf(const_cast<ModelWorkspaceItem*>(this));
    }

    return 0;
}

bool ModelWorkspaceItem::insertChildren(int position, int count)
{
    if (position < 0 || position > m_childItems.size()) {
        return false;
    }

    for (int row = 0; row < count; ++row) {
        ModelWorkspaceItem *item = new ModelWorkspaceItem(this);
        m_childItems.insert(position, item);
    }

    return true;
}
bool ModelWorkspaceItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size()) {
        return false;
    }

    for (int row = 0; row < count; ++row) {
        delete m_childItems.takeAt(position);
    }

    return true;
}

bool ModelWorkspaceItem::move(ModelWorkspaceItem *parent, int position)
{
    if(!parent) {
        return false;
    }

    if (parent == m_parentItem) {
        return false;
    }

    if(position < 0 || position > parent->childCount()) {
        return false;
    }

    if(m_parentItem) {
        m_parentItem->m_childItems.removeAt(this->childNumber());
    }

    m_parentItem = parent;
    m_parentItem->m_childItems.insert(position, this);

    return true;
}
