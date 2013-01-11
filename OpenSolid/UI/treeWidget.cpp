// Copyright 2007 Scott A.E. Lanham.
// --------------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include <QtCore/QList>

#include "treeWidget.h"

treeWidget::treeWidget ( QWidget* parent )
    :   QTreeWidget ( parent )
{
    item_moving = false;
}

bool treeWidget::itemMoving()
{
    return item_moving;
}

void treeWidget::dropEvent ( QDropEvent* event )
{
    item_moving = true;

    QList<QTreeWidgetItem*> items = selectedItems();

    QList<QTreeWidgetItem*> prevParents;

    for ( int count = 0; count < items.size(); count ++ )
        prevParents.append ( items [ count ] -> parent() );

    QList<int> prevIndexes;

    for ( int count = 0; count < items.size(); count ++ )
    {
        if ( items [ count ] -> parent() )
            prevIndexes.append ( ( items [ count ] -> parent() ) -> indexOfChild ( items [ count ] ) );
        else
            prevIndexes.append ( indexOfTopLevelItem ( items [ count ] ) );
    }

    QTreeWidget::dropEvent ( event ); // Allow base class to complete drop.

    // Send moved signals if required.

    if ( event -> isAccepted() )
    {
        for ( int count = items.size() - 1; count >= 0; count -- )
        {
            emit itemMoved ( items [ count ], prevParents [ count ], prevIndexes [ count ] );
        }
    }

    item_moving = false;
}

