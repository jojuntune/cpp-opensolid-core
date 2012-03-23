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

#include "uniqueObject.h"

namespace stk
{

long uniqueObject::object_id_counter = 0;

uniqueObject::~uniqueObject()
{
}

void uniqueObject::init()
{
    THREAD_SYNC
    object_id = object_id_counter ++;
}

uniqueObject::uniqueObject()
{
    init();
}

uniqueObject::uniqueObject ( const uniqueObject& )
    :   threadedObject()
{
    init();
}

long uniqueObject::id()
{
    return object_id;
}

}
