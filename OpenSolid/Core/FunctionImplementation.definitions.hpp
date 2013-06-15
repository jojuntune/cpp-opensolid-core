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

#include <OpenSolid/Core/FunctionImplementation.declarations.hpp>

#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Function/Deduplicator.declarations.hpp>
#include <OpenSolid/Core/Function/Evaluator.declarations.hpp>
#include <OpenSolid/Core/Function/JacobianEvaluator.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ReferenceCounted.hpp>

#include <boost/intrusive_ptr.hpp>

#include <vector>

namespace opensolid
{
    class FunctionImplementation :
        public ReferenceCounted
    {
    private:
        OPENSOLID_CORE_EXPORT
        virtual const ConstantFunction*
        asConstantImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual const IdentityFunction*
        asIdentityImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual const ParameterFunction*
        asParameterImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual int
        numDimensionsImpl() const = 0;

        OPENSOLID_CORE_EXPORT
        virtual int
        numParametersImpl() const = 0;

        OPENSOLID_CORE_EXPORT
        virtual void
        evaluateImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const = 0;
        
        OPENSOLID_CORE_EXPORT
        virtual void
        evaluateImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const = 0;

        OPENSOLID_CORE_EXPORT
        virtual void
        evaluateJacobianImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            JacobianEvaluator& jacobianEvaluator
        ) const;
        
        OPENSOLID_CORE_EXPORT
        virtual void
        evaluateJacobianImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            JacobianEvaluator& jacobianEvaluator
        ) const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        derivativeImpl(int parameterIndex) const = 0;

        OPENSOLID_CORE_EXPORT
        virtual bool
        isDuplicateOfImpl(const FunctionImplementationPtr& other) const = 0;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        deduplicatedImpl(Deduplicator& deduplicator) const = 0;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        composeImpl(const FunctionImplementationPtr& innerFunction) const;

        OPENSOLID_CORE_EXPORT 
        virtual FunctionImplementationPtr
        componentsImpl(int startIndex, int numComponents) const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        scaledImpl(double scale) const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        translatedImpl(const VectorXd& vector) const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        transformedImpl(const MatrixXd& matrix) const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        normImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        normalizedImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        squaredNormImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        tangentVectorImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        curvatureImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        normalVectorImpl() const;
        
        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        binormalVectorImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        sqrtImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        sinImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        cosImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        tanImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        acosImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        asinImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        expImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual FunctionImplementationPtr
        logImpl() const;

        OPENSOLID_CORE_EXPORT
        virtual void
        debugImpl(std::ostream& stream, int indent) const = 0;
    public:
        OPENSOLID_CORE_EXPORT
        virtual
        ~FunctionImplementation();

        const ConstantFunction*
        asConstant() const;
        
        const IdentityFunction*
        asIdentity() const;
        
        const ParameterFunction*
        asParameter() const;

        int
        numDimensions() const;
        
        int
        numParameters() const;
        
        void
        evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const;
        
        void
        evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const;
        
        void
        evaluateJacobian(
            const MapXcd& parameterValues,
            MapXd& results,
            JacobianEvaluator& jacobianEvaluator
        ) const;

        void
        evaluateJacobian(
            const MapXcI& parameterBounds,
            MapXI& results,
            JacobianEvaluator& jacobianEvaluator
        ) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        derivative(int parameterIndex = 0) const;

        OPENSOLID_CORE_EXPORT
        bool
        isDuplicateOf(const FunctionImplementationPtr& other) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        deduplicated(Deduplicator& deduplicator) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        compose(const FunctionImplementationPtr& innerFunction) const;
         
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        components(int startIndex, int numComponents) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        component(int index) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        x() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        y() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        z() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        concatenated(const FunctionImplementationPtr& other) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        scaled(double scale) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        translated(const VectorXd& vector) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        transformed(const MatrixXd& matrix) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        norm() const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        normalized() const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        squaredNorm() const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        tangentVector() const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        curvature() const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        normalVector() const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        binormalVector() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        negated() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        sum(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        difference(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        product(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        quotient(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        dotProduct(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        crossProduct(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        sqrt() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        sin() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        cos() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        tan() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        acos() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        asin() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        exp() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        log() const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        pow(const FunctionImplementationPtr& other) const;

        OPENSOLID_CORE_EXPORT
        void
        debug(std::ostream& stream, int indent) const;
    };
}
