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

#ifndef NODE_PROP_ITEM_MODEL_H
#define NODE_PROP_ITEM_MODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>

#include <opensolid/graph/graphNode.h>

namespace opensolid
{

//! Node Properties Item Model

class nodePropItemModel : public QAbstractTableModel
{
    Q_OBJECT
    
    public:
        
        virtual int rowCount ( const QModelIndex& parent ) const;

        virtual int columnCount ( const QModelIndex& parent ) const;

        virtual QVariant data ( const QModelIndex& index, int role ) const;

        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role ) const;

        virtual Qt::ItemFlags flags ( const QModelIndex& index ) const;

        virtual bool setData ( const QModelIndex& index, const QVariant& value, int role );

        void dataSource ( graphNode::sptr node ); //!< Set graph node that model gets it's data from.

    signals:

        void propertyChanged( graphNode::sptr node );

        void error ( QString title, QString message );

    public slots:

        //!< Set data source from an index from a graph item.
        void dataSource ( const QModelIndex& graphIndex, const QModelIndex& prevGraphIndex );

    private:

        graphNode::sptr data_source;
        
};

}

#endif
