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

#include <OpenSolid/Core/Mirror.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformation.definitions.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class MirrorCommon :
            public Transformation<Mirror<iNumDimensions>>
        {
        private:
            Point<iNumDimensions> _point;
            UnitVector<iNumDimensions> _mirrorDirection;
        public:
            MirrorCommon(
                const Point<iNumDimensions>& point,
                const UnitVector<iNumDimensions>& mirrorDirection
            );

            const Point<iNumDimensions>&
            point() const;

            const UnitVector<iNumDimensions>&
            mirrorDirection() const;

            double
            scale() const;

            Handedness
            transform(Handedness handedness) const;

            Point<iNumDimensions>
            transform(const Point<iNumDimensions>& point) const;

            template <class TParameter>
            ParametricExpression<Point<iNumDimensions>, TParameter>
            transform(
                const ParametricExpression<Point<iNumDimensions>, TParameter>& expression
            ) const;

            Vector<double, iNumDimensions>
            transform(const Vector<double, iNumDimensions>& vector) const;

            template <class TParameter>
            ParametricExpression<Vector<double, iNumDimensions>, TParameter>
            transform(
                const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression
            ) const;

            UnitVector<iNumDimensions>
            transform(const UnitVector<iNumDimensions>& unitVector) const;

            template <class TParameter>
            ParametricExpression<UnitVector<iNumDimensions>, TParameter>
            transform(
                const ParametricExpression<UnitVector<iNumDimensions>, TParameter>& expression
            ) const;
        };
    }

    template <>
    class Mirror<2> :
        public detail::MirrorCommon<2>
    {
    public:
        Mirror(const Point<2>& point, const UnitVector<2>& mirrorDirection);

        Mirror(const Axis<2>& axis);
    };

    typedef Mirror<2> Mirror2d;

    template <>
    class Mirror<3> :
        public detail::MirrorCommon<3>
    {
    public:
        Mirror(const Point<3>& point, const UnitVector<3>& mirrorDirection);

        Mirror(const Plane3d& plane);
    };

    typedef Mirror<3> Mirror3d;
}
