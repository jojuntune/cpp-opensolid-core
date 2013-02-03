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

// Public headers
#include <OpenSolid/Core/Matrix.hpp>

// Declarations headers
#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Transformation/declarations.hpp>

namespace opensolid
{
    template <>
    class Rotation<2>
    {
    private:
        Vector2d _originPoint;
        Matrix2d _transformationMatrix;
    public:
        OPENSOLID_CORE_EXPORT Rotation(double angle, const Vector2d& originPoint);

        const Vector2d& originPoint() const;
        const Matrix2d& transformationMatrix() const;
    };

    typedef Rotation<2> Rotation2d;

    template <>
    class Rotation<3>
    {
    private:
        Vector3d _originPoint;
        Matrix3d _transformationMatrix;
    public:
        OPENSOLID_CORE_EXPORT Rotation(double angle, const Datum<3, 1>& axis);

        const Vector3d& originPoint() const;
        const Matrix3d& transformationMatrix() const;
    };

    typedef Rotation<3> Rotation3d;
}

////////// Implementation //////////

namespace opensolid
{
    inline const Vector2d& Rotation<2>::originPoint() const {
        return _originPoint;
    }

    inline const Matrix2d& Rotation<2>::transformationMatrix() const {
        return _transformationMatrix;
    }
    
    inline const Vector3d& Rotation<3>::originPoint() const {
        return _originPoint;
    }

    inline const Matrix3d& Rotation<3>::transformationMatrix() const {
        return _transformationMatrix;
    }
}
