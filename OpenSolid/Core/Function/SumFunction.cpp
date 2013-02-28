/*************************************************************************************
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

#include <OpenSolid/Core/Function/SumFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    SumFunction::SumFunction(const Function& firstOperand, const Function& secondOperand) :
        BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand.numDimensions() == secondOperand.numDimensions());
    }
    
    int SumFunction::numDimensions() const {
        return firstOperand().numDimensions();
    }

    bool SumFunction::isDuplicate(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, true);
    }

    Function SumFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedFirstOperand = firstOperand().deduplicated(others);
        Function deduplicatedSecondOperand = secondOperand().deduplicated(others);
        return new SumFunction(deduplicatedFirstOperand, deduplicatedSecondOperand);
    }
    
    void SumFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& resultCache
    ) const {
        results = firstOperand()(parameterValues) + secondOperand()(parameterValues);
    }
    
    void SumFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& resultCache
    ) const {
        results = firstOperand()(parameterBounds) + secondOperand()(parameterBounds);
    }

    Function SumFunction::derivative(int index) const {
        return firstOperand().derivative(index) + secondOperand().derivative(index);
    }
    
    void SumFunction::debug(std::ostream& stream, int indent) const {
        stream << "SumFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
