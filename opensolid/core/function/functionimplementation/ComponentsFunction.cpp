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

#include <opensolid/Core/Function/Function.hpp>
#include <opensolid/Core/Function/FunctionImplementation/ComponentsFunction.hpp>

namespace opensolid
{
    ComponentsFunction::ComponentsFunction(const Function& operand, int index, int num) :
        UnaryOperation(operand), _index(index), _num(num) {
        assert(index >= 0);
        assert(num > 0);
        assert(index + num <= operand.dimensions());
    }
    
    int ComponentsFunction::dimensions() const {return num();}
    
    void ComponentsFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        MatrixXd operand_values = operand()(parameter_values);
        results = operand_values.middleRows(index(), num());
    }
    
    void ComponentsFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        MatrixXI operand_bounds = operand()(parameter_bounds);
        results = operand_bounds.middleRows(index(), num());
    }

    void ComponentsFunction::getDerivative(int parameter_index, Function& result) const {
        result = operand().derivative(parameter_index).components(index(), num());
    }
    
    void ComponentsFunction::getComposition(const Function& inner, Function& result) const {
        result = operand()(inner).components(index(), num());
    }
    
    void ComponentsFunction::debug(std::ostream& stream, int indent) const {
        stream << "ComponentsFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
