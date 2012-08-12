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

#include "namedObject.h"

namespace stk
{

namedObject::~namedObject()
{
}

namedObject::namedObject()
{
}

namedObject::namedObject( const string& objectName )
{
    //! @param objectName Objects name.

    object_name = objectName;
}

namedObject::namedObject ( const namedObject& copyFrom )
{
    object_name = copyFrom.object_name;
}

namedObject& namedObject::operator= ( const namedObject& copyFrom )
{
    if ( this != &copyFrom )
    {
        object_name = copyFrom.object_name;
    }

    return *this;
}

void namedObject::name ( const string& newName )
{
    //! @param newName Name to give object. Copied not stored.
    
    object_name = newName;
}

string namedObject::name() const
{
    //! @return Name of object.
    
    return object_name;
}

bool namedObject::hasName ( const string& compareName )
{
    //! @param compareName Name to compare against this objects name.
    
    return object_name == compareName;
}

char* namedObject::copyString ( const char* stringToCopy, int maxLength )
{
    //! @param stringToCopy String to take copy of.
    //! @param maxLength Maximum length of resultant string.
    //! @return Pointer to copy of string.

    int stringSize = 0;
    
    while ( stringToCopy [ stringSize ] ) stringSize ++;
    
    if ( stringSize > maxLength ) stringSize = maxLength;
    
    char* copy = new char [ stringSize + 1 ];
    
    for ( int index = 0; index < stringSize; index ++ )
        copy [ index ] = stringToCopy [ index ];
        
    copy [ stringSize ] = 0;

    return copy;
}

}
