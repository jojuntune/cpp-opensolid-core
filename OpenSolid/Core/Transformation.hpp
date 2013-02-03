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
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    class Transformation{
    private:
        Matrix<double, iNumSourceDimensions, 1> _sourceOriginPoint;
        Matrix<double, iNumDestinationDimensions, iNumSourceDimensions> _transformationMatrix;
        Matrix<double, iNumDestinationDimensions, 1> _destinationOriginPoint;
    public:
        template <int iNumAxes>
        Transformation(
            const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
            const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
        );

        const Matrix<double, iNumSourceDimensions, 1>&
        sourceOriginPoint() const;
        
        const Matrix<double, iNumDestinationDimensions, iNumSourceDimensions>&
        transformationMatrix() const;
        
        const Matrix<double, iNumDestinationDimensions, 1>&
        destinationOriginPoint() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumSourceDimensions, int iNumDestinationDimensions> template <int iNumAxes>
    Transformation<iNumSourceDimensions, iNumDestinationDimensions>::Transformation(
        const Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
        const Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
    ) : _sourceOriginPoint(sourceDatum.originPoint()),
        _transformationMatrix(destinationDatum.basisMatrix() * sourceDatum.inverseMatrix())
        _destinationOriginPoint(destinationDatum.originPoint()) {
    }

    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    const Matrix<double, iNumSourceDimensions, 1>&
    Transformation<iNumSourceDimensions, iNumDestinationDimensions>::sourceOriginPoint() const {
        return _sourceOriginPoint;
    }
    
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    const Matrix<double, iNumDestinationDimensions, iNumSourceDimensions>&
    Transformation<iNumSourceDimensions, iNumDestinationDimensions>::transformationMatrix() const {
        return _transformationMatrix;
    }
    
    template <int iNumSourceDimensions, int iNumDestinationDimensions>
    const Matrix<double, iNumDestinationDimensions, 1>&
    Transformation<iNumSourceDimensions, iNumDestinationDimensions>::destinationOriginPoint() const {
        return _destinationOriginPoint;
    }
}
