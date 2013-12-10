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

#include <OpenSolid/Core/ParametricExpression/ExpressionEvaluation.declarations.hpp>

#include <OpenSolid/Core/ExpressionImplementation.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace Eigen
{
    namespace internal
    {
        template <int iNumDimensions, int iNumParameters, class TArgument>
        struct traits<opensolid::ExpressionEvaluation<iNumDimensions, iNumParameters, TArgument>>
        {
            typedef Matrix<typename TArgument::Scalar, iNumDimensions, TArgument::ColsAtCompileTime>
                ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <int iNumDimensions>
        struct traits<opensolid::ExpressionEvaluation<iNumDimensions, 1, int>>
        {
            typedef Matrix<double, iNumDimensions, 1> ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<int iNumDimensions>
        struct traits<opensolid::ExpressionEvaluation<iNumDimensions, 1, double>>
        {
            typedef Matrix<double, iNumDimensions, 1> ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<int iNumDimensions>
        struct traits<opensolid::ExpressionEvaluation<iNumDimensions, 1, opensolid::Interval>>
        {
            typedef Matrix<opensolid::Interval, iNumDimensions, 1> ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
    }
}

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters, class TArgument>
    class ExpressionEvaluation :
        public ReturnByValue<ExpressionEvaluation<iNumDimensions, iNumParameters, TArgument>>
    {
    private:
        const ExpressionImplementation* _expressionImplementationPtr;
        const TArgument& _argument;
    public:
        ExpressionEvaluation(
            const ExpressionImplementation* expressionImplementationPtr,
            const TArgument& argument
        );

        int
        rows() const;

        int
        cols() const;
        
        template <class TResult>
        void
        evalTo(TResult& result) const;
        
        typename TArgument::Scalar
        value() const;

        bool
        isZero(double tolerance = 1e-12) const;
    };
    
    template <int iNumDimensions>
    class ExpressionEvaluation<iNumDimensions, 1, int> :
        public ReturnByValue<ExpressionEvaluation<iNumDimensions, 1, int>>
    {
    private:
        const ExpressionImplementation* _expressionImplementationPtr;
        double _argument;
    public:
        ExpressionEvaluation(
            const ExpressionImplementation* expressionImplementationPtr,
            int argument
        );

        int
        rows() const;

        int
        cols() const;
        
        template <class TResult>
        void
        evalTo(TResult& result) const;
        
        double
        value() const;
        
        bool
        isZero(double precision = 1e-12) const;
    };
    
    template <int iNumDimensions>
    class ExpressionEvaluation<iNumDimensions, 1, double> :
        public ReturnByValue<ExpressionEvaluation<iNumDimensions, 1, double>>
    {
    private:
        const ExpressionImplementation* _expressionImplementationPtr;
        double _argument;
    public:
        ExpressionEvaluation(
            const ExpressionImplementation* expressionImplementationPtr,
            double argument
        );

        int
        rows() const;

        int
        cols() const;
        
        template <class TResult>
        void
        evalTo(TResult& result) const;
        
        double
        value() const;
        
        bool
        isZero(double precision = 1e-12) const;
    };
    
    template <int iNumDimensions>
    class ExpressionEvaluation<iNumDimensions, 1, Interval> :
        public ReturnByValue<ExpressionEvaluation<iNumDimensions, 1, Interval>>
    {
    private:
        const ExpressionImplementation* _expressionImplementationPtr;
        Interval _argument;
    public:
        ExpressionEvaluation(
            const ExpressionImplementation* expressionImplementationPtr,
            Interval argument
        );

        int
        rows() const;

        int
        cols() const;
        
        template <class TResult>
        void
        evalTo(TResult& result) const;
        
        Interval
        value() const;
        
        bool
        isZero(double precision = 1e-12) const;
    };
}
