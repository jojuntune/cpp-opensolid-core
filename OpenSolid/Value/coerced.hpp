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

#ifndef OPENSOLID__COERCED_HPP
#define OPENSOLID__COERCED_HPP

namespace OpenSolid
{
    template <class ScalarType, int rows_, int cols_>
    class Value;
    
    template <class Type>
    struct ValueType;
    
    template <>
    struct ValueType<int>
    {
        typedef Value<double, 1, 1> Type;
    };
    
    template <>
    struct ValueType<float>
    {
        typedef Value<double, 1, 1> Type;
    };
    
    template <>
    struct ValueType<double>
    {
        typedef Value<double, 1, 1> Type;
    };
    
    template <>
    struct ValueType<BoostInterval>
    {
        typedef Value<BoostInterval, 1, 1> Type;
    };

    template <class ScalarType, int rows_, int cols_>
    struct ValueType<Value<ScalarType, rows_, cols_>>
    {
        typedef const Value<ScalarType, rows_, cols_>& Type;
    };
    
    template <class FirstScalarType, class SecondScalarType>
    struct CoercedScalar
    {
        typedef BoostInterval Type;
    };
    
    template <>
    struct CoercedScalar<double, double>
    {
        typedef double Type;
    };
    
    template <int first_size_, int second_size_>
    struct CoercedSize
    {
        static const int value = first_size_ >= second_size_ ? first_size_ : second_size;
    };
    
    template <>
    struct CoercedSize<-1, 1>
    {
        static const int value = -1;
    };
    
    template <>
    struct CoercedSize<1, -1>
    {
        static const int value = -1;
    };
    
    template <class FirstType, class SecondType>
    struct Coerced
    {
        typedef typename ValueType<FirstType>::Type FirstValue;
        typedef typename ValueType<SecondType>::Type SecondValue;
        
        static const int rows = CoercedSize<FirstValue::static_rows, SecondValue::static_rows>::value;
        static const int cols = CoercedSize<FirstValue::static_cols, SecondValue::static_cols>::value;
    };
    
    template <
        class FirstScalarType,
        int first_rows_,
        int first_cols_,
        class SecondScalarType,
        int second_rows_,
        int second_cols_
    >
    Value<
        typename CoercedScalar<FirstScalarType, SecondScalarType>::Type,
        CoercedSize<first_rows_, second_rows_>
}

#endif
