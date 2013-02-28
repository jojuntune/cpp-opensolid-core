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

#include <OpenSolid/Core/Function/QuotientFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    QuotientFunction::QuotientFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(secondOperand.numDimensions() == 1);
    }
    
    int QuotientFunction::numDimensions() const {
        return firstOperand().numDimensions();
    }

    bool QuotientFunction::isDuplicate(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, false);
    }

    Function QuotientFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedFirstOperand = firstOperand().deduplicated(others);
        Function deduplicatedSecondOperand = secondOperand().deduplicated(others);
        return new QuotientFunction(deduplicatedFirstOperand, deduplicatedSecondOperand);
    }
    
    void QuotientFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& resultCache
    ) const {
        results = firstOperand()(parameterValues).array() /
            secondOperand()(parameterValues).replicate(numDimensions(), 1).array();
    }
    
    void QuotientFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& resultCache
    ) const {
        results = firstOperand()(parameterBounds).array() /
            secondOperand()(parameterBounds).replicate(numDimensions(), 1).array();
    }

    Function QuotientFunction::derivative(int index) const {
        Function firstDerivative = firstOperand().derivative(index);
        Function secondDerivative = secondOperand().derivative(index);
        return(firstDerivative * secondOperand() - firstOperand() * secondDerivative) /
            secondOperand().squaredNorm();
    }
    
    void QuotientFunction::debug(std::ostream& stream, int indent) const {
        stream << "QuotientFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
