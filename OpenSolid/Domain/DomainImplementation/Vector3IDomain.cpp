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

#include <OpenSolid/Domain/DomainImplementation/Vector3IDomain.hpp>

namespace OpenSolid
{
    Vector3IDomain::Vector3IDomain(const Vector3I& bounds) : _bounds(bounds) {}

    Set<Geometry> Vector3IDomain::boundaries() const {
        Set<Geometry> results;
        return results;
    }

    bool Vector3IDomain::isEmpty() const {return _bounds.isEmpty();}

    int Vector3IDomain::dimensions() const {return 3;}

    VectorXI Vector3IDomain::bounds() const {return _bounds;}

    Domain Vector3IDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        if (matrix.isDiagonal()) {
            Interval x_interval = matrix(0, 0) * _bounds.x() + vector.x();
            Interval y_interval = matrix(1, 1) * _bounds.y() + vector.y();
            Interval z_interval = matrix(2, 2) * _bounds.z() + vector.z();
            return new Vector3IDomain(Vector3I(x_interval, y_interval, z_interval));
        } else {
            return DomainImplementation::transformed(matrix, vector);
        }
    }
}
