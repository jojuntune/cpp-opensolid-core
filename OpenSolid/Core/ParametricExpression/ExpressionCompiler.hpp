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
        template <class TScalar>
        template <
            class TFirstScalar,
            class TFunction
        >
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID)
                    );   
                }
            );
        }

        template <class TScalar>
        template <
            class TFirstScalar,
            class TSecondScalar,
            class TFunction
        >
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID)
                    );   
                }
            );
        }

        template <class TScalar>
        template <
            class TFirstScalar,
            class TSecondScalar,
            class TThirdScalar,
            class TFunction
        >
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            const MatrixID<TThirdScalar>& thirdID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID),
                        evaluationContext.matrixView(thirdID)
                    );   
                }
            );
        }

        template <class TScalar>
        template <
            class TFirstScalar,
            class TSecondScalar,
            class TThirdScalar,
            class TFourthScalar,
            class TFunction
        >
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            const MatrixID<TThirdScalar>& thirdID,
            const MatrixID<TFourthScalar>& fourthID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID),
                        evaluationContext.matrixView(thirdID),
                        evaluationContext.matrixView(fourthID)
                    );   
                }
            );
        }

        template <class TScalar>
        template <
            class TFirstScalar,
            class TSecondScalar,
            class TThirdScalar,
            class TFourthScalar,
            class TFifthScalar,
            class TFunction
        >
        void
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            const MatrixID<TThirdScalar>& thirdID,
            const MatrixID<TFourthScalar>& fourthID,
            const MatrixID<TFifthScalar>& fifthID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID),
                        evaluationContext.matrixView(thirdID),
                        evaluationContext.matrixView(fourthID),
                        evaluationContext.matrixView(fifthID)
                    );   
                }
            );
        }

        template <class TScalar>
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
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            const MatrixID<TThirdScalar>& thirdID,
            const MatrixID<TFourthScalar>& fourthID,
            const MatrixID<TFifthScalar>& fifthID,
            const MatrixID<TSixthScalar>& sixthID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID),
                        evaluationContext.matrixView(thirdID),
                        evaluationContext.matrixView(fourthID),
                        evaluationContext.matrixView(fifthID),
                        evaluationContext.matrixView(sixthID)
                    );   
                }
            );
        }

        template <class TScalar>
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
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            const MatrixID<TThirdScalar>& thirdID,
            const MatrixID<TFourthScalar>& fourthID,
            const MatrixID<TFifthScalar>& fifthID,
            const MatrixID<TSixthScalar>& sixthID,
            const MatrixID<TSeventhScalar>& seventhID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID),
                        evaluationContext.matrixView(thirdID),
                        evaluationContext.matrixView(fourthID),
                        evaluationContext.matrixView(fifthID),
                        evaluationContext.matrixView(sixthID),
                        evaluationContext.matrixView(seventhID)
                    );   
                }
            );
        }

        template <class TScalar>
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
        ExpressionCompiler<TScalar>::compute(
            const MatrixID<TFirstScalar>& firstID,
            const MatrixID<TSecondScalar>& secondID,
            const MatrixID<TThirdScalar>& thirdID,
            const MatrixID<TFourthScalar>& fourthID,
            const MatrixID<TFifthScalar>& fifthID,
            const MatrixID<TSixthScalar>& sixthID,
            const MatrixID<TSeventhScalar>& seventhID,
            const MatrixID<TEigthScalar>& eigthID,
            TFunction function
        ) {
            _evaluationOperations.push_back(
                [=] (EvaluationContext<TScalar>& evaluationContext) {
                    function(
                        evaluationContext.matrixView(firstID),
                        evaluationContext.matrixView(secondID),
                        evaluationContext.matrixView(thirdID),
                        evaluationContext.matrixView(fourthID),
                        evaluationContext.matrixView(fifthID),
                        evaluationContext.matrixView(sixthID),
                        evaluationContext.matrixView(seventhID),
                        evaluationContext.matrixView(eigthID)
                    );   
                }
            );
        }
    }
}
