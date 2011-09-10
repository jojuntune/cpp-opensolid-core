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

inline CwiseUnaryOp<LowerOperation, const Derived> cwiseLower() const;
inline CwiseUnaryOp<UpperOperation, const Derived> cwiseUpper() const;
inline CwiseUnaryOp<MedianOperation, const Derived> cwiseMedian() const;
inline CwiseUnaryOp<WidthOperation, const Derived> cwiseWidth() const;

template <class OtherDerivedType>
bool overlaps(
    const DenseBase<OtherDerivedType>& other,
    double precision = 1e-12
) const;

template <class OtherDerivedType>
bool strictlyOverlaps(
    const DenseBase<OtherDerivedType>& other,
    double precision = 1e-12
) const;

template <class OtherDerivedType>
bool contains(
    const DenseBase<OtherDerivedType>& other,
    double precision = 1e-12
) const;

template <class OtherDerivedType>
bool strictlyContains(
    const DenseBase<OtherDerivedType>& other,
    double precision = 1e-12
) const;

template <class OtherDerivedType>
CwiseBinaryOp<HullOperation, const Derived, const OtherDerivedType> hull(
    const DenseBase<OtherDerivedType>& other
) const;

template <class OtherDerivedType>
CwiseBinaryOp<IntersectionOperation, const Derived, const OtherDerivedType> intersection(
    const DenseBase<OtherDerivedType>& other
) const;

static const RandomAccessLinSpacedReturnType LinSpaced(
    Index size,
    const OpenSolid::Interval& range
);

static const RandomAccessLinSpacedReturnType LinSpaced(const OpenSolid::Interval& range);

template <class FirstDerivedType, class SecondDerivedType>
static CwiseBinaryOp<HullOperation, const FirstDerivedType, const SecondDerivedType> Hull(
    const DenseBase<FirstDerivedType>& first_argument,
    const DenseBase<SecondDerivedType>& second_argument
);

static const ConstantReturnType Empty();
static const ConstantReturnType Empty(Index size);
static const ConstantReturnType Empty(Index rows, Index cols);

static const ConstantReturnType Whole();
static const ConstantReturnType Whole(Index size);
static const ConstantReturnType Whole(Index rows, Index cols);


