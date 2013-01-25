/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template<class TEvaluated, class TArgument>
    class Evaluation;
}

namespace Eigen
{
    namespace internal
    {
        template <class TEvaluated, class TArgument>
        struct traits<opensolid::Evaluation<TEvaluated, TArgument>>
        {
            typedef Matrix<typename TArgument::Scalar, Dynamic, TArgument::ColsAtCompileTime>
                ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <class TEvaluated>
        struct traits<opensolid::Evaluation<TEvaluated, int>>
        {
            typedef VectorXd ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<class TEvaluated>
        struct traits<opensolid::Evaluation<TEvaluated, double>>
        {
            typedef VectorXd ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<class TEvaluated>
        struct traits<opensolid::Evaluation<TEvaluated, opensolid::Interval>>
        {
            typedef VectorXI ReturnType;

            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
    }
}

namespace opensolid
{
    template<class TEvaluated, class TArgument>
    class Evaluation : public ReturnByValue<Evaluation<TEvaluated, TArgument>>
    {
    private:
        const TEvaluated& _evaluated;
        const TArgument& _argument;
    public:
        Evaluation(const TEvaluated& evaluated, const TArgument& argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        typename TArgument::Scalar value() const;
        bool isZero(double tolerance = 1e-12) const;
    };
    
    template<class TEvaluated>
    class Evaluation<TEvaluated, int> : public ReturnByValue<Evaluation<TEvaluated, int>>
    {
    private:
        const TEvaluated& _evaluated;
        double _argument;
    public:
        Evaluation(const TEvaluated& evaluated, int argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<class TEvaluated>
    class Evaluation<TEvaluated, double> : public ReturnByValue<Evaluation<TEvaluated, double>>
    {
    private:
        const TEvaluated& _evaluated;
        double _argument;
    public:
        Evaluation(const TEvaluated& evaluated, double argument);
        
        int rows() const;
        int cols() const;
        
        template<class TResult>
        void evalTo(TResult& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<class TEvaluated>
    class Evaluation<TEvaluated, Interval> : public ReturnByValue<Evaluation<TEvaluated, Interval>>
    {
    private:
        const TEvaluated& _evaluated;
        Interval _argument;
    public:
        Evaluation(const TEvaluated& evaluated, Interval argument);
        
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
    namespace
    {
        template<class Type>
        class MatrixArgument
        {
        private:
            typename boost::mpl::if_c<
                Eigen::internal::has_direct_access<Type>::ret,
                const Type&,
                typename Type::PlainObject
            >::type _argument;
        public:
            MatrixArgument(const Type& argument);
        
            const typename Type::Scalar* data() const;
            int rows() const;
            int cols() const;
            int outerStride() const;
            int innerStride() const;
        };

        template<class Type>
        inline MatrixArgument<Type>::MatrixArgument(const Type& argument) : _argument(argument) {
        }
    
        template<class Type>
        inline const typename Type::Scalar* MatrixArgument<Type>::data() const {
            return _argument.data();
        }
    
        template<class Type>
        inline int MatrixArgument<Type>::rows() const {
            return _argument.rows();
        }
    
        template<class Type>
        inline int MatrixArgument<Type>::cols() const {
            return _argument.cols();
        }
    
        template<class Type>
        inline int MatrixArgument<Type>::outerStride() const {
            return (Type::Flags & RowMajorBit) ? _argument.innerStride() : _argument.outerStride();
        }
    
        template<class Type>
        inline int MatrixArgument<Type>::innerStride() const {
            return (Type::Flags & RowMajorBit) ? _argument.outerStride() : _argument.innerStride();
        }
    }

    template<class TEvaluated, class TArgument>
    inline Evaluation<TEvaluated, TArgument>::Evaluation(
        const TEvaluated& evaluated,
        const TArgument& argument
    ) : _evaluated(evaluated), _argument(argument) {
    }
    
    template<class TEvaluated, class TArgument>
    inline int Evaluation<TEvaluated, TArgument>::rows() const {
        return _evaluated.numDimensions();
    }
    
    template<class TEvaluated, class TArgument>
    inline int Evaluation<TEvaluated, TArgument>::cols() const {
        return _argument.cols();
    }
    
    template<class TEvaluated, class TArgument> template<class TResult>
    inline void Evaluation<TEvaluated, TArgument>::evalTo(TResult& result) const {
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
        
        // Evaluate evaluated
        _evaluated.evaluate(argumentMap, resultMap);
    }
    
    template<class TEvaluated, class TArgument>
    inline typename TArgument::Scalar Evaluation<TEvaluated, TArgument>::value() const {
        Matrix<typename TArgument::Scalar, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluated, class TArgument>
    inline bool Evaluation<TEvaluated, TArgument>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class TEvaluated>
    inline Evaluation<TEvaluated, int>::Evaluation(const TEvaluated& evaluated, int argument) :
        _evaluated(evaluated), _argument(argument) {
    }
    
    template <class TEvaluated>
    inline int Evaluation<TEvaluated, int>::rows() const {
        return _evaluated.numDimensions();
    }
    
    template <class TEvaluated>
    inline int Evaluation<TEvaluated, int>::cols() const {
        return 1;
    }
    
    template <class TEvaluated> template<class TResult>
    inline void Evaluation<TEvaluated, int>::evalTo(TResult& result) const {
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
        
        // Evaluate evaluated
        _evaluated.evaluate(argumentMap, resultMap);
    }
    
    template <class TEvaluated>
    inline double Evaluation<TEvaluated, int>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluated>
    inline bool Evaluation<TEvaluated, int>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class TEvaluated>
    inline Evaluation<TEvaluated, double>::Evaluation(
        const TEvaluated& evaluated,
        double argument
    ) : _evaluated(evaluated), _argument(argument) {
    }
    
    template <class TEvaluated>
    inline int Evaluation<TEvaluated, double>::rows() const {
        return _evaluated.numDimensions();
    }
    
    template <class TEvaluated>
    inline int Evaluation<TEvaluated, double>::cols() const {
        return 1;
    }
    
    template <class TEvaluated> template<class TResult>
    inline void Evaluation<TEvaluated, double>::evalTo(TResult& result) const {
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
        
        // Evaluate evaluated
        _evaluated.evaluate(argumentMap, resultMap);
    }
    
    template <class TEvaluated>
    inline double Evaluation<TEvaluated, double>::value() const {
        Matrix<double, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluated>
    inline bool Evaluation<TEvaluated, double>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class TEvaluated>
    inline Evaluation<TEvaluated, Interval>::Evaluation(
        const TEvaluated& evaluated,
        Interval argument
    ) : _evaluated(evaluated), _argument(argument) {
    }
    
    template <class TEvaluated>
    inline int Evaluation<TEvaluated, Interval>::rows() const {
        return _evaluated.numDimensions();
    }
    
    template <class TEvaluated>
    inline int Evaluation<TEvaluated, Interval>::cols() const {
        return 1;
    }
    
    template <class TEvaluated> template<class TResult>
    inline void Evaluation<TEvaluated, Interval>::evalTo(TResult& result) const {
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
        
        // Evaluate evaluated
        _evaluated.evaluate(argumentMap, resultMap);
    }
    
    template <class TEvaluated>
    inline Interval Evaluation<TEvaluated, Interval>::value() const {
        Matrix<Interval, 1, 1> result;
        this->evalTo(result);
        return result.value();
    }
    
    template <class TEvaluated>
    inline bool Evaluation<TEvaluated, Interval>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
}
