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

#include <OpenSolid/Core/Function/TangentFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TangentFunction::TangentFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.numDimensions() == 1);
    }
    
    int TangentFunction::numDimensions() const {return 1;}
    
    void TangentFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        MatrixXd operand_values = operand()(parameter_values);
        results = operand_values.array().sin() / operand_values.array().cos();
    }
    
    void TangentFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        MatrixXI operand_bounds = operand()(parameter_bounds);
        results = operand_bounds.array().sin() / operand_bounds.array().cos();
    }

    void TangentFunction::getDerivative(int index, Function& result) const {
        result = (1 + Function(this).squaredNorm()) * operand().derivative(index);
    }
    
    void TangentFunction::debug(std::ostream& stream, int indent) const {
        stream << "TangentFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
