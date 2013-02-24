/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
 *************************************************************************************/
 
#include "ConstantGeometry.hpp"

#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    ConstantGeometry::ConstantGeometry(const VectorXd& vector, int numParameters) :
        _vector(vector),
        _numParameters(numParameters) {
    }

    Function ConstantGeometry::function() const {
        return Function::Constant(_vector, numParameters());
    }

    Domain ConstantGeometry::domain() const {
        return Domain();
    }
        
    int ConstantGeometry::numParameters() const {
        return _numParameters;
    }

    int ConstantGeometry::numDimensions() const {
        return _vector.size();
    }

    void ConstantGeometry::evaluate(const MapXcd& parameter_values, MapXd& results) const {
        results.colwise() = _vector;
    }

    void ConstantGeometry::evaluate(const MapXcI& parameter_bounds, MapXI& results) const {
        results.colwise() = _vector.cast<Interval>();
    }

    bool ConstantGeometry::isConstant() const {
        return true;
    }

    VectorXI ConstantGeometry::bounds() const {
        return _vector.cast<Interval>();
    }

    Set<Geometry> ConstantGeometry::boundaries() const {
        return Set<Geometry>();
    }

    Geometry ConstantGeometry::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return new ConstantGeometry(matrix * _vector + vector, numParameters());
    }

    Geometry ConstantGeometry::reversed() const {
        return this;
    }
}
