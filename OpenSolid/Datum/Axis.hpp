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

#ifndef OPENSOLID__AXIS_HPP
#define OPENSOLID__AXIS_HPP

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    class Axis : public Datum<dimensions_, 1>
    {
    public:
        OPENSOLID_CORE_EXPORT Axis();

        OPENSOLID_CORE_EXPORT Axis(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, 1>& direction
        );

        OPENSOLID_CORE_EXPORT Axis(const Datum<dimensions_, 1>& other);
        
        OPENSOLID_CORE_EXPORT Axis<dimensions_>& operator=(const Datum<dimensions_, 1>& other);
    };
    
    typedef Axis<1> Axis1d;
    typedef Axis<2> Axis2d;
    typedef Axis<3> Axis3d;
    typedef Axis<Dynamic> AxisXd;
}

#endif
