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

#include <OpenSolid/Core/Function/IdentityFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    IdentityFunction::IdentityFunction(int numDimensions) :
        _numDimensions(numDimensions) {

        assert(_numDimensions > 0);
    }

    int IdentityFunction::numParameters() const {
        return _numDimensions;
    }

    int IdentityFunction::numDimensions() const {
        return _numDimensions;
    }

    Function IdentityFunction::deduplicated(std::vector<Function>&) const {
        return this;
    }
    
    void IdentityFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = parameterValues;
    }
    
    void IdentityFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = parameterBounds;
    }

    Function IdentityFunction::derivative(int index) const {
        return Function::Constant(VectorXd::Unit(numDimensions(), index), numDimensions());
    }
    
    Function IdentityFunction::compose(const Function& innerFunction) const {
        return innerFunction;
    }
    
    void IdentityFunction::debug(std::ostream& stream, int indent) const {
        stream << "IdentityFunction" << std::endl;
    }
}
