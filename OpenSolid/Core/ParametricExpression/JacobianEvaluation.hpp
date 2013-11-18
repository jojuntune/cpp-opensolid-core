/************************************************************************************
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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricExpression/JacobianEvaluation.definitions.hpp>

#include <OpenSolid/Core/ExpressionImplementation.hpp>
#include <OpenSolid/Core/ExpressionImplementation/Evaluator.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression/MatrixArgument.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters, class TArgument>
    inline
    JacobianEvaluation<iNumDimensions, iNumParameters, TArgument>::JacobianEvaluation(
        const ExpressionImplementation* expressionImplementationPtr,
        const TArgument& argument
    ) : _expressionImplementationPtr(expressionImplementationPtr),
        _argument(argument) {
    }
    
    template <int iNumDimensions, int iNumParameters, class TArgument>
    inline
    int
    JacobianEvaluation<iNumDimensions, iNumParameters, TArgument>::rows() const {
        return iNumDimensions;
    }
    
    template <int iNumDimensions, int iNumParameters, class TArgument>
    inline
    int
    JacobianEvaluation<iNumDimensions, iNumParameters, TArgument>::cols() const {
        return iNumParameters;
    }
    
    template <int iNumDimensions, int iNumParameters, class TArgument> template <class TResult>
    inline
    void
    JacobianEvaluation<iNumDimensions, iNumParameters, TArgument>::evalTo(TResult& result) const {
        MatrixArgument<TArgument> argument(_argument);
        
        // Common typedefs
        typedef typename TResult::Scalar Scalar;
        typedef Map<const Matrix<Scalar, Dynamic, Dynamic>, Unaligned, Stride<Dynamic, Dynamic>>
            ArgumentMapType;
            
        // Create argument map
        Stride<Dynamic, Dynamic> argumentStride(argument.outerStride(), argument.innerStride());
        ArgumentMapType argumentMap(
            argument.data(),
            argument.rows(),
            argument.cols(),
            argumentStride
        );
        
        // Create result map
        int resultOuterStride =
            (TResult::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int resultInnerStride =
            (TResult::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> resultStride(resultOuterStride, resultInnerStride);
        typedef Map<Matrix<Scalar, Dynamic, Dynamic>, Unaligned, Stride<Dynamic, Dynamic>>
            ResultMapType;
        ResultMapType resultMap(result.data(), result.rows(), result.cols(), resultStride);
        
        // Evaluate
        Evaluator evaluator;
        _expressionImplementationPtr->evaluateJacobian(argumentMap, resultMap, evaluator);
    }
    
    template <int iNumDimensions, int iNumParameters, class TArgument>
    inline
    typename TArgument::Scalar
    JacobianEvaluation<iNumDimensions, iNumParameters, TArgument>::value() const {
        Matrix<typename TArgument::Scalar, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <int iNumDimensions, int iNumParameters, class TArgument>
    inline
    bool
    JacobianEvaluation<iNumDimensions, iNumParameters, TArgument>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <int iNumDimensions>
    inline
    JacobianEvaluation<iNumDimensions, 1, int>::JacobianEvaluation(
        const ExpressionImplementation* expressionImplementationPtr,
        int argument
    ) : _expressionImplementationPtr(expressionImplementationPtr),
        _argument(argument) {
    }
    
    template <int iNumDimensions>
    inline
    int
    JacobianEvaluation<iNumDimensions, 1, int>::rows() const {
        return iNumDimensions;
    }
    
    template <int iNumDimensions>
    inline
    int
    JacobianEvaluation<iNumDimensions, 1, int>::cols() const {
        return 1;
    }
    
    template <int iNumDimensions> template <class TResult>
    inline
    void
    JacobianEvaluation<iNumDimensions, 1, int>::evalTo(TResult& result) const {
        // Create argument map
        typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argumentMap(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int resultOuterStride =
            (TResult::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int resultInnerStride =
            (TResult::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> resultStride(resultOuterStride, resultInnerStride);
        typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType resultMap(result.data(), result.rows(), result.cols(), resultStride);
        
        // Evaluate
        Evaluator evaluator;
        _expressionImplementationPtr->evaluateJacobian(argumentMap, resultMap, evaluator);
    }
    
    template <int iNumDimensions>
    inline
    double
    JacobianEvaluation<iNumDimensions, 1, int>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <int iNumDimensions>
    inline
    bool
    JacobianEvaluation<iNumDimensions, 1, int>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <int iNumDimensions>
    inline
    JacobianEvaluation<iNumDimensions, 1, double>::JacobianEvaluation(
        const ExpressionImplementation* expressionImplementationPtr,
        double argument
    ) : _expressionImplementationPtr(expressionImplementationPtr),
        _argument(argument) {
    }
    
    template <int iNumDimensions>
    inline
    int
    JacobianEvaluation<iNumDimensions, 1, double>::rows() const {
        return iNumDimensions;
    }
    
    template <int iNumDimensions>
    inline
    int
    JacobianEvaluation<iNumDimensions, 1, double>::cols() const {
        return 1;
    }
    
    template <int iNumDimensions> template <class TResult>
    inline
    void
    JacobianEvaluation<iNumDimensions, 1, double>::evalTo(TResult& result) const {
        // Create argument map
        typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argumentMap(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int resultOuterStride =
            (TResult::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int resultInnerStride =
            (TResult::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> resultStride(resultOuterStride, resultInnerStride);
        typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType resultMap(result.data(), result.rows(), result.cols(), resultStride);

        // Evaluate
        Evaluator evaluator;
        _expressionImplementationPtr->evaluateJacobian(argumentMap, resultMap, evaluator);
    }
    
    template <int iNumDimensions>
    inline
    double
    JacobianEvaluation<iNumDimensions, 1, double>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <int iNumDimensions>
    inline
    bool
    JacobianEvaluation<iNumDimensions, 1, double>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <int iNumDimensions>
    inline
    JacobianEvaluation<iNumDimensions, 1, Interval>::JacobianEvaluation(
        const ExpressionImplementation* expressionImplementationPtr,
        Interval argument
    ) : _expressionImplementationPtr(expressionImplementationPtr),
        _argument(argument) {
    }

    template <int iNumDimensions>
    inline
    int
    JacobianEvaluation<iNumDimensions, 1, Interval>::rows() const {
        return iNumDimensions;
    }
    
    template <int iNumDimensions>
    inline
    int
    JacobianEvaluation<iNumDimensions, 1, Interval>::cols() const {
        return 1;
    }
    
    template <int iNumDimensions> template <class TResult>
    inline
    void
    JacobianEvaluation<iNumDimensions, 1, Interval>::evalTo(TResult& result) const {
        // Create argument map
        typedef Map<const MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argumentMap(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int resultOuterStride =
            (TResult::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int resultInnerStride =
            (TResult::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> resultStride(resultOuterStride, resultInnerStride);
        typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType resultMap(result.data(), result.rows(), result.cols(), resultStride);
        
        // Evaluate
        Evaluator evaluator;
        _expressionImplementationPtr->evaluateJacobian(argumentMap, resultMap, evaluator);
    }
    
    template <int iNumDimensions>
    inline
    Interval
    JacobianEvaluation<iNumDimensions, 1, Interval>::value() const {
        Matrix<Interval, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <int iNumDimensions>
    inline
    bool
    JacobianEvaluation<iNumDimensions, 1, Interval>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
}
