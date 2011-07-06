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

#ifndef OPENSOLID__VECTOR_HPP
#define OPENSOLID__VECTOR_HPP

#include <OpenSolid/Value/VectorBase.hpp>
#include <OpenSolid/Value/Double.hpp>
#include <OpenSolid/Value/Interval.hpp>
#include <OpenSolid/Value/Range.hpp>

namespace OpenSolid
{
    template <class ScalarType>
    class Vector : public VectorBase
    {
    private:
        typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, 1, 0, 4, 1> MatrixType;
        
        MatrixType _matrix;
        
        friend class MatrixBase<ScalarType>;
    public:
        typedef ScalarType Scalar;
        typedef Vector<Interval> Bounds;
        
        Vector();
        Vector(int size);
        Vector(Double x, Double y);
        Vector(Double x, Double y, Double z);
        Vector(Double x, Double y, Double z, Double w);
        Vector(const Matrix<ScalarType>& argument);
    };
}

////////// Implementation //////////

#endif
