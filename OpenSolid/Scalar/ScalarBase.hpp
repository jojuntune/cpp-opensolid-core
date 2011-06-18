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

#ifndef OPENSOLID__SCALARBASE_HPP
#define OPENSOLID__SCALARBASE_HPP

namespace OpenSolid
{
    template <class DerivedType>
    class ScalarBase
    {
    public:
        DerivedType& derived();
        const DerivedType& derived() const;
        
        int rows() const;
        int cols() const;
        int size() const;
        
        DerivedType coeff(int index) const;
        DerivedType coeff(int row, int col) const;
        DerivedType& coeffRef(int index);
        DerivedType& coeffRef(int row, int col);
        
        DerivedType operator()(int index) const;
        DerivedType operator()(int row, int col) const;
        DerivedType& operator()(int index);
        DerivedType& operator()(int row, int col);
        
        const DerivedType* begin() const;
        const DerivedType* end() const;
        DerivedType* begin();
        DerivedType* end();
    };
}

////////// Implementation //////////

#include "Double.hpp"
#include "Interval.hpp"

namespace OpenSolid
{
    template <class DerivedType>
    inline DerivedType& ScalarBase<DerivedType>::derived() {
        return static_cast<DerivedType&>(*this);
    }
    
    template <class DerivedType>
    inline const DerivedType& ScalarBase<DerivedType>::derived() const {
        return static_cast<DerivedType&>(*this);
    }
    
    template <class DerivedType>
    inline int ScalarBase<DerivedType>::rows() const {return 1;}
    
    template <class DerivedType>
    inline int ScalarBase<DerivedType>::cols() const {return 1;}
    
    template <class DerivedType>
    inline int ScalarBase<DerivedType>::size() const {return 1;}
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::coeff(int index) const {
        assert(index == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::coeff(int row, int col) const {
        assert(row == 0);
        assert(col == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType& ScalarBase<DerivedType>::coeffRef(int index) {
        assert(index == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType& ScalarBase<DerivedType>::coeffRef(int row, int col) {
        assert(row == 0);
        assert(col == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::operator()(int index) const {
        assert(index == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::operator()(int row, int col) const {
        assert(row == 0);
        assert(col == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType& ScalarBase<DerivedType>::operator()(int index) {
        assert(index == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType& ScalarBase<DerivedType>::operator()(int row, int col) {
        assert(row == 0);
        assert(col == 0);
        return derived();
    }
    
    template <class DerivedType>
    inline const DerivedType* ScalarBase<DerivedType>::begin() const {return &derived();}
    
    template <class DerivedType>
    inline const DerivedType* ScalarBase<DerivedType>::end() const {return ++&derived();}
    
    template <class DerivedType>
    inline DerivedType* ScalarBase<DerivedType>::begin() {return &derived();}
    
    template <class DerivedType>
    inline DerivedType* ScalarBase<DerivedType>::end() {return ++&derived();}
}

#endif
