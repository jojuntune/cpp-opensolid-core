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

#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Function/FunctionImplementation/MirroredFunction.hpp>

namespace OpenSolid
{
    MirroredFunction::MirroredFunction(const Function& operand, const PlaneXd& plane) :
        UnaryFunction(operand), _plane(plane), _normal(plane.normalVector()) {
    }
        
    int MirroredFunction::parameters() const {}

    int MirroredFunction::dimensions() const {}
        
    void MirroredFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
    }

    void MirroredFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
    }

    void MirroredFunction::getDerivative(int index, Function& result) const {
    }
        
    void MirroredFunction::getTransformed(const DatumXd& datum, Function& result) const {
    }
        
    void MirroredFunction::debug(std::ostream& stream, int indent) const {
    }
}
