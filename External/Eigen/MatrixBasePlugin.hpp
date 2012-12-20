/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

template <class TMatrix, class TVector>
Matrix<
    typename internal::traits<Derived>::Scalar,
    TMatrix::RowsAtCompileTime,
    internal::traits<Derived>::ColsAtCompileTime
> transformed(
    const TMatrix& matrix,
    const TVector& vector
) const;

template <class TPoint>
PlainObject scaled(double scale, const EigenBase<TPoint>& point) const;

template <class TVector>
PlainObject translated(const EigenBase<TVector>& vector) const;

template <int iNumDimensions, int iNumAxes>
PlainObject translated(
    double distance,
    const opensolid::Datum<iNumDimensions, iNumAxes>& axis
) const;

PlainObject rotated(double angle, const Matrix<double, 2, 1>& point) const;

template <int iNumDimensions, int iNumAxes>
PlainObject rotated(
    double angle,
    const opensolid::Datum<iNumDimensions, iNumAxes>& axis
) const;

template <int iNumDimensions, int iNumAxes>
PlainObject mirrored(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const;

template <class TOther>
TOther as() const;
