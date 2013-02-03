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
    CompositionFunction::CompositionFunction(const Function& inner, const Function& outer) :
        _inner(inner), _outer(outer) {assert(inner.numDimensions() == outer.numParameters());}
    
    int CompositionFunction::numParameters() const {return inner().numParameters();}
    
    int CompositionFunction::numDimensions() const {return outer().numDimensions();}

    void CompositionFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = outer()(inner()(parameter_values));
    }

    void CompositionFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = outer()(inner()(parameter_bounds));
    }

    void CompositionFunction::getDerivative(int index, Function& result) const {
        Function inner_derivative = inner().derivative(index);
        result = outer().derivative(0)(inner()) * inner_derivative.component(0);
        for (int i = 1; i < outer().numParameters(); ++i) {
            result = result + outer().derivative(i)(inner()) * inner_derivative.component(i);
        }
    }
        
    void CompositionFunction::getComposition(const Function& inner, Function& result) const {
        result = new CompositionFunction(_inner(inner), outer());
    }
    
    void CompositionFunction::debug(std::ostream& stream, int indent) const {
        stream << "CompositionFunction" << std::endl;
        inner().debug(stream, indent + 1);
        outer().debug(stream, indent + 1);
    }
}
