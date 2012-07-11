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

#pragma once

#include <OpenSolid/Core/config.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>

namespace opensolid
{
    template <class DerivedType>
    class ReferenceCounted;

    template <class DerivedType>
    void intrusive_ptr_add_ref(const ReferenceCounted<DerivedType>* argument);
    
    template <class DerivedType>
    void intrusive_ptr_release(const ReferenceCounted<DerivedType>* argument);

    template <class DerivedType>
    class ReferenceCounted
    {
    private:
        ReferenceCounted(const ReferenceCounted&);

        mutable boost::detail::atomic_count _count;

        template <class Type>
        friend void intrusive_ptr_add_ref(const ReferenceCounted<Type>* argument);

        template <class Type>
        friend void intrusive_ptr_release(const ReferenceCounted<Type>* argument);
    public:
        ReferenceCounted();
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class DerivedType>
    inline ReferenceCounted<DerivedType>::ReferenceCounted() : _count(0) {}
        
    template <class DerivedType>
    inline void intrusive_ptr_add_ref(const ReferenceCounted<DerivedType>* argument) {
        ++argument->_count;
    }
    
    template <class DerivedType>
    inline void intrusive_ptr_release(const ReferenceCounted<DerivedType>* argument) {
        if (--argument->_count == 0) {
            delete static_cast<const DerivedType*>(argument);
        }
    }
}
