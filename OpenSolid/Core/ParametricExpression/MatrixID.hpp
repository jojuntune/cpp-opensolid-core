/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/Core/ParametricExpression/MatrixID.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        inline
        MatrixID<TScalar>::MatrixID() :
            _matrixIndex(-1) {
        }

        template <class TScalar>
        inline
        MatrixID<TScalar>::MatrixID(int matrixIndex) :
            _matrixIndex(matrixIndex) {
        }

        template <class TScalar>
        inline
        MatrixID<const TScalar>::MatrixID(
            Type type,
            int matrixIndex,
            const ConstantExpression* constantExpression,
            bool isBlock,
            int startRow,
            int numRows
        ) : _type(type),
            _matrixIndex(matrixIndex),
            _constantExpression(constantExpression),
            _isBlock(isBlock),
            _startRow(startRow),
            _numRows(numRows) {
        }

        template <class TScalar>
        inline
        MatrixID<const TScalar>::MatrixID(int matrixIndex) :
            _type(INDEXED),
            _matrixIndex(matrixIndex),
            _constantExpression(nullptr),
            _isBlock(false),
            _startRow(0),
            _numRows(0) {
        }

        template <class TScalar>
        inline
        MatrixID<const TScalar>::MatrixID(const ConstantExpression* constantExpression) :
            _type(CONSTANT),
            _matrixIndex(-1),
            _constantExpression(constantExpression),
            _isBlock(false),
            _startRow(0),
            _numRows(0) {
        }

        template <class TScalar>
        inline
        MatrixID<const TScalar>::MatrixID() :
            _type(INDEXED),
            _matrixIndex(-1),
            _constantExpression(nullptr),
            _isBlock(false),
            _startRow(0),
            _numRows(0) {
        }

        template <class TScalar>
        inline
        MatrixID<const TScalar>::MatrixID(MatrixID<TScalar> matrixID) :
            _type(INDEXED),
            _matrixIndex(matrixID._matrixIndex),
            _constantExpression(nullptr),
            _isBlock(false),
            _startRow(0),
            _numRows(0) {
        }

        template <class TScalar>
        inline
        MatrixID<const TScalar>
        MatrixID<const TScalar>::block(int startRow, int numRows) const {
            return MatrixID<const TScalar>(
                _type,
                _matrixIndex,
                _constantExpression,
                true,
                _startRow + startRow,
                numRows
            );
        }

        template <class TScalar>
        bool
        MatrixID<const TScalar>::operator<(const MatrixID<const TScalar>& other) const {
            if (_type != other._type) {
                return _type < other._type;
            } else if (_matrixIndex != other._matrixIndex) {
                return _matrixIndex < other._matrixIndex;
            } else if (_constantExpression != other._constantExpression) {
                return _constantExpression < other._constantExpression;
            } else if (_isBlock != other._isBlock) {
                return _isBlock < other._isBlock;
            } else if (_startRow != other._startRow) {
                return _startRow < other._startRow;
            } else if (_numRows != other._numRows) {
                return _numRows < other._numRows;
            } else {
                return false;
            }
        }
    }
}
