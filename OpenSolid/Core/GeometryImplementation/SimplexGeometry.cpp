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
 
#include <OpenSolid/Core/GeometryImplementation/SimplexGeometry.hpp>

#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    template <>
    Domain SimplexGeometry<1, 2>::domain() const {
        return Domain::UnitInterval();
    }

    template <>
    Domain SimplexGeometry<1, 3>::domain() const {
        return Domain::UnitTriangle();
    }

    template <>
    Domain SimplexGeometry<1, 4>::domain() const {
        return Domain::UnitTetrahedron();
    }

    template <>
    Domain SimplexGeometry<2, 2>::domain() const {
        return Domain::UnitInterval();
    }

    template <>
    Domain SimplexGeometry<2, 3>::domain() const {
        return Domain::UnitTriangle();
    }

    template <>
    Domain SimplexGeometry<2, 4>::domain() const {
        return Domain::UnitTetrahedron();
    }

    template <>
    Domain SimplexGeometry<3, 2>::domain() const {
        return Domain::UnitInterval();
    }

    template <>
    Domain SimplexGeometry<3, 3>::domain() const {
        return Domain::UnitTriangle();
    }

    template <>
    Domain SimplexGeometry<3, 4>::domain() const {
        return Domain::UnitTetrahedron();
    }

    template <>
    Set<Geometry> SimplexGeometry<1, 2>::boundaries() const {
        Set<Geometry> results;
        results.insert(_simplex.vertex(0));
        results.insert(_simplex.vertex(1));
        return results;
    }

    template <>
    Set<Geometry> SimplexGeometry<2, 2>::boundaries() const {
        Set<Geometry> results;
        results.insert(_simplex.vertex(0));
        results.insert(_simplex.vertex(1));
        return results;
    }

    template <>
    Set<Geometry> SimplexGeometry<3, 2>::boundaries() const {
        Set<Geometry> results;
        results.insert(_simplex.vertex(0));
        results.insert(_simplex.vertex(1));
        return results;
    }

    template <>
    Set<Geometry> SimplexGeometry<1, 3>::boundaries() const {
        assert(false);
        return Set<Geometry>();
    }

    template <>
    Set<Geometry> SimplexGeometry<2, 3>::boundaries() const {
        Set<Geometry> results;
        results.insert(new SimplexGeometry<2, 2>(_simplex.edge(1, 0)));
        results.insert(new SimplexGeometry<2, 2>(_simplex.edge(2, 1)));
        results.insert(new SimplexGeometry<2, 2>(_simplex.edge(0, 2)));
        return results;
    }

    template <>
    Set<Geometry> SimplexGeometry<3, 3>::boundaries() const {
        Set<Geometry> results;
        results.insert(new SimplexGeometry<3, 2>(_simplex.edge(1, 0)));
        results.insert(new SimplexGeometry<3, 2>(_simplex.edge(2, 1)));
        results.insert(new SimplexGeometry<3, 2>(_simplex.edge(0, 2)));
        return results;
    }

    template <>
    Set<Geometry> SimplexGeometry<1, 4>::boundaries() const {
        assert(false);
        return Set<Geometry>();
    }

    template <>
    Set<Geometry> SimplexGeometry<2, 4>::boundaries() const {
        assert(false);
        return Set<Geometry>();
    }

    template <>
    Set<Geometry> SimplexGeometry<3, 4>::boundaries() const {
        Set<Geometry> results;
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(0)));
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(1)));
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(2)));
        results.insert(new SimplexGeometry<3, 3>(_simplex.face(3)));
        return results;
    }
}
