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

#include <OpenSolid/Datum/Frame.hpp>
#include <OpenSolid/Geometry/Circle.hpp>
#include <OpenSolid/Geometry/Arc.hpp>

namespace OpenSolid
{
    Geometry Circle2d(const Vector2d& center, double radius) {
        Set<Geometry> boundary;
        boundary.insert(Arc2d(center, radius, 2 * M_PI, 0));
        return Geometry(Function::Identity(2), Domain(boundary));
    }

    Geometry Circle3d(const Axis3d& axis, double radius) {
        return Circle2d(Vector2d::Zero(), radius) * axis.normalPlane();
    }

    Geometry Circle3d(const Plane3d& plane, double radius) {
        return Circle2d(Vector2d::Zero(), radius) * plane;
    }
}
