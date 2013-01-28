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

#include "FunctionConstructors.hpp"

#include "EllipticalFunction.hpp"
#include "LinearFunction.hpp"
#include "ParametersFunction.hpp"

#include <OpenSolid/Core/Function.hpp>

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
    
    template <int iNumDimensions, int iNumAxes>
    Function FunctionConstructors::Linear(const Datum<iNumDimensions, iNumAxes>& datum) {
        return new LinearFunction<iNumDimensions, iNumAxes>(datum);
    }

    template Function FunctionConstructors::Linear<1, 1>(const Datum<1, 1>&);
    template Function FunctionConstructors::Linear<1, 2>(const Datum<1, 2>&);
    template Function FunctionConstructors::Linear<1, 3>(const Datum<1, 3>&);
    template Function FunctionConstructors::Linear<2, 1>(const Datum<2, 1>&);
    template Function FunctionConstructors::Linear<2, 2>(const Datum<2, 2>&);
    template Function FunctionConstructors::Linear<2, 3>(const Datum<2, 3>&);
    template Function FunctionConstructors::Linear<3, 1>(const Datum<3, 1>&);
    template Function FunctionConstructors::Linear<3, 2>(const Datum<3, 2>&);
    template Function FunctionConstructors::Linear<3, 3>(const Datum<3, 3>&);
    
    template <int iNumDimensions, int iNumAxes>
    Function FunctionConstructors::Elliptical(const Datum<iNumDimensions, iNumAxes>& datum) {
        return new EllipticalFunction<iNumDimensions, iNumAxes>(
            datum,
            Matrix<bool, 1, iNumAxes - 1>::Constant(true)
        );
    }

    template Function FunctionConstructors::Elliptical<1, 2>(const Datum<1, 2>&);
    template Function FunctionConstructors::Elliptical<1, 3>(const Datum<1, 3>&);
    template Function FunctionConstructors::Elliptical<2, 2>(const Datum<2, 2>&);
    template Function FunctionConstructors::Elliptical<2, 3>(const Datum<2, 3>&);
    template Function FunctionConstructors::Elliptical<3, 2>(const Datum<3, 2>&);
    template Function FunctionConstructors::Elliptical<3, 3>(const Datum<3, 3>&);
        
    template <int iNumDimensions, int iNumAxes>
    Function FunctionConstructors::Elliptical(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const Matrix<bool, 1, iNumAxes - 1>& convention
    ) {
        return new EllipticalFunction<iNumDimensions, iNumAxes>(datum, convention);
    }

    template Function FunctionConstructors::Elliptical<1, 2>(const Datum<1, 2>&, const Matrix<bool, 1, 1>&);
    template Function FunctionConstructors::Elliptical<1, 3>(const Datum<1, 3>&, const Matrix<bool, 1, 2>&);
    template Function FunctionConstructors::Elliptical<2, 2>(const Datum<2, 2>&, const Matrix<bool, 1, 1>&);
    template Function FunctionConstructors::Elliptical<2, 3>(const Datum<2, 3>&, const Matrix<bool, 1, 2>&);
    template Function FunctionConstructors::Elliptical<3, 2>(const Datum<3, 2>&, const Matrix<bool, 1, 1>&);
    template Function FunctionConstructors::Elliptical<3, 3>(const Datum<3, 3>&, const Matrix<bool, 1, 2>&);
}
