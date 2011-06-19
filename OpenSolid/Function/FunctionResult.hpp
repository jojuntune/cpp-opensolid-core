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

#ifndef OPENSOLID__FUNCTIONRESULT_HPP
#define OPENSOLID__FUNCTIONRESULT_HPP

#include "Function.hpp"
#include "FunctionArgument.hpp"

namespace OpenSolid
{
    template<class ArgumentType>
    class FunctionResult;
}

namespace Eigen
{
    namespace internal
    {
        template <class ArgumentType>
        struct traits<OpenSolid::FunctionResult<ArgumentType>>
        {
            typedef Matrix<typename ArgumentType::Scalar, Dynamic, ArgumentType::ColsAtCompileTime>
                ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <>
        struct traits<OpenSolid::FunctionResult<int>>
        {
            typedef VectorXD ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<OpenSolid::FunctionResult<double>>
        {
            typedef VectorXD ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<OpenSolid::FunctionResult<OpenSolid::Double>>
        {
            typedef VectorXD ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<OpenSolid::FunctionResult<OpenSolid::Interval>>
        {
            typedef VectorXI ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
    }
}

namespace OpenSolid
{
    template<class ArgumentType>
    class FunctionResult : public ReturnByValue<FunctionResult<ArgumentType>>
    {
    private:
        const Function& _function;
        const ArgumentType& _argument;
    public:
        FunctionResult(const Function& function, const ArgumentType& argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
    };
    
    template<>
    class FunctionResult<int> : public ReturnByValue<FunctionResult<int>>
    {
    private:
        const Function& _function;
        Double _argument;
    public:
        FunctionResult(const Function& function, int argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
    };
    
    template<>
    class FunctionResult<double> : public ReturnByValue<FunctionResult<double>>
    {
    private:
        const Function& _function;
        Double _argument;
    public:
        FunctionResult(const Function& function, double argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
    };
    
    template<>
    class FunctionResult<Double> : public ReturnByValue<FunctionResult<Double>>
    {
    private:
        const Function& _function;
        Double _argument;
    public:
        FunctionResult(const Function& function, Double argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
    };
    
    template<>
    class FunctionResult<Interval> : public ReturnByValue<FunctionResult<Interval>>
    {
    private:
        const Function& _function;
        Interval _argument;
    public:
        FunctionResult(const Function& function, Interval argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template<class ArgumentType>
    inline FunctionResult<ArgumentType>::FunctionResult(
        const Function& function,
        const ArgumentType& argument
    ) : _function(function), _argument(argument) {}
    
    template<class ArgumentType>
    inline int FunctionResult<ArgumentType>::rows() const {return _function.dimensions();}
    
    template<class ArgumentType>
    inline int FunctionResult<ArgumentType>::cols() const {return _argument.cols();}
    
    template<class ArgumentType> template<class ResultType>
    inline void FunctionResult<ArgumentType>::evalTo(ResultType& result) const {
        FunctionArgument<ArgumentType> argument(_argument);
        
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
        
        // Evaluate function
        _function.implementation()->evaluate(argument_map, result_map);
    }
    
    inline FunctionResult<int>::FunctionResult(const Function& function, int argument) :
        _function(function), _argument(argument) {}
    
    inline int FunctionResult<int>::rows() const {return _function.dimensions();}
    
    inline int FunctionResult<int>::cols() const {return 1;}
    
    template<class ResultType>
    inline void FunctionResult<int>::evalTo(ResultType& result) const {
        // Create argument map
        typedef Map<const MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argument_map(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate function
        _function.implementation()->evaluate(argument_map, result_map);
    }
    
    inline FunctionResult<double>::FunctionResult(const Function& function, double argument) :
        _function(function), _argument(argument) {}
    
    inline int FunctionResult<double>::rows() const {return _function.dimensions();}
    
    inline int FunctionResult<double>::cols() const {return 1;}
    
    template<class ResultType>
    inline void FunctionResult<double>::evalTo(ResultType& result) const {
        // Create argument map
        typedef Map<const MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argument_map(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate function
        _function.implementation()->evaluate(argument_map, result_map);
    }
    
    inline FunctionResult<Double>::FunctionResult(const Function& function, Double argument) :
        _function(function), _argument(argument) {}
    
    inline int FunctionResult<Double>::rows() const {return _function.dimensions();}
    
    inline int FunctionResult<Double>::cols() const {return 1;}
    
    template<class ResultType>
    inline void FunctionResult<Double>::evalTo(ResultType& result) const {
        // Create argument map
        typedef Map<const MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> ArgumentMapType;
        ArgumentMapType argument_map(&_argument, 1, 1, Stride<Dynamic, Dynamic>(0, 0));
        
        // Create result map
        int result_outer_stride =
            (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride =
            (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        typedef Map<MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> ResultMapType;
        ResultMapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        
        // Evaluate function
        _function.implementation()->evaluate(argument_map, result_map);
    }
    
    inline FunctionResult<Interval>::FunctionResult(const Function& function, Interval argument) :
        _function(function), _argument(argument) {}
    
    inline int FunctionResult<Interval>::rows() const {return _function.dimensions();}
    
    inline int FunctionResult<Interval>::cols() const {return 1;}
    
    template<class ResultType>
    inline void FunctionResult<Interval>::evalTo(ResultType& result) const {
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
        
        // Evaluate function
        _function.implementation()->evaluate(argument_map, result_map);
    }
}

#endif
