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

#include <OpenSolid/Core/Function/ConstantFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ConstantFunction::ConstantFunction(const VectorXd& vector, int numParameters) :
        _value(vector),
        _numParameters(numParameters) {
    }

    ConstantFunction::ConstantFunction(double value, int numParameters) :
        _value(VectorXd::Constant(1, value)),
        _numParameters(numParameters) {
    }

    bool ConstantFunction::isConstant() const {
        return true;
    }

    VectorXd ConstantFunction::value() const {
        return _value;
    }
    
    int ConstantFunction::numParameters() const {
        return _numParameters;
    }
    
    int ConstantFunction::numDimensions() const {
        return value().size();
    }

    bool ConstantFunction::isDuplicate(const Function& function) const {
        const ConstantFunction* other =
            dynamic_cast<const ConstantFunction*>(function.implementation());
        if (other) {
            return this->value().size() == other->value().size() && 
                (this->value() - other->value()).isZero();
        } else {
            return false;
        }
    }

    Function ConstantFunction::deduplicated(std::vector<Function>&) const {
        return this;
    }
        
    void ConstantFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results.colwise() = value();
    }
    
    void ConstantFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results.colwise() = value().cast<Interval>();
    }
    
    Function ConstantFunction::derivative(int) const {
        return new ConstantFunction(VectorXd::Zero(numDimensions()), numParameters());
    }
    
    Function ConstantFunction::components(int startIndex, int numComponents) const {
        return new ConstantFunction(
            value().middleRows(startIndex, numComponents),
            numParameters()
        );
    }
    
    Function ConstantFunction::compose(const Function& innerFunction) const {
        return this;
    }
    
    Function ConstantFunction::scaled(double scale) const {
        return new ConstantFunction(scale * value(), numParameters());
    }
    
    Function ConstantFunction::transformed(const MatrixXd& transformationMatrix) const {
        return new ConstantFunction(transformationMatrix * value(), numParameters());
    }
    
    Function ConstantFunction::translated(const VectorXd& vector) const {
        return new ConstantFunction(value() + vector, numParameters());
    }
    
    Function ConstantFunction::norm() const {
        return new ConstantFunction(value().norm(), numParameters());
    }
    
    Function ConstantFunction::normalized() const {
        double norm = value().norm();
        assert(norm > Zero());
        return new ConstantFunction(value() / norm, numParameters());
    }
    
    Function ConstantFunction::squaredNorm() const {
        return new ConstantFunction(value().squaredNorm(), numParameters());
    }
    
    void ConstantFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConstantFunction: " << value().transpose() << std::endl;
    }
}
