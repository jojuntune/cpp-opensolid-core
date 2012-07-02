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

#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ParametersFunction.hpp>

namespace opensolid
{
    ParametersFunction::ParametersFunction(int total, int index, int num) :
        _total(total), _index(index), _num(num) {
        assert(total > 0 && index >= 0 && num > 0 && index + num <= total);
    }
    
    int ParametersFunction::parameters() const {return total();}
    
    int ParametersFunction::dimensions() const {return num();}
    
    void ParametersFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = parameter_values.middleRows(index(), num());
    }
    
    void ParametersFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = parameter_bounds.middleRows(index(), num());
    }

    void ParametersFunction::getDerivative(int index, Function& result) const {
        if (_index <= index && index < _index + num()) {
            result = VectorXd::Unit(num(), index - _index);
        } else {
            result = VectorXd::Zero(num());
        }
    }
    
    void ParametersFunction::getComponents(int index, int num, Function& result) const {
        result = new ParametersFunction(total(), _index + index, num);
    }
    
    void ParametersFunction::getComposition(const Function& inner, Function& result) const {
        result = inner.components(index(), num());
    }
    
    void ParametersFunction::debug(std::ostream& stream, int indent) const {
        stream << "ParametersFunction:";
        stream << " total = " << _total;
        stream << ", index = " << _index;
        stream << ", num = " << _num;
        stream << std::endl;
    }
}
