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

#include <OpenSolid/Core/Function/CrossProductFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    CrossProductFunction::CrossProductFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand.numDimensions() == 3 && secondOperand.numDimensions() == 3);
    }
    
    int CrossProductFunction::numDimensions() const {
        return 3;
    }

    bool CrossProductFunction::isDuplicate(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, false);
    }

    Function CrossProductFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedFirstOperand = firstOperand().deduplicated(others);
        Function deduplicatedSecondOperand = secondOperand().deduplicated(others);
        return new CrossProductFunction(deduplicatedFirstOperand, deduplicatedSecondOperand);
    }
    
    void CrossProductFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        MapXcd firstValues = cache.results(firstOperand(), parameterValues);
        MapXcd secondValues = cache.results(secondOperand(), parameterValues);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstValues.col(i).head<3>().cross(secondValues.col(i).head<3>());
        }
    }
    
    void CrossProductFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        MapXcI firstBounds = cache.results(firstOperand(), parameterBounds);
        MapXcI secondBounds = cache.results(secondOperand(), parameterBounds);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstBounds.col(i).head<3>().cross(secondBounds.col(i).head<3>());
        }
    }

    Function CrossProductFunction::derivative(int index) const {
        return firstOperand().derivative(index).cross(secondOperand())
            + firstOperand().cross(secondOperand().derivative(index));
    }
    
    void CrossProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "CrossProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
