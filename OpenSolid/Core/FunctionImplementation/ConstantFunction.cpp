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

#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ConstantFunction::ConstantFunction(const VectorXd& vector, int numParameters) :
        _vector(vector),
        _bounds(vector.cast<Interval>()),
        _numParameters(numParameters) {
    }

    ConstantFunction::ConstantFunction(double value, int numParameters) :
        _vector(VectorXd::Constant(1, value)),
        _bounds(VectorXI::Constant(1, Interval(value))),
        _numParameters(numParameters) {
    }

    const ConstantFunction* ConstantFunction::asConstant() const {
        return this;
    }
    
    int ConstantFunction::numParameters() const {
        return _numParameters;
    }
    
    int ConstantFunction::numDimensions() const {
        return vector().size();
    }

    bool ConstantFunction::isDuplicateOf(const Function& function) const {
        const ConstantFunction* other =
            dynamic_cast<const ConstantFunction*>(function.implementation());
        if (other) {
            return this->vector().size() == other->vector().size() && 
                (this->vector() - other->vector()).isZero();
        } else {
            return false;
        }
    }

    Function ConstantFunction::deduplicated(std::vector<Function>&) const {
        return this;
    }
        
    void ConstantFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>&
    ) const {
        results.colwise() = vector();
    }
    
    void ConstantFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>&
    ) const {
        results.colwise() = bounds();
    }
    
    Function ConstantFunction::derivative(int) const {
        return new ConstantFunction(VectorXd::Zero(numDimensions()), numParameters());
    }
    
    Function ConstantFunction::components(int startIndex, int numComponents) const {
        return new ConstantFunction(
            vector().middleRows(startIndex, numComponents),
            numParameters()
        );
    }
    
    Function ConstantFunction::compose(const Function& innerFunction) const {
        return this;
    }
    
    Function ConstantFunction::scaled(double scale) const {
        return new ConstantFunction(scale * vector(), numParameters());
    }
    
    Function ConstantFunction::transformed(const MatrixXd& transformationMatrix) const {
        return new ConstantFunction(transformationMatrix * vector(), numParameters());
    }
    
    Function ConstantFunction::translated(const VectorXd& vector) const {
        return new ConstantFunction(this->vector() + vector, numParameters());
    }
    
    Function ConstantFunction::norm() const {
        return new ConstantFunction(vector().norm(), numParameters());
    }
    
    Function ConstantFunction::normalized() const {
        double norm = vector().norm();
        assert(norm > Zero());
        return new ConstantFunction(vector() / norm, numParameters());
    }
    
    Function ConstantFunction::squaredNorm() const {
        return new ConstantFunction(vector().squaredNorm(), numParameters());
    }
    
    void ConstantFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConstantFunction: " << vector().transpose() << std::endl;
    }
}
