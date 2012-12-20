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

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Datum.hpp>

namespace opensolid
{
    class Axis2d : public Datum<2, 1>
    {
    public:
        Axis2d();

        template <class OriginType, class DirectionType>
        Axis2d(const EigenBase<OriginType>& origin, const EigenBase<DirectionType>& direction);

        template <int dimensions_, int axes_>
        Axis2d(const Datum<dimensions_, axes_>& datum);
    };

    class Axis2dConstructionError : public ErrorType<100> {};
    template <> struct UniqueErrorCode<Axis2dConstructionError::error_code> {};

    class Axis2dCopyConstructionError : public ErrorType<101> {};
    template <> struct UniqueErrorCode<Axis2dCopyConstructionError::error_code> {};

    class Axis3d : public Datum<3, 1>
    {
    public:
        Axis3d();

        template <class OriginType, class DirectionType>
        Axis3d(const EigenBase<OriginType>& origin, const EigenBase<DirectionType>& direction);

        template <int dimensions_, int axes_>
        Axis3d(const Datum<dimensions_, axes_>& datum);
    };

    class Axis3dConstructionError : public ErrorType<102> {};
    template <> struct UniqueErrorCode<Axis3dConstructionError::error_code> {};

    class Axis3dCopyConstructionError : public ErrorType<103> {};
    template <> struct UniqueErrorCode<Axis3dCopyConstructionError::error_code> {};
}

////////// Implementation //////////

namespace opensolid
{
    inline Axis2d::Axis2d() {
        initialize(Vector2d::Zero(), Vector2d::UnitX());
    }

    template <class OriginType, class DirectionType>
    inline Axis2d::Axis2d(
        const EigenBase<OriginType>& origin,
        const EigenBase<DirectionType>& direction
    ) {
        bool valid_origin = origin.cols() == 1 && origin.rows() == 2;
        bool valid_direction = direction.cols() == 1 && direction.rows() == 2 &&
            !direction.derived().isZero();
        if (!valid_origin || !valid_direction ) {
            throw Axis2dConstructionError();
        }
        initialize(origin.derived(), direction.derived().normalized());
    }

    template <int dimensions_, int axes_>
    inline Axis2d::Axis2d(const Datum<dimensions_, axes_>& datum) {
        if (datum.dimensions() != 2 || datum.axes() != 1) {
            throw Axis2dCopyConstructionError();
        }
        initialize(datum);
    }

    inline Axis3d::Axis3d() {
        initialize(Vector3d::Zero(), Vector3d::UnitX());
    }

    template <class OriginType, class DirectionType>
    inline Axis3d::Axis3d(
        const EigenBase<OriginType>& origin,
        const EigenBase<DirectionType>& direction
    ) {
        bool valid_origin = origin.cols() == 1 && origin.rows() == 3;
        bool valid_direction = direction.cols() == 1 && direction.rows() == 3 &&
            !direction.derived().isZero();
        if (!valid_origin || !valid_direction ) {
            throw Axis3dConstructionError();
        }
        initialize(origin.derived(), direction.derived().normalized());
    }

    template <int dimensions_, int axes_>
    inline Axis3d::Axis3d(const Datum<dimensions_, axes_>& datum) {
        if (datum.dimensions() != 3 || datum.axes() != 1) {
            throw Axis3dCopyConstructionError();
        }
        initialize(datum);
    }
}
