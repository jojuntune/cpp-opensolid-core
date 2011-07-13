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

#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Function/FunctionImplementation/NormalizedFunction.hpp>

namespace OpenSolid
{
    NormalizedFunction::NormalizedFunction(const Function& operand) : UnaryFunction(operand) {}
    
    int NormalizedFunction::dimensions() const {return operand().dimensions();}

    void NormalizedFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        MatrixXd operand_values = operand()(parameter_values);
        VectorXd squared_norms = operand_values.colwise().squaredNorm();
        results = operand_values * squared_norms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void NormalizedFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        MatrixXI operand_bounds = operand()(parameter_bounds);
        VectorXI squared_norms = operand_bounds.colwise().squaredNorm();
        results = operand_bounds * squared_norms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void NormalizedFunction::getDerivative(int index, Function& result) const {
        Function operand_derivative = operand().derivative(index);
        Function operand_normalized = operand().normalized();
        result =
            (operand_derivative - operand_derivative.dot(operand_normalized) * operand_normalized) /
            operand().norm();
    }
    
    void NormalizedFunction::getNorm(Function& result) const {result = 1.0;}
    
    void NormalizedFunction::getNormalized(Function& result) const {result = this;}
    
    void NormalizedFunction::getSquaredNorm(Function& result) const {result = 1.0;}
    
    void NormalizedFunction::debug(std::ostream& stream, int indent) const {
        stream << "NormalizedFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
