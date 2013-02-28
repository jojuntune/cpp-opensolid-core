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
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>

// Internal headers
#include <OpenSolid/Core/Matrix/MatrixArgument.hpp>

namespace opensolid
{
    template<class TEvaluator, class TArgument>
    class MatrixReturnValue;
}

namespace Eigen
{
    namespace internal
    {
        template <class TEvaluator, class TArgument>
        struct traits<opensolid::MatrixReturnValue<TEvaluator, TArgument>>
        {
            typedef Matrix<typename TArgument::Scalar, Dynamic, TArgument::ColsAtCompileTime>
                ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <class TEvaluator>
        struct traits<opensolid::MatrixReturnValue<TEvaluator, int>>
        {
            typedef VectorXd ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<class TEvaluator>
        struct traits<opensolid::MatrixReturnValue<TEvaluator, double>>
        {
            typedef VectorXd ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<class TEvaluator>
        struct traits<opensolid::MatrixReturnValue<TEvaluator, opensolid::Interval>>
        {
            typedef VectorXI ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
    }
}

namespace opensolid
{
    template<class TEvaluator, class TArgument>
    class MatrixReturnValue : public ReturnByValue<MatrixReturnValue<TEvaluator, TArgument>>
    {
    private:
        const TEvaluator& _evaluator;
        const TArgument& _argument;
    public:
        MatrixReturnValue(const TEvaluator& evaluator, const TArgument& argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        typename TArgument::Scalar value() const;
        bool isZero(double tolerance = 1e-12) const;
    };
    
    template<class TEvaluator>
    class MatrixReturnValue<TEvaluator, int> :
        public ReturnByValue<MatrixReturnValue<TEvaluator, int>>
    {
    private:
        const TEvaluator& _evaluator;
        double _argument;
    public:
        MatrixReturnValue(const TEvaluator& evaluator, int argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<class TEvaluator>
    class MatrixReturnValue<TEvaluator, double> :
        public ReturnByValue<MatrixReturnValue<TEvaluator, double>>
    {
    private:
        const TEvaluator& _evaluator;
        double _argument;
    public:
        MatrixReturnValue(const TEvaluator& evaluator, double argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<class TEvaluator>
    class MatrixReturnValue<TEvaluator, Interval> :
        public ReturnByValue<MatrixReturnValue<TEvaluator, Interval>>
    {
    private:
        const TEvaluator& _evaluator;
        Interval _argument;
    public:
        MatrixReturnValue(const TEvaluator& evaluator, Interval argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        Interval value() const;
        bool isZero(double precision = 1e-12) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template<class TEvaluator, class TArgument>
    inline MatrixReturnValue<TEvaluator, TArgument>::MatrixReturnValue(
        const TEvaluator& evaluator,
        const TArgument& argument
    ) : _evaluator(evaluator), _argument(argument) {
    }
    
    template<class TEvaluator, class TArgument>
    inline int MatrixReturnValue<TEvaluator, TArgument>::rows() const {
        return _evaluator.numDimensions();
    }
    
    template<class TEvaluator, class TArgument>
    inline int MatrixReturnValue<TEvaluator, TArgument>::cols() const {
        return _argument.cols();
    }
    
    template<class TEvaluator, class TArgument> template<class TResult>
    inline void MatrixReturnValue<TEvaluator, TArgument>::evalTo(TResult& result) const {
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
        _evaluator.evaluate(argumentMap, resultMap, cache);
    }
    
    template<class TEvaluator, class TArgument>
    inline typename TArgument::Scalar MatrixReturnValue<TEvaluator, TArgument>::value() const {
        Matrix<typename TArgument::Scalar, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluator, class TArgument>
    inline bool MatrixReturnValue<TEvaluator, TArgument>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class TEvaluator>
    inline MatrixReturnValue<TEvaluator, int>::MatrixReturnValue(
        const TEvaluator& evaluator,
        int argument
    ) : _evaluator(evaluator),
        _argument(argument) {
    }
    
    template <class TEvaluator>
    inline int MatrixReturnValue<TEvaluator, int>::rows() const {
        return _evaluator.numDimensions();
    }
    
    template <class TEvaluator>
    inline int MatrixReturnValue<TEvaluator, int>::cols() const {
        return 1;
    }
    
    template <class TEvaluator> template<class TResult>
    inline void MatrixReturnValue<TEvaluator, int>::evalTo(TResult& result) const {
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
        _evaluator.evaluate(argumentMap, resultMap, cache);
    }
    
    template <class TEvaluator>
    inline double MatrixReturnValue<TEvaluator, int>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluator>
    inline bool MatrixReturnValue<TEvaluator, int>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class TEvaluator>
    inline MatrixReturnValue<TEvaluator, double>::MatrixReturnValue(
        const TEvaluator& evaluator,
        double argument
    ) : _evaluator(evaluator),
        _argument(argument) {
    }
    
    template <class TEvaluator>
    inline int MatrixReturnValue<TEvaluator, double>::rows() const {
        return _evaluator.numDimensions();
    }
    
    template <class TEvaluator>
    inline int MatrixReturnValue<TEvaluator, double>::cols() const {
        return 1;
    }
    
    template <class TEvaluator> template<class TResult>
    inline void MatrixReturnValue<TEvaluator, double>::evalTo(TResult& result) const {
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
        _evaluator.evaluate(argumentMap, resultMap, cache);
    }
    
    template <class TEvaluator>
    inline double MatrixReturnValue<TEvaluator, double>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluator>
    inline bool MatrixReturnValue<TEvaluator, double>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class TEvaluator>
    inline MatrixReturnValue<TEvaluator, Interval>::MatrixReturnValue(
        const TEvaluator& evaluator,
        Interval argument
    ) : _evaluator(evaluator),
        _argument(argument) {
    }
    
    template <class TEvaluator>
    inline int MatrixReturnValue<TEvaluator, Interval>::rows() const {
        return _evaluator.numDimensions();
    }
    
    template <class TEvaluator>
    inline int MatrixReturnValue<TEvaluator, Interval>::cols() const {
        return 1;
    }
    
    template <class TEvaluator> template<class TResult>
    inline void MatrixReturnValue<TEvaluator, Interval>::evalTo(TResult& result) const {
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
        _evaluator.evaluate(argumentMap, resultMap, cache);
    }
    
    template <class TEvaluator>
    inline Interval MatrixReturnValue<TEvaluator, Interval>::value() const {
        Matrix<Interval, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluator>
    inline bool MatrixReturnValue<TEvaluator, Interval>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
}
