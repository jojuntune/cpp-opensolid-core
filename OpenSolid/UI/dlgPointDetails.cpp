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

#include "dlgPointDetails.h"

dlgPointDetails::dlgPointDetails ( QWidget* parent )
    : QDialog( parent )
{
    setupUi( this );
}

void dlgPointDetails::on_dlgBtnBox_accepted()
{
    accept();
}

QString dlgPointDetails::ptName()
{
    return txtName -> text();
}

QString dlgPointDetails::x()
{
    return txtX -> text();
}

QString dlgPointDetails::y()
{
    return txtY -> text();
}

QString dlgPointDetails::z()
{
    return txtZ -> text();
}

QString dlgPointDetails::w()
{
    return txtW -> text();
}

