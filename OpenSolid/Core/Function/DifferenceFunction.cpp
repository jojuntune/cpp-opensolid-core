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

#include <OpenSolid/Core/Function/DifferenceFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    DifferenceFunction::DifferenceFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand.numDimensions() == secondOperand.numDimensions());
    }
    
    int DifferenceFunction::numDimensions() const {
        return firstOperand().numDimensions();
    }
    
    void DifferenceFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = firstOperand()(parameterValues) - secondOperand()(parameterValues);
    }
    
    void DifferenceFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = firstOperand()(parameterBounds) - secondOperand()(parameterBounds);
    }

    Function DifferenceFunction::derivative(int index) const {
        return firstOperand().derivative(index) - secondOperand().derivative(index);
    }
    
    void DifferenceFunction::debug(std::ostream& stream, int indent) const {
        stream << "DifferenceFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
