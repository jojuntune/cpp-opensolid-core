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

#include <OpenSolid/Core/ParametricExpression.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ExpressionImplementation.hpp>
#include <OpenSolid/Core/ExpressionImplementation/DeduplicationCache.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionEvaluation.hpp>
#include <OpenSolid/Core/ParametricExpression/JacobianEvaluation.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::ParametricExpression() :
        _implementation(new ConstantExpression(VectorXd::Zero(iNumDimensions), iNumParameters)) {
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::ParametricExpression(
        const ExpressionImplementation* implementation
    ) : _implementation(implementation) {
        if (!implementation) {
            throw Error(new PlaceholderError());
        }
        if (implementation->numDimensions() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        if (implementation->numParameters() != iNumParameters) {
            throw Error(new PlaceholderError());
        }
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::ParametricExpression(
        const ExpressionImplementationPtr& implementation
    ) : _implementation(implementation) {
        if (!implementation) {
            throw Error(new PlaceholderError());
        }
        if (implementation->numDimensions() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        if (implementation->numParameters() != iNumParameters) {
            throw Error(new PlaceholderError());
        }
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    const ExpressionImplementationPtr&
    ParametricExpression<iNumDimensions, iNumParameters>::implementation() const {
        return _implementation;
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    ExpressionEvaluation<iNumDimensions, 1, int>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(int value) const {
        static_assert(
            iNumParameters == 1,
            "Multiple parameters required"
        );
        return ExpressionEvaluation<iNumDimensions, 1, int>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    ExpressionEvaluation<iNumDimensions, 1, double>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(double value) const {
        static_assert(
            iNumParameters == 1,
            "Multiple parameters required"
        );
        return ExpressionEvaluation<iNumDimensions, 1, double>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    ExpressionEvaluation<iNumDimensions, 1, Interval>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(Interval interval) const {
        static_assert(
            iNumParameters == 1,
            "Multiple parameters required"
        );
        return ExpressionEvaluation<iNumDimensions, 1, Interval>(implementation().get(), interval);
    }
    
    template <int iNumDimensions, int iNumParameters> template <class TMatrix>
    inline
    ExpressionEvaluation<iNumDimensions, iNumParameters, TMatrix>
    ParametricExpression<iNumDimensions, iNumParameters>::evaluate(
        const EigenBase<TMatrix>& matrix
    ) const {
        static_assert(
            TMatrix::RowsAtCompileTime == iNumParameters || TMatrix::RowsAtCompileTime == Dynamic,
            "Incorrect number of parameters supplied"
        );
        if (TMatrix::RowsAtCompileTime == Dynamic && matrix.rows() != iNumParameters) {
            throw Error(new PlaceholderError());
        }
        return ExpressionEvaluation<iNumDimensions, iNumParameters, TMatrix>(
            implementation().get(),
            matrix.derived()
        );
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    JacobianEvaluation<iNumDimensions, 1, int>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(int value) const {
        static_assert(
            iNumParameters == 1,
            "Multiple parameters required"
        );
        return JacobianEvaluation<iNumDimensions, 1, int>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    JacobianEvaluation<iNumDimensions, 1, double>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(double value) const {
        static_assert(
            iNumParameters == 1,
            "Multiple parameters required"
        );
        return JacobianEvaluation<iNumDimensions, 1, double>(implementation().get(), value);
    }

    template <int iNumDimensions, int iNumParameters>
    inline
    JacobianEvaluation<iNumDimensions, 1, Interval>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(Interval interval) const {
        static_assert(
            iNumParameters == 1,
            "Multiple parameters required"
        );
        return JacobianEvaluation<iNumDimensions, 1, Interval>(implementation().get(), interval);
    }

    template <int iNumDimensions, int iNumParameters> template <class TVector>
    inline
    JacobianEvaluation<iNumDimensions, iNumParameters, TVector>
    ParametricExpression<iNumDimensions, iNumParameters>::jacobian(
        const EigenBase<TVector>& vector
    ) const {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Parameter vector for Jacobian matrix evaluation must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == iNumParameters || TVector::RowsAtCompileTime == Dynamic,
            "Incorrect number of parameters supplied for Jacobian matrix evaluation"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.size() != iNumParameters) {
            throw Error(new PlaceholderError());
        }
        return JacobianEvaluation<iNumDimensions, iNumParameters, TVector>(
            implementation().get(),
            vector.derived()
        );
    }

    template <int iNumDimensions, int iNumParameters> template <int iNumInnerParameters>
    ParametricExpression<iNumDimensions, iNumInnerParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::composed(
        const ParametricExpression<iNumParameters, iNumInnerParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->composed(other.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::derivative(int parameterIndex) const {
        if (parameterIndex < 0 || parameterIndex >= iNumParameters) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->derivative(parameterIndex)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::norm() const {
        DeduplicationCache deduplicationCache;
        return implementation()->norm()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::normalized() const {
        DeduplicationCache deduplicationCache;
        return implementation()->normalized()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::squaredNorm() const {
        DeduplicationCache deduplicationCache;
        return implementation()->squaredNorm()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::squared() const {
        static_assert(
            iNumDimensions == 1,
            "Use squaredNorm() for vectors (squared() is only for scalars)"
        );
        return squaredNorm();
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::x() const {
        DeduplicationCache deduplicationCache;
        return implementation()->x()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::y() const {
        static_assert(
            iNumDimensions >= 2,
            "No Y component exists"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->y()->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::z() const {
        static_assert(
            iNumDimensions >= 3,
            "No Z component exists"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->z()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::component(int index) const {
        if (index < 0 || index >= iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->component(index)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumComponents>
    ParametricExpression<iNumComponents, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::components(int startIndex) const {
        static_assert(
            iNumComponents <= iNumDimensions,
            "Too many components requested"
        );
        static_assert(
            iNumComponents > 0,
            "Zero or negative number of components requested"
        );
        if (startIndex < 0 || startIndex + iNumComponents > iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->components(startIndex, iNumComponents)->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters> template <int iNumOtherDimensions>
    ParametricExpression<iNumDimensions + iNumOtherDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::concatenated(
        const ParametricExpression<iNumOtherDimensions, iNumParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->concatenated(other.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters> template <class TVector>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::dot(
        const EigenBase<TVector>& vector
    ) const {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == iNumDimensions || TVector::RowsAtCompileTime == Dynamic,
            "Vector argument must have same number of dimensions as ParametricExpression object"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.rows() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->dot(new ConstantExpression(vector, iNumParameters))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::dot(
        const ParametricExpression<iNumDimensions, iNumParameters>& other
    ) const {
        DeduplicationCache deduplicationCache;
        return implementation()->dot(other.implementation())->deduplicated(deduplicationCache);
    }
        
    template <int iNumDimensions, int iNumParameters> template <class TVector>
    ParametricExpression<3, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::cross(
        const EigenBase<TVector>& vector
    ) const {
        static_assert(
            iNumDimensions == 3,
            "Cross product only defined in 3D"
        );
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == 3 || TVector::RowsAtCompileTime == Dynamic,
            "Vector argument must be 3D"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.rows() != 3) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return implementation()->cross(new ConstantExpression(vector, iNumParameters))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<3, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::cross(
        const ParametricExpression<3, iNumParameters>& other
    ) const {
        static_assert(
            iNumDimensions == 3,
            "Cross product only defined in 3D"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->cross(other.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::tangentVector() const {
        static_assert(
            iNumParameters == 1,
            "Tangent vector only defined for curves"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->tangentVector()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<1, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::curvature() const {
        static_assert(
            iNumParameters == 1,
            "Curvature only defined for curves"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->curvature()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>::normalVector() const {
        static_assert(
            (iNumParameters == 1) || (iNumDimensions == 3 && iNumParameters == 2),
            "Invalid numbers of dimensions/parameters for definition of normal vector"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->normalVector()->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<3, 1>
    ParametricExpression<iNumDimensions, iNumParameters>::binormalVector() const {
        static_assert(
            iNumDimensions == 3 && iNumParameters == 1,
            "Binormal only defined for 3D curves"
        );
        DeduplicationCache deduplicationCache;
        return implementation()->binormalVector()->deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumParameters, iNumDimensions>
    operator-(const ParametricExpression<iNumParameters, iNumDimensions>& expression) {
        DeduplicationCache deduplicationCache;
        return (-expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator+(const ParametricExpression<1, iNumParameters>& expression, double value) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() + value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator+(double value, const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return (value + expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const EigenBase<TVector>& vector
    ) {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == iNumDimensions || TVector::RowsAtCompileTime == Dynamic,
            "Vector argument must have same number of dimensions as ParametricExpression object"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.rows() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return (expression.implementation() + VectorXd(vector.derived()))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const EigenBase<TVector>& vector,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == iNumDimensions || TVector::RowsAtCompileTime == Dynamic,
            "Vector argument must have same number of dimensions as ParametricExpression object"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.rows() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return (VectorXd(vector.derived()) + expression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator+(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() + secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator-(const ParametricExpression<1, iNumParameters>& expression, double value) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() - value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator-(double value, const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return (value - expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        const EigenBase<TVector>& vector
    ) {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == iNumDimensions || TVector::RowsAtCompileTime == Dynamic,
            "Vector argument must have same number of dimensions as ParametricExpression object"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.rows() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return (expression.implementation() - VectorXd(vector.derived()))->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TVector>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const EigenBase<TVector>& vector,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime == iNumDimensions || TVector::RowsAtCompileTime == Dynamic,
            "Vector argument must have same number of dimensions as ParametricExpression object"
        );
        if (TVector::RowsAtCompileTime == Dynamic && vector.rows() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return (VectorXd(vector.derived()) - expression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator-(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() - secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        double value,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (value * expression.implementation())->deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        double value
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() * value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumDimensions, int iNumParameters, class TMatrix>
    ParametricExpression<TMatrix::RowsAtCompileTime, iNumParameters>
    operator*(
        const EigenBase<TMatrix>& matrix,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        static_assert(
            TMatrix::RowsAtCompileTime != Dynamic,
            "Transformation matrix must have static number of rows to determine number of "
            "dimensions in result parametric expression"
        );
        static_assert(
            TMatrix::ColsAtCompileTime == iNumDimensions || TMatrix::ColsAtCompileTime == Dynamic,
            "Parametric expression transformation matrix must have number of columns equal to "
            "parametric expression dimension"
        );
        if (TMatrix::ColsAtCompileTime == Dynamic && matrix.cols() != iNumDimensions) {
            throw Error(new PlaceholderError());
        }
        DeduplicationCache deduplicationCache;
        return (MatrixXd(matrix.derived()) * expression.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <class TVector, int iNumParameters>
    ParametricExpression<TVector::RowsAtCompileTime, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& expression,
        const EigenBase<TVector>& vector
    ) {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime != Dynamic,
            "Vector argument must have static number of rows to determine number of dimensions in "
            "result ParametricExpression object"
        );
        DeduplicationCache deduplicationCache;
        return (expression.implementation() * VectorXd(vector.derived()))->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() * secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& firstExpression,
        const ParametricExpression<iNumDimensions, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() * secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator*(
        const ParametricExpression<1, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() * secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator/(
        const ParametricExpression<iNumDimensions, iNumParameters>& expression,
        double value
    ) {
        DeduplicationCache deduplicationCache;
        return (expression.implementation() / value)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    operator/(
        double value,
        const ParametricExpression<1, iNumParameters>& expression
    ) {
        DeduplicationCache deduplicationCache;
        return (value / expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <class TVector, int iNumParameters>
    ParametricExpression<TVector::RowsAtCompileTime, iNumParameters>
    operator/(
        const EigenBase<TVector>& vector,
        const ParametricExpression<1, iNumParameters>& expression
    ) {
        static_assert(
            TVector::ColsAtCompileTime == 1,
            "Vector argument must have one column"
        );
        static_assert(
            TVector::RowsAtCompileTime != Dynamic,
            "Vector argument must have static number of rows to determine number of dimensions in "
            "result ParametricExpression object"
        );
        DeduplicationCache deduplicationCache;
        return (VectorXd(vector.derived()) / expression.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumParameters, int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumParameters>
    operator/(
        const ParametricExpression<iNumDimensions, iNumParameters>& firstExpression,
        const ParametricExpression<1, iNumParameters>& secondExpression
    ) {
        DeduplicationCache deduplicationCache;
        return (firstExpression.implementation() / secondExpression.implementation())->
            deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    sin(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return sin(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    cos(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return cos(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    tan(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return tan(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    sqrt(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return sqrt(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    acos(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return acos(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    asin(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return asin(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    exp(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return exp(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    log(const ParametricExpression<1, iNumParameters>& expression) {
        DeduplicationCache deduplicationCache;
        return log(expression.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(const ParametricExpression<1, iNumParameters>& base, double exponent) {
        DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent)->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(double base, const ParametricExpression<1, iNumParameters>& exponent) {
        DeduplicationCache deduplicationCache;
        return pow(base, exponent.implementation())->deduplicated(deduplicationCache);
    }
    
    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    pow(
        const ParametricExpression<1, iNumParameters>& base,
        const ParametricExpression<1, iNumParameters>& exponent
    ) {
        DeduplicationCache deduplicationCache;
        return pow(base.implementation(), exponent.implementation())->
            deduplicated(deduplicationCache);
    }

    template <int iNumDimensions, int iNumParameters>
    std::ostream&
    operator<<(
        std::ostream& stream,
        const ParametricExpression<iNumDimensions, iNumParameters>& expression
    ) {
        expression.implementation()->debug(stream, 0);
        return stream;
    }
}
