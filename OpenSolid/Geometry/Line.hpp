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

#ifndef OPENSOLID__LINE_HPP
#define OPENSOLID__LINE_HPP

#include <OpenSolid/config.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    OPENSOLID_CORE_EXPORT Geometry Line2d(const Vector2d& start, const Vector2d& end);
    OPENSOLID_CORE_EXPORT Geometry Line3d(const Vector3d& start, const Vector3d& end);
    OPENSOLID_CORE_EXPORT Geometry Line(const VectorXd& start, const VectorXd& end);
}

#endif
