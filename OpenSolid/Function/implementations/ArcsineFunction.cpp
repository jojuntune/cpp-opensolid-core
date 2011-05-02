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
#include "ArcsineFunction.hpp"

namespace OpenSolid
{
    ArcsineFunction::ArcsineFunction(const Function& operand) : UnaryFunction(operand) {
        assert(operand.dimensions() == 1);
    }
    
    int ArcsineFunction::dimensions() const {return 1;}
    
    void ArcsineFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = asin(operand()(parameter_values).array());
    }
    
    void ArcsineFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = asin(operand()(parameter_bounds).array());
    }

    void ArcsineFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index) / sqrt(1 - operand().squaredNorm());
    }
    
    void ArcsineFunction::debug(std::ostream& stream, int indent) const {
        stream << "ArcsineFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
