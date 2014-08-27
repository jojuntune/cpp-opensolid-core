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

#include <OpenSolid/Core/ParametricExpression/ExpressionCompiler.definitions.hpp>

#include <OpenSolid/Core/ParametricExpression/EvaluationContext.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationOperation.hpp>

#include <algorithm>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar> template <class TNullaryFunction>
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TScalar>& matrixID,
            TNullaryFunction nullaryFunction
        ) {
            _evaluationOperations.push_back(
                [matrixID, nullaryFunction] (EvaluationContext<TScalar>& evaluationContext) {
                    nullaryFunction(evaluationContext.matrixView(matrixID));   
                }
            );
        }

        template <class TScalar> template <class TUnaryFunction>
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<const TScalar>& argumentID,
            const MatrixID<TScalar>& resultID,
            TUnaryFunction unaryFunction
        ) {
            _evaluationOperations.push_back(
                [argumentID, resultID, unaryFunction] (
                    EvaluationContext<TScalar>& evaluationContext
                ) {
                    unaryFunction(
                        evaluationContext.matrixView(argumentID),
                        evaluationContext.matrixView(resultID)
                    );
                }
            );
        }

        template <class TScalar> template <class TBinaryFunction>
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<const TScalar>& firstArgumentID,
            const MatrixID<const TScalar>& secondArgumentID,
            const MatrixID<TScalar>& resultID,
            TBinaryFunction binaryFunction
        ) {
            _evaluationOperations.push_back(
                [firstArgumentID, secondArgumentID, resultID, binaryFunction] (
                    EvaluationContext<TScalar>& evaluationContext
                ) {
                    binaryFunction(
                        evaluationContext.matrixView(firstArgumentID),
                        evaluationContext.matrixView(secondArgumentID),
                        evaluationContext.matrixView(resultID)
                    );
                }
            );
        }
    }
}
