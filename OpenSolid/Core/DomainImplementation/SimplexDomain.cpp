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

#include <OpenSolid/Core/DomainImplementation/SimplexDomain.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    template <>
    Set<Geometry> SimplexDomain<1>::boundaries() const {
        Set<Geometry> results;
        results.insert(Geometry::Constant(_simplex.vertex(0), 0));
        results.insert(Geometry::Constant(_simplex.vertex(1), 0));
        return results;
    }

    template <>
    Set<Geometry> SimplexDomain<2>::boundaries() const {
        Set<Geometry> results;
        results.insert(Geometry(_simplex.edge(1, 0)));
        results.insert(Geometry(_simplex.edge(2, 1)));
        results.insert(Geometry(_simplex.edge(0, 2)));
        return results;
    }

    template <>
    Set<Geometry> SimplexDomain<3>::boundaries() const {
        Set<Geometry> results;
        results.insert(Geometry(_simplex.face(0)));
        results.insert(Geometry(_simplex.face(1)));
        results.insert(Geometry(_simplex.face(2)));
        results.insert(Geometry(_simplex.face(3)));
        return results;
    }
}
