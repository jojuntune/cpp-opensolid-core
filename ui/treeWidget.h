// Copyright 2007 Scott A.E. Lanham.
// ---------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef OS_TREEWIDGET_H
#define OS_TREEWIDGET_H

#include <QtGui/QDropEvent>
#include <QtGui/QWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>

class treeWidget : public QTreeWidget
{
    Q_OBJECT

    public:
        
        treeWidget ( QWidget* parent = 0 );

        bool itemMoving();

    signals:

        void itemMoved ( QTreeWidgetItem* item, QTreeWidgetItem* prevParent, int prevIndex );
        
    protected:

        void dropEvent ( QDropEvent* event );

    private:

        bool item_moving;
    
};

#endif
