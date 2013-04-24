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

PlainObject
scaled(double scale) const;

template <int iNumDimensions>
PlainObject
scaledAbout(double scale, const opensolid::Point<iNumDimensions>& originPoint) const;

template <class TVector>
const Derived&
translated(const EigenBase<TVector>& vector) const;

template <int iNumDimensions>
const Derived&
translatedAlong(double coordinateValue, const opensolid::Datum<iNumDimensions, 1>& axis ) const;

template <class TMatrix>
Matrix<
    typename internal::traits<Derived>::Scalar,
    TMatrix::RowsAtCompileTime,
    internal::traits<Derived>::ColsAtCompileTime
>
transformed(const EigenBase<TMatrix>& matrix) const;

PlainObject
rotated(double angle) const;

PlainObject
rotatedAbout(double angle, const opensolid::Point<2>& originPoint) const;

PlainObject
rotated(const opensolid::Rotation<2>& rotation) const;

PlainObject
rotatedAbout(double angle, const opensolid::Datum<3, 1>& axis) const;

PlainObject
rotated(const opensolid::Rotation<3>& rotation) const;

template <int iNumDimensions>
PlainObject
mirroredAbout(const opensolid::Datum<iNumDimensions, iNumDimensions - 1>& datum) const;

template <int iNumDimensions>
PlainObject
mirrored(const opensolid::Mirror<iNumDimensions>& mirror) const;

template <int iNumDimensions, int iNumAxes>
PlainObject
projectedOnto(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const;

template <int iNumDimensions>
PlainObject
projected(const opensolid::Projection<iNumDimensions>& projection) const;

template <int iNumSourceDimensions, int iNumDestinationDimensions, int iNumAxes>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transplanted(
    const opensolid::Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
    const opensolid::Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
) const;

template <int iNumSourceDimensions, int iNumDestinationDimensions>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transplanted(
    const opensolid::Transplant<iNumSourceDimensions, iNumDestinationDimensions>& transplant
) const;

template <int iNumDimensions, int iNumAxes>
Matrix<typename internal::traits<Derived>::Scalar, iNumAxes, internal::traits<Derived>::ColsAtCompileTime>
localizedTo(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const;

template <int iNumDimensions, int iNumAxes>
Matrix<typename internal::traits<Derived>::Scalar, iNumDimensions, internal::traits<Derived>::ColsAtCompileTime>
globalizedFrom(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const;

template <class TOther>
TOther
convertTo() const;
