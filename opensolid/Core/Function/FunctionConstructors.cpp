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

#include <OpenSolid/Core/Function/FunctionConstructors.hpp>

#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/EllipticalFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/LinearFunction.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation/ParametersFunction.hpp>

namespace opensolid
{
    Function FunctionConstructors::Identity(int dimensions) {
        return new ParametersFunction(dimensions, 0, dimensions);
    }

    Function FunctionConstructors::Parameter() {return new ParametersFunction(1, 0, 1);}

    Function FunctionConstructors::Parameter(int total, int index) {
        return new ParametersFunction(total, index, 1);
    }

    Function FunctionConstructors::Parameters(int total) {
        return new ParametersFunction(total, 0, total);
    }

    Function FunctionConstructors::Parameters(int total, int index, int num) {
        return new ParametersFunction(total, index, num);
    }
    
    Function FunctionConstructors::Components(const Function& x, const Function& y) {
        return x.concatenate(y);
    }
    
    Function FunctionConstructors::Components(
        const Function& x,
        const Function& y,
        const Function& z
    ) {
        return x.concatenate(y).concatenate(z);
    }
        
    Function FunctionConstructors::Linear(const DatumXd& datum) {
        return new LinearFunction(datum);
    }
        
    Function FunctionConstructors::Elliptical(const DatumXd& datum) {
        return new EllipticalFunction(datum, VectorXb::Constant(datum.axes() - 1, true));
    }
        
    Function FunctionConstructors::Elliptical(const DatumXd& datum, const VectorXb& convention) {
        return new EllipticalFunction(datum, convention);
    }
}
