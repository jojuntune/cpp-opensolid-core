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

#ifndef OPENSOLID__COORDINATESYSTEM_HPP
#define OPENSOLID__COORDINATESYSTEM_HPP

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    class CoordinateSystem : public Datum<dimensions_, axes_>
    {
    public:
        OPENSOLID_CORE_EXPORT CoordinateSystem();

        OPENSOLID_CORE_EXPORT CoordinateSystem(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, axes_>& basis
        );
        
        OPENSOLID_CORE_EXPORT CoordinateSystem(const Datum<dimensions_, axes_>& other);
        
        using Datum<dimensions_, axes_>::operator=;
    };
    
    typedef CoordinateSystem<Dynamic, Dynamic> CoordinateSystem2d;
    typedef CoordinateSystem<Dynamic, Dynamic> CoordinateSystem3d;
    typedef CoordinateSystem<Dynamic, Dynamic> CoordinateSystemXd;
}

#endif
