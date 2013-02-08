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
 
#include <OpenSolid/Core/Domain/DomainConstructors.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Domain/CuboidDomain.hpp>
#include <OpenSolid/Core/Domain/IntervalDomain.hpp>
#include <OpenSolid/Core/Domain/RectangleDomain.hpp>
#include <OpenSolid/Core/Domain/SimplexDomain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    Domain DomainConstructors::UnitInterval() {
        return new IntervalDomain(Interval::Unit());
    }

    Domain DomainConstructors::UnitSquare() {
        return new RectangleDomain(Vector2I::Constant(Interval::Unit()));
    }

    Domain DomainConstructors::UnitCube() {
        return new CuboidDomain(Vector3I::Constant(Interval::Unit()));
    }

    Domain DomainConstructors::UnitTriangle() {
        return new SimplexDomain<2>(Triangle2d::Unit());
    }

    Domain DomainConstructors::UnitTetrahedron() {
        return new SimplexDomain<3>(Tetrahedron3d::Unit());
    }
}
