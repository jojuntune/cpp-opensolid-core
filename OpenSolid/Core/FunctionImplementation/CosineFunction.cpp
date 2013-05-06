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

#include <OpenSolid/Core/FunctionImplementation/CosineFunction.hpp>

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    CosineFunction::CosineFunction(const Function& operand) :
        UnaryOperation(operand) {

        assert(operand.numDimensions() == 1);
    }
    
    int CosineFunction::numDimensions() const {
        return 1;
    }

    bool CosineFunction::isDuplicate(const Function& function) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    Function CosineFunction::deduplicated(std::vector<Function>& others) const {
        return new CosineFunction(operand().deduplicated(others));
    }
    
    void CosineFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>& cache
    ) const {
        results = cache.results(operand(), parameterValues).array().cos();
    }
    
    void CosineFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>& cache
    ) const {
        results = cache.results(operand(), parameterBounds).array().cos();
    }

    Function CosineFunction::derivative(int index) const {
        return -sin(operand()) * operand().derivative(index);
    }
    
    void CosineFunction::debug(std::ostream& stream, int indent) const {
        stream << "CosineFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
