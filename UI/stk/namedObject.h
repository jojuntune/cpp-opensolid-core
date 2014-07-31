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

#ifndef STK_NAMEDOBJECT_H
#define STK_NAMEDOBJECT_H

#include <string>
using namespace std;

#include "safePtr.h"

namespace stk
{

class namedObject
{
    public:

        typedef safePtr<namedObject> sptr;

        virtual ~namedObject();
        namedObject();

        namedObject( const string& objectName );

        namedObject ( const namedObject& copyFrom );

        namedObject& operator= ( const namedObject& copyFrom );

        //! Set objects name.
        virtual void name ( const string& newName );

        //! Get objects name.
        virtual string name() const;
        
        //! Confirm if this object has a particular name.
        bool hasName ( const string& compareName );

        //! Create a copy of the given string.http://www.adobe.com/products/flash/features/
        static char* copyString ( const char* stringToCopy, int maxLength );

    private:
    
        string object_name;
};

}

#endif

