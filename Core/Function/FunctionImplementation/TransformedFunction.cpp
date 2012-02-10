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

#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/TransformedFunction.hpp>

namespace OpenSolid
{
    TransformedFunction::TransformedFunction(
        const Function& operand,
        const MatrixXd& matrix,
        const VectorXd& vector
    ) : UnaryOperation(operand), _matrix(matrix), _vector(vector) {
        assert(operand.dimensions() == matrix.cols());
        assert(vector.size() == matrix.rows());
    }
    
    int TransformedFunction::dimensions() const {return matrix().rows();}
    
    void TransformedFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results = (matrix() * operand()(parameter_values)).colwise() + vector();
    }
    
    void TransformedFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results = (matrix().cast<Interval>() * operand()(parameter_bounds)).colwise() +
            vector().cast<Interval>();
    }
    
    void TransformedFunction::getDerivative(int index, Function& result) const {
        result = operand().derivative(index).transformed(matrix(), VectorXd::Zero(dimensions()));
    }
    
    void TransformedFunction::getComposition(const Function& inner, Function& result) const {
        result = operand()(inner).transformed(matrix(), vector());
    }
    
    void TransformedFunction::getTransformed(
        const MatrixXd& matrix,
        const VectorXd& vector,
        Function& result
    ) const {
        result = operand().transformed(matrix * this->matrix(), matrix * this->vector() + vector);
    }
    
    void TransformedFunction::debug(std::ostream& stream, int indent) const {
        stream << "TransformedFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
