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
