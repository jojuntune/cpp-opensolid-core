// Copyright 2008 Scott Lanham.
// ----------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include <QIcon>
#include <QMimeData>

#include <stk/NodeNotFound.h>

#include "graphItemModel.h"

namespace opensolid
{

graphItemModel::~graphItemModel()
{
    if ( graph_items_root ) delete graph_items_root;
}

graphItemModel::graphItemModel()
{
    graph_items_root = 0;
}

QModelIndex graphItemModel::index ( int row, int column, const QModelIndex& parent ) const
{
    if ( source_project.isNull() || column > 0 || ! graph_items_root ) return QModelIndex();

    graphItem* parentItem = 0;

    if ( parent.isValid() )
    {
        parentItem = (graphItem*)( parent.internalPointer() );
    }
    else
    {
        parentItem = graph_items_root;
    }

    // See if there is an existing graph item, otherwise create one.

    graphItem* item = 0;
    
    item = findGraphItem( parentItem, row );

    if ( ! item )
    {
        // Create new graph item.
        
        graphNode::sptr parentNode;
        graphEdge::sptr parentEdge;

        parentEdge = parentItem -> edge();
        parentNode = parentEdge -> link();
        
        // Get child that corresponds to row.

        graphEdge::sptr childEdge = parentNode -> edgeAtIndex( row );

        if ( childEdge.isNull() ) return QModelIndex();

        item = new graphItem( parentItem, childEdge );
    }

    // Create model index.

    return createIndex( row, 0, item );
}

QModelIndex graphItemModel::parent ( const QModelIndex& index ) const
{
    if ( source_project.isNull() || ! index.isValid() ) return QModelIndex();

    graphItem* item = (graphItem*)( index.internalPointer() );

    if ( item )
    {
        graphItem* parentItem = (graphItem*)(item -> parent());

        if ( parentItem && parentItem != graph_items_root ) // Don't create index to items root.
        {
            int row = parentItem -> row();
            
            return createIndex( row, 0, parentItem );
        }
    }

    return QModelIndex(); // No parent.
}

int graphItemModel::rowCount ( const QModelIndex& parent ) const
{
    if ( source_project.isNull() || ! graph_items_root ) return 0;

    int count = 0;

    if ( ! parent.isValid() )
        count = graph_items_root -> node() -> childCount(); // Root items count.
    else
    {
        graphItem* parentItem = (graphItem*)( parent.internalPointer() );

        if ( parentItem )
            count = parentItem -> node() -> childCount();
    }

    return count;
}

int graphItemModel::columnCount ( const QModelIndex& parent ) const
{
    return 1;
}

QMap<int, QVariant> graphItemModel::itemData ( const QModelIndex& index ) const
{
    QMap<int, QVariant> retData = QAbstractItemModel::itemData( index );

    // Get user role data for index. Should be edge ID.

    QVariant newData = data ( index, Qt::UserRole );
    
    if ( newData.type() != QVariant::Invalid )
        retData.insert( Qt::UserRole, newData );

    return retData;
}

QVariant graphItemModel::data ( const QModelIndex& index, int role ) const
{
    if ( source_project.isNull() || ! graph_items_root ) return QVariant();
    
    if ( ! index.isValid() )
        return QVariant();

    if ( index.column() > 0 )
        return QVariant();

    graphItem* item = (graphItem*)( index.internalPointer() );

    if ( ! item ) return QVariant();

    graphNode::sptr node = item -> node();
    
    if ( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        if ( node.isNull() ) return QString( "" );
        
        return QString( (node -> name()).c_str() );
    }
    
    if ( role == Qt::DecorationRole && ! node.isNull() )
    {
        return QIcon( iconName( node -> type() ) );
    }

    if ( role == Qt::UserRole )
    {
        // Return edge ID.
        if ( ! (item -> edge()).isNull() )
            return (int)(item -> edge() -> id());
    }

    return QVariant();
}

QVariant graphItemModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if ( role == Qt::DisplayRole && orientation == Qt::Horizontal )
    {
        if ( section == 0 )
            return QString( "Project" );
    }

    return QVariant();
}

Qt::ItemFlags graphItemModel::flags ( const QModelIndex& index ) const
{
    if ( ! index.isValid() ) return 0;

    Qt::ItemFlags retFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

    return retFlags;
}

