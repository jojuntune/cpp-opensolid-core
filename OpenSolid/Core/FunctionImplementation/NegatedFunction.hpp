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

#include <OpenSolid/Core/FunctionImplementation/UnaryOperation.hpp>

namespace opensolid
{
    class NegatedFunction :
        public UnaryOperation
    {
    private:
        OPENSOLID_CORE_EXPORT
        int
        numDimensionsImpl() const override;

        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const override;

        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        derivativeImpl(int parameterIndex) const override;

        OPENSOLID_CORE_EXPORT
        bool
        isDuplicateOfImpl(const FunctionImplementationPtr& other) const override;

        OPENSOLID_CORE_EXPORT 
        virtual FunctionImplementationPtr
        componentsImpl(int startIndex, int numComponents) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        scaledImpl(double scale) const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        transformedImpl(const MatrixXd& transformationMatrix) const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        normImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        normalizedImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        squaredNormImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        negatedImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        sinImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        cosImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        tanImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        acosImpl() const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        asinImpl() const override;

        OPENSOLID_CORE_EXPORT
        void
        debugImpl(std::ostream& stream, int indent) const override;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        withNewOperandImpl(const FunctionImplementationPtr& newOperand) const override;
    public:
        OPENSOLID_CORE_EXPORT
        NegatedFunction(const FunctionImplementationPtr& operand);
    };
}
