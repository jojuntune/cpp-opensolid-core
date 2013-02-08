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

// Public headers
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ReferenceCounted.hpp>

namespace opensolid
{
    class Function;
    
    class FunctionImplementation : public ReferenceCounted
    {
    public:
        virtual ~FunctionImplementation();
        
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameterValues, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameterBounds, MapXI& results) const;
        
        virtual int numParameters() const = 0;
        virtual int numDimensions() const = 0;
        
        virtual void getValues(const MapXcd& parameterValues, MapXd& results) const = 0;
        virtual void getBounds(const MapXcI& parameterBounds, MapXI& results) const = 0;
        
        virtual void getDerivative(int index, Function& result) const = 0;

        virtual void getComponents(int index, int num, Function& result) const;
        virtual void getComposition(const Function& inner, Function& result) const;
        
        virtual void getTransformed(
            const MatrixXd& matrix,
            const VectorXd& vector,
            Function& result
        ) const;
        
        virtual void getNorm(Function& result) const;
        virtual void getNormalized(Function& result) const;
        virtual void getSquaredNorm(Function& result) const;
        virtual void getTangent(Function& result) const;
        virtual void getCurvature(Function& result) const;
        virtual void getNormal(Function& result) const;
        virtual void getBinormal(Function& result) const;
        
        virtual void debug(std::ostream& stream, int indent) const = 0;
    };
}
