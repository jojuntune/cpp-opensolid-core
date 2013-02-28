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

#include "GeometryImplementation.hpp"

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/Function/LinearFunction.hpp>
#include <OpenSolid/Core/Simplex.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    class SimplexGeometry : public GeometryImplementation
    {
    private:
        Simplex<iNumDimensions, iNumVertices> _simplex;
        Datum<iNumDimensions, iNumVertices - 1> _simplexDatum;
    public:
        OPENSOLID_CORE_EXPORT SimplexGeometry(const Simplex<iNumDimensions, iNumVertices>& simplex);

        Function function() const;
        OPENSOLID_CORE_EXPORT Domain domain() const;
        
        int numParameters() const;
        int numDimensions() const;
        
        void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            ResultCacheXd& resultCache
        ) const;
        
        void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            ResultCacheXI& resultCache
        ) const;

        bool isConstant() const;
        VectorXI bounds() const;
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        Geometry reversed() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumVertices>
    SimplexGeometry<iNumDimensions, iNumVertices>::SimplexGeometry(
        const Simplex<iNumDimensions, iNumVertices>& simplex
    ) : _simplex(simplex),
        _simplexDatum(simplex.datum()) {
    }

    template <int iNumDimensions, int iNumVertices>
    Function SimplexGeometry<iNumDimensions, iNumVertices>::function() const {
        return new LinearFunction<iNumDimensions, iNumVertices - 1>(_simplexDatum);
    }
        
    template <int iNumDimensions, int iNumVertices>
    int SimplexGeometry<iNumDimensions, iNumVertices>::numParameters() const {
        return iNumVertices - 1;
    }
    
    template <int iNumDimensions, int iNumVertices>
    int SimplexGeometry<iNumDimensions, iNumVertices>::numDimensions() const {
        return iNumDimensions;
    }

    template <int iNumDimensions, int iNumVertices>
    void SimplexGeometry<iNumDimensions, iNumVertices>::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& resultCache
    ) const {
        results = _simplexDatum * parameterValues;
    }

    template <int iNumDimensions, int iNumVertices>
    void SimplexGeometry<iNumDimensions, iNumVertices>::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& resultCache
    ) const {
        results = _simplexDatum * parameterBounds;
    }
    
    template <int iNumDimensions, int iNumVertices>
    bool SimplexGeometry<iNumDimensions, iNumVertices>::isConstant() const {
        return false;
    }
    
    template <int iNumDimensions, int iNumVertices>
    VectorXI SimplexGeometry<iNumDimensions, iNumVertices>::bounds() const {
        return _simplex.bounds();
    }

    template <int iNumDimensions, int iNumVertices>
    Geometry SimplexGeometry<iNumDimensions, iNumVertices>::transformed(
        const MatrixXd& matrix,
        const VectorXd& vector
    ) const {
        assert(matrix.rows() == vector.size());
        assert(matrix.cols() == iNumDimensions);

        int numTransformedDimensions = matrix.rows();

        if (numTransformedDimensions == 1) {
            return new SimplexGeometry<1, iNumVertices>(
                matrix.topLeftCorner<1, iNumDimensions>() * _simplex + vector
            );
        } else if (numTransformedDimensions == 2) {
            return new SimplexGeometry<2, iNumVertices>(
                matrix.topLeftCorner<2, iNumDimensions>() * _simplex + vector
            );
        } else if (numTransformedDimensions == 3) {
            return new SimplexGeometry<3, iNumVertices>(
                matrix.topLeftCorner<3, iNumDimensions>() * _simplex + vector
            );
        } else {
            assert(false);
            return Geometry();
        }
    }

    template <int iNumDimensions, int iNumVertices>
    Geometry SimplexGeometry<iNumDimensions, iNumVertices>::reversed() const {
        assert(iNumVertices == 2);
        return new SimplexGeometry(
            Simplex<iNumDimensions, iNumVertices>(_simplex.vertices().reverse())
        );
    }
}
