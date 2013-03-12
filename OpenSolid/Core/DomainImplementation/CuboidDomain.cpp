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

#include <OpenSolid/Core/DomainImplementation/CuboidDomain.hpp>

#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    CuboidDomain::CuboidDomain(const Vector3I& bounds) : _bounds(bounds) {
    }

    Set<Geometry> CuboidDomain::boundaries() const {
        //Vector3d lower = _bounds.cwiseLower();
        //Vector3d upper = _bounds.cwiseUpper();
        Set<Geometry> results;
        // TODO - boundary construction
        return results;
    }

    bool CuboidDomain::isEmpty() const {
        return _bounds.isEmpty();
    }

    int CuboidDomain::numDimensions() const {
        return 3;
    }

    VectorXI CuboidDomain::bounds() const {
        return _bounds;
    }

    Domain CuboidDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        if (matrix.isDiagonal()) {
            Interval x_interval = matrix(0, 0) * _bounds.x() + vector.x();
            Interval y_interval = matrix(1, 1) * _bounds.y() + vector.y();
            Interval z_interval = matrix(2, 2) * _bounds.z() + vector.z();
            return new CuboidDomain(Vector3I(x_interval, y_interval, z_interval));
        } else {
            return DomainImplementation::transformed(matrix, vector);
        }
    }
}
