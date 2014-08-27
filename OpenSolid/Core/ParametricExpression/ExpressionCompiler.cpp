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

#include <OpenSolid/Core/ParametricExpression/ExpressionCompiler.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression/ComponentsExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationContext.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationOperation.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationSequence.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>
#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/MatrixID.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

#include <unordered_map>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar>
        int
        ExpressionCompiler<TScalar>::allocateMatrixIndex() {
            if (_availableMatrixIndices.empty()) {
                ++_maxTemporaryMatrices;
                // Note that _maxTemporaryMatrices is returned *after*
                // incrementing it since temporary matrix indices start at 1,
                // not 0
                return _maxTemporaryMatrices;
            } else {
                int result = _availableMatrixIndices.back();
                _availableMatrixIndices.pop_back();
                return result;
            }
        }

        template <class TScalar>
        void
        ExpressionCompiler<TScalar>::unwindStack(const std::vector<StackEntry>& stackEntries) {
            std::vector<int> stackIndices(stackEntries.size());
            _availableMatrixIndices.reserve(_availableMatrixIndices.size() + stackEntries.size());
            for (int i = 0; i < stackEntries.size(); ++i) {
                int matrixIndex = stackEntries[i].matrixIndex;

                // Collect matrix indices to use in bulk deallocation operation
                stackIndices[i] = matrixIndex;

                // Mark matrix index as available for reuse
                _availableMatrixIndices.push_back(matrixIndex);

                // Decrement count of current stack-allocated rows
                _currentStackRows -= stackEntries[i].numRows;

                // Decrement count of current stack-allocated components
                _currentStackComponents -= stackEntries[i].numComponents;
            }

            // Add evaluation operation to perform actual stack deallocation
            _evaluationOperations.push_back(
                [stackIndices] (EvaluationContext<TScalar>& evaluationContext) {
                    for (int stackIndex : stackIndices) {
                        evaluationContext.stackDeallocate(stackIndex);
                    }
                }
            );
        }

        template <class TScalar>
        void
        ExpressionCompiler<TScalar>::evaluateExpression(
            const ExpressionImplementation* expression,
            const MatrixID<const TScalar>& parameterID,
            const MatrixID<TScalar>& resultID
        ) {
            // Save current stack state
            std::vector<StackEntry> stackEntries;
            stackEntries.swap(_stackEntries);

            // Descend into expression
            expression->evaluate(parameterID, resultID, *this);

            // Restore current stack state and store any stack-allocated matrix
            // indices back in stackEntries
            stackEntries.swap(_stackEntries);

            // Deallocate stack-allocated matrices
            unwindStack(stackEntries);
        }

        template <class TScalar>
        void
        ExpressionCompiler<TScalar>::evaluateExpressionJacobian(
            const ExpressionImplementation* expression,
            const MatrixID<const TScalar>& parameterID,
            const MatrixID<TScalar>& resultID
        ) {
            // Save current stack state
            std::vector<StackEntry> stackEntries;
            stackEntries.swap(_stackEntries);

            // Descend into expression
            expression->evaluateJacobian(parameterID, resultID, *this);

            // Restore current stack state and store any stack-allocated matrix
            // indices back in stackEntries
            stackEntries.swap(_stackEntries);

            // Deallocate stack-allocated matrices
            unwindStack(stackEntries);
        }

        template <class TScalar>
        EvaluationSequence<TScalar>
        ExpressionCompiler<TScalar>::evaluationSequence() const {
            return EvaluationSequence<TScalar>(
                _evaluationOperations,
                _maxStackRows,
                _maxStackComponents,
                _numHeapRows,
                _numHeapComponents,
                _maxTemporaryMatrices
            );
        }

        template <class TScalar>
        ExpressionCompiler<TScalar>::ExpressionCompiler() :
            _currentStackRows(0),
            _maxStackRows(0),
            _currentStackComponents(0),
            _maxStackComponents(0),
            _numHeapRows(0),
            _numHeapComponents(0),
            _maxTemporaryMatrices(0) {
        }

        template <class TScalar>
        MatrixID<TScalar>
        ExpressionCompiler<TScalar>::createTemporary(int numRows) {
            int matrixIndex = allocateMatrixIndex();

            StackEntry stackEntry;
            stackEntry.matrixIndex = matrixIndex;
            stackEntry.numRows = numRows;
            stackEntry.numComponents = 0;

            _stackEntries.push_back(stackEntry);
            _currentStackRows += numRows;
            _maxStackRows = std::max(_maxStackRows, _currentStackRows);

            _evaluationOperations.push_back(
                [matrixIndex, numRows] (EvaluationContext<TScalar>& evaluationContext) {
                    evaluationContext.stackAllocate(
                        matrixIndex,
                        numRows,
                        evaluationContext.numColumns()
                    );
                }
            );

            return MatrixID<TScalar>(matrixIndex);
        }

        template <class TScalar>
        MatrixID<TScalar>
        ExpressionCompiler<TScalar>::createTemporary(int numRows, int numColumns) {
            int matrixIndex = allocateMatrixIndex();

            StackEntry stackEntry;
            stackEntry.matrixIndex = matrixIndex;
            stackEntry.numRows = 0;
            stackEntry.numComponents = numRows * numColumns;

            _stackEntries.push_back(stackEntry);
            _currentStackComponents += numRows * numColumns;
            _maxStackComponents = std::max(_maxStackComponents, _currentStackComponents);

            _evaluationOperations.push_back(
                [matrixIndex, numRows, numColumns] (EvaluationContext<TScalar>& evaluationContext) {
                    evaluationContext.stackAllocate(matrixIndex, numRows, numColumns);
                }
            );

            return MatrixID<TScalar>(matrixIndex);
        }

        template <class TScalar>
        MatrixID<const TScalar>
        ExpressionCompiler<TScalar>::evaluate(
            const ExpressionImplementation* expression,
            const MatrixID<const TScalar>& parameterID
        ) {
            if (expression->isIdentityExpression()) {
                // Identity expression: simply return parameter values
                return parameterID;
            } else if (expression->isConstantExpression()) {
                // Constant expression: return view into internal matrix
                return MatrixID<const TScalar>(expression->cast<ConstantExpression>());
            } else if (expression->isParameterExpression()) {
                // Parameter expresssion: return row of parameter values
                return parameterID.block(
                    expression->cast<ParameterExpression>()->parameterIndex(),
                    1
                );
            } else if (expression->isComponentsExpression()) {
                // Components expression: return block of operand results
                return evaluate(
                    expression->cast<ComponentsExpression>()->operand().get(),
                    parameterID
                ).block(
                    expression->cast<ComponentsExpression>()->startIndex(),
                    expression->cast<ComponentsExpression>()->numComponents()
                );
            } else {
                EvaluationKey evaluationKey(expression, parameterID);
                auto cacheIterator = _evaluationCache.find(evaluationKey);
                if (cacheIterator != _evaluationCache.end()) {
                    // Expression has already been evaluated with this parameter
                    // matrix - return the cached result
                    return cacheIterator->second;
                } else {
                    // Allocate a new heap-based matrix to evaluate expression into
                    int resultIndex = allocateMatrixIndex();
                    MatrixID<TScalar> resultID(resultIndex);
                    int numDimensions = expression->numDimensions();
                    _evaluationOperations.push_back(
                        [resultIndex, numDimensions] (
                            EvaluationContext<TScalar>& evaluationContext
                        ) {
                            evaluationContext.heapAllocate(
                                resultIndex,
                                numDimensions,
                                evaluationContext.numColumns()
                            );
                        }
                    );
                    // Update the count of how many rows (of matrices with
                    // number of columns equal to the number of parameter
                    // columns) are allocated on the 'heap' during expression
                    // evaluation
                    _numHeapRows += numDimensions;

                    // Evaluate expression into newly-allocated matrix
                    evaluateExpression(expression, parameterID, resultID);

                    // Insert result into cache
                    _evaluationCache[evaluationKey] = resultID;

                    return resultID;
                }
            }
        }

        template <class TScalar>
        void
        ExpressionCompiler<TScalar>::evaluate(
            const ExpressionImplementation* expression,
            const MatrixID<const TScalar>& parameterID,
            const MatrixID<TScalar>& resultID
        ) {
            if (expression->isIdentityExpression()) {
                // Identity expression: assign parameter values to result
                _evaluationOperations.push_back(
                    [parameterID, resultID] (EvaluationContext<TScalar>& evaluationContext) {
                        evaluationContext.matrixView(resultID) = (
                            evaluationContext.matrixView(parameterID)
                        );
                    }
                );
            } else if (expression->isConstantExpression()) {
                // Constant expression: assign constant values to result
                MatrixID<const TScalar> constantID(expression->cast<ConstantExpression>());
                _evaluationOperations.push_back(
                    [resultID, constantID] (EvaluationContext<TScalar>& evaluationContext) {
                        evaluationContext.matrixView(resultID) = (
                            evaluationContext.matrixView(constantID)
                        );
                    }
                );
            } else if (expression->isParameterExpression()) {
                // Parameter expresssion: return row of parameter values
                MatrixID<const TScalar> rowID =  parameterID.block(
                    expression->cast<ParameterExpression>()->parameterIndex(),
                    1
                );
                _evaluationOperations.push_back(
                    [resultID, rowID] (EvaluationContext<TScalar>& evaluationContext) {
                        evaluationContext.matrixView(resultID) = (
                            evaluationContext.matrixView(rowID)
                        );
                    }
                );
            } else if (expression->isComponentsExpression()) {
                // Components expression: return block of operand results
                MatrixID<const TScalar> componentsID = evaluate(
                    expression->cast<ComponentsExpression>()->operand().get(),
                    parameterID
                ).block(
                    expression->cast<ComponentsExpression>()->startIndex(),
                    expression->cast<ComponentsExpression>()->numComponents()
                );
                _evaluationOperations.push_back(
                    [resultID, componentsID] (EvaluationContext<TScalar>& evaluationContext) {
                        evaluationContext.matrixView(resultID) = (
                            evaluationContext.matrixView(componentsID)
                        );
                    }
                );
            } else {
                EvaluationKey evaluationKey(expression, parameterID);
                auto cacheIterator = _evaluationCache.find(evaluationKey);
                if (cacheIterator != _evaluationCache.end()) {
                    // Expression has already been evaluated with this parameter
                    // matrix - copy the cached values to the result
                    MatrixID<const TScalar> cachedID = cacheIterator->second;
                    _evaluationOperations.push_back(
                        [resultID, cachedID] (EvaluationContext<TScalar>& evaluationContext) {
                            evaluationContext.matrixView(resultID) = (
                                evaluationContext.matrixView(cachedID)
                            );
                        }
                    );
                } else {
                    // Evaluate expression into result matrix
                    evaluateExpression(expression, parameterID, resultID);
                }
            }
        }

        template <class TScalar>
        MatrixID<const TScalar>
        ExpressionCompiler<TScalar>::evaluateJacobian(
            const ExpressionImplementation* expression,
            const MatrixID<const TScalar>& parameterID
        ) {
            EvaluationKey evaluationKey(expression, parameterID);
            auto cacheIterator = _jacobianCache.find(evaluationKey);
            if (cacheIterator != _jacobianCache.end()) {
                // Expression Jacobian has already been evaluated with this
                // parameter matrix - return the cached result
                return cacheIterator->second;
            } else {
                // Allocate a new heap-based matrix to evaluate Jacobian into
                int resultIndex = allocateMatrixIndex();
                MatrixID<TScalar> resultID(resultIndex);
                int numDimensions = expression->numDimensions();
                int numParameters = expression->numParameters();
                _evaluationOperations.push_back(
                    [resultIndex, numDimensions, numParameters] (
                        EvaluationContext<TScalar>& evaluationContext
                    ) {
                        evaluationContext.heapAllocate(resultIndex, numDimensions, numParameters);
                    }
                );
                // Update the count of how many components of fixed-size
                // matrices are allocated on the 'heap' during expression
                // evaluation
                _numHeapComponents += numDimensions * numParameters;

                // Evaluate expression into newly-allocated matrix
                evaluateExpressionJacobian(expression, parameterID, resultID);

                // Insert result into cache
                _jacobianCache[evaluationKey] = resultID;

                return resultID;
            }
        }

        template <class TScalar>
        void
        ExpressionCompiler<TScalar>::evaluateJacobian(
            const ExpressionImplementation* expression,
            const MatrixID<const TScalar>& parameterID,
            const MatrixID<TScalar>& resultID
        ) {
            EvaluationKey evaluationKey(expression, parameterID);
            auto cacheIterator = _jacobianCache.find(evaluationKey);
            if (cacheIterator != _jacobianCache.end()) {
                // Expression Jacobian has already been evaluated with this
                // parameter matrix - copy the cached values to the result
                MatrixID<const TScalar> cachedID = cacheIterator->second;
                _evaluationOperations.push_back(
                    [resultID, cachedID] (EvaluationContext<TScalar>& evaluationContext) {
                        evaluationContext.matrixView(resultID) = (
                            evaluationContext.matrixView(cachedID)
                        );
                    }
                );
            } else {
                // Evaluate expression into result matrix
                evaluateExpressionJacobian(expression, parameterID, resultID);
            }
        }

        template <class TScalar>
        EvaluationSequence<TScalar>
        ExpressionCompiler<TScalar>::compile(const ExpressionImplementation* expression) {
            ExpressionCompiler<TScalar> compiler;
            MatrixID<const TScalar> parameterID(-1);
            MatrixID<TScalar> resultID(0);
            compiler.evaluate(expression, parameterID, resultID);
            return compiler.evaluationSequence();
        }

        template <class TScalar>
        EvaluationSequence<TScalar>
        ExpressionCompiler<TScalar>::compileJacobian(const ExpressionImplementation* expression) {
            ExpressionCompiler<TScalar> compiler;
            MatrixID<const TScalar> parameterID(-1);
            MatrixID<TScalar> resultID(0);
            compiler.evaluateJacobian(expression, parameterID, resultID);
            return compiler.evaluationSequence();
        }

        template class ExpressionCompiler<double>;
        template class ExpressionCompiler<Interval>;
    }
}
