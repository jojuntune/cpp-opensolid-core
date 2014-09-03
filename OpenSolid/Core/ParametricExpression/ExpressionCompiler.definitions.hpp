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

#include <OpenSolid/Core/ParametricExpression/EvaluationOperation.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationSequence.declarations.hpp>
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
                const ExpressionImplementationPtr& expressionPtr,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            OPENSOLID_CORE_EXPORT
            void
            evaluateExpressionJacobian(
                const ExpressionImplementationPtr& expressionPtr,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            OPENSOLID_CORE_EXPORT
            EvaluationSequence<TScalar>
            evaluationSequence() const;
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
                const ExpressionImplementationPtr& expressionPtr,
                const MatrixID<const TScalar>& parameterID
            );

            OPENSOLID_CORE_EXPORT
            void
            evaluate(
                const ExpressionImplementationPtr& expressionPtr,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            OPENSOLID_CORE_EXPORT
            MatrixID<const TScalar>
            evaluateJacobian(
                const ExpressionImplementationPtr& expressionPtr,
                const MatrixID<const TScalar>& parameterID
            );

            OPENSOLID_CORE_EXPORT
            void
            evaluateJacobian(
                const ExpressionImplementationPtr& expressionPtr,
                const MatrixID<const TScalar>& parameterID,
                const MatrixID<TScalar>& resultID
            );

            template <
                class TFirstScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TThirdScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                const MatrixID<TThirdScalar>& thirdID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TThirdScalar,
                class TFourthScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                const MatrixID<TThirdScalar>& thirdID,
                const MatrixID<TFourthScalar>& fourthID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TThirdScalar,
                class TFourthScalar,
                class TFifthScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                const MatrixID<TThirdScalar>& thirdID,
                const MatrixID<TFourthScalar>& fourthID,
                const MatrixID<TFifthScalar>& fifthID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TThirdScalar,
                class TFourthScalar,
                class TFifthScalar,
                class TSixthScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                const MatrixID<TThirdScalar>& thirdID,
                const MatrixID<TFourthScalar>& fourthID,
                const MatrixID<TFifthScalar>& fifthID,
                const MatrixID<TSixthScalar>& sixthID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TThirdScalar,
                class TFourthScalar,
                class TFifthScalar,
                class TSixthScalar,
                class TSeventhScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                const MatrixID<TThirdScalar>& thirdID,
                const MatrixID<TFourthScalar>& fourthID,
                const MatrixID<TFifthScalar>& fifthID,
                const MatrixID<TSixthScalar>& sixthID,
                const MatrixID<TSeventhScalar>& seventhID,
                TFunction function
            );

            template <
                class TFirstScalar,
                class TSecondScalar,
                class TThirdScalar,
                class TFourthScalar,
                class TFifthScalar,
                class TSixthScalar,
                class TSeventhScalar,
                class TEigthScalar,
                class TFunction
            >
            void
            compute(
                const MatrixID<TFirstScalar>& firstID,
                const MatrixID<TSecondScalar>& secondID,
                const MatrixID<TThirdScalar>& thirdID,
                const MatrixID<TFourthScalar>& fourthID,
                const MatrixID<TFifthScalar>& fifthID,
                const MatrixID<TSixthScalar>& sixthID,
                const MatrixID<TSeventhScalar>& seventhID,
                const MatrixID<TEigthScalar>& eigthID,
                TFunction function
            );

            OPENSOLID_CORE_EXPORT
            static EvaluationSequence<TScalar>
            compile(const ExpressionImplementationPtr& expressionPtr);

            OPENSOLID_CORE_EXPORT
            static EvaluationSequence<TScalar>
            compileJacobian(const ExpressionImplementationPtr& expressionPtr);
        };
    }
}
