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
#include <OpenSolid/Function/FunctionImplementation/LinearFunction.hpp>

namespace OpenSolid
{
    LinearFunction::LinearFunction(const VectorXD& point, const MatrixXD& vectors) :
        _point(point), _vectors(vectors) {assert(point.rows() == _vectors.rows());}
    
    int LinearFunction::parameters() const {return _vectors.cols();}
    
    int LinearFunction::dimensions() const {return _vectors.rows();}
    
    void LinearFunction::getValues(const MapXcD& parameter_values, MapXD& results) const {
        results = _point.replicate(1, parameter_values.cols()) + _vectors * parameter_values;
    }
    
    void LinearFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = _point.cast<Interval>().replicate(1, parameter_bounds.cols())
            + _vectors.cast<Interval>() * parameter_bounds;
    }

    void LinearFunction::getDerivative(int index, Function& result) const {
        result = _vectors.col(index);
    }
    
    void LinearFunction::getTransformed(const DatumXD& datum, Function& result) const {
        result = new LinearFunction(point() * datum, vectors() * datum);
    }
    
    void LinearFunction::debug(std::ostream& stream, int indent) const {
        stream << "LinearFunction" << std::endl;
    }
}
