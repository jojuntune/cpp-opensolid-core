// Copyright 2007 Scott Lanham.
// ----------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef STK_THREADLOCK_H
#define STK_THREADLOCK_H

namespace stk
{

class threadedObject;

class threadLock
{
    public:

        ~threadLock();

        threadLock( threadedObject* object ); //!< Create new threadLock object.

        void release();

    private:

        threadedObject* locked_object;

        bool    is_locked;
};

}

#endif
