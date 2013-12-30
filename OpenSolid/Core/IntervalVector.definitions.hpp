/************************************************************************************
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/IntervalVector.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<IntervalVector<iNumDimensions>>
    {
        typedef IntervalVector<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<IntervalVector<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<IntervalVector<iNumDimensions>, iNumResultDimensions>
    {
        typedef IntervalVector<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<IntervalVector<iNumDimensions>, iNumResultDimensions>
    {
        typedef IntervalVector<iNumResultDimensions> Type;
    };

    template <>
    class IntervalVector<2> :
        public IntervalVectorBase<2>,
        public Transformable<IntervalVector<2>>,
        public Convertible<IntervalVector<2>>
    {
    public:
        IntervalVector(Interval x, Interval y);

        const IntervalVector<2>
        unitOrthogonal() const;
    };

    typedef IntervalVector<2> IntervalVector2d;

    template <>
    class IntervalVector<3> :
        public IntervalVectorBase<3>,
        public Transformable<IntervalVector<3>>,
        public Convertible<IntervalVector<3>>
    {
    public:
        IntervalVector(Interval x, Interval y, Interval z);

        const IntervalVector<3>
        unitOrthogonal() const;

        const IntervalVector<3>
        cross(const Vector<3>& vector) const;

        const IntervalVector<3>
        cross(const IntervalVector<3>& other) const;
    };

    typedef IntervalVector<3> IntervalVector3d;
}
