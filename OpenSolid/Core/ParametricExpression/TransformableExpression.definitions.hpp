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

#include <OpenSolid/Core/ParametricExpression/TransformableExpression.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TParameter>
        class TransformableExpression<double, TParameter>
        {
        };

        template <class TParameter>
        class TransformableExpression<Vector<double, 2>, TParameter>
        {
        private:
            const ParametricExpression<Vector<double, 2>, TParameter>&
            derived() const;
        public:
            ParametricExpression<Vector<double, 2>, TParameter>
            rotatedBy(double angle) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            rotatedBy(const Matrix<double, 2, 2>& rotationMatrix) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            toLocalIn(const Frame<2>& frame) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            toGlobalFrom(const Frame<2>& frame) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            toGlobalFrom(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            projectedOnto(const Axis<2>& axis) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            mirroredAlong(const UnitVector<2>& mirrorDirection) const;
        };

        template <class TParameter>
        class TransformableExpression<Vector<double, 3>, TParameter>
        {
        private:
            const ParametricExpression<Vector<double, 3>, TParameter>&
            derived() const;
        public:
            ParametricExpression<Vector<double, 3>, TParameter>
            rotatedBy(const Matrix<double, 3, 3>& rotationMatrix) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            rotatedAbout(const UnitVector<3>& directionVector, double angle) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            toLocalIn(const Frame<3>& frame) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            toLocalIn(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            toGlobalFrom(const Frame<3>& frame) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            projectedOnto(const Axis<3>& axis) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            projectedOnto(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            mirroredAlong(const UnitVector<3>& mirrorDirection) const;
        };

        template <class TParameter>
        class TransformableExpression<Point<2>, TParameter> :
            public Transformable<ParametricExpression<Point<2>, TParameter>, 2>
        {
        private:
            const ParametricExpression<Point<2>, TParameter>&
            derived() const;
        public:
            ParametricExpression<double, TParameter>
            distanceTo(const Axis<2>& axis) const;

            ParametricExpression<double, TParameter>
            distanceAlong(const Axis<2>& axis) const;

            ParametricExpression<Point<2>, TParameter>
            scaledAbout(const Point<2>& other, double scale) const;

            ParametricExpression<Point<2>, TParameter>
            rotatedAbout(const Point<2>& other, const Matrix<double, 2, 2>& rotationMatrix) const;

            using Transformable<ParametricExpression<Point<2>, TParameter>, 2>::rotatedAbout;

            ParametricExpression<Point<2>, TParameter>
            translatedBy(const Vector<double, 2>& vector) const;

            ParametricExpression<Point<2>, TParameter>
            toLocalIn(const Frame<2>& frame) const;

            ParametricExpression<Point<2>, TParameter>
            toGlobalFrom(const Frame<2>& frame) const;

            ParametricExpression<Point<3>, TParameter>
            toGlobalFrom(const Plane3d& plane) const;

            ParametricExpression<Point<2>, TParameter>
            projectedOnto(const Axis<2>& axis) const;

            ParametricExpression<Point<2>, TParameter>
            mirroredAbout(const Point<2>& point, const UnitVector<2>& mirrorDirection) const;

            using Transformable<ParametricExpression<Point<2>, TParameter>, 2>::mirroredAbout;
        };

        template <class TParameter>
        class TransformableExpression<Point<3>, TParameter> :
            public Transformable<ParametricExpression<Point<3>, TParameter>, 3>
        {
        private:
            const ParametricExpression<Point<3>, TParameter>&
            derived() const;
        public:
            ParametricExpression<double, TParameter>
            squaredDistanceTo(const Axis<3>& axis) const;

            ParametricExpression<double, TParameter>
            distanceTo(const Axis<3>& axis) const;

            ParametricExpression<double, TParameter>
            distanceAlong(const Axis<3>& axis) const;

            ParametricExpression<double, TParameter>
            distanceTo(const Plane3d& plane) const;

            ParametricExpression<Point<3>, TParameter>
            scaledAbout(const Point<3>& other, double scale) const;

            ParametricExpression<Point<3>, TParameter>
            rotatedAbout(const Point<3>& other, const Matrix<double, 3, 3>& rotationMatrix) const;

            using Transformable<ParametricExpression<Point<3>, TParameter>, 3>::rotatedAbout;

            ParametricExpression<Point<3>, TParameter>
            translatedBy(const Vector<double, 3>& vector) const;

            ParametricExpression<Point<3>, TParameter>
            toLocalIn(const Frame<3>& frame) const;

            ParametricExpression<Point<3>, TParameter>
            toGlobalFrom(const Frame<3>& frame) const;

            ParametricExpression<Point<2>, TParameter>
            toLocalIn(const Plane3d& plane) const;

            ParametricExpression<Point<3>, TParameter>
            projectedOnto(const Axis<3>& axis) const;

            ParametricExpression<Point<3>, TParameter>
            projectedOnto(const Plane3d& plane) const;

            ParametricExpression<Point<3>, TParameter>
            mirroredAbout(const Point<3>& point, const UnitVector<3>& mirrorDirection) const;

            using Transformable<ParametricExpression<Point<3>, TParameter>, 3>::mirroredAbout;
        };
    }
}
