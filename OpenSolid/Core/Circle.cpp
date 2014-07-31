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

#include <OpenSolid/Core/Circle.hpp>

#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    Circle2d::Circle(
        double radius,
        WindingDirection windingDirection,
        const Point2d& firstPoint,
        const Point2d& secondPoint
    ) : _radius(radius) {

        if (radius <= Zero()) {
            throw Error(new PlaceholderError());
        }

        Vector2d displacementVector = secondPoint - firstPoint;
        double halfDistance = displacementVector.norm() / 2;

        if (halfDistance == Zero()) {
            // Points are coincident
            throw Error(new PlaceholderError());
        }

        if (halfDistance - radius > Zero()) {
            // Points are too far apart
            throw Error(new PlaceholderError());
        }

        Vector2d sidewaysDirection = displacementVector.unitOrthogonal();
        if (windingDirection == COUNTERCLOCKWISE) {
            sidewaysDirection = -sidewaysDirection;
        }

        double sidewaysDistance = 0.0;
        if (halfDistance - radius == Zero()) {
            sidewaysDistance = radius;
        } else {
            sidewaysDistance = sqrt(halfDistance * halfDistance - radius * radius);
        }

        _centerPoint = firstPoint + displacementVector / 2 + sidewaysDistance * sidewaysDirection;
    }

    Circle2d::Circle(
        const Point2d& firstPoint,
        const Point2d& secondPoint,
        const Point2d& thirdPoint
    ) : _radius(0.0) {

        double a = (secondPoint - firstPoint).norm();
        double b = (thirdPoint - secondPoint).norm();
        double c = (firstPoint - thirdPoint).norm();
        double s = (a + b + c) / 2.0;

        if(s - a <= Zero() || s - b <= Zero() || s - c <= Zero()) {
            // Points are collinear
            throw Error(new PlaceholderError());
        }

        double a2 = a * a;
        double b2 = b * b;
        double c2 = c * c;
        double t1 = a2 * (b2 + c2 - a2);
        double t2 = b2 * (c2 + a2 - b2);
        double t3 = c2 * (a2 + b2 - c2);
        double sum = t1 + t2 + t3;
        t1 /= sum;
        t2 /= sum;
        t3 /= sum;

        _centerPoint = Point2d(
            t1 * thirdPoint.components() +
            t2 * firstPoint.components() +
            t3 * secondPoint.components()
        );

        double firstRadius = (firstPoint - _centerPoint).norm();
        double secondRadius = (secondPoint - _centerPoint).norm();
        double thirdRadius = (thirdPoint - _centerPoint).norm();
        _radius = (firstRadius + secondRadius + thirdRadius) / 3.0;
        
        assert(_radius - firstRadius == Zero());
        assert(_radius - secondRadius == Zero());
        assert(_radius - thirdRadius == Zero());
    }

    Circle3d::Circle(
        const UnitVector3d& normalVector,
        double radius,
        const Point3d& firstPoint,
        const Point3d& secondPoint
    ) : _normalVector(normalVector),
        _radius(0.0) {

        Plane3d plane(firstPoint + 0.5 * (secondPoint - firstPoint), normalVector);

        if (!plane.contains(firstPoint) || !plane.contains(secondPoint)) {
            throw Error(new PlaceholderError());
        }

        PlanarCoordinateSystem3d planarCoordinateSystem = plane.coordinateSystem();
        Circle2d circle2d(
            radius,
            COUNTERCLOCKWISE,
            firstPoint / planarCoordinateSystem,
            secondPoint / planarCoordinateSystem
        );
        _centerPoint = planarCoordinateSystem * circle2d.centerPoint();
        _radius = circle2d.radius();
    }

    Circle3d::Circle(
        const Point3d& firstPoint,
        const Point3d& secondPoint,
        const Point3d& thirdPoint
    ) : _radius(0.0) {

        Vector3d firstLeg = secondPoint - firstPoint;
        Vector3d secondLeg = thirdPoint - secondPoint;
        _normalVector = firstLeg.cross(secondLeg).normalized();
        
        if (_normalVector.isZero()) {
            throw Error(new PlaceholderError());
        }
        
        Plane3d plane(secondPoint, _normalVector);
        PlanarCoordinateSystem3d planarCoordinateSystem = plane.coordinateSystem();
        Circle2d circle2d(
            firstPoint / planarCoordinateSystem,
            secondPoint / planarCoordinateSystem,
            thirdPoint / planarCoordinateSystem
        );
        _centerPoint = planarCoordinateSystem * circle2d.centerPoint();
        _radius = circle2d.radius();
    }
}
