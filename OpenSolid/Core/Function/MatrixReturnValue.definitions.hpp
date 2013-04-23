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

#include <OpenSolid/Core/Function/MatrixReturnValue.declarations.hpp>

#include <OpenSolid/Core/FunctionImplementation.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace Eigen
{
    namespace internal
    {
        template <class TArgument>
        struct traits<opensolid::MatrixReturnValue<TArgument>>
        {
            typedef Matrix<typename TArgument::Scalar, Dynamic, TArgument::ColsAtCompileTime>
                ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <>
        struct traits<opensolid::MatrixReturnValue<int>>
        {
            typedef VectorXd ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<opensolid::MatrixReturnValue<double>>
        {
            typedef VectorXd ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<opensolid::MatrixReturnValue<opensolid::Interval>>
        {
            typedef VectorXI ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
    }
}

namespace opensolid
{
    template <class TArgument>
    class MatrixReturnValue :
        public ReturnByValue<MatrixReturnValue<TArgument>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        const TArgument& _argument;
    public:
        MatrixReturnValue(
            const FunctionImplementation* functionImplementation,
            const TArgument& argument
        );
        
        int
        rows() const;
        
        int
        cols() const;
        
        template <class TResult>
        void
        evalTo(TResult& result) const;
        
        typename TArgument::Scalar value() const;
        bool
        isZero(double tolerance = 1e-12) const;
    };
    
    template<>
    class MatrixReturnValue<int> :
        public ReturnByValue<MatrixReturnValue<int>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        double _argument;
    public:
        MatrixReturnValue(const FunctionImplementation* functionImplementation, int argument);
        
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
    
    template<>
    class MatrixReturnValue<double> :
        public ReturnByValue<MatrixReturnValue<double>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        double _argument;
    public:
        MatrixReturnValue(const FunctionImplementation* functionImplementation, double argument);
        
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
    
    template<>
    class MatrixReturnValue<Interval> :
        public ReturnByValue<MatrixReturnValue<Interval>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        Interval _argument;
    public:
        MatrixReturnValue(const FunctionImplementation* functionImplementation, Interval argument);
        
        int
        rows() const;
        
        int
        cols() const;
        
        template <class TResult>
        void
        evalTo(TResult& result) const;
        
        Interval value() const;
        bool
        isZero(double precision = 1e-12) const;
    };
}
