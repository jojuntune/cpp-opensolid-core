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

#ifndef OPENSOLID__VALUE_HPP
#define OPENSOLID__VALUE_HPP

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE

#include <boost/numeric/interval.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace OpenSolid
{
    template <class ScalarType, int rows_, int cols_>
    class Value
    {
    private:
        Eigen::Matrix<ScalarType, rows_, cols_> _matrix;
    public:
        typedef Value<ScalarType, 1, 1> Scalar;
        
        Value();
        
        Value(Scalar scalar);
        
        Value(Scalar x, Scalar y);
        
        Value(Scalar x, Scalar y, Scalar z);
        
        Value(const Value<ScalarType, rows_, cols_>& other);
        
        template <class OtherScalarType, int other_rows_, int other_cols_>
        Value(const Value<OtherScalarType, other_rows_, other_cols_>& other);
        
        Value& operator=(Scalar scalar);
        
        Value& operator=(const Value<ScalarType, rows_, cols_>& other);
        
        template <class OtherScalarType, int other_rows_, int other_cols_>
        Value& operator=(const Value<OtherScalarType, other_rows_, other_cols_>& other);
        
        bool isZero(double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isEqualTo(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isLessThan(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isGreaterThan(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isLessThanOrEqualTo(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isGreaterThanOrEqualTo(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        
        template <class Type>
        bool overlaps(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isSubsetOf(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isSupersetOf(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isProperSubsetOf(const Type& other, double precision = OPENSOLID_PRECISION) const;
        
        template <class Type>
        bool isProperSupersetOf(const Type& other, double precision = OPENSOLID_PRECISION) const;
    };
    
    template <
        class FirstScalarType,
        int first_rows_,
        int first_cols_,
        class SecondScalarType,
        int second_rows,
        int second_cols_
    >
    operator+(
        const Value<FirstScalarType, first_rows_, first_cols_>& first_value,
        const Value<SecondScalarType, second_rows_, second_cols_>& second_value
    );
    
    operator+(Value, Scalar)
    operator+(Scalar, Value)
    
    typedef Value<double, 1, 1> Double;
    typedef Value<BoostInterval, 1, 1> Interval;
}

////////// Implementation //////////

#endif
