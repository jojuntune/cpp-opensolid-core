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

#include <OpenSolid/Domain/DomainImplementation/Vector2IDomain.hpp>

namespace OpenSolid
{
    Vector2IDomain::Vector2IDomain(const Vector2I& bounds) : _bounds(bounds) {}

    Set<Geometry> Vector2IDomain::boundaries() const {
        double x_lower = _bounds.x().lower();
        double y_lower = _bounds.y().lower();
        double x_upper = _bounds.x().upper();
        double y_upper = _bounds.y().upper();
        Vector2d p0(x_lower, y_lower);
        Vector2d p1(x_lower, y_upper);
        Vector2d p2(x_upper, y_upper);
        Vector2d p3(x_upper, y_lower);
        Set<Geometry> results;
        results.insert(LineSegment2d(p0, p1));
        results.insert(LineSegment2d(p1, p2));
        results.insert(LineSegment2d(p2, p3));
        results.insert(LineSegment2d(p3, p0));
        return results;
    }

    bool Vector2IDomain::isEmpty() const {return _bounds.isEmpty();}

    int Vector2IDomain::dimensions() const {return 2;}

    VectorXI Vector2IDomain::bounds() const {return _bounds;}

    Domain Vector2IDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        if (matrix.isDiagonal()) {
            Interval x_interval = matrix(0, 0) * _bounds.x() + vector.x();
            Interval y_interval = matrix(1, 1) * _bounds.y() + vector.y();
            return new Vector2IDomain(Vector2I(x_interval, y_interval));
        } else {
            return DomainImplementation::transformed(matrix, vector);
        }
    }
}
