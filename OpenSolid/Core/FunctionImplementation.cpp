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
 
#include <OpenSolid/Core/FunctionImplementation.hpp>

#include <OpenSolid/Core/FunctionImplementation/ComponentsFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/CompositionFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LinearTransformationFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NormFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/NormalizedFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ScalingFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/SquaredNormFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/TranslationFunction.hpp>

namespace opensolid
{
    // TODO
    void FunctionImplementation::evaluateJacobian(
        const MapXcd& parameterValues,
        MapXd& results
    ) const {
        throw FeatureNotImplemented();
    }
    
    // TODO
    void FunctionImplementation::evaluateJacobian(
        const MapXcI& parameterBounds,
        MapXI& results
    ) const {
        throw FeatureNotImplemented();
    }

    FunctionImplementation::~FunctionImplementation() {
    }
        
    const ConstantFunction* FunctionImplementation::asConstant() const {
        return 0;
    }

    const IdentityFunction* FunctionImplementation::asIdentity() const {
        return 0;
    }

    const ParameterFunction* FunctionImplementation::asParameter() const {
        return 0;
    }
    
    Function FunctionImplementation::components(int startIndex, int numComponents) const {
        return new ComponentsFunction(this, startIndex, numComponents);
    }
    
    Function FunctionImplementation::compose(const Function& innerFunction) const {
        return new CompositionFunction(this, innerFunction);
    }
        
    Function FunctionImplementation::scaled(double scale) const {
        return new ScalingFunction(scale, this);
    }
        
    Function FunctionImplementation::translated(const VectorXd& vector) const {
        return new TranslationFunction(this, vector);
    }
        
    Function FunctionImplementation::transformed(const MatrixXd& transformationMatrix) const {
        return new LinearTransformationFunction(transformationMatrix, this);
    }
    
    Function FunctionImplementation::norm() const {
        return new NormFunction(this);
    }
    
    Function FunctionImplementation::normalized() const {
        return new NormalizedFunction(this);
    }
    
    Function FunctionImplementation::squaredNorm() const {
        return new SquaredNormFunction(this);
    }
    
    Function FunctionImplementation::tangentVector() const {
        return derivative().normalized();
    }
    
    Function FunctionImplementation::curvature() const {
        return tangentVector().derivative().norm() / derivative().norm();
    }
    
    Function FunctionImplementation::normalVector() const {
        assert(numParameters() == 1 || numParameters() == 2);
        if (numParameters() == 1) {
            return tangentVector().derivative().normalized();
        } else {
            assert(numDimensions() == 3);
            return derivative(0).cross(derivative(1)).normalized();
        }
    }
    
    Function FunctionImplementation::binormalVector() const {
        return tangentVector().cross(normalVector());
    }
}
