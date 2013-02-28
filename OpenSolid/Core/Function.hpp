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

#pragma once

#include <OpenSolid/config.hpp>

// Public headers
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Transformation.hpp>

// Internal headers
#include <OpenSolid/Core/Function/FunctionConstructors.hpp>
#include <OpenSolid/Core/Function/FunctionImplementation.hpp>
#include <OpenSolid/Core/Matrix/JacobianReturnValue.hpp>
#include <OpenSolid/Core/Matrix/MatrixReturnValue.hpp>

// Declarations headers
#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Domain/declarations.hpp>
#include <OpenSolid/Core/Function/declarations.hpp>
#include <OpenSolid/Core/Geometry/declarations.hpp>
#include <OpenSolid/Core/Simplex/declarations.hpp>
#include <OpenSolid/Core/Transformation/declarations.hpp>
 
#include <boost/intrusive_ptr.hpp>

#include <typeinfo>

namespace opensolid
{
    class Function :
        public FunctionConstructors,
        public Convertible<Function>,
        public Transformable<Function>
    {
    private:
        boost::intrusive_ptr<const FunctionImplementation> _implementation;
    public:
        OPENSOLID_CORE_EXPORT Function();
        OPENSOLID_CORE_EXPORT Function(const FunctionImplementation* function);

        OPENSOLID_CORE_EXPORT Function(const Rotation2d& rotation);
        OPENSOLID_CORE_EXPORT Function(const Rotation3d& rotation);
        OPENSOLID_CORE_EXPORT Function(const Mirror2d& mirror);
        OPENSOLID_CORE_EXPORT Function(const Mirror3d& mirror);
        OPENSOLID_CORE_EXPORT Function(const Projection2d& projection);
        OPENSOLID_CORE_EXPORT Function(const Projection3d& projection);

        template <int iNumSourceDimensions, int iNumDestinationDimensions>
        Function(
            const Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation
        );
        
        const FunctionImplementation* implementation() const;
        bool isValid() const;
        
        OPENSOLID_CORE_EXPORT int numDimensions() const;
        OPENSOLID_CORE_EXPORT int numParameters() const;

        OPENSOLID_CORE_EXPORT const ConstantFunction* asConstant() const;
        OPENSOLID_CORE_EXPORT const IdentityFunction* asIdentity() const;
        OPENSOLID_CORE_EXPORT const ParameterFunction* asParameter() const;

        OPENSOLID_CORE_EXPORT bool isDuplicate(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function deduplicated() const;
        OPENSOLID_CORE_EXPORT Function deduplicated(std::vector<Function>& others) const;

        OPENSOLID_CORE_EXPORT void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            ResultCacheXd& cache
        ) const;
        
        OPENSOLID_CORE_EXPORT void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            ResultCacheXI& cache
        ) const;

        OPENSOLID_CORE_EXPORT void evaluateJacobian(
            const MapXcd& parameterValues,
            MapXd& results
        ) const;
        
        OPENSOLID_CORE_EXPORT void evaluateJacobian(
            const MapXcI& parameterBounds,
            MapXI& results
        ) const;

        MatrixReturnValue<Function, int> operator()(int value) const;
        MatrixReturnValue<Function, double> operator()(double value) const;
        MatrixReturnValue<Function, Interval> operator()(Interval interval) const;
        
        template <class TDerived>
        MatrixReturnValue<Function, TDerived> operator()(const EigenBase<TDerived>& matrix) const;

        JacobianReturnValue<Function, int> jacobian(int value) const;
        JacobianReturnValue<Function, double> jacobian(double value) const;
        JacobianReturnValue<Function, Interval> jacobian(Interval interval) const;
        
        template <class TDerived>
        JacobianReturnValue<Function, TDerived> jacobian(const EigenBase<TDerived>& vector) const;
        
        OPENSOLID_CORE_EXPORT Function operator()(const Function& function) const;
        OPENSOLID_CORE_EXPORT Geometry operator()(const Domain& domain) const;
        
        OPENSOLID_CORE_EXPORT Function derivative(int parameterIndex = 0) const;
        
