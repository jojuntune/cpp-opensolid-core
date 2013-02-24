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

// Internal headers
#include <OpenSolid/Core/Function/FunctionImplementation.hpp>

namespace opensolid
{
    class ConstantFunction : public FunctionImplementation
    {
    private:
        VectorXd _value;
        int _numParameters;
    public:
        OPENSOLID_CORE_EXPORT ConstantFunction(double value, int numParameters);
        OPENSOLID_CORE_EXPORT ConstantFunction(const VectorXd& vector, int numParameters);

        OPENSOLID_CORE_EXPORT bool isConstant() const;
        OPENSOLID_CORE_EXPORT VectorXd value() const;
        
        OPENSOLID_CORE_EXPORT int numParameters() const;
        OPENSOLID_CORE_EXPORT int numDimensions() const;
        
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameter_values, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameter_bounds, MapXI& results) const;
        
        OPENSOLID_CORE_EXPORT Function derivative(int index) const;
        
        OPENSOLID_CORE_EXPORT Function components(int startIndex, int numComponents) const;

        OPENSOLID_CORE_EXPORT Function compose(const Function& innerFunction) const;

        OPENSOLID_CORE_EXPORT Function scaled(double scale) const;
        OPENSOLID_CORE_EXPORT Function transformed(const MatrixXd& transformationMatrix) const;
        OPENSOLID_CORE_EXPORT Function translated(const VectorXd& vector) const;
        
        OPENSOLID_CORE_EXPORT Function norm() const;
        OPENSOLID_CORE_EXPORT Function normalized() const;
        OPENSOLID_CORE_EXPORT Function squaredNorm() const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}
