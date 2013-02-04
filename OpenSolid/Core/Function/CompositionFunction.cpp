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

#include <OpenSolid/Core/Function/CompositionFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    CompositionFunction::CompositionFunction(
        const Function& innerFunction,
        const Function& outerFunction
    ) : _innerFunction(innerFunction), _outerFunction(outerFunction) {

        assert(innerFunction.numDimensions() == outerFunction.numParameters());
    }
    
    int CompositionFunction::numParameters() const {
        return innerFunction().numParameters();
    }
    
    int CompositionFunction::numDimensions() const {
        return outerFunction().numDimensions();
    }

    void CompositionFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = outerFunction()(innerFunction()(parameterValues));
    }

    void CompositionFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = outerFunction()(innerFunction()(parameterBounds));
    }

    void CompositionFunction::getDerivative(int index, Function& result) const {
        Function innerDerivative = innerFunction().derivative(index);
        result = outerFunction().derivative(0)(innerFunction()) * innerDerivative.component(0);
        for (int i = 1; i < outerFunction().numParameters(); ++i) {
            Function outerDerivative = outerFunction().derivative(i);
            result = result + outerDerivative(innerFunction()) * innerDerivative.component(i);
        }
    }
        
    void CompositionFunction::getComposition(
        const Function& newInnerFunction,
        Function& result
    ) const {
        result = outerFunction()(innerFunction()(newInnerFunction));
    }
    
    void CompositionFunction::debug(std::ostream& stream, int indent) const {
        stream << "CompositionFunction" << std::endl;
        innerFunction().debug(stream, indent + 1);
        outerFunction().debug(stream, indent + 1);
    }
}
