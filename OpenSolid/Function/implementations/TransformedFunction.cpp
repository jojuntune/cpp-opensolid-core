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
#include "TransformedFunction.hpp"

namespace OpenSolid
{
    TransformedFunction::TransformedFunction(const Function& operand, const DatumXd& datum) :
        UnaryFunction(operand), _datum(datum) {
        assert(operand.dimensions() == datum.axes());
    }
    
    int TransformedFunction::dimensions() const {return datum().dimensions();}
    
    void TransformedFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = operand()(parameter_values) * datum();
    }
    
    void TransformedFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = operand()(parameter_bounds) * datum();
    }
    
    void TransformedFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index) * datum().linear();
    }
    
    void TransformedFunction::getComposition(const Function& inner, Function& result) const {
        result = operand()(inner) * datum();
    }
    
    void TransformedFunction::getTransformed(const DatumXd& other, Function& result) const {
        result = operand() * (datum() * other);
    }
    
    void TransformedFunction::debug(std::ostream& stream, int indent) const {
        stream << "TransformedFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
