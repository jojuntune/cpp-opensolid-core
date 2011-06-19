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
 
#include "FunctionImplementation.hpp"
#include "implementations/ComponentsFunction.hpp"
#include "implementations/CompositionFunction.hpp"
#include "implementations/NormFunction.hpp"
#include "implementations/NormalizedFunction.hpp"
#include "implementations/SquaredNormFunction.hpp"
#include "implementations/TransformedFunction.hpp"

namespace OpenSolid
{
    FunctionImplementation::~FunctionImplementation() {}
    
    void FunctionImplementation::getComponents(int index, int num, Function& result) const {
        result = new ComponentsFunction(this, index, num);
    }
    
    void FunctionImplementation::getComposition(const Function& inner, Function& result) const {
        result = new CompositionFunction(inner, this);
    }
        
    void FunctionImplementation::getTransformed(const DatumXD& datum, Function& result) const {
        result = new TransformedFunction(this, datum);
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
        assert(parameters() == 1 || parameters() == 2);
        if (parameters() == 1) {
            result = Function(this).tangent().derivative().normalized();
        } else {
            assert(dimensions() == 3);
            result = Function(this).derivative(0).cross(Function(this).derivative(1)).normalized();
        }
    }
    
    void FunctionImplementation::getBinormal(Function& result) const {
        result = Function(this).tangent().cross(Function(this).normal());
    }
}
