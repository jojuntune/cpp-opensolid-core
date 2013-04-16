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

#include <OpenSolid/Core/FunctionImplementation/SquareRootFunction.hpp>

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    SquareRootFunction::SquareRootFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.numDimensions() == 1);
    }
    
    int SquareRootFunction::numDimensions() const {
        return 1;
    }

    bool SquareRootFunction::isDuplicate(const Function& function) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    Function SquareRootFunction::deduplicated(std::vector<Function>& others) const {
        return new SquareRootFunction(operand().deduplicated(others));
    }
    
    struct SquareRoot
    {
        inline double operator()(double value) const {
            assert(value >= Zero());
            return value > 0.0 ? sqrt(value) : 0.0;
        }
        
        inline Interval operator()(const Interval& bounds) const {
            assert(bounds >= Zero());
            return Interval(operator()(bounds.lowerBound()), operator()(bounds.upperBound()));
        }
    };
    
    void SquareRootFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        results = cache.results(operand(), parameterValues).unaryExpr(SquareRoot());
    }
    
    void SquareRootFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        results = cache.results(operand(), parameterBounds).unaryExpr(SquareRoot());
    }

    Function SquareRootFunction::derivative(int index) const {
        return 0.5 * operand().derivative(index) / Function(this);
    }
    
    Function SquareRootFunction::squaredNorm() const {
        return operand().norm();
    }
    
    void SquareRootFunction::debug(std::ostream& stream, int indent) const {
        stream << "SquareRootFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