bool graphItemModel::dropMimeData ( const QMimeData* data, Qt::DropAction action, int row, int column,
                                    const QModelIndex& parent )
{
    if ( action == Qt::IgnoreAction )
         return true;

    graphItem* parentItem = (graphItem*) parent.internalPointer();
         
    // Get edge list of nodes to move.

    QList<int> edges = decodeEdgesFromMimeData( data );

    for ( int index = 0; index < edges.count(); index ++ )
    {
        // If edge is valid get project to move edge.

        int edgeId = edges.at( index );

        if ( edgeId != -1 )
        {
            int newRow = ( row == -1 ? row : row + index );
            
            try
            {
                source_project -> moveNode( edgeId, parentItem -> node(), newRow );
            }
            catch( project::ActionCancelled )
            {
            }
        }
    }
        
    return true;
}

Qt::DropActions graphItemModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

void graphItemModel::sourceProject ( project::sptr proj )
{
    emit layoutAboutToBeChanged();

    source_project = proj;

    setupGraphItemsRoot();
    
    emit layoutChanged();

    proj -> addEventListener( this );
}

// Events.

void graphItemModel::projectChanging()
{
    emit layoutAboutToBeChanged();
}

void graphItemModel::projectChangesCancelled()
{
    emit layoutChanged();
}

void graphItemModel::projectGraphNodeChanged ( graphNode::sptr node )
{
    refresh( node );
}

void graphItemModel::projectGraphNodeAdded ( graphNode::nodeInfo info )
{
    // Find graph itmes that reference parent of node added.

    ptrList< graphItem > foundItems;

    graph_items_root -> find( info.parent(), foundItems );

    graphItem* parentItem = foundItems.first();

    while ( parentItem )
    {
        // Add new graph item to parent item.
            
        QModelIndex parentIndex;

        if ( parentItem != graph_items_root )
        {
            parentIndex = createIndex( parentItem -> row(), 0, parentItem );
        }

        int insertRow = (info.parent()) -> childIndex( info.edgeId() );

        beginInsertRows( parentIndex, insertRow, insertRow ); // Child graph items should be created in index function.
        endInsertRows();

        emit rowInserted( parentIndex );
    
        parentItem = foundItems.next();
    }

    emit layoutChanged();
}

void graphItemModel::projectGraphNodeRemoved ( int edgeIndex, graphNode::nodeInfo info )
{
    // Find graph items that have edge.

    ptrList< graphItem > foundItems;

    graph_items_root -> find( info.edge(), foundItems );

    // Iterate through items and remove from model.

    graphItem* childItem = foundItems.first();

    while ( childItem )
    {
        graphItem* parentItem = (graphItem*)(childItem -> parent());

        QModelIndex parentIndex;

        if ( parentItem != graph_items_root )
            parentIndex = createIndex( parentItem -> row(), 0, parentItem );

        beginRemoveRows( parentIndex, edgeIndex, edgeIndex );
        endRemoveRows();

        childItem -> deleteLater(); //! As graphItem is a QObject, can't delete it directly.
    
        childItem = foundItems.next();
    }

    emit layoutChanged();
}

// SLOTS

void graphItemModel::refresh( graphNode::sptr node )
{
    //! @param node Node to refresh item information for.

    if ( ! graph_items_root ) return;

    ptrList< graphItem > foundItems;

    graph_items_root -> find( node, foundItems );

    graphItem* item = foundItems.first();

    if ( item -> node() == node )
    {
        QModelIndex index = createIndex( item -> row(), 0, item );
        emit dataChanged( index, index );
        item = foundItems.next();
    }
}

void graphItemModel::rebuild()
{
    emit layoutAboutToBeChanged();

    bool rowsRemoved = false;

    if ( graph_items_root )
    {
        int lastIndex = (graph_items_root -> children()).size() - 1;

        if ( lastIndex >= 0 )
        {
            beginRemoveRows( QModelIndex(), 0, lastIndex );
        
            rowsRemoved = true;
        }
    }
    
    setupGraphItemsRoot();
    
    if ( rowsRemoved )
        endRemoveRows();

    emit layoutChanged();
}

// PRIVATE

