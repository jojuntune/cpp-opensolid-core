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
        UnaryFunction(operand),
        _plane(plane),
        _normal(plane.normalVector()),
        _d(plane.origin().dot(_normal)) {
        assert(operand.dimensions() == plane.dimensions());
    }
        
    int MirroredFunction::parameters() const {return operand().parameters();}

    int MirroredFunction::dimensions() const {return operand().dimensions();}
        
    void MirroredFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        MatrixXd operand_values = operand()(parameter_values);
        results =  operand_values -
            2 * _normal * ((_normal.transpose() * operand_values).array() - _d).matrix();
    }

    void MirroredFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        MatrixXI operand_bounds = operand()(parameter_bounds);
        results =  operand_bounds -
            2 * _normal.cast<Interval>() * (
                (_normal.transpose().cast<Interval>() * operand_bounds).array() - Interval(_d)
            ).matrix();
    }

    void MirroredFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index).mirrored(plane().linear());
    }
        
    void MirroredFunction::debug(std::ostream& stream, int indent) const {
        stream << "MirroredFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
