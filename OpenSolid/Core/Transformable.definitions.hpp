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

        TDerived
        scaledAbout(const Point<NumDimensions<TDerived>::Value>& originPoint, double scale) const;

        template <class TVector>
        TDerived
        translated(const EigenBase<TVector>& vector) const;

        TDerived
        translatedAlong(
            const Axis<NumDimensions<TDerived>::Value>& axis,
            double distance
        ) const;

        TDerived
        rotatedAbout(const Point<2>& originPoint, double angle) const;

        TDerived
        rotatedAbout(const Axis<3>& axis, double angle) const;

        TDerived
        mirroredAbout(const Axis<2>& axis) const;

        TDerived
        mirroredAbout(const Plane3d& plane) const;

        TDerived
        projectedOnto(const Axis<2>& axis) const;

        TDerived
        projectedOnto(const Axis<3>& axis) const;

        TDerived
        projectedOnto(const Plane3d& plane) const;

        TDerived
        transformed(
            const LinearTransformation<NumDimensions<TDerived>::Value>& transformation
        ) const;

        template <int iNumResultDimensions, int iNumAxes>
        typename ChangeDimensions<TDerived, iNumResultDimensions>::Type
        transplanted(
            const CoordinateSystem<NumDimensions<TDerived>::Value, iNumAxes>& sourceCoordinateSystem,
            const CoordinateSystem<iNumResultDimensions, iNumAxes>& destinationCoordinateSystem
        ) const;

        template <int iNumResultDimensions>
        typename ChangeDimensions<TDerived, iNumResultDimensions>::Type
        transplanted(
            const Transplant<NumDimensions<TDerived>::Value, iNumResultDimensions>& transplant
        ) const;

        template <int iNumResultDimensions>
        typename ChangeDimensions<TDerived, iNumResultDimensions>::Type
        morphed(
            const Function<iNumResultDimensions, NumDimensions<TDerived>::Value>& function
        ) const;

        ///// Low-level static functions /////

        static TDerived
        scaling(const TDerived& argument, double scale);

        template <class TVector>
        static TDerived
        translation(const TDerived& argument, const EigenBase<TVector>& vector);

        template <class TMatrix>
        static typename ChangeDimensions<TDerived, TMatrix::RowsAtCompileTime>::Type
        transformation(const TDerived& argument, const EigenBase<TMatrix>& matrix);

        template <int iNumResultDimensions>
        static typename ChangeDimensions<TDerived, iNumResultDimensions>::Type
        morphing(
            const TDerived& argument,
            const Function<iNumResultDimensions, NumDimensions<TDerived>::Value>& function
        );
    };

    template <class TDerived, int iNumAxes>
    typename ChangeDimensions<TDerived, iNumAxes>::Type
    operator/(
        const Transformable<TDerived>& transformable,
        const CoordinateSystem<NumDimensions<TDerived>::Value, iNumAxes>& coordinateSystem
    );

    template <class TDerived, int iNumDimensions>
    typename ChangeDimensions<TDerived, iNumDimensions>::Type
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
    struct NumDimensions<float>
    {
        static const int Value = 1;
    };

    template <>
    struct NumDimensions<int>
    {
        static const int Value = 1;
    };

    template <>
    struct NumDimensions<Interval>
    {
        static const int Value = 1;
    };
}
