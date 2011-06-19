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
#include "ConcatenationFunction.hpp"

namespace OpenSolid
{
    ConcatenationFunction::ConcatenationFunction(
        const Function& first_operand,
        const Function& second_operand
    ) : BinaryFunction(first_operand, second_operand) {}
    
    int ConcatenationFunction::dimensions() const {
        return firstOperand().dimensions() + secondOperand().dimensions();
    }
    
    void ConcatenationFunction::getValues(const MapXcD& parameter_values, MapXD& results) const {
        results.topRows(firstOperand().dimensions()) = firstOperand()(parameter_values);
        results.bottomRows(secondOperand().dimensions()) = secondOperand()(parameter_values);
    }
    
    void ConcatenationFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results.topRows(firstOperand().dimensions()) = firstOperand()(parameter_bounds);
        results.bottomRows(secondOperand().dimensions()) = secondOperand()(parameter_bounds);
    }
    
    void ConcatenationFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index).concatenate(secondOperand().derivative(index));
    }
    
    void ConcatenationFunction::getComponents(int index, int num, Function& result) const {
        if (index < firstOperand().dimensions() && index + num <= firstOperand().dimensions()) {
            result = firstOperand().components(index, num);
        } else if (index >= firstOperand().dimensions()) {
            result = secondOperand().components(index - firstOperand().dimensions(), num);
        } else {
            result = new ConcatenationFunction(
                firstOperand().components(index, firstOperand().dimensions() - index),
                secondOperand().components(0, num + index - firstOperand().dimensions())
            );
        }
    }
    
    void ConcatenationFunction::getComposition(const Function& inner, Function& result) const {
        result = firstOperand()(inner).concatenate(secondOperand()(inner));
    }
    
    void ConcatenationFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConcatenationFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
