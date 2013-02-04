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

#pragma once

#include <OpenSolid/config.hpp>

// Internal headers
#include <OpenSolid/Core/Function/UnaryOperation.hpp>

namespace opensolid
{
    class ComponentsFunction : public UnaryOperation
    {
    private:
        int _startIndex;
        int _numComponents;
    public:
        OPENSOLID_CORE_EXPORT ComponentsFunction(
            const Function& operand,
            int startIndex,
            int numComponents
        );
        
        int startIndex() const;
        int numComponents() const;
        
        OPENSOLID_CORE_EXPORT int numDimensions() const;

        OPENSOLID_CORE_EXPORT void getValues(const MapXcd& parameterValues, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void getBounds(const MapXcI& parameterBounds, MapXI& results) const;

        OPENSOLID_CORE_EXPORT void getDerivative(int parameterIndex, Function& result) const;
        
        OPENSOLID_CORE_EXPORT void getComponents(
            int startIndex,
            int numComponents,
            Function& result
        ) const;

        OPENSOLID_CORE_EXPORT void getComposition(
            const Function& innerFunction,
            Function& result
        ) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline int ComponentsFunction::startIndex() const {
        return _startIndex;
    }

    inline int ComponentsFunction::numComponents() const {
        return _numComponents;
    }
}
