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

#include <OpenSolid/Core/Function/ConstantFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ConstantFunction::ConstantFunction(const VectorXd& vector) : _vector(vector) {}
    
    int ConstantFunction::numParameters() const {return 0;}
    
    int ConstantFunction::numDimensions() const {return vector().size();}
    
    void ConstantFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results.colwise() = vector();
    }
    
    void ConstantFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results.colwise() = vector().cast<Interval>();
    }
    
    void ConstantFunction::getDerivative(int index, Function& result) const {
        result = VectorXd::Zero(vector().size());
    }
    
    void ConstantFunction::getComponents(int index, int num, Function& result) const {
        result = vector().middleRows(index, num);
    }
    
    void ConstantFunction::getComposition(const Function& inner, Function& result) const {
        result = vector();
    }
    
    void ConstantFunction::getTransformed(
        const MatrixXd& matrix,
        const VectorXd& vector,
        Function& result
    ) const {result = matrix * this->vector() + vector;}
    
    void ConstantFunction::getNorm(Function& result) const {result = vector().norm();}
    
    void ConstantFunction::getNormalized(Function& result) const {
        double norm = vector().norm();
        assert(norm > Zero());
        result = vector() / norm;
    }
    
    void ConstantFunction::getSquaredNorm(Function& result) const {result = vector().squaredNorm();}
    
    void ConstantFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConstantFunction: " << vector().transpose() << std::endl;
    }
}
