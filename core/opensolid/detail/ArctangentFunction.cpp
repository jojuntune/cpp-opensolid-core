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

#include <opensolid/Function/Function.hpp>
#include <opensolid/Function/FunctionImplementation/ArctangentFunction.hpp>

namespace OpenSolid
{
    ArctangentFunction::ArctangentFunction(const Function& operand) : UnaryFunction(operand) {
        assert(operand.dimensions() == 1);
    }
    
    int ArctangentFunction::dimensions() const {return 1;}
    
    void ArctangentFunction::getValues(const MapXcD& parameter_values, MapXD& results) const {
        results = atan(operand()(parameter_values).array());
    }
    
    void ArctangentFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = atan(operand()(parameter_bounds).array());
    }

    void ArctangentFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index) / (1 + operand().squaredNorm());
    }
    
    void ArctangentFunction::debug(std::ostream& stream, int indent) const {
        stream << "ArctangentFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
