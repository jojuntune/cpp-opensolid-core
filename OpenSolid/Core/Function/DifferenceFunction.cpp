/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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
    
    void DifferenceFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = firstOperand()(parameterValues) - secondOperand()(parameterValues);
    }
    
    void DifferenceFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = firstOperand()(parameterBounds) - secondOperand()(parameterBounds);
    }

    void DifferenceFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index) - secondOperand().derivative(index);
    }
    
    void DifferenceFunction::debug(std::ostream& stream, int indent) const {
        stream << "DifferenceFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
