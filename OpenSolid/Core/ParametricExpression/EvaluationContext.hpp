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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricExpression/EvaluationContext.definitions.hpp>

#include <OpenSolid/Core/MatrixView.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        EvaluationContext<TScalar>::EvaluationContext(
            const MatrixView<const TScalar, -1, -1, -1>& parameterView,
            MatrixView<TScalar, -1, -1, -1>& resultView,
            int stackSize,
            int heapSize,
            int numTemporaryMatrices
        ) : _parameterView(parameterView),
            _mutableViews(
                1 + numTemporaryMatrices,
                MatrixView<TScalar, -1, -1, -1>(nullptr, 0, 0, 0)
            ),
            _memory(stackSize + heapSize),
            _stackEnd(_memory.data()),
            _heapStart(_memory.data() + stackSize),
            _heapEnd(_heapStart ) {

            // First element in mutable matrices list is result matrix
            new (&_mutableViews.front()) MatrixView<TScalar, -1, -1, -1>(resultView);
        }

        template <class TScalar>
        inline
        int
        EvaluationContext<TScalar>::numColumns() const {
            return _parameterView.numColumns();
        }

        template <class TScalar>
        inline
        void
        EvaluationContext<TScalar>::stackAllocate(int viewIndex, int numRows, int numColumns) {
            // Check that the given index does not refer to the result view
            // (index 0) and is otherwise a valid index
            assert(viewIndex > 0 && viewIndex < _mutableViews.size());

            // Check for valid matrix dimensions
            assert(numRows > 0 && numColumns > 0);

            // Get pointer to current end of internal stack
            TScalar* data = _stackEnd;

            // Advance end of internal stack by requested matrix size
            _stackEnd += numRows * numColumns;

            // Check for internal stack overflow
            assert(_stackEnd <= _heapStart);

            // Get pointer to target matrix view
            MatrixView<TScalar, -1, -1, -1>& view = _mutableViews[viewIndex];

            // Check that the existing view at this index is empty
            assert(view.data() == nullptr);

            // Create new MatrixView pointing to block of internal stack
            new (&view) MatrixView<TScalar, -1, -1, -1>(data, numRows, numColumns, numRows);
        }

        template <class TScalar>
        inline
        void
        EvaluationContext<TScalar>::stackDeallocate(int viewIndex) {
            // Check that the given index does not refer to the result view
            // (index 0) and is otherwise a valid index
            assert(viewIndex > 0 && viewIndex < _mutableViews.size());

            // Get pointer to target matrix view
            MatrixView<TScalar, -1, -1, -1>& view = _mutableViews[viewIndex];

            // Rewind end of internal stack by size of given matrix
            _stackEnd -= view.numRows() * view.numColumns();

            // Check for internal stack underflow
            assert(_stackEnd >= _memory.data());

            // Check that the target MatrixView does indeed point to the end of
            // the internal stack
            assert(view.data() == _stackEnd);

            // Use target matrix view to reset internal stack block to zero
            view.setZero();

            // Reset target MatrixView to empty
            new (&view) MatrixView<TScalar, -1, -1, -1>(nullptr, 0, 0, 0);
        }

        template <class TScalar>
        inline
        void
        EvaluationContext<TScalar>::heapAllocate(int viewIndex, int numRows, int numColumns) {
            // Check that the given index does not refer to the result view
            // (index 0) and is otherwise a valid index
            assert(viewIndex > 0 && viewIndex < _mutableViews.size());

            // Check for valid matrix dimensions
            assert(numRows > 0 && numColumns > 0);

            // Get pointer to current end of internal heap
            TScalar* data = _heapEnd;

            // Advance end of internal heap by requested matrix size
            _heapEnd += numRows * numColumns;

            // Check for internal heap overflow
            assert(_heapEnd - _memory.data() <= _memory.size());

            // Get pointer to target matrix view
            MatrixView<TScalar, -1, -1, -1>& view = _mutableViews[viewIndex];

            // Create new MatrixView pointing to block of internal heap
            new (&view) MatrixView<TScalar, -1, -1, -1>(data, numRows, numColumns, numRows);
        }

        template <class TScalar>
        const TScalar*
        dataPointer(const ConstantExpression* constantExpression);

        template <>
        const double*
        dataPointer<double>(const ConstantExpression* constantExpression) {
            return constantExpression->columnMatrix().data();
        }

        template <>
        const Interval*
        dataPointer<Interval>(const ConstantExpression* constantExpression) {
            return constantExpression->intervalColumnMatrix().data();
        }

        template <class TScalar>
        inline
        MatrixView<TScalar, -1, -1, -1>
        EvaluationContext<TScalar>::matrixView(const MatrixID<TScalar>& matrixID) {
            assert(matrixID._matrixIndex >= 0);
            assert(matrixID._matrixIndex < _mutableViews.size());
            assert(_mutableViews[matrixID._matrixIndex].data() != nullptr);
            return _mutableViews[matrixID._matrixIndex];
        }

        template <class TScalar>
        inline
        MatrixView<const TScalar, -1, -1, -1>
        EvaluationContext<TScalar>::matrixView(const MatrixID<const TScalar>& matrixID) const {
            if (matrixID._type == MatrixID<const TScalar>::INDEXED) {
                int index = matrixID._matrixIndex;
                if (index == -1) {
                    if (matrixID._isBlock) {
                        return _parameterView.block(
                            matrixID._startRow,
                            0,
                            matrixID._numRows,
                            numColumns()
                        );
                    } else {
                        return _parameterView;
                    }
                } else {
                    assert(index >= 0 && index < _mutableViews.size());
                    MatrixView<const TScalar, -1, -1, -1> view = _mutableViews[index];
                    assert(view.data() != nullptr);
                    if (matrixID._isBlock) {
                        return view.block(
                            matrixID._startRow,
                            0,
                            matrixID._numRows,
                            view.numColumns()
                        );
                    } else {
                        return view;
                    }
                }
            } else {
                const ConstantExpression* constantExpression = matrixID._constantExpression;
                const TScalar* data = dataPointer<TScalar>(constantExpression);
                if (matrixID._isBlock) {
                    return MatrixView<const TScalar, -1, -1, -1>(
                        data + matrixID._startRow,
                        matrixID._numRows,
                        numColumns(),
                        0
                    );
                } else {
                    return MatrixView<const TScalar, -1, -1, -1>(
                        data,
                        constantExpression->numDimensions(),
                        numColumns(),
                        0
                    );
                }
            }
        }
    }
}
