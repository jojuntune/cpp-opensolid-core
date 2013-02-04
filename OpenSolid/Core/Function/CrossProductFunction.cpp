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
    
    void CrossProductFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        Matrix3Xd firstValues = firstOperand()(parameterValues);
        Matrix3Xd secondValues = secondOperand()(parameterValues);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstValues.col(i).cross(secondValues.col(i));
        }
    }
    
    void CrossProductFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        Matrix3XI firstBounds = firstOperand()(parameterBounds);
        Matrix3XI secondBounds = secondOperand()(parameterBounds);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstBounds.col(i).cross(secondBounds.col(i));
        }
    }

    void CrossProductFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index).cross(secondOperand())
            + firstOperand().cross(secondOperand().derivative(index));
    }
    
    void CrossProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "CrossProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
