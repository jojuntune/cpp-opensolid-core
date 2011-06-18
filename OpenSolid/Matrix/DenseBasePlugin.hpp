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

inline auto cwiseLower() const -> decltype(derived().unaryExpr(LowerOperation())) {
    return derived().unaryExpr(LowerOperation());
}

inline auto cwiseUpper() const -> decltype(derived().unaryExpr(UpperOperation())) {
    return derived().unaryExpr(UpperOperation());
}

inline auto cwiseMedian() const -> decltype(derived().unaryExpr(MedianOperation())) {
    return derived().unaryExpr(MedianOperation());
}

inline auto cwiseWidth() const -> decltype(derived().unaryExpr(WidthOperation())) {
    return derived().unaryExpr(WidthOperation());
}

template <class OtherDerivedType>
inline bool isEqualTo(
    const DenseBase<OtherDerivedType>& other,
    Scalar precision = NumTraits<Scalar>::dummy_precision
) {return derived().isApprox(other, precision);}

template<class OtherDerivedType>
inline bool overlaps(
    const DenseBase<OtherDerivedType>& other,
    Scalar precision = NumTraits<Scalar>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.overlaps(second_argument, precision.lower());
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isSubsetOf(
    const DenseBase<OtherDerivedType>& other,
    Scalar precision = NumTraits<Scalar>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isSubsetOf(second_argument, precision.lower());
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isProperSubsetOf(
    const DenseBase<OtherDerivedType>& other,
    Scalar precision = NumTraits<Scalar>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isProperSubsetOf(second_argument, precision.lower());
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isSupersetOf(
    const DenseBase<OtherDerivedType>& other,
    Scalar precision = NumTraits<Scalar>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isSupersetOf(second_argument, precision.lower());
        }
    ).all();
}

template<class OtherDerivedType>
inline bool isProperSupersetOf(
    const DenseBase<OtherDerivedType>& other,
    Scalar precision = NumTraits<Scalar>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.isProperSupersetOf(second_argument, precision.lower());
        }
    ).all();
}

template <class OtherDerivedType>
inline auto hull(const DenseBase<OtherDerivedType>& other) const ->
    decltype(derived().binaryExpr(other.derived(), HullOperation())) {
    return derived().binaryExpr(other.derived(), HullOperation());
}

template <class OtherDerivedType>
inline auto intersection(const DenseBase<OtherDerivedType>& other) const ->
    decltype(derived().binaryExpr(other.derived(), HullOperation())) {
    return derived().binaryExpr(other.derived(), IntersectionOperation());
}

inline auto bounds() const -> decltype(derived().cast<OpenSolid::Interval>()) {
    return derived().cast<OpenSolid::Interval>();
}

inline std::size_t hashValue() const {
    HashVisitor visitor;
    derived().visit(visitor);
    return visitor.result;
}

inline static auto LinSpaced(Index size, const OpenSolid::Interval& range) ->
    decltype(LinSpaced(size, range.lower(), range.upper())) {
    return LinSpaced(size, range.lower(), range.upper());
}

inline static auto LinSpaced(const OpenSolid::Interval& range) ->
    decltype(LinSpaced(range.lower(), range.upper()) {
    return LinSpaced(range.lower(), range.upper());
}
