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

#include <OpenSolid/Core/Function/ParametersFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ParametersFunction::ParametersFunction(
        int numParameters,
        int startIndex,
        int numDimensions
    ) : _numParameters(numParameters),
        _startIndex(startIndex),
        _numDimensions(numDimensions) {

        assert(numParameters > 0);
        assert(startIndex >= 0);
        assert(numDimensions > 0 && startIndex + numDimensions <= numParameters);
    }
    
    void ParametersFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = parameterValues.middleRows(startIndex(), numDimensions());
    }
    
    void ParametersFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = parameterBounds.middleRows(startIndex(), numDimensions());
    }

    void ParametersFunction::getDerivative(int index, Function& result) const {
        if (startIndex() <= index && index < startIndex() + numDimensions()) {
            result = VectorXd::Unit(numDimensions(), index - startIndex());
        } else {
            result = VectorXd::Zero(numDimensions());
        }
    }
    
    void ParametersFunction::getComponents(
        int startIndex,
        int numComponents,
        Function& result
    ) const {
        result = new ParametersFunction(
            numParameters(), 
            this->startIndex() + startIndex,
            numComponents
        );
    }
    
    void ParametersFunction::getComposition(const Function& innerFunction, Function& result) const {
        result = innerFunction.components(startIndex(), numDimensions());
    }
    
    void ParametersFunction::debug(std::ostream& stream, int indent) const {
        stream << "ParametersFunction:";
        stream << " numParameters = " << numParameters();
        stream << ", startIndex = " << startIndex();
        stream << ", numDimensions = " << numDimensions();
        stream << std::endl;
    }
}
