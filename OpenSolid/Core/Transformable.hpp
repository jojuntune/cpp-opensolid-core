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

#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Globalization.hpp>
#include <OpenSolid/Core/Localization.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Transplant.hpp>

namespace opensolid
{
    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    typename ScaledAboutPointType<TDerived>::Type
    Transformable<TDerived>::scaledAbout(
        const Point<NumDimensions<TDerived>::Value>& originPoint,
        double scale
    ) const {
        return detail::translated(
            detail::scaled(
                detail::translated(
                    derived(),
                    -originPoint.vector()
                ),
                scale
            ),
            originPoint.vector()
        );
    }

    template <class TDerived> template <class TVector>
    inline
    typename TranslatedType<TDerived>::Type
    Transformable<TDerived>::translatedBy(const EigenBase<TVector>& vector) const {
        return detail::translated(derived(), vector.derived());
    }
    
    template <class TDerived>
    inline
    typename TranslatedType<TDerived>::Type
    Transformable<TDerived>::translatedAlong(
        const Axis<NumDimensions<TDerived>::Value>& axis,
        double distance
    ) const {
        return detail::translated(derived(), distance * axis.directionVector());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::rotatedAbout(const Point<2>& originPoint, double angle) const {
        return Rotation2d(originPoint, angle)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::rotatedAbout(const Axis<3>& axis, double angle) const {
        return Rotation3d(axis, angle)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::mirroredAbout(const Axis<2>& axis) const {
        return Mirror2d(axis)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::mirroredAbout(const Plane3d& plane) const {
        return Mirror3d(plane)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::projectedOnto(const Axis<2>& axis) const {
        return Projection2d(axis)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::projectedOnto(const Axis<3>& axis) const {
        return Projection3d(axis)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::projectedOnto(const Plane3d& plane) const {
        return Projection3d(plane)(derived());
    }

    template <class TDerived>
    inline
    typename TransformedAboutPointType<TDerived>::Type
    Transformable<TDerived>::transformed(
        const LinearTransformation<NumDimensions<TDerived>::Value>& transformation
    ) const {
        return transformation(derived());
    }

    template <class TDerived>
    template <int iNumResultDimensions, int iNumAxes>
    inline
    typename TransplantedType<TDerived, iNumResultDimensions>::Type
    Transformable<TDerived>::transplanted(
        const CoordinateSystem<NumDimensions<TDerived>::Value, iNumAxes>& sourceCoordinateSystem,
        const CoordinateSystem<iNumResultDimensions, iNumAxes>& destinationCoordinateSystem
    ) const {
        return destinationCoordinateSystem * (derived() / sourceCoordinateSystem);
    }

    template <class TDerived>
    template <int iNumResultDimensions>
    inline
    typename TransplantedType<TDerived, iNumResultDimensions>::Type
    Transformable<TDerived>::transplanted(
        const Transplant<NumDimensions<TDerived>::Value, iNumResultDimensions>& transplant
    ) const {
        return transplant(derived());
    }

    template <class TDerived> template <int iNumResultDimensions>
    inline
    typename MorphedType<TDerived, iNumResultDimensions>::Type
    Transformable<TDerived>::morphedBy(
        const ParametricExpression<
            iNumResultDimensions,
            NumDimensions<TDerived>::Value
        >& morphingExpression
    ) const {
        return detail::morphed(derived(), morphingExpression);
    }

    namespace detail
    {
        template <class TTransformable>
        inline
        typename ScaledType<TTransformable>::Type
        scaled(const TTransformable& transformable, double scale) {
            return ScalingFunction<TTransformable>()(transformable, scale);
        }

        template <class TTransformable, class TVector>
        inline
        typename TranslatedType<TTransformable>::Type
        translated(const TTransformable& transformable, const EigenBase<TVector>& vector) {
            return TranslationFunction<TTransformable>()(transformable, vector.derived());
        }

        template <class TTransformable, class TMatrix>
        inline
        typename TransformedType<TTransformable, TMatrix::RowsAtCompileTime>::Type
        transformed(const TTransformable& transformable, const EigenBase<TMatrix>& matrix) {
            return TransformationFunction<TTransformable, TMatrix::RowsAtCompileTime>()(
                transformable,
                matrix.derived()
            );
        }

        template <class TTransformable, int iNumResultDimensions>
        inline
        typename MorphedType<TTransformable, iNumResultDimensions>::Type
        morphed(
            const TTransformable& transformable,
            const ParametricExpression<
                iNumResultDimensions,
                NumDimensions<TTransformable>::Value
            >& morphingExpression
        ) {
            return MorphingFunction<TTransformable, iNumResultDimensions>()(
                transformable,
                morphingExpression
            );
        }
    }

    template <class TDerived, int iNumAxes>
    inline
    typename LocalizedType<TDerived, iNumAxes>::Type
    operator/(
        const Transformable<TDerived>& transformable,
        const CoordinateSystem<NumDimensions<TDerived>::Value, iNumAxes>& coordinateSystem
    ) {
        return Localization<NumDimensions<TDerived>::Value, iNumAxes>(coordinateSystem)(
            transformable.derived()
        );
    }

    template <class TDerived, int iNumDimensions>
    inline
    typename GlobalizedType<TDerived, iNumDimensions>::Type
    operator*(
        const CoordinateSystem<iNumDimensions, NumDimensions<TDerived>::Value>& coordinateSystem,
        const Transformable<TDerived>& transformable
    ) {
        return Globalization<iNumDimensions, NumDimensions<TDerived>::Value>(coordinateSystem)(
            transformable.derived()
        );
    }
}
