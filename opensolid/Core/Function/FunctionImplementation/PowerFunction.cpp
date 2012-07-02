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
#include <OpenSolid/Core/Function/FunctionImplementation/PowerFunction.hpp>

namespace opensolid
{
    PowerFunction::PowerFunction(const Function& base, const Function& exponent) :
        BinaryOperation(base, exponent) {
        assert(base.dimensions() == 1);
        assert(exponent.dimensions() == 1);
        if (exponent.isConstant()) {
            _exponent_is_constant = true;
            _constant_exponent = exponent.as<double>();
            _integer_exponent = floor(_constant_exponent + 0.5);
            _exponent_is_integer = (_constant_exponent - _integer_exponent == Zero());
        } else {
            _exponent_is_constant = false;
            _exponent_is_integer = false;
            _constant_exponent = 0.0;
            _integer_exponent = 0;
        }
    }
        
    int PowerFunction::dimensions() const {return 1;}

    struct IntegerPower
    {
        int exponent;

        inline IntegerPower(int exponent_) : exponent(exponent_) {}

        inline double operator()(double base) const {return std::pow(base, exponent);}

        inline Interval operator()(const Interval& base) const {return pow(base, exponent);}
    };

    struct ConstantPower
    {
        double exponent;

        inline ConstantPower(double exponent_) : exponent(exponent_) {}

        inline Interval operator()(const Interval& base) const {return pow(base, exponent);}
    };

    struct Power
    {
        inline double operator()(double base, double exponent) const {return pow(base, exponent);}

        inline Interval operator()(const Interval& base, const Interval& exponent) const {
            return pow(base, exponent);
        }
    };
        
    void PowerFunction::getValues(const MapXcd& parameter_values, MapXd& results) const {
        RowVectorXd base_values = firstOperand()(parameter_values);
        if (_exponent_is_integer) {
            results = base_values.unaryExpr(IntegerPower(_integer_exponent));
        } else if (_exponent_is_constant) {
            results = base_values.array().pow(_constant_exponent);
        } else {
            results = base_values.binaryExpr(secondOperand()(parameter_values), Power());
        }
    }

    void PowerFunction::getBounds(const MapXcI& parameter_bounds, MapXI& results) const {
        RowVectorXI base_bounds = firstOperand()(parameter_bounds);
        if (_exponent_is_integer) {
            results = base_bounds.unaryExpr(IntegerPower(_integer_exponent));
        } else if (_exponent_is_constant) {
            results = base_bounds.array().unaryExpr(ConstantPower(_constant_exponent));
        } else {
            results = base_bounds.binaryExpr(secondOperand()(parameter_bounds), Power());
        }
    }

    void PowerFunction::getDerivative(int index, Function& result) const {
        if (_exponent_is_constant) {
            result = _constant_exponent * pow(firstOperand(), _constant_exponent - 1) *
                firstOperand().derivative(index);
        } else {
            result = (
                secondOperand().derivative(index) * log(firstOperand()) +
                secondOperand() * firstOperand().derivative(index) / firstOperand()
            ) * Function(this);
        }
    }
        
    void PowerFunction::debug(std::ostream& stream, int indent) const {
        std::cout << "PowerFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
