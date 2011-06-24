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

#ifndef OPENSOLID__VALUEBASE_HPP
#define OPENSOLID__VALUEBASE_HPP

#include <cstddef>

namespace OpenSolid
{
    typedef std::ptrdiff_t Index;
    
    template <class DerivedType, class ScalarType>
    class ValueBase
    {
    public:
        DerivedType& derived();
        const DerivedType& derived() const;
        
        Index rows() const;
        Index cols() const;
        Index size() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class DerivedType, class ScalarType>
    inline DerivedType& ValueBase<DerivedType, ScalarType>::derived() {
        return static_cast<DerivedType&>(*this);
    }
    
    template <class DerivedType, class ScalarType>
    inline const DerivedType& ValueBase<DerivedType, ScalarType>::derived() const {
        return static_cast<DerivedType&>(*this);
    }
    
    template <class DerivedType, class ScalarType>
    inline Index ValueBase<DerivedType, ScalarType>::rows() const {return derived().rows();}
    
    template <class DerivedType, class ScalarType>
    inline Index ValueBase<DerivedType, ScalarType>::cols() const {return derived().cols();}
    
    template <class DerivedType, class ScalarType>
    inline Index ValueBase<DerivedType, ScalarType>::size() const {return rows() * cols();}
}

#endif
