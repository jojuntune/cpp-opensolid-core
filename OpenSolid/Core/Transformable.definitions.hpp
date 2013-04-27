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

#include <OpenSolid/Core/Datum.declarations.hpp>
#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Globalization.declarations.hpp>
#include <OpenSolid/Core/Localization.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Mirror.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Projection.declarations.hpp>
#include <OpenSolid/Core/Rotation.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <class TDerived>
    class Transformable
    {
    public:
        const TDerived&
        derived() const;

        TDerived
        scaled(double scale) const;

        template <int iNumDimensions>
        TDerived
        scaledAbout(double scale, const Point<iNumDimensions>& originPoint) const;

        template <class TVector>
        TDerived
        translated(const EigenBase<TVector>& vector) const;

        template <int iNumDimensions>
        TDerived
        translatedAlong(const Datum<iNumDimensions, 1>& axis, double coordinateValue) const;

        template <class TMatrix>
        typename TransformationFunction<TDerived, TMatrix::RowsAtCompileTime>::ResultType
        transformed(const EigenBase<TMatrix>& matrix) const;

        TDerived
        rotated(double angle) const;

        TDerived
        rotatedAbout(const Point<2>& originPoint, double angle) const;

        TDerived
        rotated(const Rotation<2>& rotation) const;

        TDerived
        rotatedAbout(const Datum<3, 1>& axis, double angle) const;

        TDerived
        rotated(const Rotation<3>& rotation) const;

        template <int iNumDimensions>
        TDerived
        mirroredAbout(const Datum<iNumDimensions, iNumDimensions - 1>& datum) const;

        template <int iNumDimensions>
        TDerived
        mirrored(const Mirror<iNumDimensions>& mirror) const;

        template <int iNumDimensions, int iNumAxes>
        TDerived
        projectedOnto(const Datum<iNumDimensions, iNumAxes>& datum) const;

        template <int iNumDimensions>
        TDerived
        projected(const Projection<iNumDimensions>& projection) const;

        template <int iNumSourceDimensions, int iNumDestinationDimensions, int iNumAxes>
        typename TransformationFunction<TDerived, iNumDestinationDimensions>::ResultType
        transplanted(
            const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
        ) const;

        template <int iNumSourceDimensions, int iNumDestinationDimensions>
        typename TransformationFunction<TDerived, iNumDestinationDimensions>::ResultType
        transplanted(
            const Transplant<iNumSourceDimensions, iNumDestinationDimensions>& transplant
        ) const;

        template <int iNumDestinationDimensions>
        typename MorphingFunction<TDerived, iNumDestinationDimensions>::ResultType
        morphed(const Function& function) const;

        template <int iNumDimensions, int iNumAxes>
        typename TransformationFunction<TDerived, iNumAxes>::ResultType
        localizedTo(const Datum<iNumDimensions, iNumAxes>& datum) const;

        template <int iNumDimensions, int iNumAxes>
        typename TransformationFunction<TDerived, iNumDimensions>::ResultType
        globalizedFrom(const Datum<iNumDimensions, iNumAxes>& datum) const;
    };
}
