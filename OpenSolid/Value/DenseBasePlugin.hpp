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

inline Scalar scalar() const {
    assert(derived().size() == 1);
    return derived().eval().coeff(0, 0);
}

typedef ConstMatrixRowIterator<Derived> ConstRowIterator;
typedef MatrixRowIterator<Derived> RowIterator;
typedef ConstMatrixColIterator<Derived> ConstColIterator;
typedef MatrixColIterator<Derived> ColIterator;

inline ConstRowIterator rowBegin() const {return ConstRowIterator(derived(), 0);}

inline ConstRowIterator rowEnd() const {return ConstRowIterator(derived(), rows());}

inline RowIterator rowBegin() {return RowIterator(derived(), 0);}

inline RowIterator rowEnd() {return RowIterator(derived(), rows());}

inline ConstColIterator colBegin() const {return ConstColIterator(derived(), 0);}

inline ConstColIterator colEnd() const {return ConstColIterator(derived(), cols());}

inline ColIterator colBegin() {return ColIterator(derived(), 0);}

inline ColIterator colEnd() {return ColIterator(derived(), cols());}

inline MatrixListAdapter<Derived> list() const {
    return MatrixListAdapter<Derived>(derived());
}

template<class OtherDerived>
inline bool overlap(const DenseBase<OtherDerived>& other, double tolerance = 0.0) const {
    return derived().binaryExpr(other.derived(), OverlapOperation(tolerance)).all();
}

template<class OtherDerived>
inline bool contain(const DenseBase<OtherDerived>& other, double tolerance = 0.0) const {
    return derived().binaryExpr(other.derived(), ContainOperation(tolerance)).all();
}

template<class OtherDerived>
inline bool adjacent(const DenseBase<OtherDerived>& other, double tolerance = 0.0) const {
    return
        overlap(other, tolerance) &&
        derived().binaryExpr(other.derived(), AdjacentOperation(tolerance)).any();
}

inline CwiseUnaryOp<LowerOperation, const Derived> cwiseLower() const {
    return derived().unaryExpr(LowerOperation());
}

inline CwiseUnaryOp<UpperOperation, const Derived> cwiseUpper() const {
    return derived().unaryExpr(UpperOperation());
}

inline CwiseUnaryOp<MedianOperation, const Derived> cwiseMedian() const {
    return derived().unaryExpr(MedianOperation());
}

inline CwiseUnaryOp<WidthOperation, const Derived> cwiseWidth() const {
    return derived().unaryExpr(WidthOperation());
}

inline CwiseUnaryOp<CenteredOperation, const Derived> cwiseCentered() const {
    return derived().unaryExpr(CenteredOperation());
}

template <class OtherDerived>
inline CwiseBinaryOp<HullOperation, const Derived, const OtherDerived> hull(
    const DenseBase<OtherDerived>& other
) const {return derived().binaryExpr(other.derived(), HullOperation());}

template <class OtherDerived>
inline CwiseBinaryOp<IntersectionOperation, const Derived, const OtherDerived> intersection(
    const DenseBase<OtherDerived>& other
) const {return derived().binaryExpr(other.derived(), IntersectionOperation());}

inline static const RandomAccessLinSpacedReturnType LinSpaced(Index size, const Interval& range) {
    return LinSpaced(size, lowerBound(range), upperBound(range));
}

inline static const RandomAccessLinSpacedReturnType LinSpaced(const Interval& range) {
    return LinSpaced(lowerBound(range), upperBound(range));
}

inline Bisected<Derived> bisected() const {return Bisected<Derived>(derived());}
