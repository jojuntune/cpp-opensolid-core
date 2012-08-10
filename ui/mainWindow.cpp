// Copyright 2007 Scott Lanham.
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

#include <iostream>
using namespace std;

#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtGui/QHeaderView>
#include <QtGui/QIcon>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QTreeWidgetItem>

#include <stk/NameInUse.h>
#include <stk/NodeNotFound.h>
#include <stk/ptrList.h>

#include "dlgPointDetails.h"
#include "graphItemModel.h"
#include "mainWindow.h"
#include "nodePropItemModel.h"
#include "projectRenderTarget.h"

namespace opensolid
{

mainWindow::~mainWindow()
{
}

mainWindow::mainWindow ( QWidget* parent )
    :   QMainWindow ( parent )
{
    setupUi ( this );
    
    setStartupUiState();

    ignore_item_changed = false;
}

void mainWindow::setStartupUiState()
{
    // Setup components tree view.

    graphItemModel* graphModel = new graphItemModel();

    graphTreeView -> setModel( graphModel );

    graphTreeView -> header() -> hide();

    // Setup properties table view.

    nodePropItemModel* propModel = new nodePropItemModel();

    tblProperties -> setModel( propModel );

    ( tblProperties -> verticalHeader() ) -> setVisible( false );
    ( tblProperties -> horizontalHeader() ) -> setResizeMode( 1, QHeaderView::Stretch );

    // Connect signals
    
    connect( propModel, SIGNAL( error( QString, QString ) ), this, SLOT( showErrorMessage( QString, QString ) ) );

    connect( graphTreeView -> selectionModel(), SIGNAL( currentChanged( const QModelIndex&, const QModelIndex& ) ),
             propModel, SLOT( dataSource( const QModelIndex&, const QModelIndex& ) ));

    connect( graphModel, SIGNAL( rowInserted( const QModelIndex& ) ),
             graphTreeView, SLOT( expand( const QModelIndex& ) ) );
}

void mainWindow::render()
{
    if ( ! current_project.isNull() )
        renderProject();
}

void mainWindow::showErrorMessage( QString title, QString message )
{
    QMessageBox::critical( this, title, message );
}

void mainWindow::on_actionOrtho_triggered ( bool checked )
{
    currentModelView -> toggleOrthoMode ( checked );
}

void mainWindow::on_actionNewProject_triggered()
{
    createNewProject();
}

void mainWindow::on_actionAddComponent_triggered()
{
    createNewComponent();
}

void mainWindow::on_actionAddFragment_triggered()
{
    createNewFragment();
}

void mainWindow::on_actionAddPoint_triggered()
{
    createNewPoint();
}

void mainWindow::on_actionAddCurve_triggered()
{
}

void mainWindow::on_actionAddSurface_triggered()
{
}

void mainWindow::on_actionAddParameter_triggered()
{
    createNewParam();
}

//Private

int mainWindow::currentComponentTreeParentId()
{
    QModelIndex curIndex = graphTreeView -> currentIndex();

    if ( ! curIndex.isValid() ) return -1;

    graphItemModel::graphItem* item = (graphItemModel::graphItem*)( curIndex.internalPointer() );

    if ( ( item -> node() ).isNull() ) return -1;

    return ( item -> node() ) -> id();
}

void mainWindow::renderProject()
{
    currentModelView -> refresh();
}

void mainWindow::createNewProject()
{
    // Get new projects name.

    bool ok;

    QString newProjName = QInputDialog::getText ( this, "Create New Project", "Please enter new projects name",
                                                  QLineEdit::Normal, "", &ok);

    if ( ! ok || newProjName.isEmpty() ) return;

    // Create a new project.

    current_project = project::sptr( new project( ( newProjName.toUtf8() ).constData() ) );

    ((graphItemModel*)( graphTreeView -> model() )) -> sourceProject( project::sptr( current_project ) );

    // Set project dock widgets title.

    dockProjectControl -> setWindowTitle( "Project: " + newProjName );

    // Bind current modelview GL context to project.
    
    renderTarget::sptr rTarget( new projectRenderTarget( current_project ) );
    
    currentModelView -> refresh( rTarget );

    // Register for project events.

    current_project -> addEventListener( this );
}

void mainWindow::createNewComponent()
{
    if ( current_project.isNull() ) return;

    int parentId = currentComponentTreeParentId();

    graphNode::nodeInfo newComponentInfo;

    try
    {
        newComponentInfo = current_project -> addNewComponent ( parentId );
    }
    catch ( stk::NameInUse )
    {
        processError ( NAME_IN_USE );
        return;
    }
}

void mainWindow::createNewFragment()
{
    if ( current_project.isNull() ) return;

    int parentId = currentComponentTreeParentId();

    graphNode::nodeInfo newFragmentInfo;

    try
    {
        newFragmentInfo = current_project -> addNewFragment( parentId );
    }
    catch ( stk::NameInUse )
    {
        processError ( NAME_IN_USE );
        return;
    }
}

void mainWindow::createNewPoint()
{
    if ( current_project.isNull() ) return;

    int parentId = currentComponentTreeParentId();

    current_project -> addNewPoint( parentId );
}

void mainWindow::createNewParam()
{
    if ( current_project.isNull() ) return;

    int parentId = currentComponentTreeParentId();

    current_project -> addNewParam( parentId );
}

void mainWindow::processError ( int error )
{
    switch ( error )
    {
        case NAME_IN_USE:
            QMessageBox::critical ( this, "Name Already In Use", "The name you have entered is already in use. Please try again using a different name." );
            break;

        case EXPR_PARSE:
            QMessageBox::critical ( this, "Parse Error", "An expression you have entered could not be parsed." );
            break;
    }
}

// Events.

void mainWindow::projectGraphEvaluated()
{
    render();
}

}

