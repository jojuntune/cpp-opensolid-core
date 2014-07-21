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

#include <OpenSolid/Core/Vector.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector/DoubleVectorBase.definitions.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.definitions.hpp>

#include <ostream>

namespace opensolid
{
    template <class TScalar, int iNumDimensions>
    struct BoundsType<Vector<TScalar, iNumDimensions>>
    {
        typedef Vector<Interval, iNumDimensions> Type;
    };

    template <class TScalar, int iNumDimensions>
    struct NumDimensions<Vector<TScalar, iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <class TScalar, int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Vector<TScalar, iNumDimensions>, iNumResultDimensions>
    {
        typedef Vector<TScalar, iNumResultDimensions> Type;
    };

    template <>
    class Vector<double, 1> :
        public detail::DoubleVectorBase<1>,
        public Transformable<Vector<double, 1>>,
        public Convertible<Vector<double, 1>>
    {
    public:
        Vector();

        explicit
        Vector(double value);

        explicit
        Vector(const Matrix<double, 1, 1>& components);

        static const UnitVector<1>
        unitRandom();

        static const UnitVector<1>
        unitX();
    };

    typedef Vector<double, 1> Vector1d;

    template <>
    class Vector<double, 2> :
        public detail::DoubleVectorBase<2>,
        public Transformable<Vector<double, 2>>,
        public Convertible<Vector<double, 2>>
    {
    public:
        Vector();

        Vector(double x, double y);

        explicit
        Vector(const Matrix<double, 2, 1>& components);

        const UnitVector<2>
        unitOrthogonal() const;

        static const UnitVector<2>
        unitRandom();

        static const UnitVector<2>
        unitX();

        static const UnitVector<2>
        unitY();
    };

    typedef Vector<double, 2> Vector2d;

    template <>
    class Vector<double, 3> :
        public detail::DoubleVectorBase<3>,
        public Transformable<Vector<double, 3>>,
        public Convertible<Vector<double, 3>>
    {
    public:
        Vector();

        Vector(double x, double y, double z);

        explicit
        Vector(const Matrix<double, 3, 1>& components);

        const Vector<double, 3>
        cross(const Vector<double, 3>& other) const;

        const Vector<Interval, 3>
        cross(const Vector<Interval, 3>& intervalVector) const;

        const UnitVector<3>
        unitOrthogonal() const;

        static const UnitVector<3>
        unitRandom();

        static const UnitVector<3>
        unitX();

        static const UnitVector<3>
        unitY();

        static const UnitVector<3>
        unitZ();
    };

    typedef Vector<double, 3> Vector3d;

    template <>
    class Vector<Interval, 1> :
        public detail::IntervalVectorBase<1>,
        public Transformable<Vector<Interval, 1>>,
        public Convertible<Vector<Interval, 1>>
    {
    public:
        Vector();

        explicit
        Vector(const Matrix<Interval, 1, 1>& components);

        explicit
        Vector(Interval x);
    };

    typedef Vector<Interval, 1> IntervalVector1d;

    template <>
    class Vector<Interval, 2> :
        public detail::IntervalVectorBase<2>,
        public Transformable<Vector<Interval, 2>>,
        public Convertible<Vector<Interval, 2>>
    {
    public:
        Vector();

        explicit
        Vector(const Matrix<Interval, 2, 1>& components);

        Vector(Interval x, Interval y);
    };

    typedef Vector<Interval, 2> IntervalVector2d;

    template <>
    class Vector<Interval, 3> :
        public detail::IntervalVectorBase<3>,
        public Transformable<Vector<Interval, 3>>,
        public Convertible<Vector<Interval, 3>>
    {
    public:
        Vector();

        Vector(Interval x, Interval y, Interval z);

        explicit
        Vector(const Matrix<Interval, 3, 1>& components);

        const Vector<Interval, 3>
        cross(const Vector<double, 3>& other) const;

        const Vector<Interval, 3>
        cross(const Vector<Interval, 3>& other) const;
    };

    typedef Vector<Interval, 3> IntervalVector3d;

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() * TSecondScalar()), iNumDimensions>
    operator*(TFirstScalar scale, const Vector<TSecondScalar, iNumDimensions>& vector);

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() * TSecondScalar()), iNumDimensions>
    operator*(const Vector<TFirstScalar, iNumDimensions>& vector, TSecondScalar scale);

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() / TSecondScalar()), iNumDimensions>
    operator/(const Vector<TFirstScalar, iNumDimensions>& vector, TSecondScalar divisor);

    template <class TScalar, int iNumDimensions>
    const Vector<TScalar, iNumDimensions>
    operator-(const Vector<TScalar, iNumDimensions>& vector);

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() + TSecondScalar()), iNumDimensions>
    operator+(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    );

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() - TSecondScalar()), iNumDimensions>
    operator-(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    );

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Vector<double, iNumDimensions>& vector);

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Vector<Interval, iNumDimensions>& vector);

    template <int iNumDimensions>
    struct EqualityFunction<Vector<double, iNumDimensions>>
    {
        bool
        operator()(
            const Vector<double, iNumDimensions>& firstVector,
            const Vector<double, iNumDimensions>& secondVector,
            double precision
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Vector<double, iNumDimensions>>
    {
        const Vector<Interval, iNumDimensions>
        operator()(const Vector<double, iNumDimensions>& vector) const;
    };

    template <int iNumDimensions>
    struct BoundsFunction<Vector<Interval, iNumDimensions>>
    {
        const Vector<Interval, iNumDimensions>&
        operator()(const Vector<Interval, iNumDimensions>& vector) const;
    };

    template <class TScalar, int iNumDimensions>
    struct ScalingFunction<Vector<TScalar, iNumDimensions>>
    {
        const Vector<TScalar, iNumDimensions>
        operator()(
            const Vector<TScalar, iNumDimensions>& vector,
            const Point<iNumDimensions>& originPoint,
            double scale
        ) const;
    };

    template <class TScalar, int iNumDimensions>
    struct TranslationFunction<Vector<TScalar, iNumDimensions>>
    {
        const Vector<TScalar, iNumDimensions>&
        operator()(
            const Vector<TScalar, iNumDimensions>& vector,
            const Vector<double, iNumDimensions>& translationVector
        ) const;
    };

    template <class TScalar, int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Vector<TScalar, iNumDimensions>, iNumResultDimensions>
    {
        const Vector<TScalar, iNumResultDimensions>
        operator()(
            const Vector<TScalar, iNumDimensions>& vector,
            const Point<iNumDimensions>& originPoint,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& transformationMatrix,
            const Point<iNumResultDimensions>& destinationPoint
        ) const;
    };
}
