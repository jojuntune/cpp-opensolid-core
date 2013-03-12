/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
 *************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Transformation/declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Projection
    {
    private:
        Matrix<double, iNumDimensions, 1> _originPoint;
        Matrix<double, iNumDimensions, iNumDimensions> _transformationMatrix;
    public:
        template <int iNumAxes>
        Projection(const Datum<iNumDimensions, iNumAxes>& datum);

        const Matrix<double, iNumDimensions, 1>& originPoint() const;
        const Matrix<double, iNumDimensions, iNumDimensions>& transformationMatrix() const;
    };

    typedef Projection<2> Projection2d;
    typedef Projection<3> Projection3d;
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions> template <int iNumAxes>
    Projection<iNumDimensions>::Projection(const Datum<iNumDimensions, iNumAxes>& datum) :
        _originPoint(datum.originPoint()),
        _transformationMatrix(datum.basisMatrix() * datum.inverseMatrix()) {
    }

    template <int iNumDimensions>
    const Matrix<double, iNumDimensions, 1>&
    Projection<iNumDimensions>::originPoint() const {
        return _originPoint;
    }

    template <int iNumDimensions>
    const Matrix<double, iNumDimensions, iNumDimensions>&
    Projection<iNumDimensions>::transformationMatrix() const {
        return _transformationMatrix;
    }
}
