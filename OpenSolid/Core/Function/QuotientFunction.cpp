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
    
    void QuotientFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = firstOperand()(parameterValues).array() /
            secondOperand()(parameterValues).replicate(numDimensions(), 1).array();
    }
    
    void QuotientFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = firstOperand()(parameterBounds).array() /
            secondOperand()(parameterBounds).replicate(numDimensions(), 1).array();
    }

    void QuotientFunction::getDerivative(int index, Function& result) const {
        Function firstDerivative = firstOperand().derivative(index);
        Function secondDerivative = secondOperand().derivative(index);
        result =(firstDerivative * secondOperand() - firstOperand() * secondDerivative) /
            secondOperand().squaredNorm();
    }
    
    void QuotientFunction::debug(std::ostream& stream, int indent) const {
        stream << "QuotientFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
