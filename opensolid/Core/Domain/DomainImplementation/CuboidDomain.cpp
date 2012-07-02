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

#include <OpenSolid/Core/Datum/Frame.hpp>
#include <OpenSolid/Core/Datum/Plane.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Domain/DomainImplementation/CuboidDomain.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>

namespace opensolid
{
    CuboidDomain::CuboidDomain(const Vector3I& bounds) : _bounds(bounds) {}

    Set<Geometry> CuboidDomain::boundaries() const {
        Vector3d lower = _bounds.cwiseLower();
        Vector3d upper = _bounds.cwiseUpper();
        Set<Geometry> results;
        // TODO - boundary construction
        return results;
    }

    bool CuboidDomain::isEmpty() const {return _bounds.isEmpty();}

    int CuboidDomain::dimensions() const {return 3;}

    VectorXI CuboidDomain::bounds() const {return _bounds;}

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
