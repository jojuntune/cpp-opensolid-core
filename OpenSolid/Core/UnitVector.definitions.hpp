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

#include <OpenSolid/Core/UnitVector.declarations.hpp>

#include <OpenSolid/Core/Vector.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<UnitVector<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct BoundsType<UnitVector<iNumDimensions>>
    {
        typedef Vector<Interval, iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScaledType<UnitVector<iNumDimensions>>
    {
        typedef Vector<double, iNumDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<UnitVector<iNumDimensions>, iNumResultDimensions>
    {
        typedef Vector<double, iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<
        UnitVector<iNumDimensions>,
        ParametricExpression<Vector<double, iNumResultDimensions>, Vector<double, iNumDimensions>>
    >
    {
        typedef Vector<double, iNumResultDimensions> Type;
    };

    template <>
    class UnitVector<1> :
        public Vector<double, 1>
    {
    public:
        UnitVector();

        explicit
        UnitVector(double x);

        explicit
        UnitVector(const Matrix<double, 1, 1>& components);

        explicit
        UnitVector(const Vector<double, 1>& vector);

        double
        norm();

        double
        squaredNorm() const;

        const UnitVector<1>
        normalized() const;

        static const UnitVector<1>
        i();

        static const UnitVector<1>
        random();
    };

    typedef UnitVector<1> UnitVector1d;
 
    template <>
    class UnitVector<2> :
        public Vector<double, 2>
    {
    public:
        UnitVector();

        UnitVector(double x, double y);

        explicit
        UnitVector(const Matrix<double, 2, 1>& components);

        explicit
        UnitVector(const Vector<double, 2>& vector);

        double
        norm() const;

        double
        squaredNorm() const;

        const UnitVector<2>
        normalized() const;

        const UnitVector<2>
        unitOrthogonal() const;

        static const UnitVector<2>
        i();

        static const UnitVector<2>
        j();

        static const UnitVector<2>
        random();
    };

    typedef UnitVector<2> UnitVector2d;

    template <>
    class UnitVector<3> :
        public Vector<double, 3>
    {
    public:
        UnitVector();

        UnitVector(double x, double y, double z);

        explicit
        UnitVector(const Matrix<double, 3, 1>& components);

        explicit
        UnitVector(const Vector<double, 3>& vector);

        double
        norm() const;

        double
        squaredNorm() const;

        UnitVector<3>
        normalized() const;

        static const UnitVector<3>
        i();

        static const UnitVector<3>
        j();

        static const UnitVector<3>
        k();

        static const UnitVector<3>
        random();
    };

    typedef UnitVector<3> UnitVector3d;

    const UnitVector1d
    operator-(const UnitVector1d& unitVector);

    const UnitVector2d
    operator-(const UnitVector2d& unitVector);

    const UnitVector3d
    operator-(const UnitVector3d& unitVector);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const UnitVector<iNumDimensions>& unitVector);

    template <int iNumDimensions>
    struct BoundsFunction<UnitVector<iNumDimensions>> :
        public BoundsFunction<Vector<double, iNumDimensions>>
    {
    };

    template <int iNumDimensions>
    struct ScalingFunction<UnitVector<iNumDimensions>> :
        public ScalingFunction<Vector<double, iNumDimensions>>
    {
    };

    template <int iNumDimensions>
    struct TranslationFunction<UnitVector<iNumDimensions>>
    {
        const UnitVector<iNumDimensions>&
        operator()(
            const UnitVector<iNumDimensions>& unitVector,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<UnitVector<iNumDimensions>, iNumResultDimensions> :
        public TransformationFunction<Vector<double, iNumDimensions>, iNumResultDimensions>
    {
    };
}
