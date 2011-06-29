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

#include <type_traits>

#include <OpenSolid/config.hpp>
#include <OpenSolid/Value/Double.hpp>
#include <OpenSolid/Value/Interval.hpp>

namespace OpenSolid
{   
    template <class ScalarType, Index rows_ = -1, Index cols_ = -1>
    class Matrix : public ValueBase<Matrix<ScalarType, rows_, cols_>>
    {
    private:
        Eigen::Matrix<ScalarType, rows_, cols_> _matrix;
    public:
        Matrix();
        Matrix(Index size);
        Matrix(Index rows, Index cols);
        Matrix(const ScalarType& x, const ScalarType& y);
        Matrix(const ScalarType& x, const ScalarType& y, const ScalarType& z);
        
        Matrix(const Matrix<ScalarType, rows_, cols_>& other);
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix(const Matrix<ScalarType, argument_rows_, argument_cols_>& argument);
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix(Matrix<ScalarType, argument_rows_, argument_cols_>&& argument);
        
        Matrix<ScalarType, rows_, cols_>& operator=(const Matrix<ScalarType, rows_, cols_>& other);
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix<ScalarType, rows_, cols_> operator=(
            const Matrix<ScalarType, argument_rows_, argument_cols_>& argument
        );
        
        template <Index argument_rows_, Index argument_cols_>
        Matrix<ScalarType, rows_, cols_>::operator=(
            Matrix<ScalarType, argument_rows_, argument_cols_>&& argument
        );
        
        Index rows() const;
        Index cols() const;
        
        
        
        static Matrix<ScalarType, rows_, cols_> Zero();
        static Matrix<ScalarType, rows_, cols_> Zero(Index size);
        static Matrix<ScalarType, rows_, cols_> Zero(Index rows, Index cols);
        
        static Matrix<ScalarType, rows_, cols_> Ones();
        static Matrix<ScalarType, rows_, cols_> Ones(Index size);
        static Matrix<ScalarType, rows_, cols_> Ones(Index rows, Index cols);
        
        static Matrix<ScalarType, rows_, cols_> Identity();
        static Matrix<ScalarType, rows_, cols_> Identity(Index size);
        
        static Matrix<ScalarType, rows_, cols_> UnitX();
        static Matrix<ScalarType, rows_, cols_> UnitY();
        static Matrix<ScalarType, rows_, cols_> UnitZ();
        static Matrix<ScalarType, rows_, cols_> Unit(Index index);
        
        static Matrix<ScalarType, rows_, cols_> LinSpaced(const Interval& range);
        static Matrix<ScalarType, rows_, cols_> LinSpaced(Index size, const Interval& range);
    }
}

////////// Implementation //////////

namespace OpenSolid
{
}

#endif
