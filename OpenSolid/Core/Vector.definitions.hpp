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

#include <OpenSolid/Core/Vector.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/IntervalVector.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<Vector<iNumDimensions>>
    {
        typedef IntervalVector<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<Vector<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Vector<iNumDimensions>, iNumResultDimensions>
    {
        typedef Vector<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Vector<iNumDimensions>, iNumResultDimensions>
    {
        typedef Vector<iNumResultDimensions> Type;
    };

    template <>
    class Vector<2> :
        public VectorBase<2>,
        public Transformable<Vector<2>>,
        public Convertible<Vector<2>>
    {
    public:
        Vector(double x, double y);

        const Vector<2>
        unitOrthogonal() const;
    };

    typedef Vector<2> Vector2d;

    template <>
    class Vector<3> :
        public VectorBase<3>,
        public Transformable<Vector<3>>,
        public Convertible<Vector<3>>
    {
    public:
        Vector(double x, double y, double z);

        const Vector<3>
        cross(const Vector<3>& other) const;

        const Vector<3>
        unitOrthogonal() const;
    };

    typedef Vector<3> Vector3d;

    template <int iNumDimensions>
    const bool
    operator==(const Vector<iNumDimensions>& vector, Zero zero);

    template <int iNumDimensions>
    const bool
    operator!=(const Vector<iNumDimensions>& vector, Zero zero);

    template <int iNumDimensions>
    const Vector<iNumDimensions>
    operator*(double scale, const Vector<iNumDimensions>& vector);

    template <int iNumDimensions>
    const Vector<iNumDimensions>
    operator*(const Vector<iNumDimensions>& vector, double scale);

    template <int iNumDimensions>
    const Vector<iNumDimensions>
    operator/(const Vector<iNumDimensions>& vector, double divisor);

    template <int iNumDimensions>
    const Vector<iNumDimensions>
    operator+(
        const Vector<iNumDimensions>& firstVector,
        const Vector<iNumDimensions>& secondVector
    );

    template <int iNumDimensions>
    const Vector<iNumDimensions>
    operator-(
        const Vector<iNumDimensions>& firstVector,
        const Vector<iNumDimensions>& secondVector
    );

    template <int iNumDimensions>
    struct EqualityFunction<Vector<iNumDimensions>>
    {
        const bool
        operator()(
            const Vector<iNumDimensions>& firstVector,
            const Vector<iNumDimensions>& secondVector,
            double precision
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Vector<iNumDimensions>>
    {
        const IntervalVector<iNumDimensions>
        operator()(const Vector<iNumDimensions>& vector) const;
    };
}
