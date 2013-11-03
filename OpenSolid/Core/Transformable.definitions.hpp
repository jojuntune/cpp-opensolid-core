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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Globalization.declarations.hpp>
#include <OpenSolid/Core/LinearTransformation.declarations.hpp>
#include <OpenSolid/Core/Localization.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    template <class TDerived>
    class Transformable
    {
    public:
        const TDerived&
        derived() const;

        typename ScaledAboutPointType<TDerived>::Type
        scaledAbout(const Point<NumDimensions<TDerived>::Value>& originPoint, double scale) const;

        template <class TVector>
        typename TranslatedType<TDerived>::Type
        translated(const EigenBase<TVector>& vector) const;

        typename TranslatedType<TDerived>::Type
        translatedAlong(
            const Axis<NumDimensions<TDerived>::Value>& axis,
            double distance
        ) const;

        typename TransformedAboutPointType<TDerived>::Type
        rotatedAbout(const Point<2>& originPoint, double angle) const;

        typename TransformedAboutPointType<TDerived>::Type
        rotatedAbout(const Axis<3>& axis, double angle) const;

        typename TransformedAboutPointType<TDerived>::Type
        mirroredAbout(const Axis<2>& axis) const;

        typename TransformedAboutPointType<TDerived>::Type
        mirroredAbout(const Plane3d& plane) const;

        typename TransformedAboutPointType<TDerived>::Type
        projectedOnto(const Axis<2>& axis) const;

        typename TransformedAboutPointType<TDerived>::Type
        projectedOnto(const Axis<3>& axis) const;

        typename TransformedAboutPointType<TDerived>::Type
        projectedOnto(const Plane3d& plane) const;

        typename TransformedAboutPointType<TDerived>::Type
        transformed(
            const LinearTransformation<NumDimensions<TDerived>::Value>& transformation
        ) const;

        template <int iNumResultDimensions, int iNumAxes>
        typename TransplantedType<TDerived, iNumResultDimensions>::Type
        transplanted(
            const CoordinateSystem<NumDimensions<TDerived>::Value, iNumAxes>& sourceCoordinateSystem,
            const CoordinateSystem<iNumResultDimensions, iNumAxes>& destinationCoordinateSystem
        ) const;

        template <int iNumResultDimensions>
        typename TransplantedType<TDerived, iNumResultDimensions>::Type
        transplanted(
            const Transplant<NumDimensions<TDerived>::Value, iNumResultDimensions>& transplant
        ) const;

        template <int iNumResultDimensions>
        typename MorphedType<TDerived, iNumResultDimensions>::Type
        morphed(
            const Function<iNumResultDimensions, NumDimensions<TDerived>::Value>& function
        ) const;
    };

    namespace detail
    {
        template <class TTransformable>
        typename ScaledType<TTransformable>::Type
        scaled(const TTransformable& transformable, double scale);

        template <class TTransformable, class TVector>
        typename TranslatedType<TTransformable>::Type
        translated(const TTransformable& transformable, const EigenBase<TVector>& vector);

        template <class TTransformable, class TMatrix>
        typename TransformedType<TTransformable, TMatrix::RowsAtCompileTime>::Type
        transformed(const TTransformable& transformable, const EigenBase<TMatrix>& matrix);

        template <class TTransformable, int iNumResultDimensions>
        typename MorphedType<TTransformable, iNumResultDimensions>::Type
        morphed(
            const TTransformable& transformable,
            const Function<iNumResultDimensions, NumDimensions<TTransformable>::Value>& function
        );
    }

    template <class TDerived, int iNumAxes>
    typename LocalizedType<TDerived, iNumAxes>::Type
    operator/(
        const Transformable<TDerived>& transformable,
        const CoordinateSystem<NumDimensions<TDerived>::Value, iNumAxes>& coordinateSystem
    );

    template <class TDerived, int iNumDimensions>
    typename GlobalizedType<TDerived, iNumDimensions>::Type
    operator*(
        const CoordinateSystem<iNumDimensions, NumDimensions<TDerived>::Value>& coordinateSystem,
        const Transformable<TDerived>& transformable
    );
}

////////// Specializations //////////

namespace opensolid
{
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
    struct ScaledAboutPointType
    {
        typedef typename TranslatedType<
            typename ScaledType<
                typename TranslatedType<
                    TTransformable
                >::Type
            >::Type
        >::Type Type;
    };

    template <class TTransformable>
    struct TransformedAboutPointType
    {
        typedef typename TranslatedType<
            typename TransformedType<
                typename TranslatedType<TTransformable>::Type,
                NumDimensions<TTransformable>::Value
            >::Type
        >::Type Type;
    };

    template <class TTransformable, int iNumResultDimensions>
    struct LocalizedType
    {
        typedef typename TransformedType<
            typename TranslatedType<TTransformable>::Type,
            iNumResultDimensions
        >::Type Type;
    };

    template <class TTransformable, int iNumResultDimensions>
    struct GlobalizedType
    {
        typedef typename TranslatedType<
            typename TransformedType<
                TTransformable,
                iNumResultDimensions
            >::Type
        >::Type Type;
    };

    template <class TTransformable, int iNumResultDimensions>
    struct TransplantedType
    {
        typedef typename TranslatedType<
            typename TransformedType<
                typename TranslatedType<TTransformable>::Type,
                iNumResultDimensions
            >::Type
        >::Type Type;
    };
}
