/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
 *  ian.e.mackenzie@gmail.com                                                        *
 *                                                                                   *
 *  This library is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU Lesser General Public                       *
 *  License as published by the Free Software Foundation; either                     *
 *  version 2.1 of the License, or (at your option) any later version.               *
 *                                                                                   *
 *  This library is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
 *  Lesser General Public License for more details.                                  *
 *                                                                                   *
 *  You should have received a copy of the GNU Lesser General Public                 *
 *  License along with this library; if not, write to the Free Software              *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
 *                                                                                   *
 *************************************************************************************/

#include <OpenSolid/Core/Function/ParameterFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ParameterFunction::ParameterFunction(int numParameters, int index) :
        _numParameters(numParameters),
        _index(index) {

        assert(numParameters > 0);
        assert(index >= 0 && index < numParameters);
    }

    int ParameterFunction::numParameters() const {
        return _numParameters;
    }

    int ParameterFunction::numDimensions() const {
        return 1;
    }

    Function ParameterFunction::deduplicated(std::vector<Function>&) const {
        return this;
    }
    
    void ParameterFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = parameterValues.row(index());
    }
    
    void ParameterFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = parameterBounds.row(index());
    }

    Function ParameterFunction::derivative(int index) const {
        return Function::Constant(index == this->index() ? 1.0 : 0.0, numParameters());
    }
    
    Function ParameterFunction::compose(const Function& innerFunction) const {
        return innerFunction.components(index(), 1);
    }
    
    void ParameterFunction::debug(std::ostream& stream, int indent) const {
        stream << "ParameterFunction: index = " << index() << std::endl;
    }
}
