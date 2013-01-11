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

#include "LinearFunction.hpp"

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    LinearFunction::LinearFunction(const DatumXd& datum) : _datum(datum) {}
    
    int LinearFunction::parameters() const {return datum().axes();}
    
    int LinearFunction::dimensions() const {return datum().dimensions();}
    
    void LinearFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = parameter_values * datum();
    }
    
    void LinearFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = parameter_bounds * datum();
    }

    void LinearFunction::getDerivative(int index, Function& result) const {
        result = datum().direction(index);
    }
    
    void LinearFunction::getTransformed(
        const MatrixXd& matrix,
        const VectorXd& vector,
        Function& result
    ) const {result = new LinearFunction(datum().transformed(matrix, vector));}
    
    void LinearFunction::debug(std::ostream& stream, int indent) const {
        stream << "LinearFunction" << std::endl;
    }
}
