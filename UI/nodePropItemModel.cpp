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

#include <stk/PropertyException.h>

#include "graphItemModel.h"
#include "nodePropItemModel.h"

namespace opensolid
{

int nodePropItemModel::rowCount ( const QModelIndex& parent ) const
{
    if ( parent.isValid() ) return 0; // Not a hierarchical data structure.

    if ( data_source.isNull() ) return 0;

    graphNode::sptr ds = data_source; // Must do this to avoid compile errors from const.

    return ( ds -> propertyCount() );
}

int nodePropItemModel::columnCount ( const QModelIndex& parent ) const
{
    if ( parent.isValid() ) return 0; // Not a hierarchical data structure.

    return 2;
}

QVariant nodePropItemModel::data ( const QModelIndex& index, int role ) const
{
    if ( data_source.isNull() ) return QVariant();
    
    if ( ! index.isValid() )
        return QVariant();

    graphNode::sptr ds = data_source; // Must do this to avoid compile errors from const.

    if ( index.column() > 1 || index.row() >= ( ds -> propertyCount() ) )
        return QVariant();

    property::sptr prop = ( ds -> getProperty( index.row() ) );

    if ( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        if ( index.column() == 0 )
            return QString( (prop -> name()).c_str() );
        else
            return QString( (prop -> stringValue()).c_str() );
    }

    if ( role == Qt::DecorationRole && index.column() == 1 && prop -> hasError() )
    {
        return QIcon( QString( ":/images/error_small.png" ) );
    }

    return QVariant();
}

QVariant nodePropItemModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if ( role == Qt::DisplayRole && orientation == Qt::Horizontal )
    {
        if ( section == 0 )
            return QString( "Property" );
        else if ( section == 1 )
            return QString( "Value" );
    }

    return QVariant();
}

Qt::ItemFlags nodePropItemModel::flags ( const QModelIndex& index ) const
{
    if ( ! index.isValid() )
        return 0;

    Qt::ItemFlags retFlags = Qt::ItemIsEnabled;

    if ( index.column() == 1 )
        retFlags |= Qt::ItemIsSelectable | Qt::ItemIsEditable;

    return retFlags;
}

bool nodePropItemModel::setData ( const QModelIndex& index, const QVariant& value, int role )
{
    if ( index.isValid() && role == Qt::EditRole && !value.toString().isEmpty() )
    {
        property::sptr prop = data_source -> getProperty( index.row() );

        try
        {
            prop -> stringValue( value.toString().toUtf8().constData() );
        }
        catch( PropertyException ex )
        {
            emit error( QString( "Property Error" ), QString( ex.message().c_str() ) );
            return false;
        }

        emit dataChanged( index, index );

        emit propertyChanged( data_source );
        
        return true;
    }

    return false;
}

void nodePropItemModel::dataSource ( graphNode::sptr node )
{
    //! @param node Graph node that is the source of property data.

    emit layoutAboutToBeChanged();

    data_source = node;

    emit layoutChanged();
}

// SLOTS

void nodePropItemModel::dataSource ( const QModelIndex& graphIndex, const QModelIndex& /*prevGraphIndex*/ )
{
    //! @param graphIndex Current model index.
    
    if ( ! graphIndex.isValid() ) return;
    
    graphItemModel::graphItem* item = (graphItemModel::graphItem*)( graphIndex.internalPointer() );

    dataSource( item -> node() );
}

}
