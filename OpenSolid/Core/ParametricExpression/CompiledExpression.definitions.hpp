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

#include <OpenSolid/Core/ParametricExpression/CompiledExpression.declarations.hpp>

#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/MatrixView.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression/EvaluationSequence.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        class CompiledExpression
        {
        private:
            ExpressionImplementationPtr _implementationPtr;
            EvaluationSequence<double> _doubleEvaluationSequence;
            EvaluationSequence<Interval> _intervalEvaluationSequence;
            EvaluationSequence<double> _doubleJacobianEvaluationSequence;
            EvaluationSequence<Interval> _intervalJacobianEvaluationSequence;
        public:
            OPENSOLID_CORE_EXPORT
            CompiledExpression(ExpressionImplementationPtr implementationPtr);

            const ExpressionImplementationPtr&
            implementation() const;

            void
            evaluate(
                const MatrixView<const double, -1, -1, -1>& parameterView,
                MatrixView<double, -1, -1, -1>& resultView
            ) const;

            void
            evaluate(
                const MatrixView<const Interval, -1, -1, -1>& parameterView,
                MatrixView<Interval, -1, -1, -1>& resultView
            ) const;

            void
            evaluateJacobian(
                const MatrixView<const double, -1, -1, -1>& parameterView,
                MatrixView<double, -1, -1, -1>& resultView
            ) const;

            void
            evaluateJacobian(
                const MatrixView<const Interval, -1, -1, -1>& parameterView,
                MatrixView<Interval, -1, -1, -1>& resultView
            ) const;
        };
    }
}
