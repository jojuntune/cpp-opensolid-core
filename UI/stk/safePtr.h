// Copyright 2007 Scott A.E. Lanham
// --------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef SAFEPTR_H
#define SAFEPTR_H

//! Thread safe pointer to object with automatic garbage collection.

#include "threadMutex.h"

namespace stk
{

template < class T > class safePtr
{
    //! T is the type that the safe pointer points to.
    //! Only ever pass an instance of this class by value.
    //! This ensures that only one thread can "see" the instance and copying that instance is thread safe.

    public:

        template < class C > friend class safePtr;  // Used for type casting.

        ~safePtr()
        {
            dereference();
        }

        safePtr()
        {
            init();
        }

        safePtr ( T* objectPtr )
        {
            init();
            
            ptr = objectPtr;
            ref_count = new int ( 1 );
            mutex = new threadMutex();
        }
        
        safePtr ( const safePtr<T>& copyFrom, bool deepCopy = false )
        {
            init();

            if ( ! copyFrom.isNull() )
            {
                if ( ! deepCopy )
                {
                    ptr = copyFrom.ptr;
                    ref_count = copyFrom.ref_count;
                    (*ref_count) ++;
                    mutex = copyFrom.mutex;
                }
                else
                {
                    ptr = new T( *(copyFrom.ptr) ); // Assume there is a T( const T& ) copy constructor.
                    ref_count = new int ( 1 );
                    mutex = new threadMutex();
                }
            }
        }

        safePtr ( const safePtr<T>* copyFrom, bool deepCopy = false )
        {
            init();
            
            if ( copyFrom )
            {
                if ( ! copyFrom -> isNull() )
                {
                    if ( ! deepCopy )
                    {
                        ptr = (*copyFrom).ptr;
                        ref_count = (*copyFrom).ref_count;
                        (*ref_count) ++;
                        mutex = (*copyFrom).mutex;
                    }
                    else
                    {
                        ptr = new T( *((*copyFrom).ptr) ); // Assume there is a T( const T& ) copy constructor.
                        ref_count = new int ( 1 );
                        mutex = new threadMutex();
                    }
                }
            }
        }

        template < class C > safePtr ( const safePtr<C>& copyFrom )
        {
            init();

            if ( ! copyFrom.isNull() )
            {
                ptr = (T*)(copyFrom.ptr);
                ref_count = copyFrom.ref_count;
                (*ref_count) ++;
                mutex = copyFrom.mutex;
            }
        }

        template < class C > safePtr ( const safePtr<C>* copyFrom )
        {
            init();
            
            if ( copyFrom )
            {
                if ( ! copyFrom -> isNull() )
                {
                    ptr = (T*)((*copyFrom).ptr);
                    ref_count = (*copyFrom).ref_count;
                    (*ref_count) ++;
                    mutex = (*copyFrom).mutex;
                }
            }
        }

        safePtr<T>& operator= ( const safePtr<T>& copyFrom )
        {
            if ( this != &copyFrom )
            {
                dereference();

                if ( ! copyFrom.isNull() )
                {
                    ptr = copyFrom.ptr;
                    ref_count = copyFrom.ref_count;
                    (*ref_count) ++;
                    mutex = copyFrom.mutex;
                }
            }
        
            return *this;
        }

        safePtr<T>& operator= ( const safePtr<T>* copyFrom )
        {
            if ( this != copyFrom )
            {
                if ( copyFrom )
                {
                    dereference();

                    if ( ! copyFrom -> isNull() )
                    {   
                        ptr = (*copyFrom).ptr;
                        ref_count = (*copyFrom).ref_count;
                        (*ref_count) ++;
                        mutex = (*copyFrom).mutex;
                    }
                }
                else
                    release();
            }
        
            return *this;
        }

        template < class C > safePtr<T>& operator= ( const safePtr<C>& copyFrom )
        {
            // C and T are different types so can't compare pointers directly.
            // Compare the ref_count pointers instead.
            
            if ( ref_count != copyFrom.ref_count )
            {
                dereference();

                if ( ! copyFrom.isNull() )
                {
                    ptr = (T*)(copyFrom.ptr);
                    ref_count = copyFrom.ref_count;
                    (*ref_count) ++;
                    mutex = copyFrom.mutex;
                }
            }
        
            return *this;
        }

        template < class C > safePtr<T>& operator= ( const safePtr<C>* copyFrom )
        {
            // C and T are different types so can't compare pointers directly.
            // Compare the ref_count pointers instead.
            
            if ( ref_count != copyFrom -> ref_count )
            {
                if ( copyFrom )
                {
                    dereference();
                    
                    if ( ! copyFrom -> isNull() )
                    {
                        ptr = (T*)((*copyFrom).ptr);
                        ref_count = (*copyFrom).ref_count;
                        (*ref_count) ++;
                        mutex = (*copyFrom).mutex;
                    }
                }
                else
                    release();
            }
        
            return *this;
        }

        bool operator== ( T* comparePtr ) { return ptr == comparePtr; }

        bool operator== ( safePtr<T>& compare )
        {
            return ( ptr == compare.ptr ) && ( ref_count == compare.ref_count ) && ( mutex == compare.mutex );
        }

        bool operator!= ( safePtr<T>& compare )
        {
            return !(( ptr == compare.ptr ) && ( ref_count == compare.ref_count ) && ( mutex == compare.mutex ));
        }

        T* operator->() { return ptr; }
        const T* operator->() const { return ptr; }
        T& operator*() { return *ptr; }
        const T& operator*() const { return *ptr; }

        T& operator[] ( int index )
        {
            return ptr[ index ];
        }
        
        const T& operator[] ( int index ) const
        {
            return ptr[ index ];
        }

        T* pointer() { return ptr; }
        const T* pointer() const { return ptr; }

        bool isNull() const { return ptr == 0; };

        //! Release safe pointer and optionally garbage collect if underlying pointer is no longer referenced.
        void release()
        {
            dereference();
            ptr = 0;
            ref_count = 0;
            mutex = 0;
        }

        bool lock() { return mutex -> lock(); } //!< Lock safe pointers mutex.
                                                //!< Allows a third party to utilise the shared mutex for objects that
                                                //!< aren't necessarily lockable. An example of this is
                                                //!< the stk::ptrList.
                                                //!< Be very very careful to unlock the mutex as soon as possible.

        bool unlock() { return mutex -> unlock(); } //!< Unlock safe pointers mutex.

    protected:
        
        void dereference()
        {
            if ( ! ref_count ) return; // Empty object.
        
            bool final = false;
            
            if ( mutex -> lock() )
            {
                if ( ( -- (*ref_count) ) == 0 ) final = true;
                mutex -> unlock();
            }

            if ( final )
            {
                delete ref_count;
                delete mutex;
                delete ptr; // Garbage collect.
            }

            // Once dereferenced, can no longer hold pointers to anything.
            
            ptr = 0;
            ref_count = 0;
            mutex = 0;
        }

        void init()
        {
            ptr = 0;
            ref_count = 0;
            mutex = 0;
        }

    private:

        T*              ptr;

        int*            ref_count;
        threadMutex*    mutex;
};

}

#endif

