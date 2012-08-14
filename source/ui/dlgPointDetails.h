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

#ifndef OS_DLGPOINTDETAILS_H
#define OS_DLGPOINTDETAILS_H

#include "ui_dlgPointDetails.h"

class dlgPointDetails : public QDialog, private Ui::dlgPointDetails
{
    Q_OBJECT

    public:

        dlgPointDetails ( QWidget* parent = 0 );

        QString ptName();
        QString x();
        QString y();
        QString z();
        QString w();

    public slots:

        void on_dlgBtnBox_accepted();
};

#endif
