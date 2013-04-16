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

#include <OpenSolid/Core/Function.definitions.hpp>

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Datum/TransformedDatum.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Core/Simplex/TransformedSimplex.hpp>

namespace opensolid
{
    // Declared in TransformedSimplex.hpp
    template <int iNumDimensions, int iNumVertices>
    inline
    TransformedSimplex<iNumDimensions, iNumVertices>::TransformedSimplex(
        const Simplex<iNumDimensions, iNumVertices>& simplex,
        const Function& function
    ) : _simplex(simplex),
        _function(function) {

        assert(function.numParameters() == iNumDimensions);
    }
    
    // Declared in TransformedSimplex.hpp
    template <int iNumDimensions, int iNumVertices>
    inline const Simplex<iNumDimensions, iNumVertices>&
    TransformedSimplex<iNumDimensions, iNumVertices>::simplex() const {
        return _simplex;
    }
    
    // Declared in TransformedSimplex.hpp
    template <int iNumDimensions, int iNumVertices>
    inline const Function&
    TransformedSimplex<iNumDimensions, iNumVertices>::function() const {
        return _function;
    }

    // Declared in Simplex.hpp
    template <int iNumDimensions, int iNumVertices> template <int iArgumentDimensions>
    Simplex<iNumDimensions, iNumVertices>::Simplex(
        const TransformedSimplex<iArgumentDimensions, iNumVertices>& transformedSimplex
    ) {
        if (transformedSimplex.function().numDimensions() == iNumDimensions) {
            _vertices = transformedSimplex.function()(transformedSimplex.argument().vertices());
        } else {
            assert(false);
            _vertices.setZero();
        }
    }

    // Declared in TransformedDatum.hpp
    template <int iNumDimensions, int iNumAxes>
    inline
    TransformedDatum<iNumDimensions, iNumAxes>::TransformedDatum(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const Function& function
    ) : _datum(datum),
        _function(function) {

        assert(function.numParameters() == iNumDimensions);
    }
    
    // Declared in TransformedDatum.hpp
    template <int iNumDimensions, int iNumAxes>
    inline const Datum<iNumDimensions, iNumAxes>&
    TransformedDatum<iNumDimensions, iNumAxes>::datum() const {
        return _datum;
    }
    
    // Declared in TransformedDatum.hpp
    template <int iNumDimensions, int iNumAxes>
    inline const Function&
    TransformedDatum<iNumDimensions, iNumAxes>::function() const {
        return _function;
    }

    // Declared in Datum.hpp
    template <int iNumDimensions, int iNumAxes> template <int iArgumentDimensions>
    Datum<iNumDimensions, iNumAxes>::Datum(
        const TransformedDatum<iArgumentDimensions, iNumAxes>& transformedDatum
    ) {
        if (transformedDatum.function().numDimensions() == iNumDimensions) {
            Matrix<double, iArgumentDimensions, 1> argumentOrigin =
                transformedDatum.argument().originPoint();

            Matrix<double, iNumDimensions, iNumAxes> jacobian =
                transformedDatum.function().jacobian(argumentOrigin);

            initialize(
                transformedDatum.function()(argumentOrigin),
                jacobian * transformedDatum.argument().basisMatrix()
            );
        } else {
            assert(false);
            _originPoint.setZero();
            _basisMatrix.setZero();
            _inverseMatrix.setZero();
        }
    }
    
    inline const FunctionImplementation*
    Function::implementation() const {
        return _implementation.get();
    }

    inline bool
    Function::isValid() const {
        return implementation() != 0;
    }

    inline MatrixReturnValue<int>
    Function::operator()(int value) const {
        return MatrixReturnValue<int>(implementation(), value);
    }

    inline MatrixReturnValue<double>
    Function::operator()(double value) const {
        return MatrixReturnValue<double>(implementation(), value);
    }

    inline MatrixReturnValue<Interval>
    Function::operator()(Interval interval) const {
        return MatrixReturnValue<Interval>(implementation(), interval);
    }
    
    template <class TMatrix>
    inline MatrixReturnValue<TMatrix>
    Function::operator()(const EigenBase<TMatrix>& matrix) const {
        return MatrixReturnValue<TMatrix>(implementation(), matrix.derived());
    }

    inline JacobianReturnValue<Function, int>
    Function::jacobian(int value) const {
        return JacobianReturnValue<Function, int>(*this, value);
    }

    inline JacobianReturnValue<Function, double>
    Function::jacobian(double value) const {
        return JacobianReturnValue<Function, double>(*this, value);
    }

    inline JacobianReturnValue<Function, Interval>
    Function::jacobian(Interval interval) const {
        return JacobianReturnValue<Function, Interval>(*this, interval);
    }

    template <class TVector>
    inline JacobianReturnValue<Function, TVector>
    Function::jacobian(const EigenBase<TVector>& vector) const {
        return JacobianReturnValue<Function, TVector>(*this, vector.derived());
    }

    inline Function
    ScalingFunction<Function>::operator()(const Function& function, double scale) const {
        return scale * function;
    }

    inline Function
    TranslationFunction<Function>::operator()(
        const Function& function,
        const VectorXd& vector
    ) const {
        return function + vector;
    }

    template <int iTransformedDimensions>
    inline Function
    TransformationFunction<Function, iTransformedDimensions>::operator()(
        const Function& function,
        const MatrixXd& matrix
    ) const {
        return matrix * function;
    }
}