        OPENSOLID_CORE_EXPORT Function norm() const;
        OPENSOLID_CORE_EXPORT Function normalized() const;
        OPENSOLID_CORE_EXPORT Function squaredNorm() const;
        OPENSOLID_CORE_EXPORT Function x() const;
        OPENSOLID_CORE_EXPORT Function y() const;
        OPENSOLID_CORE_EXPORT Function z() const;
        OPENSOLID_CORE_EXPORT Function component(int index) const;
        OPENSOLID_CORE_EXPORT Function components(int startIndex, int numComponents) const;
        OPENSOLID_CORE_EXPORT Function concatenate(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function dot(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function cross(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function tangentVector() const;
        OPENSOLID_CORE_EXPORT Function curvature() const;
        OPENSOLID_CORE_EXPORT Function normalVector() const;
        OPENSOLID_CORE_EXPORT Function binormalVector() const;

        OPENSOLID_CORE_EXPORT Function operator+(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function operator-(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function operator*(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function operator/(const Function& other) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent = 0) const;
    };

    OPENSOLID_CORE_EXPORT Function operator*(double scale, const Function& function);
    OPENSOLID_CORE_EXPORT Function operator*(const MatrixXd& matrix, const Function& function);
    OPENSOLID_CORE_EXPORT Function operator+(const Function& function, const VectorXd& vector);

    OPENSOLID_CORE_EXPORT Function operator+(const Function& function, double value);
    OPENSOLID_CORE_EXPORT Function operator+(double value, const Function& function);
    OPENSOLID_CORE_EXPORT Function operator-(const Function& function, double value);
    OPENSOLID_CORE_EXPORT Function operator-(double value, const Function& function);
    OPENSOLID_CORE_EXPORT Function operator*(const Function& function, const VectorXd& vector);
    OPENSOLID_CORE_EXPORT Function operator/(double value, const Function& function);
    OPENSOLID_CORE_EXPORT Function operator/(const VectorXd& vector, const Function& function);
    
    OPENSOLID_CORE_EXPORT Function sin(const Function& argument);
    OPENSOLID_CORE_EXPORT Function cos(const Function& argument);
    OPENSOLID_CORE_EXPORT Function tan(const Function& argument);
    OPENSOLID_CORE_EXPORT Function sqrt(const Function& argument);
    OPENSOLID_CORE_EXPORT Function acos(const Function& argument);
    OPENSOLID_CORE_EXPORT Function asin(const Function& argument);
    OPENSOLID_CORE_EXPORT Function exp(const Function& argument);
    OPENSOLID_CORE_EXPORT Function log(const Function& argument);
    OPENSOLID_CORE_EXPORT Function pow(const Function& base, const Function& exponent);
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(
        std::ostream& stream,
        const Function& function
    );
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Conversion<Function, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const Function& argument) const;
    };
    
    template <>
    struct Conversion<Function, Vector2d>
    {
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Function& argument) const;
    };
    
    template <>
    struct Conversion<Function, Vector3d>
    {
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Function& argument) const;
    };
    
    template <>
    struct Conversion<Function, VectorXd>
    {
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Function& argument) const;
    };

    template <int iNumResultDimensions>
    struct Transformed<Function, iNumResultDimensions>
    {
        typedef Function Type;
    };
}

////////// Implementation //////////

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Simplex.hpp>

#include <OpenSolid/Core/Datum/TransformedDatum.hpp>
#include <OpenSolid/Core/Simplex/TransformedSimplex.hpp>

namespace opensolid
{
    // Declared in TransformedSimplex.hpp
    template <int iNumDimensions, int iNumVertices>
    inline TransformedSimplex<iNumDimensions, iNumVertices>::TransformedSimplex(
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
    inline TransformedDatum<iNumDimensions, iNumAxes>::TransformedDatum(
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
    
    inline const FunctionImplementation* Function::implementation() const {
        return _implementation.get();
    }

    inline bool Function::isValid() const {
        return implementation() != 0;
    }

    inline MatrixReturnValue<Function, int> Function::operator()(int value) const {
        return MatrixReturnValue<Function, int>(*this, value);
    }

    inline MatrixReturnValue<Function, double> Function::operator()(double value) const {
        return MatrixReturnValue<Function, double>(*this, value);
    }

    inline MatrixReturnValue<Function, Interval> Function::operator()(Interval interval) const {
        return MatrixReturnValue<Function, Interval>(*this, interval);
    }
    
    template <class TDerived>
    inline MatrixReturnValue<Function, TDerived> Function::operator()(
        const EigenBase<TDerived>& matrix
    ) const {
        return MatrixReturnValue<Function, TDerived>(*this, matrix.derived());
    }

    inline JacobianReturnValue<Function, int> Function::jacobian(int value) const {
        return JacobianReturnValue<Function, int>(*this, value);
    }

    inline JacobianReturnValue<Function, double> Function::jacobian(double value) const {
        return JacobianReturnValue<Function, double>(*this, value);
    }

    inline JacobianReturnValue<Function, Interval> Function::jacobian(Interval interval) const {
        return JacobianReturnValue<Function, Interval>(*this, interval);
    }

    template <class TDerived>
    inline JacobianReturnValue<Function, TDerived> Function::jacobian(
        const EigenBase<TDerived>& vector
    ) const {
        return JacobianReturnValue<Function, TDerived>(*this, vector.derived());
    }
}
