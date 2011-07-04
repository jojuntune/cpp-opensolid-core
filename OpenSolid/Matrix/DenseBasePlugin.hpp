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

typedef ConstMatrixIterator<Derived> ConstIterator;
typedef MatrixIterator<Derived> Iterator; 
typedef ConstMatrixRowIterator<Derived> ConstRowIterator;
typedef MatrixRowIterator<Derived> RowIterator;
typedef ConstMatrixColIterator<Derived> ConstColIterator;
typedef MatrixColIterator<Derived> ColIterator;

typedef Matrix<OpenSolid::Interval, RowsAtCompileTime, ColsAtCompileTime> Bounds;

inline ConstIterator begin() const;
inline ConstIterator end() const;
inline Iterator begin();
inline Iterator end();

inline ConstRowIterator rowBegin();
inline ConstRowIterator rowEnd();
inline RowIterator rowBegin();
inline RowIterator rowEnd();

inline ConstColIterator colBegin() const;
inline ConstColIterator colEnd() const;
inline ColIterator colBegin();
inline ColIterator colEnd();

inline OpenSolid::Double lower() const;
inline OpenSolid::Double upper() const;
inline OpenSolid::Double median() const;
inline OpenSolid::Double width() const;

inline CwiseUnaryOp<LowerOperation, const Derived> cwiseLower() const;
inline CwiseUnaryOp<UpperOperation, const Derived> cwiseUpper() const;
inline CwiseUnaryOp<MedianOperation, const Derived> cwiseMedian() const;
inline CwiseUnaryOp<WidthOperation, const Derived> cwiseWidth() const;

template <class OtherDerivedType>
inline bool isEqualTo(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template <class OtherDerivedType>
inline bool isLessThan(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template <class OtherDerivedType>
inline bool isGreaterThan(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template <class OtherDerivedType>
inline bool isLessThanOrEqualTo(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template <class OtherDerivedType>
inline bool isGreaterThanOrEqualTo(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template<class OtherDerivedType>
inline bool overlaps(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template<class OtherDerivedType>
inline bool isSubsetOf(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template<class OtherDerivedType>
inline bool isProperSubsetOf(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template<class OtherDerivedType>
inline bool isSupersetOf(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template<class OtherDerivedType>
inline bool isProperSupersetOf(
    const DenseBase<OtherDerivedType>& other,
    double precision = OPENSOLID_PRECISION
) const;

template <class OtherDerivedType>
inline CwiseBinaryOp<HullOperation, const Derived, const OtherDerivedType> hull(
    const DenseBase<OtherDerivedType>& other
) const;

template <class OtherDerivedType>
inline CwiseBinaryOp<IntersectionOperation, const Derived, const OtherDerivedType> intersection(
    const DenseBase<OtherDerivedType>& other
) const;

inline typename internal::conditional<
    internal::is_same<Scalar, OpenSolid::Interval>::value,
    const Derived&,
    const CwiseUnaryOp<internal::scalar_cast_op<Scalar, OpenSolid::Interval>, const Derived>
>::type bounds() const;

inline std::size_t hashValue() const;

inline static const RandomAccessLinSpacedReturnType LinSpaced(
    Index size,
    const OpenSolid::Interval& range
);

inline static const RandomAccessLinSpacedReturnType LinSpaced(const OpenSolid::Interval& range);
