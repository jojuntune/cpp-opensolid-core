/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__SHARED_HPP
#define OPENSOLID__SHARED_HPP

#include <boost/intrusive_ptr.hpp>

#include "ReferenceCounted.hpp"

namespace OpenSolid
{
    template <class Type>
    class Shared
    {
    private:
        boost::intrusive_ptr<Type> _pointer;
    public:
        Shared(Type* object);
        
        bool valid() const;
        bool unique() const;
        
        Shared<Type>& swap(Shared<Type>& other);
        
        Type& reference();
        const Type& constReference() const;
        
        Type* pointer();
        const Type* constPointer() const;
    };
    
    template <class Type>
    class Shared<const Type>
    {
    private:
        boost::intrusive_ptr<const Type> _pointer;
    public:
        Shared(const Type* object);
        
        bool valid() const;
        bool unique() const;
        
        Shared<const Type>& swap(Shared<const Type>& other);
        
        const Type& constReference() const;
        const Type* constPointer() const;
    };
    
    template <class Type>
    class Shared<ReferenceCounted<Type> >
    {
    private:
        boost::intrusive_ptr<ReferenceCounted<Type> > _pointer;
    public:
        Shared(Type* object);
        
        bool valid() const;
        bool unique() const;
        
        Shared<ReferenceCounted<Type> >& swap(Shared<ReferenceCounted<Type> >& other);
        
        Type& reference();
        const Type& constReference() const;
        
        Type* pointer();
        const Type* constPointer() const;
    };
    
    template <class Type>
    class Shared<ReferenceCounted<const Type> >
    {
    private:
        boost::intrusive_ptr<ReferenceCounted<const Type> > _pointer;
    public:
        Shared(const Type* object);
        
        bool valid() const;
        bool unique() const;
        
        Shared<ReferenceCounted<const Type> >& swap(Shared<ReferenceCounted<const Type> >& other);
        
        const Type& constReference() const;
        const Type* constPointer() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    inline Shared<Type>::Shared(Type* object) : _pointer(object) {}
    
    template <class Type>
    inline bool Shared<Type>::valid() const {return _pointer;}
    
    template <class Type>
    inline bool Shared<Type>::unique() const {return _pointer->intrusive_ptr_count == 1;}
    
    template <class Type>
    inline Shared<Type>& Shared<Type>::swap(Shared<Type>& other) {_pointer.swap(other._pointer);}
    
    template <class Type>
    inline Type& Shared<Type>::reference() {
        if (!unique()) {_pointer = new Type(*_pointer);}
        return *_pointer;
    }
    
    template <class Type>
    inline const Type& Shared<Type>::constReference() const {return *_pointer;}
    
    template <class Type>
    inline Type* Shared<Type>::pointer() {
        if (!unique()) {_pointer = new Type(*_pointer);}
        return _pointer.get();
    }
    
    template <class Type>
    inline const Type* Shared<Type>::constPointer() const {return _pointer.get();}

    template <class Type>
    inline Shared<const Type>::Shared(const Type* object) : _pointer(object) {}
    
    template <class Type>
    inline bool Shared<const Type>::valid() const {return _pointer;}
    
    template <class Type>
    inline bool Shared<const Type>::unique() const {return _pointer->intrusive_ptr_count == 1;}
    
    template <class Type>
    inline Shared<const Type>& Shared<const Type>::swap(Shared<const Type>& other) {
        _pointer.swap(other._pointer);
    }
    
    template <class Type>
    inline const Type& Shared<const Type>::constReference() const {return *_pointer;}
    
    template <class Type>
    inline const Type* Shared<const Type>::constPointer() const {return _pointer.get();}

    template <class Type>
    inline Shared<ReferenceCounted<Type> >::Shared(Type* object) :
        _pointer(new ReferenceCounted<Type>(object)) {}
    
    template <class Type>
    inline bool Shared<ReferenceCounted<Type> >::valid() const {return _pointer;}
    
    template <class Type>
    inline bool Shared<ReferenceCounted<Type> >::unique() const {
        return _pointer->intrusive_ptr_count == 1;
    }
    
    template <class Type>
    inline Shared<ReferenceCounted<Type> >& Shared<ReferenceCounted<Type> >::swap(
        Shared<ReferenceCounted<Type> >& other
    ) {_pointer.swap(other._pointer);}
    
    template <class Type>
    inline Type& Shared<ReferenceCounted<Type> >::reference() {
        if (!unique()) {_pointer = new ReferenceCounted<Type>(new Type(*_pointer->object()));}
        return *_pointer->object();
    }
    
    template <class Type>
    inline const Type& Shared<ReferenceCounted<Type> >::constReference() const {
        return *_pointer->object();
    }
    
    template <class Type>
    inline Type* Shared<ReferenceCounted<Type> >::pointer() {
        if (!unique()) {_pointer = new ReferenceCounted<Type>(new Type(*_pointer->object()));}
        return _pointer->object();
    }
    
    template <class Type>
    inline const Type* Shared<ReferenceCounted<Type> >::constPointer() const {
        return _pointer->object();
    }

    template <class Type>
    inline Shared<ReferenceCounted<const Type> >::Shared(const Type* object) :
        _pointer(new ReferenceCounted<const Type>(object)) {}
    
    template <class Type>
    inline bool Shared<ReferenceCounted<const Type> >::valid() const {return _pointer;}
    
    template <class Type>
    inline bool Shared<ReferenceCounted<const Type> >::unique() const {
        return _pointer->intrusive_ptr_count == 1;
    }
    
    template <class Type>
    inline Shared<ReferenceCounted<const Type> >& Shared<ReferenceCounted<const Type> >::swap(
        Shared<ReferenceCounted<const Type> >& other
    ) {_pointer.swap(other._pointer);}
    
    template <class Type>
    inline const Type& Shared<ReferenceCounted<const Type> >::constReference() const {
        return *_pointer->object();
    }
    
    template <class Type>
    inline const Type* Shared<ReferenceCounted<const Type> >::constPointer() const {
        return _pointer->object();
    }
}

#endif
