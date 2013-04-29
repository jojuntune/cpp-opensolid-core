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
        scaledAbout(const Point<NumDimensions<TDerived>::Value>& originPoint, double scale) const;

        template <class TVector>
        TDerived
        translated(const EigenBase<TVector>& vector) const;

        TDerived
        translatedAlong(
            const Datum<NumDimensions<TDerived>::Value, 1>& axis,
            double distance
        ) const;

        TDerived
        rotatedAbout(const Point<2>& originPoint, double angle) const;

        TDerived
        rotatedAbout(const Datum<3, 1>& axis, double angle) const;

        TDerived
        rotated(const Rotation<NumDimensions<TDerived>::Value>& rotation) const;

        TDerived
        mirroredAbout(
            const Datum<NumDimensions<TDerived>::Value, NumDimensions<TDerived>::Value - 1>& datum
        ) const;

        TDerived
        mirrored(const Mirror<NumDimensions<TDerived>::Value>& mirror) const;

        template <int iNumAxes>
        TDerived
        projectedOnto(const Datum<NumDimensions<TDerived>::Value, iNumAxes>& datum) const;

        TDerived
        projected(const Projection<NumDimensions<TDerived>::Value>& projection) const;

        template <int iNumDestinationDimensions, int iNumAxes>
        typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
        transplanted(
            const Datum<NumDimensions<TDerived>::Value, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
        ) const;

        template <int iNumDestinationDimensions>
        typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
        transplanted(
            const Transplant<NumDimensions<TDerived>::Value, iNumDestinationDimensions>& transplant
        ) const;

        template <int iNumDestinationDimensions>
        typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
        morphed(const Function& function) const;

        template <int iNumAxes>
        typename ChangeDimensions<TDerived, iNumAxes>::Type
        localizedTo(const Datum<NumDimensions<TDerived>::Value, iNumAxes>& datum) const;

        template <int iNumDimensions>
        typename ChangeDimensions<TDerived, iNumDimensions>::Type
        globalizedFrom(const Datum<iNumDimensions, NumDimensions<TDerived>::Value>& datum) const;

        ///// Low-level static functions /////

        static TDerived
        scaling(const TDerived& argument, double scale);

        template <class TVector>
        static TDerived
        translation(const TDerived& argument, const EigenBase<TVector>& vector);

        template <class TMatrix>
        static typename ChangeDimensions<TDerived, TMatrix::RowsAtCompileTime>::Type
        transformation(const TDerived& argument, const EigenBase<TMatrix>& matrix);

        template <int iNumDestinationDimensions>
        static typename ChangeDimensions<TDerived, iNumDestinationDimensions>::Type
        morphing(const TDerived& argument, const Function& function);
    };
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
}
