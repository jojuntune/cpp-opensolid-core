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

#ifndef OS_GRAPH_SCRIPT_PROPERTY_H
#define OS_GRAPH_SCRIPT_PROPERTY_H

#include <stk/propertyDelegate.h>
#include <stk/PropertyException.h>
using namespace stk;

#include "graphScript.h"

namespace opensolid
{

template < class T > class graphScriptProperty : public propertyDelegate<T>
{
    public:

        graphScriptProperty ( const string& name, T* connectTo, typename propertyDelegate<T>::getStringFunct getter,
                            typename propertyDelegate<T>::setStringFunct setter )
            : propertyDelegate<T>( name, connectTo, getter, setter ) {}

        //! Set properties value as a string.
        virtual void stringValue ( const string& propertyValue )
        {
            try
            {
                propertyDelegate<T>::stringValue( propertyValue );
            }
            catch( graphScript::Error error )
            {
                throw PropertyException( error.message() );
                property::hasError( true );
            }

            property::hasError( false );
        }
};

}

#endif
