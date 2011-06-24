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

#include <OpenSolid/config.hpp>

namespace OpenSolid
{   
    class Interval;
    
    template <class DerivedType>
    class ScalarBase
    {
    public:
        typedef Interval Bounds;
        
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
        
        DerivedType minCoeff() const;
        DerivedType minCoeff(int* index) const;
        DerivedType minCoeff(int* row, int* col) const;
        DerivedType maxCoeff() const;
        DerivedType maxCoeff(int* index) const;
        DerivedType maxCoeff(int* row, int* col) const;
        
        bool isApprox(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isApprox(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isApprox(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isEqualTo(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isEqualTo(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isEqualTo(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isLessThan(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThan(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThan(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isGreaterThan(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThan(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThan(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isLessThanOrEqualTo(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThanOrEqualTo(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThanOrEqualTo(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isGreaterThanOrEqualTo(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThanOrEqualTo(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThanOrEqualTo(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool overlaps(int argument, double precision = OPENSOLID_PRECISION) const;
        bool overlaps(float argument, double precision = OPENSOLID_PRECISION) const;
        bool overlaps(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isSubsetOf(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isSubsetOf(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isSubsetOf(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isProperSubsetOf(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSubsetOf(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSubsetOf(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isSupersetOf(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isSupersetOf(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isSupersetOf(double argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isProperSupersetOf(int argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSupersetOf(float argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSupersetOf(double argument, double precision = OPENSOLID_PRECISION) const;
    };
}

////////// Implementation //////////

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
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::minCoeff() const {
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::minCoeff(int* index) const {
        *index = 0;
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::minCoeff(int* row, int* col) const {
        *row = 0;
        *col = 0;
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::maxCoeff() const {
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::maxCoeff(int* index) const {
        *index = 0;
        return derived();
    }
    
    template <class DerivedType>
    inline DerivedType ScalarBase<DerivedType>::maxCoeff(int* row, int* col) const {
        *row = 0;
        *col = 0;
        return derived();
    }
        
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isApprox(int argument, double precision) const {
        return derived().isApprox(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isApprox(float argument, double precision) const {
        return derived().isApprox(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isApprox(double argument, double precision) const {
        return derived().isApprox(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isEqualTo(int argument, double precision) const {
        return derived().isEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isEqualTo(float argument, double precision) const {
        return derived().isEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isEqualTo(double argument, double precision) const {
        return derived().isEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isLessThan(int argument, double precision) const {
        return derived().isLessThan(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isLessThan(float argument, double precision) const {
        return derived().isLessThan(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isLessThan(double argument, double precision) const {
        return derived().isLessThan(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isGreaterThan(int argument, double precision) const {
        return derived().isGreaterThan(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isGreaterThan(float argument, double precision) const {
        return derived().isGreaterThan(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isGreaterThan(double argument, double precision) const {
        return derived().isGreaterThan(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isLessThanOrEqualTo(int argument, double precision) const {
        return derived().isLessThanOrEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isLessThanOrEqualTo(float argument, double precision) const {
        return derived().isLessThanOrEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isLessThanOrEqualTo(double argument, double precision) const {
        return derived().isLessThanOrEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isGreaterThanOrEqualTo(int argument, double precision) const {
        return derived().isGreaterThanOrEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isGreaterThanOrEqualTo(float argument, double precision) const {
        return derived().isGreaterThanOrEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isGreaterThanOrEqualTo(double argument, double precision) const {
        return derived().isGreaterThanOrEqualTo(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::overlaps(int argument, double precision) const {
        return derived().overlaps(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::overlaps(float argument, double precision) const {
        return derived().overlaps(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::overlaps(double argument, double precision) const {
        return derived().overlaps(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isSubsetOf(int argument, double precision) const {
        return derived().isSubsetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isSubsetOf(float argument, double precision) const {
        return derived().isSubsetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isSubsetOf(double argument, double precision) const {
        return derived().isSubsetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isProperSubsetOf(int argument, double precision) const {
        return derived().isProperSubsetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isProperSubsetOf(float argument, double precision) const {
        return derived().isProperSubsetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isProperSubsetOf(double argument, double precision) const {
        return derived().isProperSubsetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isSupersetOf(int argument, double precision) const {
        return derived().isSupersetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isSupersetOf(float argument, double precision) const {
        return derived().isSupersetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isSupersetOf(double argument, double precision) const {
        return derived().isSupersetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isProperSupersetOf(int argument, double precision) const {
        return derived().isProperSupersetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isProperSupersetOf(float argument, double precision) const {
        return derived().isProperSupersetOf(Double(argument), precision);
    }
    
    template <class DerivedType>
    inline bool ScalarBase<DerivedType>::isProperSupersetOf(double argument, double precision) const {
        return derived().isProperSupersetOf(Double(argument), precision);
    }
}

#endif
