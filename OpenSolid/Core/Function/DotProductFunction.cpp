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

#include "DotProductFunction.hpp"

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    DotProductFunction::DotProductFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand.numDimensions() == secondOperand.numDimensions());
    }
    
    int DotProductFunction::numDimensions() const {
        return 1;
    }
    
    void DotProductFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = firstOperand()(parameterValues).cwiseProduct(secondOperand()(parameterValues)).
            colwise().sum();
    }
    
    void DotProductFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = firstOperand()(parameterBounds).cwiseProduct(secondOperand()(parameterBounds)).
            colwise().sum();
    }

    void DotProductFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index).dot(secondOperand())
            + firstOperand().dot(secondOperand().derivative(index));
    }
    
    void DotProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "DotProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
