/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/BoundedVolume.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/ParametricSurface.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<BoundedVolume3d>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<BoundedVolume3d>
    {
        static const int Value = 3;
    };

    class BoundedVolume3d :
        public Transformable<BoundedVolume3d, 3>
    {
    private:
        SpatialSet<ParametricSurface3d> _boundaries;
    public:
        OPENSOLID_CORE_EXPORT
        BoundedVolume3d();

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d(const BoundedVolume3d& other);

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d(BoundedVolume3d&& other);

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d(const SpatialSet<ParametricSurface3d>& boundaries);

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d(SpatialSet<ParametricSurface3d>&& boundaries);

        const SpatialSet<ParametricSurface3d>&
        boundaries() const;

        bool
        isEmpty() const;

        Box<3>
        bounds() const;

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d
        scaledAbout(const Point<3>& point, double scale) const;

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d
        rotatedAbout(const Point<3>& point, const Matrix<double, 3, 3>& rotationMatrix) const;

        using Transformable<BoundedVolume3d, 3>::rotatedAbout;

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d
        translatedBy(const Vector<double, 3>& vector) const;

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d
        toLocalIn(const Frame<3>& frame) const;

        // TODO
        // OPENSOLID_CORE_EXPORT
        // const BoundedArea2d
        // toLocalIn(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d
        toGlobalFrom(const Frame<3>& frame) const;

        OPENSOLID_CORE_EXPORT
        BoundedVolume3d
        mirroredAbout(const Point<3>& point, const UnitVector<3>& directionVector) const;

        using Transformable<BoundedVolume3d, 3>::mirroredAbout;

        // TODO
        // OPENSOLID_CORE_EXPORT
        // const ParametricSurface3d
        // projectedOnto(const Plane3d& plane) const;
    };
}
