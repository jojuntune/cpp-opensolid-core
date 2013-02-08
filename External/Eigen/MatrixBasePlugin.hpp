/*************************************************************************************
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

template <class TPoint>
PlainObject scaled(double scale, const EigenBase<TPoint>& originPoint) const;

template <int iNumDimensions, int iNumAxes>
PlainObject translated(
    double coordinateValue,
    const opensolid::Datum<iNumDimensions, iNumAxes>& axis
) const;

PlainObject rotated(double angle) const;

PlainObject rotated(double angle, const Matrix<double, 2, 1>& originPoint) const;

PlainObject rotated(const opensolid::Rotation<2>& rotation) const;

PlainObject rotated(const opensolid::Rotation<2>& rotation, opensolid::LinearTag) const;

template <int iNumDimensions, int iNumAxes>
PlainObject rotated(double angle, const opensolid::Datum<iNumDimensions, iNumAxes>& axis) const;

PlainObject rotated(const opensolid::Rotation<3>& rotation) const;

PlainObject rotated(const opensolid::Rotation<3>& rotation, opensolid::LinearTag) const;

template <int iNumDimensions, int iNumAxes>
PlainObject mirrored(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const;

template <int iNumDimensions>
PlainObject mirrored(const opensolid::Mirror<iNumDimensions>& mirror) const;

template <int iNumDimensions, class TPoint>
PlainObject mirrored(const opensolid::Mirror<iNumDimensions>& mirror, opensolid::LinearTag) const;

template <int iNumDimensions, int iNumAxes>
PlainObject projected(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const;

template <int iNumDimensions>
PlainObject projected(const opensolid::Projection<iNumDimensions>& projection) const;

template <int iNumDimensions, class TPoint>
PlainObject projected(
    const opensolid::Projection<iNumDimensions>& projection,
    opensolid::LinearTag
) const;

template <
    int iNumSourceDatumDimensions,
    int iNumSourceDatumAxes,
    int iNumDestinationDatumDimensions,
    int iNumDestinationDatumAxes
>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDatumDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transformed(
    const opensolid::Datum<iNumSourceDatumDimensions, iNumSourceDatumAxes>& sourceDatum,
    const opensolid::Datum<iNumDestinationDatumDimensions, iNumDestinationDatumAxes>& destinationDatum
) const;

template <int iNumSourceDimensions, int iNumDestinationDimensions>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transformed(
    const opensolid::Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation
) const;

template <int iNumSourceDimensions, int iNumDestinationDimensions>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transformed(
    const opensolid::Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation,
    opensolid::LinearTag
) const;

template <class TOther>
TOther as() const;