graphItemModel::graphItem* graphItemModel::findGraphItem ( graphItem* parent, int row ) const
{
    //! @param parent Parent graph item.
    //! @param row Row (index) in underlying data store.
    //! @par Notes graphItem child indexes DO NOT correspond to the underlying data store.

    // Get edge to find.
    
    graphEdge::sptr edge = parent -> node() -> edgeAtIndex( row );

    if ( edge.isNull() ) return 0;

    // Look for edge under parent item.

    return parent -> findChild( edge );
}

QString graphItemModel::iconName( int nodeType ) const
{
    QString retName;
    
    switch ( nodeType )
    {
        case graphNode::COMPONENT:
            retName = ":/images/component.png";
            break;
            
        case graphNode::FRAGMENT:
            retName = ":/images/fragment.png";
            break;
            
        case graphNode::POINT:
            retName = ":/images/point.png";
            break;
            
        case graphNode::CURVE:
            retName = ":/images/curve.png";
            break;
            
        case graphNode::SURFACE:
            retName = ":/images/surface.png";
            break;
            
        case graphNode::PARAMETER:
            retName = ":/images/param.png";
            break;
    }

    return retName;
}

void graphItemModel::setupGraphItemsRoot()
{
    if ( graph_items_root ) delete graph_items_root;

    graph_items_root = 0;

    if ( source_project.isNull() ) return;

    graphNode::sptr parentNode = source_project -> graphRoot();
    graph_items_root = new graphItem( 0, graphEdge::sptr( new graphEdge( "", parentNode ) ) );
}

QList<int> graphItemModel::decodeEdgesFromMimeData ( const QMimeData* mimeData )
{
    //! @param mimeData MIME data to get edge list from.
    
    QStringList types = mimeTypes();
    
    if ( types.isEmpty() )
        return QList<int>();
        
    QString mimeFormat = types.at( 0 );
    
    if ( ! mimeData -> hasFormat( mimeFormat ) )
        return QList<int>();
    
    QByteArray encodedData = mimeData -> data( mimeFormat );

    QDataStream dataStream( &encodedData, QIODevice::ReadOnly );

    int row, col;

    QMap<int, QVariant> data;

    QList<int> edges;

    while ( ! dataStream.atEnd() )
    {
        dataStream >> row >> col >> data;

        edges.append( data.value( Qt::UserRole, -1 ).toInt() ); // Get edge ID from items user role.
    }

    return edges;
}

// CLASS graphItem

int graphItemModel::graphItem::row()
{
    graphItem* parentItem = (graphItem*) parent();

    if ( ! parentItem ) return 0;

    return ( parentItem -> node() ) -> childIndex( _edge -> id() );
}

void graphItemModel::graphItem::find ( graphNode::sptr nodeToFind, ptrList< graphItem >& retItems )
{
    //! @param nodeToFind Find nodes that reference this node.
    //! @param retItems ptrList to return items in. Make sure ptrList does not own pointers!

    if ( node() == nodeToFind ) retItems.append( this, false );

    const QObjectList& childItems = children();

    for ( int index = 0; index < childItems.size(); index ++ )
    {
        graphItem* childItem = (graphItem*)( childItems.at( index ) );

        childItem -> find ( nodeToFind, retItems );
    }
}

void graphItemModel::graphItem::find ( graphEdge::sptr edgeToFind, ptrList< graphItem >& retItems )
{
    //! @param edgeToFind Edge to find.
    //! @param retItems ptrList to return items in. Make sure ptrList does not own pointers!

    if ( edge() == edgeToFind ) retItems.append( this, false );

    const QObjectList& childItems = children();

    for ( int index = 0; index < childItems.size(); index ++ )
    {
        graphItem* childItem = (graphItem*)( childItems.at( index ) );

        childItem -> find ( edgeToFind, retItems );
    }
}

graphItemModel::graphItem* graphItemModel::graphItem::findChild ( graphEdge::sptr edgeToFind )
{
    //! @param edgeToFind Edge to find.

    const QObjectList& childItems = children();

    for ( int index = 0; index < childItems.size(); index ++ )
    {
        graphItem* childItem = (graphItem*)( childItems.at( index ) );

        if ( childItem -> edge() == edgeToFind )
            return childItem;
    }

    return 0;
}

}
