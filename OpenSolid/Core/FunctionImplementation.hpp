/************************************************************************************
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

#include <OpenSolid/Core/FunctionImplementation.definitions.hpp>

#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Function/Evaluator.hpp>
#include <OpenSolid/Core/Function/JacobianEvaluator.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    inline const ConstantFunction*
    FunctionImplementation::asConstant() const {
        return asConstantImpl();
    }
    
    inline const IdentityFunction*
    FunctionImplementation::asIdentity() const {
        return asIdentityImpl();
    }
    
    inline const ParameterFunction*
    FunctionImplementation::asParameter() const {
        return asParameterImpl();
    }
    
    inline int
    FunctionImplementation::numDimensions() const {
        return numDimensionsImpl();
    }
    
    inline int
    FunctionImplementation::numParameters() const {
        return numParametersImpl();
    }
    
    inline void
    FunctionImplementation::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        evaluateImpl(parameterValues, results, evaluator);
    }
    
    inline void
    FunctionImplementation::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        evaluateImpl(parameterBounds, results, evaluator);
    }
    
    inline void
    FunctionImplementation::evaluateJacobian(
        const MapXcd& parameterValues,
        MapXd& results,
        JacobianEvaluator& jacobianEvaluator
    ) const {
        evaluateJacobianImpl(parameterValues, results, jacobianEvaluator);
    }

    inline void
    FunctionImplementation::evaluateJacobian(
        const MapXcI& parameterBounds,
        MapXI& results,
        JacobianEvaluator& jacobianEvaluator
    ) const {
        evaluateJacobianImpl(parameterBounds, results, jacobianEvaluator);
    }
}
