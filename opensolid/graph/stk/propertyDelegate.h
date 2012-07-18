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

#ifndef STK_PROPERTY_DELEGATE_H
#define STK_PROPERTY_DELEGATE_H

#include "property.h"

namespace stk
{

//! Used to bind a property to it's source of data.
//! @tparam T Type of object parameter connects to get/set data.

template < class T > class propertyDelegate : public property
{
    public:

        typedef string ( T::*getStringFunct )() const;
        typedef void ( T::*setStringFunct )( const string& );
    
        virtual ~propertyDelegate() {}

        propertyDelegate ( const string& name, T* connectTo, getStringFunct getter, setStringFunct setter )
            : property( name ), connect_to( connectTo ), string_get( getter ), string_set( setter ) {}

        //! Get properties value as a string.
        virtual string stringValue()
        {
            if ( string_get && connect_to )
                return ( connect_to ->* string_get )();
            else
                return string();
        }

        //! Set properties value as a string.
        virtual void stringValue ( const string& propertyValue )
        {
            if ( string_set && connect_to )
                return ( connect_to ->* string_set )( propertyValue );
        }

    private:

        T* connect_to; // Object that property is connected to.
        
        getStringFunct  string_get;
        setStringFunct  string_set;
};

}

#endif
