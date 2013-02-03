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

// Declarations headers
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
