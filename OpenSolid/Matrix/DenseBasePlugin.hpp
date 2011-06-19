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

inline void assertIsScalar() const {
    static_assert(
        RowsAtCompileTime == 1 || RowsAtCompileTime == Dynamic,
        "1x1 (scalar) matrix expected"
    );
    static_assert(
        ColsAtCompileTime == 1 || ColsAtCompileTime == Dynamic,
        "1x1 (scalar) matrix expected"
    );
    assert(size() == 1 && "1x1 (scalar) matrix expected");
}

inline ConstIterator begin() const {return ConstIterator(derived(), 0);}

inline ConstIterator end() const {return ConstIterator(derived(), size());}

inline Iterator begin() {return Iterator(derived(), 0);}

inline Iterator end() {return Iterator(derived(), size());}

inline ConstRowIterator rowBegin() const {return ConstRowIterator(derived(), 0);}

inline ConstRowIterator rowEnd() const {return ConstRowIterator(derived(), rows());}

inline RowIterator rowBegin() {return RowIterator(derived(), 0);}

inline RowIterator rowEnd() {return RowIterator(derived(), rows());}

inline ConstColIterator colBegin() const {return ConstColIterator(derived(), 0);}

inline ConstColIterator colEnd() const {return ConstColIterator(derived(), cols());}

inline ColIterator colBegin() {return ColIterator(derived(), 0);}

inline ColIterator colEnd() {return ColIterator(derived(), cols());}

inline OpenSolid::Double lower() const {
    assertIsScalar();
    return derived().eval().coeff(0, 0).lower();
}

inline OpenSolid::Double upper() const {
    assertIsScalar();
    return derived().eval().coeff(0, 0).upper();
}

inline OpenSolid::Double median() const {
    assertIsScalar();
    return derived().eval().coeff(0, 0).median();
}

inline OpenSolid::Double width() const {
    assertIsScalar();
    return derived().eval().coeff(0, 0).width();
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

template <class OtherDerivedType>
inline bool isEqualTo(
    const DenseBase<OtherDerivedType>& other,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {return derived().isApprox(other, precision);}

template <class DerivedType>
inline bool isEqualTo(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isEqualTo(argument.derived(), precision);
}

template <class DerivedType>
inline bool isLessThan(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isLessThan(argument.derived(), precision);
}

template <class DerivedType>
inline bool isGreaterThan(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isGreaterThan(argument.derived(), precision);
}

template <class DerivedType>
inline bool isLessThanOrEqualTo(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isLessThanOrEqualTo(argument.derived(), precision);
}

template <class DerivedType>
inline bool isGreaterThanOrEqualTo(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isGreaterThanOrEqualTo(argument.derived(), precision);
}

template <class DerivedType>
inline bool overlaps(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).overlaps(argument.derived(), precision);
}

template <class DerivedType>
inline bool isSubsetOf(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isSubsetOf(argument.derived(), precision);
}

template <class DerivedType>
inline bool isProperSubsetOf(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isProperSubsetOf(argument.derived(), precision);
}

template <class DerivedType>
inline bool isSupersetOf(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isSupersetOf(argument.derived(), precision);
}

template <class DerivedType>
inline bool isProperSupersetOf(
    const OpenSolid::ScalarBase<DerivedType>& argument,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).isProperSupersetOf(argument.derived(), precision);
}

template<class OtherDerivedType>
inline bool overlaps(
    const DenseBase<OtherDerivedType>& other,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.overlaps(second_argument, precision);
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isSubsetOf(
    const DenseBase<OtherDerivedType>& other,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isSubsetOf(second_argument, precision);
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isProperSubsetOf(
    const DenseBase<OtherDerivedType>& other,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isProperSubsetOf(second_argument, precision);
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isSupersetOf(
    const DenseBase<OtherDerivedType>& other,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isSupersetOf(second_argument, precision);
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isProperSupersetOf(
    const DenseBase<OtherDerivedType>& other,
    OpenSolid::Double precision = OpenSolid::Double::defaultPrecision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isProperSupersetOf(second_argument, precision);
        }
    ).all();
}

template <class OtherDerivedType>
inline CwiseBinaryOp<HullOperation, const Derived, const OtherDerivedType> hull(
    const DenseBase<OtherDerivedType>& other
) {return derived().binaryExpr(other.derived(), HullOperation());}

template <class OtherDerivedType>
inline CwiseBinaryOp<IntersectionOperation, const Derived, const OtherDerivedType> intersection(
    const DenseBase<OtherDerivedType>& other
) {return derived().binaryExpr(other.derived(), IntersectionOperation());}


inline OpenSolid::Interval hull(Scalar argument) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).hull(argument);
}

inline OpenSolid::Interval intersection(Scalar argument) {
    assertIsScalar();
    return derived().eval().coeff(0, 0).intersection(argument);
}

inline typename internal::conditional<
    internal::is_same<Scalar, OpenSolid::Interval>::value,
    const Derived&,
    const CwiseUnaryOp<internal::scalar_cast_op<Scalar, OpenSolid::Interval>, const Derived>
>::type bounds() const {
    return derived().cast<OpenSolid::Interval>();
}

inline std::size_t hashValue() const {
    HashVisitor visitor;
    derived().visit(visitor);
    return visitor.result;
}

inline static const RandomAccessLinSpacedReturnType LinSpaced(
    Index size,
    const OpenSolid::Interval& range
) {return LinSpaced(size, range.lower(), range.upper());}

inline static const RandomAccessLinSpacedReturnType LinSpaced(const OpenSolid::Interval& range) {
    return LinSpaced(range.lower(), range.upper());
}
