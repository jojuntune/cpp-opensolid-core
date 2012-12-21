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

#include "ProductFunction.hpp"

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ProductFunction::ProductFunction(
        const Function& first_operand,
        const Function& second_operand
    ) : BinaryOperation(first_operand, second_operand) {
        assert(second_operand.dimensions() == 1);
    }
    
    int ProductFunction::dimensions() const {return firstOperand().dimensions();}
    
    void ProductFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = firstOperand()(parameter_values) *
            secondOperand()(parameter_values).eval().asDiagonal();
    }
    
    void ProductFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = firstOperand()(parameter_bounds) *
            secondOperand()(parameter_bounds).eval().asDiagonal();
    }

    void ProductFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index) * secondOperand()
            + firstOperand() * secondOperand().derivative(index);
    }
    
    void ProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "ProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
