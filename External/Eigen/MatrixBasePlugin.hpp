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

template <class MatrixType, class VectorType>
Matrix<
    typename internal::traits<Derived>::Scalar,
    MatrixType::RowsAtCompileTime,
    internal::traits<Derived>::ColsAtCompileTime
> transformed(
    const MatrixType& matrix,
    const VectorType& vector
) const;

template <class PointType>
PlainObject scaled(double scale, const EigenBase<PointType>& point) const;

template <class VectorType>
PlainObject translated(const EigenBase<VectorType>& vector) const;

template <int dimensions_, int axes_>
PlainObject translated(double distance, const opensolid::Datum<dimensions_, axes_>& axis) const;

PlainObject rotated(double angle, const Matrix<double, 2, 1>& point) const;

template <int dimensions_, int axes_>
PlainObject rotated(double angle, const opensolid::Datum<dimensions_, axes_>& axis) const;

template <int dimensions_, int axes_>
PlainObject mirrored(const opensolid::Datum<dimensions_, axes_>& datum) const;

template <class OtherType>
OtherType as() const;
