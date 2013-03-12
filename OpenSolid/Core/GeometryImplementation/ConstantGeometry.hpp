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

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/GeometryImplementation.hpp>

namespace opensolid
{
    class ConstantGeometry : public GeometryImplementation
    {
    private:
        VectorXd _vector;
        int _numParameters;
    public:
        OPENSOLID_CORE_EXPORT ConstantGeometry(const VectorXd& vector, int numParameters);

        Function function() const;
        Domain domain() const;
        
        int numParameters() const;
        int numDimensions() const;

        void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            ResultCacheXd& cache
        ) const;
        
        void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            ResultCacheXI& cache
        ) const;

        bool isConstant() const;
        VectorXI bounds() const;
        Set<Geometry> boundaries() const;
        Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        Geometry reversed() const;
    };
}
