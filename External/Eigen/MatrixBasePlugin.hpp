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

static const int NumDimensions = internal::traits<Derived>::RowsAtCompileTime;

PlainObject
scaledAbout(const opensolid::Point<NumDimensions>& originPoint, double scale) const;

template <class TVector>
const Derived&
translated(const EigenBase<TVector>& vector) const;

const Derived&
translatedAlong(const opensolid::Datum<NumDimensions, 1>& axis, double distance) const;

PlainObject
rotatedAbout(const opensolid::Point<2>& originPoint, double angle) const;

PlainObject
rotatedAbout(const opensolid::Datum<3, 1>& axis, double angle) const;

PlainObject
rotated(const opensolid::Rotation<NumDimensions>& rotation) const;

PlainObject
mirroredAbout(
    const opensolid::Datum<NumDimensions, NumDimensions - 1>& datum
) const;

PlainObject
mirrored(const opensolid::Mirror<NumDimensions>& mirror) const;

template <int iNumAxes>
PlainObject
projectedOnto(const opensolid::Datum<NumDimensions, iNumAxes>& datum) const;

PlainObject
projected(const opensolid::Projection<NumDimensions>& projection) const;

template <int iNumDestinationDimensions, int iNumAxes>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transplanted(
    const opensolid::Datum<NumDimensions, iNumAxes>& sourceDatum,
    const opensolid::Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
) const;

template <int iNumDestinationDimensions>
Matrix<
    typename internal::traits<Derived>::Scalar,
    iNumDestinationDimensions,
    internal::traits<Derived>::ColsAtCompileTime
>
transplanted(
    const opensolid::Transplant<NumDimensions, iNumDestinationDimensions>& transplant
) const;

template <int iNumAxes>
Matrix<typename internal::traits<Derived>::Scalar, iNumAxes, internal::traits<Derived>::ColsAtCompileTime>
localizedTo(const opensolid::Datum<NumDimensions, iNumAxes>& datum) const;

template <int iNumDimensions>
Matrix<typename internal::traits<Derived>::Scalar, iNumDimensions, internal::traits<Derived>::ColsAtCompileTime>
globalizedFrom(const opensolid::Datum<iNumDimensions, NumDimensions>& datum) const;

static const CwiseUnaryOp<internal::scalar_multiple_op<typename internal::traits<Derived>::Scalar>, const Derived>
scaling(const Derived& argument, double scale);

template <class TVector>
const Derived&
translation(const Derived& argument, const EigenBase<TVector>& vector);

template <class TMatrix>
static Matrix<
    typename internal::traits<Derived>::Scalar,
    TMatrix::RowsAtCompileTime,
    internal::traits<Derived>::ColsAtCompileTime
>
transformation(const Derived& argument, const EigenBase<TMatrix>& matrix);

template <class TOther>
TOther
convertTo() const;
