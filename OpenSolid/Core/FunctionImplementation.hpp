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

#include <OpenSolid/Core/FunctionImplementation/Evaluator.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    inline FunctionImplementationPtr
    FunctionImplementation::self() const {
        return this;
    }

    inline bool
    FunctionImplementation::isConstant() const {
        return typeid(*this) == typeid(ConstantFunction);
    }
    
    inline bool
    FunctionImplementation::isIdentity() const {
        return typeid(*this) == typeid(IdentityFunction);
    }
    
    inline bool
    FunctionImplementation::isParameter() const {
        return typeid(*this) == typeid(ParameterFunction);
    }
    
    template <class TFunctionImplementation>
    const TFunctionImplementation*
    FunctionImplementation::cast() const {
        assert(dynamic_cast<const TFunctionImplementation*>(this));
        return static_cast<const TFunctionImplementation*>(this);
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
        Evaluator& evaluator
    ) const {
        evaluateJacobianImpl(parameterValues, results, evaluator);
    }

    inline void
    FunctionImplementation::evaluateJacobian(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        evaluateJacobianImpl(parameterBounds, results, evaluator);
    }
}
