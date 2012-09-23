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

namespace opensolid
{
    class Zero
    {
    private:
        double _precision;
    public:
        Zero(double precision = 1e-12);

        double precision() const;
    };

    bool operator==(double value, Zero zero);
    bool operator!=(double value, Zero zero);
    bool operator<(double value, Zero zero);
    bool operator>(double value, Zero zero);
    bool operator<=(double value, Zero zero);
    bool operator>=(double value, Zero zero);
}

////////// Implementation //////////

namespace opensolid
{
    inline Zero::Zero(double precision) : _precision(precision) {}

    inline double Zero::precision() const {return _precision;}

    inline bool operator==(double value, Zero zero) {
        return value >= -zero.precision() && value <= zero.precision();
    }

    inline bool operator!=(double value, Zero zero) {
        return value > zero.precision() || value < -zero.precision();
    }

    inline bool operator<(double value, Zero zero) {
        return value < -zero.precision();
    }

    inline bool operator>(double value, Zero zero) {
        return value > zero.precision();
    }

    inline bool operator<=(double value, Zero zero) {
        return value <= zero.precision();
    }

    inline bool operator>=(double value, Zero zero) {
        return value >= -zero.precision();
    }
}
