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

#include "ArccosineFunction.hpp"

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ArccosineFunction::ArccosineFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.dimensions() == 1);
    }
    
    int ArccosineFunction::dimensions() const {return 1;}
    
    struct Arccosine
    {
        inline double operator()(double value) const {
            assert(Interval(-1, 1).contains(value));
            return acos(Interval(-1, 1).clamp(value));
        }
        
        inline Interval operator()(const Interval& bounds) const {
            assert(Interval(-1, 1).overlaps(bounds));
            return acos(Interval(-1, 1).clamp(bounds));
        }
    };
    
    void ArccosineFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = operand()(parameter_values).unaryExpr(Arccosine());
    }
    
    void ArccosineFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = operand()(parameter_bounds).unaryExpr(Arccosine());
    }

    void ArccosineFunction::getDerivative(int index, Function& result) const {
        result = -operand().derivative(index) / sqrt(1 - operand().squaredNorm());
    }
    
    void ArccosineFunction::debug(std::ostream& stream, int indent) const {
        stream << "ArccosineFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
