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

#ifndef THREADCOND_H
#define THREADCOND_H

#include "threadMutex.h"

#include <QtCore/QWaitCondition>

namespace stk
{

class threadCond
{
    public:
    
        threadCond();
        ~threadCond();

        threadCond ( const threadCond& copyFrom );
        threadCond& operator= ( const threadCond& copyFrom );
        
        void init();
        
        bool signal();
        bool broadcast();
        
        bool wait ( threadMutex& mutex );
        bool waitTimeout ( threadMutex& mutex, int timeout );
        
    private:
    
        QWaitCondition*   cond;
};

}

#endif
