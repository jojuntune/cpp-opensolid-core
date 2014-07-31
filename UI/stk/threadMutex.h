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

#ifndef THREADMUTEX_H
#define THREADMUTEX_H

#include <QtCore/QMutex>

namespace stk
{

class threadCond;

class threadMutex
{
    public:

        friend class threadCond;
    
        threadMutex();
        ~threadMutex();

        threadMutex ( const threadMutex& copyFrom );
        threadMutex& operator= ( const threadMutex& copyFrom );

        //! Class for handling automatic unlock of a mutex.
        class token
        {
            //! @par Notes Typically used for exception safe mutex operations.
            
            public:

                ~token() { if ( _locked ) _mutex -> unlock(); }

                token ( threadMutex* mutex )
                {
                    _mutex = mutex;
                    _locked = mutex -> lock();
                }

                bool locked() { return _locked; }

            private:

                bool _locked;
                threadMutex* _mutex;
        };
        
        bool lock();
        token lockToken();
        bool unlock();
        
    private:

        void init();
    
        QMutex* qMutex;
};

}

#endif
