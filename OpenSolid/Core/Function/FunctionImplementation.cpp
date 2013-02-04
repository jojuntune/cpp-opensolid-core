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
 
#include <OpenSolid/Core/Function/FunctionImplementation.hpp>

// Internal headers
#include <OpenSolid/Core/Function/ComponentsFunction.hpp>
#include <OpenSolid/Core/Function/CompositionFunction.hpp>
#include <OpenSolid/Core/Function/NormFunction.hpp>
#include <OpenSolid/Core/Function/NormalizedFunction.hpp>
#include <OpenSolid/Core/Function/SquaredNormFunction.hpp>
#include <OpenSolid/Core/Function/TransformedFunction.hpp>

namespace opensolid
{
    FunctionImplementation::~FunctionImplementation() {
    }

    void FunctionImplementation::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        getValues(parameterValues, results);
    }
    
    void FunctionImplementation::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        getBounds(parameterBounds, results);
    }
    
    void FunctionImplementation::getComponents(
        int startIndex,
        int numComponents,
        Function& result
    ) const {
        result = new ComponentsFunction(this, startIndex, numComponents);
    }
    
    void FunctionImplementation::getComposition(
        const Function& innerFunction,
        Function& result
    ) const {
        result = new CompositionFunction(innerFunction, this);
    }
        
    void FunctionImplementation::getTransformed(
        const MatrixXd& transformationMatrix,
        const VectorXd& translationVector,
        Function& result
    ) const {
        result = new TransformedFunction(this, transformationMatrix, translationVector);
    }
    
    void FunctionImplementation::getNorm(Function& result) const {
        result = new NormFunction(this);
    }
    
    void FunctionImplementation::getNormalized(Function& result) const {
        result = new NormalizedFunction(this);
    }
    
    void FunctionImplementation::getSquaredNorm(Function& result) const {
        result = new SquaredNormFunction(this);
    }
    
    void FunctionImplementation::getTangent(Function& result) const {
        result = Function(this).derivative().normalized();
    }
    
    void FunctionImplementation::getCurvature(Function& result) const {
        result = Function(this).tangent().derivative().norm() / Function(this).derivative().norm();
    }
    
    void FunctionImplementation::getNormal(Function& result) const {
        assert(numParameters() == 1 || numParameters() == 2);
        if (numParameters() == 1) {
            result = Function(this).tangent().derivative().normalized();
        } else {
            assert(numDimensions() == 3);
            result = Function(this).derivative(0).cross(Function(this).derivative(1)).normalized();
        }
    }
    
    void FunctionImplementation::getBinormal(Function& result) const {
        result = Function(this).tangent().cross(Function(this).normal());
    }
}
