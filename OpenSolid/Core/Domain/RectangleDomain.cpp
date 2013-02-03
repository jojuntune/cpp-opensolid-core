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

#include "RectangleDomain.hpp"

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    RectangleDomain::RectangleDomain(const Vector2I& bounds) : _bounds(bounds) {
    }

    Set<Geometry> RectangleDomain::boundaries() const {
        double xLower = _bounds.x().lowerBound();
        double yLower = _bounds.y().lowerBound();
        double xUpper = _bounds.x().upperBound();
        double yUpper = _bounds.y().upperBound();
        Vector2d p0(xLower, yLower);
        Vector2d p1(xLower, yUpper);
        Vector2d p2(xUpper, yUpper);
        Vector2d p3(xUpper, yLower);
        Set<Geometry> results;
        results.insert(LineSegment2d(p0, p1));
        results.insert(LineSegment2d(p1, p2));
        results.insert(LineSegment2d(p2, p3));
        results.insert(LineSegment2d(p3, p0));
        return results;
    }

    bool RectangleDomain::isEmpty() const {
        return _bounds.isEmpty();
    }

    int RectangleDomain::numDimensions() const {
        return 2;
    }

    VectorXI RectangleDomain::bounds() const {
        return _bounds;
    }

    Domain RectangleDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        if (matrix.isDiagonal()) {
            Interval xInterval = matrix(0, 0) * _bounds.x() + vector.x();
            Interval yInterval = matrix(1, 1) * _bounds.y() + vector.y();
            return new RectangleDomain(Vector2I(xInterval, yInterval));
        } else {
            return DomainImplementation::transformed(matrix, vector);
        }
    }
}
