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

#include <OpenSolid/Core/ParametricExpression/ExpressionCompiler.declarations.hpp>

#include <OpenSolid/Core/ParametricExpression/CompiledExpression.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationOperation.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/MatrixID.declarations.hpp>

#include <map>
#include <vector>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        class ExpressionCompiler
        {
        private:
            typedef std::pair<
                const ExpressionImplementation*,
                MatrixID<const TScalar>
            > EvaluationKey;

            struct StackEntry
            {
                int matrixIndex;
                int numRows;
                int numComponents;
            };

            std::vector<EvaluationOperation<TScalar>> _evaluationOperations;
            
            std::vector<StackEntry> _stackEntries;
            
            int _currentStackRows;
            int _maxStackRows;
            int _currentStackComponents;
            int _maxStackComponents;

            int _numHeapRows;
            int _numHeapComponents;

            int _maxTemporaryMatrices;
            std::vector<int> _availableMatrixIndices;
            
            std::map<EvaluationKey, MatrixID<const TScalar>> _evaluationCache;
            std::map<EvaluationKey, MatrixID<const TScalar>> _jacobianCache;
        private:
            OPENSOLID_CORE_EXPORT
            int
            allocateMatrixIndex();

            OPENSOLID_CORE_EXPORT
            void
            unwindStack(const std::vector<StackEntry>& stackEntries);

            OPENSOLID_CORE_EXPORT
            void
            evaluateExpression(
                const ExpressionImplementation* expression,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            OPENSOLID_CORE_EXPORT
            void
            evaluateExpressionJacobian(
                const ExpressionImplementation* expression,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            OPENSOLID_CORE_EXPORT
            CompiledExpression<TScalar>
            compiledExpression() const;
        public:
            OPENSOLID_CORE_EXPORT
            ExpressionCompiler();

            OPENSOLID_CORE_EXPORT
            MatrixID<TScalar>
            createTemporary(int numRows);

            OPENSOLID_CORE_EXPORT
            MatrixID<TScalar>
            createTemporary(int numRows, int numColumns);

            OPENSOLID_CORE_EXPORT
            MatrixID<const TScalar>
            evaluate(
                const ExpressionImplementation* expression,
                const MatrixID<const TScalar>& parameterID
            );

            OPENSOLID_CORE_EXPORT
            void
            evaluate(
                const ExpressionImplementation* expression,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            OPENSOLID_CORE_EXPORT
            MatrixID<const TScalar>
            evaluateJacobian(
                const ExpressionImplementation* expression,
                const MatrixID<const TScalar>& parameterID
            );

            OPENSOLID_CORE_EXPORT
            void
            evaluateJacobian(
                const ExpressionImplementation* expression,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            template <class TNullaryFunction>
            void
            compute(const MatrixID<TScalar>& matrixID, TNullaryFunction nullaryFunction);

            template <class TUnaryFunction>
            void
            compute(
                const MatrixID<const TScalar>& argumentID,
                const MatrixID<TScalar>& resultID,
                TUnaryFunction unaryFunction
            );

            template <class TBinaryFunction>
            void
            compute(
                const MatrixID<const TScalar>& firstArgumentID,
                const MatrixID<const TScalar>& secondArgumentID,
                const MatrixID<TScalar>& resultID,
                TBinaryFunction binaryFunction
            );

            OPENSOLID_CORE_EXPORT
            static CompiledExpression<TScalar>
            compile(const ExpressionImplementation* expression);

            OPENSOLID_CORE_EXPORT
            static CompiledExpression<TScalar>
            compileJacobian(const ExpressionImplementation* expression);
        };
    }
}
