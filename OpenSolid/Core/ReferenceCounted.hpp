/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <boost/smart_ptr/detail/atomic_count.hpp>

namespace opensolid
{
    class ReferenceCounted
    {
    private:
        mutable boost::detail::atomic_count _referenceCount;

        template <class TReferenceCounted> friend void intrusive_ptr_add_ref(const TReferenceCounted* argument);
        template <class TReferenceCounted> friend void intrusive_ptr_release(const TReferenceCounted* argument);

        ReferenceCounted(const ReferenceCounted&);
    protected:
        ReferenceCounted();
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class TReferenceCounted>
    inline
    void
    intrusive_ptr_add_ref(const TReferenceCounted* argument) {
        ++argument->_referenceCount;
    }
    
    template <class TReferenceCounted>
    inline
    void
    intrusive_ptr_release(const TReferenceCounted* argument) {
        if (--argument->_referenceCount == 0) {
            delete argument;
        }
    }

    inline
    ReferenceCounted::ReferenceCounted() :
        _referenceCount(0) {
    }
}
