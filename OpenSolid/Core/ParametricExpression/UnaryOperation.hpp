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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.definitions.hpp>

namespace opensolid
{
    class UnaryOperation :
        public ExpressionImplementation
    {
    private:
        ExpressionImplementationPtr _operand;
        
        OPENSOLID_CORE_EXPORT
        int
        numParametersImpl() const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const override;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        composedImpl(const ExpressionImplementationPtr& innerExpression) const override;

        OPENSOLID_CORE_EXPORT
        virtual ExpressionImplementationPtr
        withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const = 0;
    protected:
        OPENSOLID_CORE_EXPORT
        bool
        duplicateOperands(const ExpressionImplementationPtr& other) const;
    public:
        OPENSOLID_CORE_EXPORT
        UnaryOperation(const ExpressionImplementationPtr& operand);
        
        const ExpressionImplementationPtr&
        operand() const;

        OPENSOLID_CORE_EXPORT
        ExpressionImplementationPtr
        withNewOperand(const ExpressionImplementationPtr& newOperand) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline
    const ExpressionImplementationPtr&
    UnaryOperation::operand() const {
        return _operand;
    }
}
