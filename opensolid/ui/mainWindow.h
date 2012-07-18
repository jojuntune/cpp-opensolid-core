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

#ifndef OS_MAINWINDOW_H
#define OS_MAINWINDOW_H

#include "ui_mainWindow.h"

#include <opensolid/graph/project.h>
#include <opensolid/graph/projectEventListener.h>

namespace opensolid
{

class mainWindow : public QMainWindow, private Ui::mainWindow, public projectEventListener
{
    Q_OBJECT

    public:

        ~mainWindow();

        mainWindow ( QWidget* parent = 0 );

        enum errors
        {
            NAME_IN_USE,
            EXPR_PARSE
        };
        
        // Events

        virtual void projectGraphEvaluated();

    public slots:

        void render();

        void showErrorMessage( QString title, QString message );
    
        void on_actionOrtho_triggered ( bool checked );
        
        void on_actionNewProject_triggered();

        void on_actionAddComponent_triggered();

        void on_actionAddFragment_triggered();

        void on_actionAddPoint_triggered();

        void on_actionAddCurve_triggered();

        void on_actionAddSurface_triggered();

        void on_actionAddParameter_triggered();

    private:

        int currentComponentTreeParentId();

        void renderProject();

        void setStartupUiState();

        void createNewProject();

        void createNewComponent();

        void createNewFragment();

        void createNewPoint();

        void createNewParam();

        void processError ( int error );

        // Data
        
        project::sptr current_project;

        bool ignore_item_changed;
};

}

#endif
