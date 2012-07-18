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

#ifndef UNIQUEOBJECT_H
#define UNIQUEOBJECT_H

#include "threadedObject.h"

namespace stk
{

class  uniqueObject : public threadedObject
{
    public:

        ~uniqueObject();
        uniqueObject();

        uniqueObject ( const uniqueObject& copyFrom );

        void init();

        long id() const; //!< Return the ID of this object.

    private:

        static long object_id_counter;

        long        object_id;
};

}

#endif
