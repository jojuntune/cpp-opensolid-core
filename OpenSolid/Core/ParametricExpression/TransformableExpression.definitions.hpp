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
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TParameter>
        class TransformableExpression<double, TParameter>
        {
        };

        template <class TParameter>
        class TransformableExpression<Vector<double, 2>, TParameter> :
            public Transformable<
                ParametricExpression<Vector<double, 2>, TParameter>,
                Vector<double, 2>
            >
        {
        private:
            const ParametricExpression<Vector<double, 2>, TParameter>&
            derived() const;
        public:
            ParametricExpression<UnitVector<2>, TParameter>
            unitOrthogonal() const;

            template <class TTransformation>
            ParametricExpression<Vector<double, 2>, TParameter>
            transformedBy(const TTransformation& transformation) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            placedOnto(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            projectedOnto(const Axis<2>& axis) const;
        };

        template <class TParameter>
        class TransformableExpression<Vector<double, 3>, TParameter> :
            public Transformable<
                ParametricExpression<Vector<double, 3>, TParameter>,
                Vector<double, 3>
            >
        {
        private:
            const ParametricExpression<Vector<double, 3>, TParameter>&
            derived() const;
        public:
            template <class TTransformation>
            ParametricExpression<Vector<double, 3>, TParameter>
            transformedBy(const TTransformation& transformation) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            projectedInto(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            projectedOnto(const Axis<3>& axis) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            projectedOnto(const Plane3d& plane) const;
        };

        template <class TParameter>
        class TransformableExpression<UnitVector<2>, TParameter> :
            public Transformable<ParametricExpression<UnitVector<2>, TParameter>, Vector<double, 2>>
        {
        private:
            const ParametricExpression<UnitVector<2>, TParameter>&
            derived() const;
        public:
            ParametricExpression<UnitVector<2>, TParameter>
            unitOrthogonal() const;
            
            template <class TTransformation>
            ParametricExpression<UnitVector<2>, TParameter>
            transformedBy(const TTransformation& transformation) const;

            ParametricExpression<UnitVector<3>, TParameter>
            placedOnto(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            projectedOnto(const Axis<2>& axis) const;
        };

        template <class TParameter>
        class TransformableExpression<UnitVector<3>, TParameter> :
            public Transformable<ParametricExpression<UnitVector<3>, TParameter>, Vector<double, 3>>
        {
        private:
            const ParametricExpression<UnitVector<3>, TParameter>&
            derived() const;
        public:
            template <class TTransformation>
            ParametricExpression<UnitVector<3>, TParameter>
            transformedBy(const TTransformation& transformation) const;

            ParametricExpression<Vector<double, 2>, TParameter>
            projectedInto(const Plane3d& plane) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            projectedOnto(const Axis<3>& axis) const;

            ParametricExpression<Vector<double, 3>, TParameter>
            projectedOnto(const Plane3d& plane) const;
        };

        template <class TParameter>
        class TransformableExpression<Point<2>, TParameter> :
            public Transformable<ParametricExpression<Point<2>, TParameter>, Point<2>>
        {
        private:
            const ParametricExpression<Point<2>, TParameter>&
            derived() const;
        public:
            ParametricExpression<double, TParameter>
            distanceTo(const Axis<2>& axis) const;

            ParametricExpression<double, TParameter>
            distanceAlong(const Axis<2>& axis) const;

            template <class TTransformation>
            ParametricExpression<Point<2>, TParameter>
            transformedBy(const TTransformation& transformation) const;

            ParametricExpression<Point<3>, TParameter>
            placedOnto(const Plane3d& plane) const;

            ParametricExpression<Point<2>, TParameter>
            projectedOnto(const Axis<2>& axis) const;
        };

        template <class TParameter>
        class TransformableExpression<Point<3>, TParameter> :
            public Transformable<ParametricExpression<Point<3>, TParameter>, Point<3>>
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

            template <class TTransformation>
            ParametricExpression<Point<3>, TParameter>
            transformedBy(const TTransformation& transformation) const;

            ParametricExpression<Point<2>, TParameter>
            projectedInto(const Plane3d& plane) const;

            ParametricExpression<Point<3>, TParameter>
            projectedOnto(const Axis<3>& axis) const;

            ParametricExpression<Point<3>, TParameter>
            projectedOnto(const Plane3d& plane) const;
        };
    }
}
