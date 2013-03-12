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

#include <OpenSolid/Core/DomainImplementation/IntervalDomain.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    IntervalDomain::IntervalDomain(const Interval& interval) : _interval(interval) {
    }

    Set<Geometry> IntervalDomain::boundaries() const {
        Set<Geometry> result;
        result.insert(Geometry::Constant(_interval.lowerBound(), 0));
        result.insert(Geometry::Constant(_interval.upperBound(), 0));
        return result;
    }

    bool IntervalDomain::isEmpty() const {
        return _interval.isEmpty();
    }

    int IntervalDomain::numDimensions() const {
        return 1;
    }

    VectorXI IntervalDomain::bounds() const {
        return _interval.as<VectorXI>();
    }

    Domain IntervalDomain::transformed(const MatrixXd& matrix, const VectorXd& vector) const {
        return new IntervalDomain(matrix.value() + vector.value() * _interval);
    }
}
