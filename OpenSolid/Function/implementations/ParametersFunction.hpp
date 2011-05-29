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

#ifndef OPENSOLID__PARAMETERSFUNCTION_HPP
#define OPENSOLID__PARAMETERSFUNCTION_HPP

#include "../FunctionImplementation.hpp"

namespace OpenSolid
{
    class ParametersFunction : public FunctionImplementation
    {
    private:
        int _total;
        int _index;
        int _num;
    public:
        OPENSOLID_EXPORT ParametersFunction(int total, int index, int num);
        
        int total() const;
        int index() const;
        int num() const;
        
        OPENSOLID_EXPORT int parameters() const;
        OPENSOLID_EXPORT int dimensions() const;
        
        OPENSOLID_EXPORT void getValues(const MapXcd& parameter_values, MapXd& results) const;
        OPENSOLID_EXPORT void getBounds(const MapXcI& parameter_bounds, MapXI& results) const;

        OPENSOLID_EXPORT void getDerivative(int index, Function& result) const;
        
        OPENSOLID_EXPORT void getComponents(int index, int num, Function& result) const;
        OPENSOLID_EXPORT void getComposition(const Function& inner, Function& result) const;
        
        OPENSOLID_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline int ParametersFunction::total() const {return _total;}
    
    inline int ParametersFunction::index() const {return _index;}
    
    inline int ParametersFunction::num() const {return _num;}
}

#endif
