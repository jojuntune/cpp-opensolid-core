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

#include "detail/CrossProductFunction.hpp"

#include "Function.hpp"

namespace opensolid
{
    CrossProductFunction::CrossProductFunction(
        const Function& first_operand,
        const Function& second_operand
    ) : BinaryOperation(first_operand, second_operand) {
        assert(first_operand.dimensions() == 3 && second_operand.dimensions() == 3);
    }
    
    int CrossProductFunction::dimensions() const {return 3;}
    
    void CrossProductFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        Matrix3Xd first_values = firstOperand()(parameter_values);
        Matrix3Xd second_values = secondOperand()(parameter_values);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = first_values.col(i).cross(second_values.col(i));
        }
    }
    
    void CrossProductFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        Matrix3XI first_bounds = firstOperand()(parameter_bounds);
        Matrix3XI second_bounds = secondOperand()(parameter_bounds);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = first_bounds.col(i).cross(second_bounds.col(i));
        }
    }

    void CrossProductFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index).cross(secondOperand())
            + firstOperand().cross(secondOperand().derivative(index));
    }
    
    void CrossProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "CrossProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
