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

#ifndef OPENSOLID__GEOMETRYEVALUATION_HPP
#define OPENSOLID__GEOMETRYEVALUATION_HPP

#include <OpenSolid/Scalar/double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Evaluation/MatrixArgument.hpp>

namespace OpenSolid
{
    template<class EvaluatedType, class ArgumentType>
    class Evaluation;
}

namespace Eigen
{
    namespace internal
    {
        template <class EvaluatedType, class ArgumentType>
        struct traits<OpenSolid::Evaluation<EvaluatedType, ArgumentType>>
        {
            typedef Matrix<typename ArgumentType::Scalar, Dynamic, ArgumentType::ColsAtCompileTime>
                ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <class EvaluatedType>
        struct traits<OpenSolid::Evaluation<EvaluatedType, int>>
        {
            typedef VectorXd ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<class EvaluatedType>
        struct traits<OpenSolid::Evaluation<EvaluatedType, double>>
        {
            typedef VectorXd ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<class EvaluatedType>
        struct traits<OpenSolid::Evaluation<EvaluatedType, OpenSolid::Interval>>
        {
            typedef VectorXI ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
    }
}

namespace OpenSolid
{
    template<class EvaluatedType, class ArgumentType>
    class Evaluation : public ReturnByValue<Evaluation<EvaluatedType, ArgumentType>>
    {
    private:
        const EvaluatedType& _evaluated;
        const ArgumentType& _argument;
    public:
        Evaluation(const EvaluatedType& evaluated, const ArgumentType& argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        typename ArgumentType::Scalar value() const;
        bool isZero(double tolerance = 1e-12) const;
    };
    
    template<class EvaluatedType>
    class Evaluation<EvaluatedType, int> : public ReturnByValue<Evaluation<EvaluatedType, int>>
    {
    private:
        const EvaluatedType& _evaluated;
        double _argument;
    public:
        Evaluation(const EvaluatedType& evaluated, int argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<class EvaluatedType>
    class Evaluation<EvaluatedType, double> : public ReturnByValue<Evaluation<EvaluatedType, double>>
    {
    private:
        const EvaluatedType& _evaluated;
        double _argument;
    public:
        Evaluation(const EvaluatedType& evaluated, double argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<class EvaluatedType>
    class Evaluation<EvaluatedType, Interval> : public ReturnByValue<Evaluation<EvaluatedType, Interval>>
    {
    private:
        const EvaluatedType& _evaluated;
        Interval _argument;
    public:
        Evaluation(const EvaluatedType& evaluated, Interval argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        Interval value() const;
        bool isZero(double precision = 1e-12) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template<class EvaluatedType, class ArgumentType>
    inline Evaluation<EvaluatedType, ArgumentType>::Evaluation(
        const EvaluatedType& evaluated,
        const ArgumentType& argument
    ) : _evaluated(evaluated), _argument(argument) {}
    
    template<class EvaluatedType, class ArgumentType>
    inline int Evaluation<EvaluatedType, ArgumentType>::rows() const {return _evaluated.dimensions();}
    
    template<class EvaluatedType, class ArgumentType>
    inline int Evaluation<EvaluatedType, ArgumentType>::cols() const {return _argument.cols();}
    
    template<class EvaluatedType, class ArgumentType> template<class ResultType>
    inline void Evaluation<EvaluatedType, ArgumentType>::evalTo(ResultType& result) const {
        MatrixArgument<ArgumentType> argument(_argument);
        
        // Common typedefs
        typedef typename ResultType::Scalar Scalar;
        typedef Map<const Matrix<Scalar, Dynamic, Dynamic>, Unaligned, Stride<Dynamic, Dynamic>>
            ArgumentMapType;
            
        // Create argument map
        Stride<Dynamic, Dynamic> argument_stride(argument.outerStride(), argument.innerStride());
        ArgumentMapType argument_map(
            argument.data(),
            argument.rows(),
            argument.cols(),
            argument_stride
        );
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<Matrix<Scalar, Dynamic, Dynamic>, Unaligned, Stride<Dynamic, Dynamic>>
            ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate evaluated
        _evaluated.implementation()->evaluate(argument_map, result_map);
    }
    
    template<class EvaluatedType, class ArgumentType>
    inline typename ArgumentType::Scalar Evaluation<EvaluatedType, ArgumentType>::value() const {
        Matrix<typename ArgumentType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    template <class EvaluatedType, class ArgumentType>
    inline bool Evaluation<EvaluatedType, ArgumentType>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    template <class EvaluatedType>
    inline Evaluation<EvaluatedType, int>::Evaluation(const EvaluatedType& evaluated, int argument) :
        _evaluated(evaluated), _argument(argument) {}
    
    template <class EvaluatedType>
    inline int Evaluation<EvaluatedType, int>::rows() const {return _evaluated.dimensions();}
    
    template <class EvaluatedType>
    inline int Evaluation<EvaluatedType, int>::cols() const {return 1;}
    
    template <class EvaluatedType> template<class ResultType>
    inline void Evaluation<EvaluatedType, int>::evalTo(ResultType& result) const {
        // Create argument map
        typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argument_map(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate evaluated
        _evaluated.implementation()->evaluate(argument_map, result_map);
    }
    
    template <class EvaluatedType>
    inline double Evaluation<EvaluatedType, int>::value() const {
        Matrix<double, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    template <class EvaluatedType>
    inline bool Evaluation<EvaluatedType, int>::isZero(double precision) const {
        return eval().isZero(precision);
    }
    
    template <class EvaluatedType>
    inline Evaluation<EvaluatedType, double>::Evaluation(const EvaluatedType& evaluated, double argument) :
        _evaluated(evaluated), _argument(argument) {}
    
    template <class EvaluatedType>
    inline int Evaluation<EvaluatedType, double>::rows() const {return _evaluated.dimensions();}
    
    template <class EvaluatedType>
    inline int Evaluation<EvaluatedType, double>::cols() const {return 1;}
    
    template <class EvaluatedType> template<class ResultType>
    inline void Evaluation<EvaluatedType, double>::evalTo(ResultType& result) const {
        // Create argument map
        typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argument_map(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate evaluated
        _evaluated.implementation()->evaluate(argument_map, result_map);
    }
    
    template <class EvaluatedType>
    inline double Evaluation<EvaluatedType, double>::value() const {
        Matrix<double, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    template <class EvaluatedType>
    inline bool Evaluation<EvaluatedType, double>::isZero(double precision) const {
        return eval().isZero(precision);
    }
    
    template <class EvaluatedType>
    inline Evaluation<EvaluatedType, Interval>::Evaluation(const EvaluatedType& evaluated, Interval argument) :
        _evaluated(evaluated), _argument(argument) {}
    
    template <class EvaluatedType>
    inline int Evaluation<EvaluatedType, Interval>::rows() const {return _evaluated.dimensions();}
    
    template <class EvaluatedType>
    inline int Evaluation<EvaluatedType, Interval>::cols() const {return 1;}
    
    template <class EvaluatedType> template<class ResultType>
    inline void Evaluation<EvaluatedType, Interval>::evalTo(ResultType& result) const {
        // Create argument map
        typedef Map<const MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argument_map(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate evaluated
        _evaluated.implementation()->evaluate(argument_map, result_map);
    }
    
    template <class EvaluatedType>
    inline Interval Evaluation<EvaluatedType, Interval>::value() const {
        Matrix<Interval, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    template <class EvaluatedType>
    inline bool Evaluation<EvaluatedType, Interval>::isZero(double precision) const {
        return eval().isZero(precision);
    }
}

#endif
