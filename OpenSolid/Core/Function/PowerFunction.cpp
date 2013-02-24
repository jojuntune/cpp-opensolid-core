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

#include <OpenSolid/Core/Function/PowerFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    PowerFunction::PowerFunction(const Function& baseFunction, const Function& exponentFunction) :
        BinaryOperation(baseFunction, exponentFunction) {
        assert(baseFunction.numDimensions() == 1);
        assert(exponentFunction.numDimensions() == 1);
        if (exponentFunction.isConstant()) {
            _exponentIsConstant = true;
            _constantExponent = exponentFunction.as<double>();
            _integerExponent = floor(_constantExponent + 0.5);
            _exponentIsInteger = (_constantExponent - _integerExponent == Zero());
        } else {
            _exponentIsConstant = false;
            _exponentIsInteger = false;
            _constantExponent = 0.0;
            _integerExponent = 0;
        }
    }
        
    int PowerFunction::numDimensions() const {
        return 1;
    }

    struct IntegerPower
    {
        int exponent;

        inline IntegerPower(int exponent_) : exponent(exponent_) {
        }

        inline double operator()(double base) const {
            return std::pow(base, exponent);
        }

        inline Interval operator()(const Interval& base) const {
            return pow(base, exponent);
        }
    };

    struct ConstantPower
    {
        double exponent;

        inline ConstantPower(double exponent_) : exponent(exponent_) {
        }

        inline Interval operator()(const Interval& base) const {
            return pow(base, exponent);
        }
    };

    struct Power
    {
        inline double operator()(double base, double exponent) const {
            return pow(base, exponent);
        }

        inline Interval operator()(const Interval& base, const Interval& exponent) const {
            return pow(base, exponent);
        }
    };
        
    void PowerFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        RowVectorXd baseValues = firstOperand()(parameterValues);
        if (_exponentIsInteger) {
            results = baseValues.unaryExpr(IntegerPower(_integerExponent));
        } else if (_exponentIsConstant) {
            results = baseValues.array().pow(_constantExponent);
        } else {
            results = baseValues.binaryExpr(secondOperand()(parameterValues), Power());
        }
    }

    void PowerFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        RowVectorXI baseBounds = firstOperand()(parameterBounds);
        if (_exponentIsInteger) {
            results = baseBounds.unaryExpr(IntegerPower(_integerExponent));
        } else if (_exponentIsConstant) {
            results = baseBounds.array().unaryExpr(ConstantPower(_constantExponent));
        } else {
            results = baseBounds.binaryExpr(secondOperand()(parameterBounds), Power());
        }
    }

    Function PowerFunction::derivative(int index) const {
        if (_exponentIsConstant) {
            return _constantExponent *
                pow(
                    firstOperand(),
                    Function::Constant(_constantExponent - 1, firstOperand().numParameters())
                ) *
                firstOperand().derivative(index);
        } else {
            return (
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
