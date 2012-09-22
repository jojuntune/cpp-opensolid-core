// Copyright 2007 Scott Lanham
// ---------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include <QtGui/QApplication>

#include <mainWindow.h>
using namespace opensolid;

int main( int argc, char *argv[] )
{
     Q_INIT_RESOURCE ( images );
    
     QApplication app(argc, argv);

     mainWindow mainWin;
     mainWin.show();
     
     return app.exec();
}
