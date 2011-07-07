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

#include "../Function.hpp"
#include "DotProductFunction.hpp"

namespace OpenSolid
{
    DotProductFunction::DotProductFunction(
        const Function& first_operand,
        const Function& second_operand
    ) : BinaryFunction(first_operand, second_operand) {
        assert(first_operand.dimensions() == second_operand.dimensions());
    }
    
    int DotProductFunction::dimensions() const {return 1;}
    
    void DotProductFunction::getValues(const MapXcD& parameter_values, MapXD& results) const {
        results = firstOperand()(parameter_values).cwiseProduct(
            secondOperand()(parameter_values)
        ).colwise().sum();
    }
    
    void DotProductFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = firstOperand()(parameter_bounds).cwiseProduct(
            secondOperand()(parameter_bounds)
        ).colwise().sum();
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
