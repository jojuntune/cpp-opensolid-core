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

#include <OpenSolid/Core/ParametricExpression/BinaryOperation.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        BinaryOperation::numParametersImpl() const {
            return firstOperand()->numParameters();
        }

        ExpressionImplementationPtr
        BinaryOperation::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
            return this->withNewOperands(
                firstOperand()->deduplicated(deduplicationCache),
                secondOperand()->deduplicated(deduplicationCache)
            );
        }

        ExpressionImplementationPtr
        BinaryOperation::composedImpl(const ExpressionImplementationPtr& innerExpression) const {
            return this->withNewOperands(
                firstOperand()->composed(innerExpression),
                secondOperand()->composed(innerExpression)
            );
        }

        bool
        BinaryOperation::duplicateOperands(
            const ExpressionImplementationPtr& other,
            bool isCommutative
        ) const {
            ExpressionImplementationPtr otherFirstOperand =
                other->cast<BinaryOperation>()->firstOperand();
            ExpressionImplementationPtr otherSecondOperand =
                other->cast<BinaryOperation>()->secondOperand();

            bool nonCommutativeCheck = firstOperand()->isDuplicateOf(otherFirstOperand) &&
                secondOperand()->isDuplicateOf(otherSecondOperand);
                
            if (nonCommutativeCheck) {
                return true;
            } else if (isCommutative) {
                return (
                    firstOperand()->isDuplicateOf(otherSecondOperand) &&
                    secondOperand()->isDuplicateOf(otherFirstOperand)
                );
            } else {
                return false;
            }
        }

        BinaryOperation::BinaryOperation(
            const ExpressionImplementationPtr& firstOperand,
            const ExpressionImplementationPtr& secondOperand
        ) : _firstOperand(firstOperand),
            _secondOperand(secondOperand) {
            
            assert(firstOperand->numParameters() == secondOperand->numParameters());
        }

        ExpressionImplementationPtr
        BinaryOperation::withNewOperands(
            const ExpressionImplementationPtr& newFirstOperand,
            const ExpressionImplementationPtr& newSecondOperand
        ) const {
            return withNewOperandsImpl(newFirstOperand, newSecondOperand);
        }
    }
}
