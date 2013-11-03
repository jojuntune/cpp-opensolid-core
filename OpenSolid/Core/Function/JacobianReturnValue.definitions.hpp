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

#include <OpenSolid/Core/Function/JacobianReturnValue.declarations.hpp>

#include <OpenSolid/Core/FunctionImplementation.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace Eigen
{
    namespace internal
    {
        template <int iNumDimensions, int iNumParameters, class TArgument>
        struct traits<opensolid::JacobianReturnValue<iNumDimensions, iNumParameters, TArgument>>
        {
            typedef Matrix<typename TArgument::Scalar, iNumDimensions, iNumParameters>
                ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <int iNumDimensions>
        struct traits<opensolid::JacobianReturnValue<iNumDimensions, 1, int>>
        {
            typedef Matrix<double, iNumDimensions, 1> ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <int iNumDimensions>
        struct traits<opensolid::JacobianReturnValue<iNumDimensions, 1, double>>
        {
            typedef Matrix<double, iNumDimensions, 1> ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <int iNumDimensions>
        struct traits<opensolid::JacobianReturnValue<iNumDimensions, 1, opensolid::Interval>>
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
    class JacobianReturnValue :
        public ReturnByValue<JacobianReturnValue<iNumDimensions, iNumParameters, TArgument>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        const TArgument& _argument;
    public:
        JacobianReturnValue(
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
        
        typename TArgument::Scalar
        value() const;
        
        bool
        isZero(double tolerance = 1e-12) const;
    };
    
    template <int iNumDimensions>
    class JacobianReturnValue<iNumDimensions, 1, int> :
        public ReturnByValue<JacobianReturnValue<iNumDimensions, 1, int>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        double _argument;
    public:
        JacobianReturnValue(
            const FunctionImplementation* functionImplementation,
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
    class JacobianReturnValue<iNumDimensions, 1, double> :
        public ReturnByValue<JacobianReturnValue<iNumDimensions, 1, double>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        double _argument;
    public:
        JacobianReturnValue(
            const FunctionImplementation* functionImplementation,
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
    class JacobianReturnValue<iNumDimensions, 1, Interval> :
        public ReturnByValue<JacobianReturnValue<iNumDimensions, 1, Interval>>
    {
    private:
        const FunctionImplementation* _functionImplementation;
        Interval _argument;
    public:
        JacobianReturnValue(
            const FunctionImplementation* functionImplementation,
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
