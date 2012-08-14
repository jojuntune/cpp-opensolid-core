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

#include "propertiedObject.h"

namespace stk
{

propertiedObject::propertiedObject()
{
    _properties = property::listSptr( new ptrList<property::sptr>() );
}

property::sptr propertiedObject::getProperty ( int index )
{
    //! @param index 0 based index of property to return.

    threadMutex::token token = mutex.lockToken();
    
    return _properties -> atIndex( index );
}

int propertiedObject::propertyIndex ( string propertyName )
{
    //! @param propertyName Name of property to find index of.
    
    threadMutex::token token = mutex.lockToken();

    property::sptr prop = _properties -> first();

    int index = 0;

    while ( ! prop.isNull() )
    {
        if ( prop -> name() == propertyName ) return index;

        index ++;
        
        prop = _properties -> next();
    }

    return -1;
}

void propertiedObject::addProperty ( property* prop )
{
    //! @param prop Property to add to node.
    //! @par Notes This object owns property pointer.

    threadMutex::token token = mutex.lockToken();

    _properties -> append( new property::sptr( prop ), true );
}

int propertiedObject::propertyCount()
{
    threadMutex::token token = mutex.lockToken();

    return _properties -> count();
}

}
