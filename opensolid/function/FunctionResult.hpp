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

namespace opensolid
{
    template<class ArgumentType>
    class FunctionResult;
}

namespace Eigen
{
    template<class ArgumentType>
    struct ei_traits<opensolid::FunctionResult<ArgumentType> >
    {
        typedef Matrix<typename ArgumentType::Scalar, Dynamic, ArgumentType::ColsAtCompileTime> ReturnType;
        static const int Flags = (ei_traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
    };
    
    template<>
    struct ei_traits<opensolid::FunctionResult<int> >
    {
        typedef VectorXd ReturnType;
        static const int Flags = (ei_traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
    };
    
    template<>
    struct ei_traits<opensolid::FunctionResult<double> >
    {
        typedef VectorXd ReturnType;
        static const int Flags = (ei_traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
    };
    
    template<>
    struct ei_traits<opensolid::FunctionResult<Interval> >
    {
        typedef VectorXI ReturnType;
        static const int Flags = (ei_traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
    };
}

namespace opensolid
{    
    template<class ArgumentType>
    class FunctionResult : public ReturnByValue<FunctionResult<ArgumentType> >
    {
    private:
        const Function& _function;
        FunctionArgument<ArgumentType> _argument;
    public:
        FunctionResult(const Function& function, const ArgumentType& argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
    };
}

////////// Implementation //////////

namespace opensolid
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
        // Common typedefs
        typedef typename ResultType::Scalar Scalar;
        typedef Map<Matrix<Scalar, Dynamic, Dynamic>, Unaligned, Stride<Dynamic, Dynamic> > MapType;
        // Create argument map
        Stride<Dynamic, Dynamic> argument_stride(_argument.outerStride(), _argument.innerStride());
        MapType argument_map(_argument.data(), _argument.rows(), _argument.cols(), argument_stride);
        // Create result map
        int result_outer_stride = (ResultType::Flags & RowMajorBit) ? result.innerStride() : result.outerStride();
        int result_inner_stride = (ResultType::Flags & RowMajorBit) ? result.outerStride() : result.innerStride();
        Stride<Dynamic, Dynamic> result_stride(result_outer_stride, result_inner_stride);
        MapType result_map(result.data(), result.rows(), result.cols(), result_stride);
        // Evaluate function
        _function.implementation()->evaluate(argument_map, result_map);
    }
}

#endif
