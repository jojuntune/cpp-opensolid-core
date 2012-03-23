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

#ifndef OS_GRAPH_ITEM_MODEL_H
#define OS_GRAPH_ITEM_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>

#include <OpenSolid/Graph/graphNode.h>
#include <OpenSolid/Graph/project.h>
#include <OpenSolid/Graph/projectEventListener.h>

#include <stk/ptrList.h>

namespace opensolid
{

class graphItemModel : public QAbstractItemModel, public projectEventListener
{
    Q_OBJECT
    
    public:

        virtual ~graphItemModel();

        graphItemModel();

        virtual QModelIndex index ( int row, int column, const QModelIndex& parent ) const;

        virtual QModelIndex parent ( const QModelIndex& index ) const;

        // QAbstractModel Implementation.

        virtual int rowCount ( const QModelIndex& parent ) const;

        virtual int columnCount ( const QModelIndex& parent ) const;
        
        virtual QMap<int, QVariant> itemData ( const QModelIndex& index ) const;

        virtual QVariant data ( const QModelIndex& index, int role ) const;

        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role ) const;

        virtual Qt::ItemFlags flags ( const QModelIndex& index ) const;

        virtual Qt::DropActions supportedDropActions() const;

        virtual bool dropMimeData ( const QMimeData* data, Qt::DropAction action, int row, int column,
                                    const QModelIndex& parent );

        // Other functions.

        void sourceProject ( project::sptr proj ); //!< Set models data source.

        //! Class for converting the D.A.G. into a form that the modelview stuff can handle.
        class graphItem : public QObject
        {
            public:

                graphItem ( graphItem* parent, graphEdge::sptr nodesEdge )
                    : QObject( parent ), _edge( nodesEdge ){}

                graphNode::sptr node() { return _edge -> link(); };

                int row();

                //! Find all items that reference node from this item onwards.
                void find ( graphNode::sptr nodeToFind, ptrList< graphItem >& retItems );

                //! Find all items that reference edge from this item onwards.
                void find ( graphEdge::sptr edgeToFind, ptrList< graphItem >& retItems );

                //! Find a single child that matches an edge.
                graphItem* findChild ( graphEdge::sptr edgeToFind );

                graphEdge::sptr edge() { return _edge; }

            private:

                graphEdge::sptr _edge;
        };

        // Events.

        void projectChanging();

        void projectChangesCancelled();

        void projectGraphNodeChanged ( graphNode::sptr node );

        void projectGraphNodeAdded ( graphNode::nodeInfo info );

        void projectGraphNodeRemoved ( int edgeIndex, graphNode::nodeInfo info );

    signals:

        void rowInserted( const QModelIndex& parent );

    public slots:

        void refresh( graphNode::sptr node ); //!< Refresh the displayed information for a node.

        void rebuild(); //!< Cause a complete rebuild of the model structure.

    private:

        project::sptr source_project; //!< Project that is source of data.

        graphItem* graph_items_root; //!< Root of all graph items.

        //! Find graph item that corresponds to a parent items row.
        graphItem* findGraphItem ( graphItem* parent, int row ) const;

        QString iconName( int nodeType ) const; //!< Get icon name given a nodes type.

        void setupGraphItemsRoot();

        //! Generate a list of edges from MIME data.
        QList<int> decodeEdgesFromMimeData ( const QMimeData* );
};

}

#endif
