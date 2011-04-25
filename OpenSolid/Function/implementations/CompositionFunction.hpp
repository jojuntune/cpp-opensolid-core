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

#ifndef OPENSOLID__COMPOSITIONFUNCTION_HPP
#define OPENSOLID__COMPOSITIONFUNCTION_HPP

#include "../Function.hpp"
#include "../FunctionImplementation.hpp"

namespace opensolid
{
    class CompositionFunction : public FunctionImplementation
    {
    private:
        Function _inner;
        Function _outer;
    public:
        OPENSOLID_EXPORT CompositionFunction(const Function& inner, const Function& outer);
        
        const Function& inner() const;
        const Function& outer() const;
        
        OPENSOLID_EXPORT int parameters() const;
        OPENSOLID_EXPORT int dimensions() const;

        OPENSOLID_EXPORT void getValues(const MapXd& parameter_values, MapXd& results) const;
        OPENSOLID_EXPORT void getBounds(const MapXI& parameter_bounds, MapXI& results) const;

        OPENSOLID_EXPORT void getDerivative(int index, Function& result) const;
        
        OPENSOLID_EXPORT void getComposition(const Function& inner, Function& result) const;
        
        OPENSOLID_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline const Function& CompositionFunction::inner() const {return _inner;}
    
    inline const Function& CompositionFunction::outer() const {return _outer;}
}

#endif
