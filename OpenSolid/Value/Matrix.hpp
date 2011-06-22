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
#include <OpenSolid/Value/Scalar.hpp>
#include <OpenSolid/Value/Interval.hpp>

namespace OpenSolid
{
    class Matrix : public MatrixBase<Matrix, Scalar>
    {
    protected:
        Eigen::Map<Eigen::MatrixXd, Aligned>& map();
        const Eigen::Map<Eigen::MatrixXd, Aligned>& map() const;
    public:
        Matrix(Index rows, Index cols);
    }
    
    class Vector : public Matrix
    {
    public:
        Vector(Index size);
        Vector(Scalar x, Scalar y);
        Vector(Scalar x, Scalar y, Scalar z);
        Vector(Scalar x, Scalar y, Scalar z, Scalar w);
        
        static Vector Zero(Index size);
        static Vector Unit(Index size, Index index);
        static Vector LinSpaced(Index size, Interval interval);
    };
    
    class RowVector : public Matrix
    {
    public:
        RowVector(Index size);
        RowVector(Scalar x, Scalar y);
        RowVector(Scalar x, Scalar y, Scalar z);
        RowVector(Scalar x, Scalar y, Scalar z, Scalar w);
        
        static RowVector Zero(Index size);
        static RowVector Unit(Index size, Index index);
        static RowVector LinSpaced(Index size, Interval interval);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Eigen::Map<Eigen::MatrixXd, Aligned>& map() {
        return reinterpret_cast<Eigen::Map<Eigen::MatrixXd, Aligned>&>(_map);
    }
    
    const Eigen::Map<Eigen::MatrixXd, Aligned>& map() const {
        return reinterpret_cast<const Eigen::Map<Eigen::MatrixXd, Aligned>&>(_map);
    }
    
    inline Matrix::Matrix(Index rows, Index cols) : MatrixBase(rows, cols) {}
    
    inline Vector::Vector(Index size) : Matrix(size, 1) {}
    
    inline Vector::Vector(Scalar x, Scalar y) : Matrix(2, 1) {
        map() = Eigen::Vector2d(x, y);
    }
    
    inline Vector::Vector(Scalar x, Scalar y, Scalar z) : Matrix(3, 1) {
         map() = Eigen::Vector3d(x, y, z);
    }
    
    inline Vector::Vector(Scalar x, Scalar y, Scalar z, Scalar w) : Matrix(4, 1) {
         map() = Eigen::Vector4d(x, y, z, w);
    }
    
    inline Vector Vector::Zero(Index size) : Matrix(size, 1) {map().setZero();}
    
    inline Vector Vector::Unit(Index size, Index index) : Matrix(size, 1) {
        map() = VectorXd::Unit(size, index);
    }
    
    inline Vector Vector::LinSpaced(Index size, Interval interval) {
        map().setLinSpaced(size, interval.lower(), interval.upper());
    }
    
    inline RowVector::RowVector(Index size) : Matrix(1, size) {}
    
    inline RowVector::RowVector(Scalar x, Scalar y) : Matrix(1, 2) {
        map() = Eigen::RowVector2d(x, y);
    }
    
    inline RowVector::RowVector(Scalar x, Scalar y, Scalar z) : Matrix(1, 3) {
         map() = Eigen::RowVector3d(x, y, z);
    }
    
    inline RowVector::RowVector(Scalar x, Scalar y, Scalar z, Scalar w) : Matrix(1, 4) {
         map() = Eigen::RowVector4d(x, y, z, w);
    }
    
    inline RowVector RowVector::Zero(Index size) : Matrix(1, size) {map().setZero();}
    
    inline RowVector RowVector::Unit(Index size, Index index) : Matrix(1, size) {
        map() = RowVectorXd::Unit(size, index);
    }
    
    inline RowVector RowVector::LinSpaced(Index size, Interval interval) {
        map().setLinSpaced(size, interval.lower(), interval.upper());
    }
}

#endif
