// Copyright 2008 Scott Lanham
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

#include "property.h"

namespace stk
{

property::property ( const string& name )
    : namedObject( name ), has_error( false )
{
    //! @param name Properties name.
}

bool property::hasError()
{
    return has_error;
}

void property::hasError( bool yesNo )
{
    has_error = yesNo;
}

}
