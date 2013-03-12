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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ReferenceCounted.hpp>

#include <OpenSolid/Core/Function/ResultCache.hpp>

#include <OpenSolid/Core/Function/declarations.hpp>

#include <vector>

namespace opensolid
{
    class FunctionImplementation : public ReferenceCounted
    {
    public:
        OPENSOLID_CORE_EXPORT virtual ~FunctionImplementation();

        OPENSOLID_CORE_EXPORT virtual int numDimensions() const = 0;
        OPENSOLID_CORE_EXPORT virtual int numParameters() const = 0;
        
        OPENSOLID_CORE_EXPORT virtual const ConstantFunction* asConstant() const;
        OPENSOLID_CORE_EXPORT virtual const IdentityFunction* asIdentity() const;
        OPENSOLID_CORE_EXPORT virtual const ParameterFunction* asParameter() const;

        OPENSOLID_CORE_EXPORT virtual bool isDuplicate(const Function& other) const = 0;
        
        OPENSOLID_CORE_EXPORT virtual Function deduplicated(
            std::vector<Function>& others
        ) const = 0;

        OPENSOLID_CORE_EXPORT virtual void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            ResultCacheXd& cache
        ) const = 0;
        
        OPENSOLID_CORE_EXPORT virtual void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            ResultCacheXI& cache
        ) const = 0;

        OPENSOLID_CORE_EXPORT virtual void evaluateJacobian(
            const MapXcd& parameterValues,
            MapXd& results
        ) const;
        
        OPENSOLID_CORE_EXPORT virtual void evaluateJacobian(
            const MapXcI& parameterBounds,
            MapXI& results
        ) const;

        OPENSOLID_CORE_EXPORT virtual Function derivative(int parameterIndex = 0) const = 0;

        OPENSOLID_CORE_EXPORT virtual Function components(int startIndex, int numComponents) const;
        OPENSOLID_CORE_EXPORT virtual Function compose(const Function& innerFunction) const;
        OPENSOLID_CORE_EXPORT virtual Function scaled(double scale) const;
        OPENSOLID_CORE_EXPORT virtual Function translated(const VectorXd& vector) const;
        OPENSOLID_CORE_EXPORT virtual Function transformed(const MatrixXd& matrix) const;
        OPENSOLID_CORE_EXPORT virtual Function norm() const;
        OPENSOLID_CORE_EXPORT virtual Function normalized() const;
        OPENSOLID_CORE_EXPORT virtual Function squaredNorm() const;
        OPENSOLID_CORE_EXPORT virtual Function tangentVector() const;
        OPENSOLID_CORE_EXPORT virtual Function curvature() const;
        OPENSOLID_CORE_EXPORT virtual Function normalVector() const;
        OPENSOLID_CORE_EXPORT virtual Function binormalVector() const;
        
        OPENSOLID_CORE_EXPORT virtual void debug(std::ostream& stream, int indent) const = 0;
    };
}
