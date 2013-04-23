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

#include <OpenSolid/Core/FunctionImplementation/ArcsineFunction.hpp>

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ArcsineFunction::ArcsineFunction(const Function& operand) :
        UnaryOperation(operand) {

        assert(operand.numDimensions() == 1);
    }
    
    int ArcsineFunction::numDimensions() const {
        return 1;
    }

    bool ArcsineFunction::isDuplicate(const Function& function) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    Function ArcsineFunction::deduplicated(std::vector<Function>& others) const {
        return new ArcsineFunction(operand().deduplicated(others));
    }
    
    struct Arcsine
    {
        inline double operator()(double value) const {
            assert(Interval(-1, 1).contains(value));
            return asin(Interval(-1, 1).clamp(value));
        }
        
        inline Interval operator()(const Interval& bounds) const {
            assert(Interval(-1, 1).overlaps(bounds));
            return asin(Interval(-1, 1).clamp(bounds));
        }
    };
    
    void ArcsineFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>& cache
    ) const {
        results = cache.results(operand(), parameterValues).unaryExpr(Arcsine());
    }
    
    void ArcsineFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>& cache
    ) const {
        results = cache.results(operand(), parameterBounds).unaryExpr(Arcsine());
    }

    Function ArcsineFunction::derivative(int index) const {
        return operand().derivative(index) / sqrt(1 - operand().squaredNorm());
    }
    
    void ArcsineFunction::debug(std::ostream& stream, int indent) const {
        stream << "ArcsineFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
