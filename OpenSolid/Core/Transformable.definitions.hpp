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

#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Quaternion.declarations.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <class TDerived>
    class Transformable<TDerived, Vector<double, 2>>
    {
    private:
        const TDerived&
        derived() const;
    public:
        // To be provided by derived class:
        //   transformedBy(transformation)
        //   projectedOnto(axis) (if meaningful)
        //   placedOnto(plane) (if meaningful)

        TDerived
        rotatedBy(double angle) const;

        TDerived
        rotatedBy(const Quaternion<2>& quaternion) const;

        TDerived
        rotatedBy(const Matrix<double, 2, 2>& rotationMatrix) const;

        TDerived
        relativeTo(const Frame<2>& frame) const;

        TDerived
        placedIn(const Frame<2>& frame) const;

        TDerived
        mirroredAlong(const UnitVector<2>& mirrorDirection) const;

        TDerived
        mirroredAbout(const Axis<2>& axis) const;
    };

    template <class TDerived>
    class Transformable<TDerived, Vector<double, 3>>
    {
    private:
        const TDerived&
        derived() const;
    public:
        // To be provided by derived class:
        //   transformedBy(transformation)
        //   projectedOnto(axis) (if meaningful)
        //   projectedOnto(plane) (if meaningful)
        //   projectedInto(plane) (if meaningful)

        TDerived
        rotatedBy(const Quaternion<3>& quaternion) const;

        TDerived
        rotatedBy(const Matrix<double, 3, 3>& rotationMatrix) const;

        TDerived
        rotatedAbout(const UnitVector<3>& axisDirection, double angle) const;

        TDerived
        rotatedAbout(const Axis<3>& axis, double angle) const;

        TDerived
        relativeTo(const Frame<3>& frame) const;

        TDerived
        placedIn(const Frame<3>& frame) const;

        TDerived
        mirroredAlong(const UnitVector<3>& mirrorDirection) const;

        TDerived
        mirroredAbout(const Plane3d& plane) const;
    };

    template <class TDerived>
    class Transformable<TDerived, Point<2>>
    {
    private:
        const TDerived&
        derived() const;
    public:
        // To be provided by derived class:
        //   transformedBy(transformation)
        //   projectedOnto(axis) (if meaningful)
        //   placedOnto(plane) (if meaningful)

        TDerived
        scaledAbout(const Point<2>& point, double scale) const;

        TDerived
        rotatedAbout(const Point<2>& point, double angle) const;

        TDerived
        rotatedAbout(const Point<2>& point, const Quaternion<2>& quaternion) const;

        TDerived
        rotatedAbout(const Point<2>& point, const Matrix<double, 2, 2>& rotationMatrix) const;

        TDerived
        translatedBy(const Vector<double, 2>& vector) const;

        TDerived
        translatedAlong(const Axis<2>& axis, double distance) const;

        TDerived
        relativeTo(const Frame<2>& frame) const;

        TDerived
        placedIn(const Frame<2>& frame) const;

        TDerived
        mirroredAbout(const Point<2>& point, const UnitVector<2>& mirrorDirection) const;

        TDerived
        mirroredAbout(const Axis<2>& axis) const;
    };

    template <class TDerived>
    class Transformable<TDerived, Point<3>>
    {
    public:
        // To be provided by derived class:
        //   transformedBy(transformation)
        //   projectedOnto(axis) (if meaningful)
        //   projectedOnto(plane) (if meaningful)
        //   projectedInto(plane) (if meaningful)

        const TDerived&
        derived() const;

        TDerived
        scaledAbout(const Point<3>& point, double scale) const;

        TDerived
        rotatedAbout(const Axis<3>& axis, double angle) const;

        TDerived
        rotatedAbout(const Point<3>& point, const Quaternion<3>& quaternion) const;

        TDerived
        rotatedAbout(const Point<3>& point, const Matrix<double, 3, 3>& rotationMatrix) const;

        TDerived
        translatedBy(const Vector<double, 3>& vector) const;

        TDerived
        translatedAlong(const Axis<3>& axis, double distance) const;

        TDerived
        relativeTo(const Frame<3>& frame) const;

        TDerived
        placedIn(const Frame<3>& frame) const;

        TDerived
        mirroredAbout(const Point<3>& point, const UnitVector<3>& mirrorDirection) const;

        TDerived
        mirroredAbout(const Plane3d& plane) const;
    };
}
