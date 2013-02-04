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

#include <OpenSolid/Core/Function/ExponentialFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ExponentialFunction::ExponentialFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.numDimensions() == 1);
    }
        
    int ExponentialFunction::numDimensions() const {
        return 1;
    }
        
    void ExponentialFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = operand()(parameterValues).array().exp();
    }

    void ExponentialFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = operand()(parameterBounds).array().exp();
    }

    void ExponentialFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index) * Function(this);
    }
        
    void ExponentialFunction::debug(std::ostream& stream, int indent) const {
        stream << "ExponentialFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
