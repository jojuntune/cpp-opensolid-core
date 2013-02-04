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

#include <OpenSolid/Core/Function/ArcsineFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ArcsineFunction::ArcsineFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.numDimensions() == 1);
    }
    
    int ArcsineFunction::numDimensions() const {
        return 1;
    }
    
    struct Arcsine
    {
        inline double operator()(double value) const {
            assert(Interval(-1, 1).contains(value));
            return asin(Interval(-1, 1).clamp(value));
        }
        
        inline Interval operator()(const Interval& bounds) const {
            assert(Interval(-1, 1).overlaps(bounds));
            return asin(Interval(-1, 1).clamp(bounds));
        }
    };
    
    void ArcsineFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = operand()(parameterValues).unaryExpr(Arcsine());
    }
    
    void ArcsineFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = operand()(parameterBounds).unaryExpr(Arcsine());
    }

    void ArcsineFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index) / sqrt(1 - operand().squaredNorm());
    }
    
    void ArcsineFunction::debug(std::ostream& stream, int indent) const {
        stream << "ArcsineFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
