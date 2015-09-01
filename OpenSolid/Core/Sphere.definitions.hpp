/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Sphere.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Circle.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<Sphere3d>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<Sphere3d>
    {
        static const int Value = 3;
    };

    class Sphere3d :
        public Transformable<Sphere3d, Point<3>>,
        public Convertible<Sphere3d>
    {
    private:
        Point<3> _centerPoint;
        double _radius;
    public:
        Sphere3d();
        
        Sphere3d(const Point<3>& centerPoint, double radius);

        const Point<3>&
        centerPoint() const;

        double
        radius() const;

        double
        volume() const;

        double
        surfaceArea() const;

        Box<3>
        bounds() const;

        bool
        equals(const Sphere3d& other, double precision = 1e-12) const;

        template <class TTransformation>
        Sphere3d
        transformedBy(const TTransformation& transformation) const;

        LineSegment<3>
        projectedOnto(const Axis<3>& axis) const;

        Circle<3>
        projectedOnto(const Plane3d& plane) const;

        Circle<2>
        projectedInto(const Plane3d& plane) const;

        static Sphere3d
        UNIT();
    };
}
