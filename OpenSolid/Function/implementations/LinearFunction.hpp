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

#ifndef OPENSOLID__LINEARFUNCTION_HPP
#define OPENSOLID__LINEARFUNCTION_HPP

#include "../FunctionImplementation.hpp"

namespace OpenSolid
{
    class LinearFunction : public FunctionImplementation
    {
    private:
        VectorXD _point;
        MatrixXD _vectors;
    public:
        OPENSOLID_CORE_EXPORT LinearFunction(const VectorXD& point, const MatrixXD& vectors);
        
        const VectorXD& point() const;
        const MatrixXD& vectors() const;
        
        OPENSOLID_CORE_EXPORT int parameters() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        
        OPENSOLID_CORE_EXPORT void getValues(const MapXcD& parameter_values, MapXD& results) const;
        OPENSOLID_CORE_EXPORT void getBounds(const MapXcI& parameter_bounds, MapXI& results) const;

        OPENSOLID_CORE_EXPORT void getDerivative(int index, Function& result) const;
        
        OPENSOLID_CORE_EXPORT void getTransformed(const DatumXD& datum, Function& result) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline const VectorXD& LinearFunction::point() const {return _point;}
    
    inline const MatrixXD& LinearFunction::vectors() const {return _vectors;}
}

#endif
