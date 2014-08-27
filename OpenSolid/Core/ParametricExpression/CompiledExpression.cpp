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

#include <OpenSolid/Core/ParametricExpression/CompiledExpression.definitions.hpp>

#include <OpenSolid/Core/ParametricExpression/EvaluationContext.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationOperation.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        CompiledExpression<TScalar>::CompiledExpression(
            std::vector<EvaluationOperation<TScalar>> evaluationOperations,
            int maxStackRows,
            int maxStackComponents,
            int numHeapRows,
            int numHeapComponents,
            int maxTemporaryMatrices
        ) : _evaluationOperations(std::move(evaluationOperations)),
            _maxStackRows(maxStackRows),
            _maxStackComponents(maxStackComponents),
            _numHeapRows(numHeapRows),
            _numHeapComponents(numHeapComponents),
            _maxTemporaryMatrices(maxTemporaryMatrices) {
        }

        template <class TScalar>
        void
        CompiledExpression<TScalar>::evaluate(
            const MatrixView<TScalar, -1, -1, -1>& parameterView,
            MatrixView<TScalar, -1, -1, -1>& resultView
        ) const {
            int numColumns = parameterView.numColumns();
            int stackSize = _maxStackRows * numColumns + _maxStackComponents;
            int heapSize = _numHeapRows * numColumns + _numHeapComponents;
            EvaluationContext<TScalar> evaluationContext(
                parameterView,
                resultView,
                stackSize,
                heapSize,
                _maxTemporaryMatrices
            );
            for (const EvaluationOperation<TScalar>& evaluationOperation : _evaluationOperations) {
                evaluationOperation.execute(evaluationContext);
            }
        }

        template class CompiledExpression<double>;
        template class CompiledExpression<Interval>;
    }
}
