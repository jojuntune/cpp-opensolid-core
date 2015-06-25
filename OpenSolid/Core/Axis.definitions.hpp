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

#include <OpenSolid/Core/Axis.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/FrameBase.definitions.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/NumDimensions.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<Axis<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class Axis<2> :
        public FrameBase<2, 1>,
        public Convertible<Axis<2>>,
        public Transformable<Axis<2>, 2>
    {
    public:
        Axis();

        Axis(const Point<2>& originPoint, const UnitVector<2>& directionVector);
        
        UnitVector<2>
        directionVector() const;

        UnitVector<2>
        normalVector() const;

        Axis<2>
        flipped() const;

        Axis<2>
        normalAxis() const;
        
        Point<2>
        pointAt(double distance) const;

        Axis<2>
        scaledAbout(const Point<2>& point, double scale) const;

        Axis<2>
        rotatedAbout(const Point<2>& point, const Matrix<double, 2, 2>& rotationMatrix) const;

        using Transformable<Axis<2>, 2>::rotatedAbout;

        Axis<2>
        translatedBy(const Vector<double, 2>& vector) const;

        Axis<2>
        toLocalIn(const Frame<2>& frame) const;

        Axis<2>
        toGlobalFrom(const Frame<2>& frame) const;

        Axis<3>
        toGlobalFrom(const Plane3d& plane) const;

        Axis<2>
        mirroredAbout(const Point<2>& point, const UnitVector<2>& directionVector) const;

        using Transformable<Axis<2>, 2>::mirroredAbout;

        OPENSOLID_CORE_EXPORT
        Axis<2>
        projectedOnto(const Axis<2>& other) const;

        OPENSOLID_CORE_EXPORT
        ParametricExpression<Point<2>, double>
        expression() const;

        static Axis<2>
        x();    

        static Axis<2>
        y();
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> :
        public FrameBase<3, 1>,
        public Convertible<Axis<3>>,
        public Transformable<Axis<3>, 3>
    {
    public:
        Axis();

        Axis(const Point<3>& originPoint, const UnitVector<3>& directionVector);

        UnitVector<3>
        directionVector() const;

        Axis<3>
        flipped() const;

        Plane3d
        normalPlane() const;
        
        bool
        contains(const Point<3>& point, double precision = 1e-12) const;

        Intersection<Axis<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;

        Intersection<Axis<3>, Triangle<3>>
        intersection(const Triangle<3>& triangle, double precision = 1e-12) const;

        Axis<3>
        scaledAbout(const Point<3>& point, double scale) const;

        Axis<3>
        rotatedAbout(const Point<3>& point, const Matrix<double, 3, 3>& rotationMatrix) const;

        using Transformable<Axis<3>, 3>::rotatedAbout;

        Axis<3>
        translatedBy(const Vector<double, 3>& vector) const;

        Axis<3>
        toLocalIn(const Frame<3>& frame) const;

        OPENSOLID_CORE_EXPORT
        Axis<2>
        toLocalIn(const Plane3d& plane) const;

        Axis<3>
        toGlobalFrom(const Frame<3>& frame) const;

        Axis<3>
        mirroredAbout(const Point<3>& point, const UnitVector<3>& directionVector) const;

        using Transformable<Axis<3>, 3>::mirroredAbout;

        OPENSOLID_CORE_EXPORT
        Axis<3>
        projectedOnto(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        ParametricExpression<Point<3>, double>
        expression() const;

        static Axis<3>
        x();

        static Axis<3>
        y();

        static Axis<3>
        z();
    };

    typedef Axis<3> Axis3d;
}
