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

#include "graphParam.h"
namespace opensolid
{

graphParam::graphParam ( const string& paramName, double paramValue )
{
    _value = paramValue;
    name( paramName );
}

graphParam::graphParam ( const graphParam& copyFrom )
    : namedObject( copyFrom )
{
    //! @param copyFrom Graph parameter to copy from.

    _value = copyFrom._value;
}

graphParam& graphParam::operator= ( const graphParam& copyFrom )
{
    //! @param copyFrom Graph parameter to copy from.

    if ( this != &copyFrom )
    {
        namedObject::operator=( copyFrom );
        _value = copyFrom._value;
    }

    return *this;
}

double graphParam::value()
{
    return _value;
}

void graphParam::value( double paramValue )
{
    _value = paramValue;
}

}
