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

#pragma once

#include <OpenSolid/config.hpp>

// Internal headers
#include <OpenSolid/Core/Function/FunctionImplementation.hpp>

namespace opensolid
{
    class ParameterFunction : public FunctionImplementation
    {
    private:
        int _numParameters;
        int _index;
    public:
        OPENSOLID_CORE_EXPORT ParameterFunction(int numParameters, int index);
        
        int index() const;
        
        OPENSOLID_CORE_EXPORT int numParameters() const;
        OPENSOLID_CORE_EXPORT int numDimensions() const;

        OPENSOLID_CORE_EXPORT bool isDuplicate(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function deduplicated(std::vector<Function>& others) const;
        
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameterValues, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameterBounds, MapXI& results) const;

        OPENSOLID_CORE_EXPORT Function derivative(int index) const;
        
        OPENSOLID_CORE_EXPORT Function compose(const Function& innerFunction) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline int ParameterFunction::index() const {
        return _index;
    }
}
