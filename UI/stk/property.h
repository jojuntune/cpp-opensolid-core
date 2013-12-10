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

#ifndef STK_PROPERTY_H
#define STK_PROPERTY_H

#include "namedObject.h"
#include "ptrList.h"
#include "safePtr.h"
#include "threadedObject.h"

namespace stk
{

//! Generic property of any object.
//! @par Notes Properties must never be stored beyond the scope of the object which contains them.
//!            In other words only use them while a thread safe reference to the containing object is still held.

class property : public namedObject, public threadedObject
{
    public:

        typedef safePtr< property > sptr;
        typedef safePtr< ptrList<sptr> > listSptr;

        virtual ~property() {}

        property ( const string& name );

        // Property get/set functions as default do nothing. Sub classes should re-implement these functions.

        //! Get properties value as a string.
        virtual string stringValue() { return string(); }

        //! Set properties value as a string.
        virtual void stringValue ( const string& /*propertyValue*/ ) {}

        virtual bool hasError();

    protected:

        virtual void hasError( bool yesNo );

    private:

        bool    has_error;
};

}

#endif
