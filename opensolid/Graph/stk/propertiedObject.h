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

#ifndef STK_PROPERTIED_OBJECT_H
#define STK_PROPERTIED_OBJECT_H

#include "threadMutex.h"
#include "property.h"

namespace stk
{

class propertiedObject
{
    public:

        propertiedObject();

        //! Return property at index.
        property::sptr getProperty ( int index );

        //! Return properties index with given name.
        int propertyIndex ( string propertyName );

        //! Add property to node.
        void addProperty ( property* prop );

        //! Get number of properties.
        int propertyCount();

    private:

        property::listSptr _properties;

        threadMutex     mutex;
};

}

#endif
