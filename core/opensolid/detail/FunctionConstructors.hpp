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

#include <opensolid/config.hpp>

#include <opensolid/Datum.hpp>
#include <opensolid/Matrix.hpp>

namespace opensolid
{
    class Function;

    class FunctionConstructors
    {
    public:
        OPENSOLID_CORE_EXPORT static Function Identity(int dimensions = 1);

        OPENSOLID_CORE_EXPORT static Function Parameter();

        OPENSOLID_CORE_EXPORT static Function Parameter(int total, int index);

        OPENSOLID_CORE_EXPORT static Function Parameters(int total);

        OPENSOLID_CORE_EXPORT static Function Parameters(int total, int index, int num);

        OPENSOLID_CORE_EXPORT static Function Components(
            const Function& x,
            const Function& y
        );

        OPENSOLID_CORE_EXPORT static Function Components(
            const Function& x,
            const Function& y,
            const Function& z
        );
        
        OPENSOLID_CORE_EXPORT static Function Linear(const DatumXd& datum);
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(const DatumXd& datum);
        
        OPENSOLID_CORE_EXPORT static Function Elliptical(
            const DatumXd& datum,
            const VectorXb& convention
        );
    };
}
