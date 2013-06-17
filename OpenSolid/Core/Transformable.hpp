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

#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Transplant.hpp>
#include <OpenSolid/Core/Localization.hpp>
#include <OpenSolid/Core/Globalization.hpp>

namespace opensolid
{
    template <class TDerived>
    inline const TDerived&
    Transformable<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::scaledAbout(
        const Point<NumDimensions<TDerived>::Value>& originPoint,
        double scale
    ) const {
        if (originPoint.isOrigin()) {
            return scaling(derived(), scale);
        } else {
            return translation(
                scaling(
                    translation(
                        derived(),
                        -originPoint.vector()
                    ),
                    scale
                ),
                originPoint.vector()
            );
        }
    }

    template <class TDerived> template <class TVector>
    inline TDerived
    Transformable<TDerived>::translated(const EigenBase<TVector>& vector) const {
        return translation(derived(), vector.derived());
    }
    
    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::translatedAlong(
        const Datum<NumDimensions<TDerived>::Value, 1>& axis,
        double distance
    ) const {
        return translation(derived(), distance * axis.basisVector().normalized());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::rotatedAbout(const Point<2>& originPoint, double angle) const {
        return Rotation2d(originPoint, angle)(derived());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::rotatedAbout(const Datum<3, 1>& axis, double angle) const {
        return Rotation3d(axis, angle)(derived());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::rotated(
        const Rotation<NumDimensions<TDerived>::Value>& rotation
    ) const {
        return rotation(derived());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::mirroredAbout(const MirrorDatumType& datum) const {
        return Mirror<NumDimensions<TDerived>::Value>(datum)(derived());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::mirrored(const Mirror<NumDimensions<TDerived>::Value>& mirror) const {
        return mirror(derived());
    }

    template <class TDerived> template <int iNumAxes>
    inline TDerived
    Transformable<TDerived>::projectedOnto(
        const Datum<NumDimensions<TDerived>::Value, iNumAxes>& datum
    ) const {
        return Projection<NumDimensions<TDerived>::Value>(datum)(derived());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::projected(
        const Projection<NumDimensions<TDerived>::Value>& projection
    ) const {
        return projection(derived());
    }

    template <class TDerived>
    template <int iNumDestinationDimensions, int iNumAxes>
    inline typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
    Transformable<TDerived>::transplanted(
        const Datum<NumDimensions<TDerived>::Value, iNumAxes>& sourceDatum,
        const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
    ) const {
        return localizedTo(sourceDatum).globalizedFrom(destinationDatum);
    }

    template <class TDerived>
    template <int iNumDestinationDimensions>
    inline typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
    Transformable<TDerived>::transplanted(
        const Transplant<NumDimensions<TDerived>::Value, iNumDestinationDimensions>& transplant
    ) const {
        return transplant(derived());
    }

    template <class TDerived> template <int iNumDestinationDimensions>
    inline typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
    Transformable<TDerived>::morphed(
        const Function<iNumDestinationDimensions, NumDimensions<TDerived>::Value>& function
    ) const {
        return morphing(derived(), function);
    }

    template <class TDerived> template <int iNumAxes>
    inline typename ChangeDimensions<TDerived, iNumAxes>::Type
    Transformable<TDerived>::localizedTo(
        const Datum<NumDimensions<TDerived>::Value, iNumAxes>& datum
    ) const {
        return Localization<NumDimensions<TDerived>::Value, iNumAxes>(datum)(derived());
    }

    template <class TDerived> template <int iNumDimensions>
    inline typename ChangeDimensions<TDerived, iNumDimensions>::Type
    Transformable<TDerived>::globalizedFrom(
        const Datum<iNumDimensions, NumDimensions<TDerived>::Value>& datum
    ) const {
        return Globalization<iNumDimensions, NumDimensions<TDerived>::Value>(datum)(derived());
    }

    template <class TDerived>
    TDerived
    Transformable<TDerived>::scaling(const TDerived& argument, double scale) {
        return ScalingFunction<TDerived>()(argument, scale);
    }

    template <class TDerived> template <class TVector>
    TDerived
    Transformable<TDerived>::translation(
        const TDerived& argument,
        const EigenBase<TVector>& vector
    ) {
        return TranslationFunction<TDerived>()(argument, vector.derived());
    }

    template <class TDerived> template <class TMatrix>
    typename ChangeDimensions<TDerived, TMatrix::RowsAtCompileTime>::Type
    Transformable<TDerived>::transformation(
        const TDerived& argument,
        const EigenBase<TMatrix>& matrix
    ) {
        return TransformationFunction<TDerived, TMatrix::RowsAtCompileTime>()(argument, matrix);
    }

    template <class TDerived> template <int iNumDestinationDimensions>
    typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
    Transformable<TDerived>::morphing(
        const TDerived& argument,
        const Function<iNumDestinationDimensions, NumDimensions<TDerived>::Value>& function
    ) {
        return MorphingFunction<TDerived, iNumDestinationDimensions>()(argument, function);
    }
}
