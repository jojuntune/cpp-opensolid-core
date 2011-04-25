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

#ifndef OPENSOLID__REFERENCECOUNTEDBASE_HPP
#define OPENSOLID__REFERENCECOUNTEDBASE_HPP

#include <boost/intrusive_ptr.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>

namespace opensolid
{
    template <class DerivedType>
    class ReferenceCountedBase
    {
    private:
        ReferenceCountedBase(const ReferenceCountedBase&);
    public:
        typedef boost::intrusive_ptr<const DerivedType> Pointer;
        mutable boost::detail::atomic_count intrusive_ptr_count;
        
        ReferenceCountedBase();
    };
    
    template <class DerivedType>
    void intrusive_ptr_add_ref(const ReferenceCountedBase<DerivedType>* argument);
    
    template <class DerivedType>
    void intrusive_ptr_release(const ReferenceCountedBase<DerivedType>* argument);
}

////////// Implementation //////////

namespace opensolid
{
    template <class DerivedType>
    inline ReferenceCountedBase<DerivedType>::ReferenceCountedBase() : intrusive_ptr_count(0) {}
        
    template <class DerivedType>
    inline void intrusive_ptr_add_ref(const ReferenceCountedBase<DerivedType>* argument) {
        ++argument->intrusive_ptr_count;
    }
    
    template <class DerivedType>
    inline void intrusive_ptr_release(const ReferenceCountedBase<DerivedType>* argument) {
        if (--argument->intrusive_ptr_count == 0) {
            delete static_cast<const DerivedType*>(argument);
        }
    }
}

#endif
