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

#include <OpenSolid/Value/Tolerance.hpp>
#include "../Function.hpp"
#include "ConstantFunction.hpp"

namespace opensolid
{
    ConstantFunction::ConstantFunction(const VectorXd& value) : _value(value) {}
    
    int ConstantFunction::parameters() const {return 0;}
    
    int ConstantFunction::dimensions() const {return value().size();}
    
    void ConstantFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        results.colwise() = value();
    }
    
    void ConstantFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        results.colwise() = value().cast<Interval>();
    }
    
    void ConstantFunction::getDerivative(int index, Function& result) const {
        result = VectorXd::Zero(value().size());
    }
    
    void ConstantFunction::getComponents(int index, int num, Function& result) const {
        result = value().middleRows(index, num);
    }
    
    void ConstantFunction::getComposition(const Function& inner, Function& result) const {
        result = value();
    }
    
    void ConstantFunction::getTransformed(const DatumXd& datum, Function& result) const {
        result = value() * datum;
    }
    
    void ConstantFunction::getNorm(Function& result) const {result = value().norm();}
    
    void ConstantFunction::getNormalized(Function& result) const {    
        double norm = value().norm();
        assert(abs(norm) > Tolerance::roundoff());
        result = value() / norm;
    }
    
    void ConstantFunction::getSquaredNorm(Function& result) const {result = value().squaredNorm();}
    
    void ConstantFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConstantFunction: " << value().transpose() << std::endl;
    }
}
