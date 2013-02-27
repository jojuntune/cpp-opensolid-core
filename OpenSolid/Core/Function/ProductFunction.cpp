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

#include <OpenSolid/Core/Function/ProductFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ProductFunction::ProductFunction(
        const Function& multiplier,
        const Function& multiplicand
    ) : BinaryOperation(multiplier, multiplicand) {

        assert(multiplier.numDimensions() == 1);
    }
    
    int ProductFunction::numDimensions() const {
        return secondOperand().numDimensions();
    }

    bool ProductFunction::isDuplicate(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, true);
    }

    Function ProductFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedFirstOperand = firstOperand().deduplicated(others);
        Function deduplicatedSecondOperand = secondOperand().deduplicated(others);
        return deduplicatedFirstOperand * deduplicatedSecondOperand;
    }
    
    void ProductFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = secondOperand()(parameterValues) *
            firstOperand()(parameterValues).eval().asDiagonal();
    }
    
    void ProductFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = secondOperand()(parameterBounds) *
            firstOperand()(parameterBounds).eval().asDiagonal();
    }

    Function ProductFunction::derivative(int index) const {
        return firstOperand().derivative(index) * secondOperand()
            + firstOperand() * secondOperand().derivative(index);
    }
    
    void ProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "ProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
