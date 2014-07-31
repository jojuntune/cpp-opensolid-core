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
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <>
    struct NumDimensions<int>
    {
        static const int Value = 1;
    };

    template <>
    struct NumDimensions<double>
    {
        static const int Value = 1;
    };

    template <>
    struct NumDimensions<Interval>
    {
        static const int Value = 1;
    };

    template <class TTransformable>
    struct ScaledType
    {
        typedef TTransformable Type;
    };

    template <class TTransformable>
    struct TranslatedType
    {
        typedef TTransformable Type;
    };

    template <class TTransformable, int iNumResultDimensions>
    struct TransformedType
    {
        static_assert(
            iNumResultDimensions == NumDimensions<TTransformable>::Value,
            "Must specialize TransformedType<TTransformable, iNumResultDimensions> "
            "when transforming into a different number of dimensions"
        );

        typedef TTransformable Type;
    };

    template <class TTransformable, int iNumResultDimensions>
    struct MorphedType
    {
        static_assert(
            iNumResultDimensions == NumDimensions<TTransformable>::Value,
            "Must specialize MorphedType<TTransformable, iNumResultDimensions> "
            "when morphing into a different number of dimensions"
        );

        typedef TTransformable Type;
    };

    template <class TTransformable>
    struct RotatedType
    {
        typedef typename TransformedType<
            TTransformable,
            NumDimensions<TTransformable>::Value
        >::Type Type;
    };

    template <class TTransformable>
    struct MirroredType
    {
        typedef typename TransformedType<
            TTransformable,
            NumDimensions<TTransformable>::Value
        >::Type Type;
    };

    template <class TTransformable, class TDatum>
    struct ProjectedType
    {
        typedef typename TransformedType<
            TTransformable,
            NumDimensions<TTransformable>::Value
        >::Type Type;
    };

    template <class TTransformable, class TCoordinateSystem>
    struct LocalizedType
    {
        typedef typename TransformedType<
            TTransformable,
            TCoordinateSystem::NumAxes
        >::Type Type;
    };

    template <class TTransformable, class TCoordinateSystem>
    struct GlobalizedType
    {
        typedef typename TransformedType<
            TTransformable,
            TCoordinateSystem::NumDimensions
        >::Type Type;
    };

    template <class TDerived>
    class Transformable
    {
    public:
        const TDerived&
        derived() const;

        typename ScaledType<TDerived>::Type
        scaledAbout(const Point<NumDimensions<TDerived>::Value>& originPoint, double scale) const;

        typename TranslatedType<TDerived>::Type
        translatedBy(const Vector<double, NumDimensions<TDerived>::Value>& vector) const;

        typename TranslatedType<TDerived>::Type
        translatedAlong(
            const Axis<NumDimensions<TDerived>::Value>& axis,
            double distance
        ) const;

        typename RotatedType<TDerived>::Type
        rotatedAbout(const Point<2>& originPoint, double angle) const;

        typename RotatedType<TDerived>::Type
        rotatedAbout(const Axis<3>& axis, double angle) const;

        typename MirroredType<TDerived>::Type
        mirroredAbout(const Axis<2>& axis) const;

        typename MirroredType<TDerived>::Type
        mirroredAbout(const Plane3d& plane) const;

        typename ProjectedType<TDerived, Axis<NumDimensions<TDerived>::Value>>::Type
        projectedOnto(const Axis<NumDimensions<TDerived>::Value>& axis) const;

        typename ProjectedType<TDerived, Plane3d>::Type
        projectedOnto(const Plane3d& plane) const;

        template <int iNumResultDimensions>
        typename TransformedType<TDerived, iNumResultDimensions>::Type
        transformed(
            const Point<NumDimensions<TDerived>::Value>& originPoint,
            const Matrix<
                double,
                iNumResultDimensions,
                NumDimensions<TDerived>::Value
            >& transformationMatrix,
            const Point<iNumResultDimensions>& destinationPoint
        ) const;

        template <int iNumResultDimensions>
        typename MorphedType<TDerived, iNumResultDimensions>::Type
        morphedBy(
            const ParametricExpression<
                iNumResultDimensions,
                NumDimensions<TDerived>::Value
            >& morphingExpression
        ) const;
    };

    template <class TTransformable>
    struct RotationFunction
    {
        typename RotatedType<TTransformable>::Type
        operator()(
            const TTransformable& transformable,
            const Point<NumDimensions<TTransformable>::Value>& originPoint,
            const Matrix<
                double,
                NumDimensions<TTransformable>::Value,
                NumDimensions<TTransformable>::Value
            >& rotationMatrix
        ) const;
    };

    template <class TTransformable>
    struct MirrorFunction
    {
        typename MirroredType<TTransformable>::Type
        operator()(
            const TTransformable& transformable,
            const Point<NumDimensions<TTransformable>::Value>& originPoint,
            const UnitVector<NumDimensions<TTransformable>::Value>& normalVector
        ) const;
    };

    template <class TTransformable>
    struct ProjectionFunction<TTransformable, Axis<NumDimensions<TTransformable>::Value>>
    {
        typename ProjectedType<TTransformable, Axis<NumDimensions<TTransformable>::Value>>::Type
        operator()(
            const TTransformable& transformable,
            const Axis<NumDimensions<TTransformable>::Value>& axis
        ) const;
    };

    template <class TTransformable>
    struct ProjectionFunction<TTransformable, Plane3d>
    {
        typename ProjectedType<TTransformable, Plane3d>::Type
        operator()(const TTransformable& transformable, const Plane3d& plane) const;
    };

    template <class TTransformable, class TCoordinateSystem>
    struct LocalizationFunction
    {
        typename LocalizedType<TTransformable, TCoordinateSystem>::Type
        operator()(
            const TTransformable& transformable,
            const TCoordinateSystem& coordinateSystem
        ) const;
    };

    template <class TTransformable, class TCoordinateSystem>
    struct GlobalizationFunction
    {
        typename GlobalizedType<TTransformable, TCoordinateSystem>::Type
        operator()(
            const TTransformable& transformable,
            const TCoordinateSystem& coordinateSystem
        ) const;
    };

    template <class TTransformable>
    typename ScaledType<TTransformable>::Type
    scaled(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        double scale
    );

    template <class TTransformable>
    typename TranslatedType<TTransformable>::Type
    translated(
        const TTransformable& transformable,
        const Vector<double, NumDimensions<TTransformable>::Value>& vector
    );

    template <class TTransformable, int iNumResultDimensions>
    typename TransformedType<TTransformable, iNumResultDimensions>::Type
    transformed(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const Matrix<
            double,
            iNumResultDimensions,
            NumDimensions<TTransformable>::Value
        >& transformationMatrix,
        const Point<iNumResultDimensions>& destinationPoint
    );

    template <class TTransformable, int iNumResultDimensions>
    typename MorphedType<TTransformable, iNumResultDimensions>::Type
    morphed(
        const TTransformable& transformable,
        const ParametricExpression<
            iNumResultDimensions,
            NumDimensions<TTransformable>::Value
        >& morphingExpression
    );

    template <class TTransformable>
    typename RotatedType<TTransformable>::Type
    rotated(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const Matrix<
            double,
            NumDimensions<TTransformable>::Value,
            NumDimensions<TTransformable>::Value
        >& rotationMatrix
    );

    template <class TTransformable>
    typename MirroredType<TTransformable>::Type
    mirrored(
        const TTransformable& transformable,
        const Point<NumDimensions<TTransformable>::Value>& originPoint,
        const UnitVector<NumDimensions<TTransformable>::Value>& normalVector
    );

    template <class TTransformable>
    typename ProjectedType<TTransformable, Axis<NumDimensions<TTransformable>::Value>>::Type
    projected(
        const TTransformable& transformable,
        const Axis<NumDimensions<TTransformable>::Value>& axis
    );

    template <class TTransformable>
    typename ProjectedType<TTransformable, Plane3d>::Type
    projected(const TTransformable& transformable, const Plane3d& plane);

    template <class TTransformable, class TCoordinateSystem>
    typename LocalizedType<TTransformable, TCoordinateSystem>::Type
    localized(const TTransformable& transformable, const TCoordinateSystem& coordinateSystem);

    template <class TTransformable, class TCoordinateSystem>
    typename GlobalizedType<TTransformable, TCoordinateSystem>::Type
    globalized(const TTransformable& transformable, const TCoordinateSystem& coordinateSystem);
}
