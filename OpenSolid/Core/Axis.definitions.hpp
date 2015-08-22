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
#include <OpenSolid/Core/Handedness.definitions.hpp>
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
    namespace detail
    {
        template <int iNumDimensions>
        class AxisBase :
            public FrameBase<iNumDimensions, 1>,
            public Convertible<Axis<iNumDimensions>>,
            public Transformable<Axis<iNumDimensions>, Point<iNumDimensions>>
        {
        protected:
            AxisBase();

            AxisBase(
                const Point<iNumDimensions>& originPoint,
                const UnitVector<iNumDimensions>& directionVector
            );
        public:
            UnitVector<iNumDimensions>
            directionVector() const;
        
            Point<iNumDimensions>
            pointAt(double distance) const;

            OPENSOLID_CORE_EXPORT
            ParametricExpression<Point<iNumDimensions>, double>
            expression() const;
        }; 
    }

    template <int iNumDimensions>
    struct NumDimensions<Axis<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class Axis<2> :
        public detail::AxisBase<2>
    {
    private:
        Handedness _handedness;
    public:
        Axis();

        Axis(const Point<2>& originPoint, const UnitVector<2>& directionVector);

        Axis(
            const Point<2>& originPoint,
            const UnitVector<2>& directionVector,
            Handedness handedness
        );

        Handedness
        handedness() const;

        UnitVector<2>
        normalVector() const;

        Axis<2>
        reversed() const;

        Axis<2>
        normalAxis() const;

        template <class TTransformation>
        Axis<2>
        transformedBy(const TTransformation& transformation) const;

        Axis<2>
        projectedOnto(const Axis<2>& other) const;

        Axis<3>
        placedOnto(const Plane3d& plane) const;

        static Axis<2>
        X();    

        static Axis<2>
        Y();
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> :
        public detail::AxisBase<3>
    {
    public:
        Axis();

        Axis(const Point<3>& originPoint, const UnitVector<3>& directionVector);

        Axis<3>
        reversed() const;

        Plane3d
        normalPlane() const;

        Intersection<Axis<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;

        Intersection<Axis<3>, Triangle<3>>
        intersection(const Triangle<3>& triangle, double precision = 1e-12) const;

        template <class TTransformation>
        Axis<3>
        transformedBy(const TTransformation& transformation) const;

        Axis<3>
        projectedOnto(const Axis<3>& other) const;

        Axis<3>
        projectedOnto(const Plane3d& plane) const;

        Axis<2>
        projectedInto(const Plane3d& plane) const;

        static Axis<3>
        X();

        static Axis<3>
        Y();

        static Axis<3>
        Z();
    };

    typedef Axis<3> Axis3d;
}
