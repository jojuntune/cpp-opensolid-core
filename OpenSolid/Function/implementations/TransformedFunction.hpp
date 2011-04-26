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

#ifndef OPENSOLID__TRANSFORMEDFUNCTION_HPP
#define OPENSOLID__TRANSFORMEDFUNCTION_HPP

#include <OpenSolid/Datum/Datum.hpp>

#include "UnaryFunction.hpp"

namespace opensolid
{
    class TransformedFunction : public UnaryFunction
    {
    private:
        DatumXd _datum;
    public:
        OPENSOLID_EXPORT TransformedFunction(const Function& function, const DatumXd& datum);
        
        const DatumXd& datum() const;
        
        OPENSOLID_EXPORT int dimensions() const;
        
        OPENSOLID_EXPORT void getValues(const MapXcd& parameter_values, MapXd& results) const;
        OPENSOLID_EXPORT void getBounds(const MapXcI& parameter_bounds, MapXI& results) const;
        
        OPENSOLID_EXPORT void getDerivative(int index, Function& result) const;
        
        OPENSOLID_EXPORT void getComposition(const Function& inner, Function& result) const;
        OPENSOLID_EXPORT void getTransformed(const DatumXd& other, Function& result) const;
        
        OPENSOLID_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline const DatumXd& TransformedFunction::datum() const {return _datum;}
}

#endif
