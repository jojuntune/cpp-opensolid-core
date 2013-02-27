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

#include <OpenSolid/Core/Function/LogarithmFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    LogarithmFunction::LogarithmFunction(const Function& operand) : UnaryOperation(operand) {
        assert(operand.numDimensions() == 1);
    }
        
    int LogarithmFunction::numDimensions() const {
        return 1;
    }

    bool LogarithmFunction::isDuplicate(const Function& function) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    Function LogarithmFunction::deduplicated(std::vector<Function>& others) const {
        return new LogarithmFunction(operand().deduplicated(others));
    }
        
    void LogarithmFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = operand()(parameterValues).array().log();
    }

    void LogarithmFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = operand()(parameterBounds).array().log();
    }

    Function LogarithmFunction::derivative(int index) const {
        return operand().derivative(index) / operand();
    }
        
    void LogarithmFunction::debug(std::ostream& stream, int indent) const {
        stream << "LogarithmFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
