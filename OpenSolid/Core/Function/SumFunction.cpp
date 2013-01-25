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

#include "SumFunction.hpp"

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    SumFunction::SumFunction(const Function& first_operand, const Function& second_operand) :
        BinaryOperation(first_operand, second_operand) {
        assert(first_operand.numDimensions() == second_operand.numDimensions());
    }
    
    int SumFunction::numDimensions() const {return firstOperand().numDimensions();}
    
    void SumFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = firstOperand()(parameter_values) + secondOperand()(parameter_values);
    }
    
    void SumFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = firstOperand()(parameter_bounds) + secondOperand()(parameter_bounds);
    }

    void SumFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index) + secondOperand().derivative(index);
    }
    
    void SumFunction::debug(std::ostream& stream, int indent) const {
        stream << "SumFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
