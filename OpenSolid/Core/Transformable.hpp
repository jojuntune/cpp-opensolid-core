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
    Transformable<TDerived>::scaled(double scale) const {
        ScalingFunction<TDerived> scalingFunction;
        return scalingFunction(derived(), scale);
    }

    template <class TDerived> template <int iNumDimensions>
    inline TDerived
    Transformable<TDerived>::scaledAbout(
        double scale,
        const Point<iNumDimensions>& originPoint
    ) const {
        return translated(-originPoint.vector()).scaled(scale).translated(originPoint.vector());
    }

    template <class TDerived> template <class TVector>
    inline TDerived
    Transformable<TDerived>::translated(const EigenBase<TVector>& vector) const {
        TranslationFunction<TDerived> translationFunction;
        return translationFunction(derived(), vector);
    }
    
    template <class TDerived> template <int iNumDimensions>
    inline TDerived
    Transformable<TDerived>::translatedAlong(
        const Datum<iNumDimensions, 1>& axis,
        double coordinateValue
    ) const {
        return translated(coordinateValue * axis.basisVector());
    }

    template <class TDerived> template<class TMatrix>
    inline typename TransformationFunction<TDerived, TMatrix::RowsAtCompileTime>::ResultType
    Transformable<TDerived>::transformed(const EigenBase<TMatrix>& matrix) const {
        TransformationFunction<TDerived, TMatrix::RowsAtCompileTime> transformationFunction;
        return transformationFunction(derived(), matrix);
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::rotated(double angle) const {
        return transformed(Matrix2d(Rotation2Dd(angle)));
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::rotatedAbout(const Point<2>& originPoint, double angle) const {
        return Rotation2d(originPoint, angle)(derived());
    }

    template <class TDerived>
    TDerived
    Transformable<TDerived>::rotated(const Rotation2d& rotation) const {
        return rotation(derived());
    }

    template <class TDerived>
    inline TDerived
    Transformable<TDerived>::rotatedAbout(const Datum<3, 1>& axis, double angle) const {
        return rotated(Rotation3d(axis, angle));
    }

    template <class TDerived>
    TDerived
    Transformable<TDerived>::rotated(const Rotation3d& rotation) const {
        return rotation(derived());
    }

    template <class TDerived> template <int iNumDimensions>
    inline TDerived
    Transformable<TDerived>::mirroredAbout(
        const Datum<iNumDimensions, iNumDimensions - 1>& datum
    ) const {
        return mirrored(Mirror<iNumDimensions>(datum));
    }

    template <class TDerived> template <int iNumDimensions>
    TDerived
    Transformable<TDerived>::mirrored(const Mirror<iNumDimensions>& mirror) const {
        return mirror(derived());
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline TDerived
    Transformable<TDerived>::projectedOnto(
        const Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return projected(Projection<iNumDimensions>(datum));
    }

    template <class TDerived> template <int iNumDimensions>
    TDerived
    Transformable<TDerived>::projected(const Projection<iNumDimensions>& projection) const {
        return projection(derived());
    }

    template <class TDerived>
    template <int iNumSourceDimensions, int iNumDestinationDimensions, int iNumAxes>
    typename TransformationFunction<TDerived, iNumDestinationDimensions>::ResultType
    Transformable<TDerived>::transplanted(
        const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
        const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
    ) const {
        return localizedTo(sourceDatum).globalizedFrom(destinationDatum);
    }

    template <class TDerived>
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    typename TransformationFunction<TDerived, iNumDestinationDimensions>::ResultType
    Transformable<TDerived>::transplanted(
        const Transplant<iNumSourceDimensions, iNumDestinationDimensions>& transplant
    ) const {
        return transplant(derived());
    }

    template <class TDerived> template <int iNumDestinationDimensions>
    typename MorphingFunction<TDerived, iNumDestinationDimensions>::ResultType
    Transformable<TDerived>::morphed(const Function& function) const {
        MorphingFunction<TDerived, iNumDestinationDimensions> MorphingFunction;
        return MorphingFunction(derived(), function);
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    typename TransformationFunction<TDerived, iNumAxes>::ResultType
    Transformable<TDerived>::localizedTo(const Datum<iNumDimensions, iNumAxes>& datum) const {
        return Localization<iNumDimensions, iNumAxes>(datum)(derived());
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    typename TransformationFunction<TDerived, iNumDimensions>::ResultType
    Transformable<TDerived>::globalizedFrom(const Datum<iNumDimensions, iNumAxes>& datum) const {
        return Globalization<iNumDimensions, iNumAxes>(datum)(derived());
    }
}
