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

#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ReferenceCounted.hpp>
#include <OpenSolid/Core/Set.hpp>

#include <OpenSolid/Core/Geometry/declarations.hpp>
#include <OpenSolid/Core/Domain/declarations.hpp>

namespace opensolid
{
    class GeometryImplementation : public ReferenceCounted
    {
    public:
        virtual ~GeometryImplementation();
        
        virtual Function function() const = 0;
        virtual Domain domain() const = 0;
        
        virtual int numParameters() const;
        virtual int numDimensions() const;
        
        virtual void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            ResultCacheXd& cache
        ) const;
        
        virtual void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            ResultCacheXI& cache
        ) const;
        
        virtual bool isConstant() const;
        virtual VectorXI bounds() const;
        virtual Set<Geometry> boundaries() const;
        virtual Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        virtual Geometry reversed() const;
    };
}
