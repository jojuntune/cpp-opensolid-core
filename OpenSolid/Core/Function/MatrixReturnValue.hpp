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

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Function.declarations.hpp>

#include <OpenSolid/Core/Function/MatrixArgument.hpp>

namespace opensolid
{
    template <class TArgument>
    class MatrixReturnValue;
}

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
    class MatrixReturnValue : public ReturnByValue<MatrixReturnValue<TArgument>>
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

////////// Implementation //////////

namespace opensolid
{
    template <class TArgument>
    inline
    MatrixReturnValue<TArgument>::MatrixReturnValue(
        const FunctionImplementation* functionImplementation,
        const TArgument& argument
    ) : _functionImplementation(functionImplementation),
        _argument(argument) {
    }
    
    template <class TArgument>
    inline int
    MatrixReturnValue<TArgument>::rows() const {
        return _functionImplementation->numDimensions();
    }
    
    template <class TArgument>
    inline int
    MatrixReturnValue<TArgument>::cols() const {
        return _argument.cols();
    }
    
    template <class TArgument> template <class TResult>
    inline void
    MatrixReturnValue<TArgument>::evalTo(TResult& result) const {
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
        
        // Allocate empty result cache
        ResultCache<Scalar> cache;

        // Evaluate
        _functionImplementation->evaluate(argumentMap, resultMap, cache);
    }
    
    template <class TArgument>
    inline typename TArgument::Scalar
    MatrixReturnValue<TArgument>::value() const {
        Matrix<typename TArgument::Scalar, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TArgument>
    inline bool
    MatrixReturnValue<TArgument>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    inline
    MatrixReturnValue<int>::MatrixReturnValue(
        const FunctionImplementation* functionImplementation,
        int argument
    ) : _functionImplementation(functionImplementation),
        _argument(argument) {
    }
    
    inline int
    MatrixReturnValue<int>::rows() const {
        return _functionImplementation->numDimensions();
    }
    
    inline int
    MatrixReturnValue<int>::cols() const {
        return 1;
    }
    
    template <class TResult>
    inline void
    MatrixReturnValue<int>::evalTo(TResult& result) const {
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
        
        // Allocate empty result cache
        ResultCache<double> cache;

        // Evaluate
        _functionImplementation->evaluate(argumentMap, resultMap, cache);
    }
    
    inline double
    MatrixReturnValue<int>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    inline bool
    MatrixReturnValue<int>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    inline
    MatrixReturnValue<double>::MatrixReturnValue(
        const FunctionImplementation* functionImplementation,
        double argument
    ) : _functionImplementation(functionImplementation),
        _argument(argument) {
    }
    
    inline int
    MatrixReturnValue<double>::rows() const {
        return _functionImplementation->numDimensions();
    }
    
    inline int
    MatrixReturnValue<double>::cols() const {
        return 1;
    }
    
    template <class TResult>
    inline void
    MatrixReturnValue<double>::evalTo(TResult& result) const {
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
        
        // Allocate empty result cache
        ResultCache<double> cache;

        // Evaluate
        _functionImplementation->evaluate(argumentMap, resultMap, cache);
    }
    
    inline double
    MatrixReturnValue<double>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    inline bool
    MatrixReturnValue<double>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    inline
    MatrixReturnValue<Interval>::MatrixReturnValue(
        const FunctionImplementation* functionImplementation,
        Interval argument
    ) : _functionImplementation(functionImplementation),
        _argument(argument) {
    }

    inline int
    MatrixReturnValue<Interval>::rows() const {
        return _functionImplementation->numDimensions();
    }
    
    inline int
    MatrixReturnValue<Interval>::cols() const {
        return 1;
    }
    
    template <class TResult>
    inline void
    MatrixReturnValue<Interval>::evalTo(TResult& result) const {
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
        
        // Allocate empty result cache
        ResultCache<Interval> cache;
        
        // Evaluate
        _functionImplementation->evaluate(argumentMap, resultMap, cache);
    }
    
    inline Interval
    MatrixReturnValue<Interval>::value() const {
        Matrix<Interval, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    inline bool
    MatrixReturnValue<Interval>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
}
