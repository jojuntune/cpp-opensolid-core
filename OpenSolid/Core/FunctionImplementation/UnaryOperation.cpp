/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
*************************************************************************************/

#include <OpenSolid/Core/FunctionImplementation/UnaryOperation.hpp>

namespace opensolid
{
    int
    UnaryOperation::numParametersImpl() const {
        return operand()->numParameters();
    }

    bool
    UnaryOperation::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return this->operand()->isDuplicateOf(other->cast<UnaryOperation>()->operand());
    }

    FunctionImplementationPtr
    UnaryOperation::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this->withNewOperand(operand()->deduplicated(deduplicationCache));
    }

    FunctionImplementationPtr
    UnaryOperation::composeImpl(const FunctionImplementationPtr& innerFunction) const {
        return this->withNewOperand(operand()->compose(innerFunction));
    }
    
    UnaryOperation::UnaryOperation(const FunctionImplementationPtr& operand) :
        _operand(operand) {
    }

    FunctionImplementationPtr
    UnaryOperation::withNewOperand(const FunctionImplementationPtr& newOperand) {
        return withNewOperandImpl(newOperand);
    }
}
