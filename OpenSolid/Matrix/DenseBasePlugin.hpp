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

inline auto cwiseLower() const ->
    decltype(derived().unaryExpr([] (Scalar argument) {return argument.lower();})) {
    return derived().unaryExpr([] (Scalar argument) {return argument.lower();});
}

inline auto cwiseUpper() const ->
    decltype(derived().unaryExpr([] (Scalar argument) {return argument.upper();})) {
    return derived().unaryExpr([] (Scalar argument) {return argument.upper();});
}

inline auto cwiseMedian() const ->
    decltype(derived().unaryExpr([] (Scalar argument) {return argument.median();})) {
    return derived().unaryExpr([] (Scalar argument) {return argument.median();});
}

inline auto cwiseWidth() const ->
    decltype(derived().unaryExpr([] (Scalar argument) {return argument.width();})) {
    return derived().unaryExpr([] (Scalar argument) {return argument.width();});
}

template<class OtherDerivedType>
inline bool overlap(
    const EigenBase<OtherDerivedType>& other,
    Double precision = NumTraits<Double>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.overlap(second_argument, precision);
        }
    ).all();
}

template<class OtherDerivedType>
inline bool contain(
    const EigenBase<OtherDerivedType>& other,
    Double precision = NumTraits<Double>::dummy_precision()
) const {
    return derived().binaryExpr(
        other.derived(),
        [precision] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.contain(second_argument, precision);
        }
    ).all();
}

template <class OtherDerivedType>
inline auto hull(const EigenBase<OtherDerivedType>& other) const -> 
    decltype(
        derived().binaryExpr(
            other.derived(),
            [] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
                return first_argument.hull(second_argument);
            }
        )
    ) {
    return derived().binaryExpr(
        other.derived(),
        [] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.hull(second_argument);
        }
    );
}

template <class OtherDerivedType>
inline auto hull(const EigenBase<OtherDerivedType>& other) const -> 
    decltype(
        derived().binaryExpr(
            other.derived(),
            [] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
                return first_argument.intersection(second_argument);
            }
        )
    ) {
    return derived().binaryExpr(
        other.derived(),
        [] (Scalar first_argument, typename OtherDerivedType::Scalar second_argument) {
            return first_argument.intersection(second_argument);
        }
    );
}

inline static auto LinSpaced(Index size, const OpenSolid::Interval& range) ->
    decltype(LinSpaced(size, range.lower(), range.upper())) {
    return LinSpaced(size, range.lower(), range.upper());
}

inline static auto LinSpaced(const OpenSolid::Interval& range) ->
    decltype(LinSpaced(range.lower(), range.upper()) {
    return LinSpaced(range.lower(), range.upper());
}
