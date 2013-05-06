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

#ifndef OS_NODE_NAME_PROPERTY_H
#define OS_NODE_NAME_PROPERTY_H

#include <stk/namedObject.h>
#include <stk/propertyDelegate.h>
#include <stk/PropertyException.h>
#include <stk/NameInUse.h>

#include "graphNode.h"

namespace opensolid
{

//! Property to manipulate a nodes name.
//! @tparam T Type of object parameter connects to get/set data.

template < class T > class nodeNameProperty : public propertyDelegate<T>
{
    public:

        nodeNameProperty ( const string& name, T* connectTo, typename propertyDelegate<T>::getStringFunct getter,
                           typename propertyDelegate<T>::setStringFunct setter )
            : propertyDelegate<T>( name, connectTo, getter, setter ) {}

        //! Set properties value as a string.
        virtual void stringValue ( const string& propertyValue )
        {
            try
            {
                propertyDelegate<T>::stringValue( propertyValue );
            }
            catch( stk::NameInUse error )
            {
                throw PropertyException( "NameInUse" );
                property::hasError( true );
            }

            property::hasError( false );
        }
};

}

#endif
