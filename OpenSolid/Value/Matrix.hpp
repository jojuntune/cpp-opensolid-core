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

#ifndef OPENSOLID__MATRIX_HPP
#define OPENSOLID__MATRIX_HPP

#include <OpenSolid/Value/MatrixBase.hpp>
#include <OpenSolid/Value/Double.hpp>
#include <OpenSolid/Value/Interval.hpp>
#include <OpenSolid/Value/Range.hpp>

namespace OpenSolid
{
    template <>
    class Matrix<Double> : public MatrixBase<Double>
    {
    public:
        Matrix();
        Matrix(int rows, int cols);
        Matrix(Double argument);
        Matrix(const Vector<Double>& argument);
        Matrix(const Matrix<Double>& argument);
        Matrix(Matrix<Double>&& argument);
        
        using MatrixBase<Double>::operator=;
        void operator=(const Matrix<Double>& argument);
        
        Matrix<Interval> bounds() const;
        std::size_t hashValue() const;
        
        ScalarType min() const;
        ScalarType min(int* index) const;
        ScalarType min(int* row, int* col) const;
        ScalarType max() const;
        ScalarType max(int* index) const;
        ScalarType max(int* row, int* col) const;
        
        Double& operator+=(Double argument);
        Double& operator-=(Double argument);
        Double& operator*=(Double argument);
        Double& operator/=(Double argument);
        
        Matrix<Double> LinSpaced(int size, const Interval& interval);
    };
    
    Matrix<Double> operator-(const MatrixBase<Double>& argument);
    
    Double operator+(Double value, const Matrix<Double>& matrix);
    Vector<Double> operator+(const Vector<Double>& vector, const Matrix<Double>& matrix);
    Vector<Double> operator+(const Matrix<Double>& matrix, const Vector<Double>& vector);
    
    Matrix<Double> operator+(
        const MatrixBase<Double>& first_argument,
        const Matrix<Double>& second_argument
    );
    
    Vector<Double> operator-(const Vector<Double>& vector, const Matrix<Double>& matrix);
    Vector<Double> operator-(const Matrix<Double>& matrix, const Vector<Double>& vector);
    
    Matrix<Double> operator-(
        const MatrixBase<Double>& first_argument,
        const Matrix<Double>& second_argument
    );
    
    template <>
    class Matrix<Interval> : public MatrixBase<Interval>
    {
    public:
        Matrix();
        Matrix(int rows, int cols);
        Matrix(const Interval& argument);
        Matrix(const Vector<Interval>& argument);
        Matrix(const Matrix<Interval>& argument);
        Matrix(Matrix<Interval>&& argument);
        
        using MatrixBase<Interval>::operator=;
        void operator=(const Matrix<Interval>& argument);
        
        Matrix<Interval> bounds() const;
        std::size_t hashValue() const;
        
        Matrix<Double> cwiseLower() const;
        Matrix<Double> cwiseUpper() const;
        Matrix<Double> cwiseMedian() const;
        Matrix<Double> cwiseWidth() const;
        
        bool overlaps(
            const Matrix<Interval>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyOverlaps(
            const Matrix<Interval>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isSubsetOf(
            const Matrix<Interval>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isStrictSubsetOf(
            const Matrix<Interval>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isSupersetOf(
            const Matrix<Interval>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isStrictSupersetOf(
            const Matrix<Interval>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
    };
    
    
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Double MatrixBase<Double>::min() const;
    
    inline Double MatrixBase<Double>::min(int* index) const;
    
    inline Double MatrixBase<Double>::min(int* row, int* col) const;
    
    inline Double MatrixBase<Double>::max() const;
    
    inline Double MatrixBase<Double>::max(int* index) const;
    
    inline Double MatrixBase<Double>::max(int* row, int* col) const;
}

#endif
