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

#include <OpenSolid/Core/Scalar/double.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Function/FunctionArgument.hpp>

namespace OpenSolid
{
    template<class ArgumentType>
    class GeometryEvaluation;
}

namespace Eigen
{
    namespace internal
    {
        template <class ArgumentType>
        struct traits<OpenSolid::GeometryEvaluation<ArgumentType>>
        {
            typedef Matrix<typename ArgumentType::Scalar, Dynamic, ArgumentType::ColsAtCompileTime>
                ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template <>
        struct traits<OpenSolid::GeometryEvaluation<int>>
        {
            typedef VectorXd ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<OpenSolid::GeometryEvaluation<double>>
        {
            typedef VectorXd ReturnType;
            static const int Flags =
                (traits<ReturnType>::Flags | EvalBeforeNestingBit) & ~DirectAccessBit;
        };
        
        template<>
        struct traits<OpenSolid::GeometryEvaluation<OpenSolid::Interval>>
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
    class GeometryEvaluation : public ReturnByValue<GeometryEvaluation<ArgumentType>>
    {
    private:
        const Geometry& _geometry;
        const ArgumentType& _argument;
    public:
        GeometryEvaluation(const Geometry& geometry, const ArgumentType& argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        typename ArgumentType::Scalar value() const;
        bool isZero(double tolerance = 1e-12) const;
    };
    
    template<>
    class GeometryEvaluation<int> : public ReturnByValue<GeometryEvaluation<int>>
    {
    private:
        const Geometry& _geometry;
        double _argument;
    public:
        GeometryEvaluation(const Geometry& geometry, int argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<>
    class GeometryEvaluation<double> : public ReturnByValue<GeometryEvaluation<double>>
    {
    private:
        const Geometry& _geometry;
        double _argument;
    public:
        GeometryEvaluation(const Geometry& geometry, double argument);
        
        int rows() const;
        int cols() const;
        
        template<class ResultType>
        void evalTo(ResultType& result) const;
        
        double value() const;
        bool isZero(double precision = 1e-12) const;
    };
    
    template<>
    class GeometryEvaluation<Interval> : public ReturnByValue<GeometryEvaluation<Interval>>
    {
    private:
        const Geometry& _geometry;
        Interval _argument;
    public:
        GeometryEvaluation(const Geometry& geometry, Interval argument);
        
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
    template<class ArgumentType>
    inline GeometryEvaluation<ArgumentType>::GeometryEvaluation(
        const Geometry& geometry,
        const ArgumentType& argument
    ) : _geometry(geometry), _argument(argument) {}
    
    template<class ArgumentType>
    inline int GeometryEvaluation<ArgumentType>::rows() const {return _geometry.dimensions();}
    
    template<class ArgumentType>
    inline int GeometryEvaluation<ArgumentType>::cols() const {return _argument.cols();}
    
    template<class ArgumentType> template<class ResultType>
    inline void GeometryEvaluation<ArgumentType>::evalTo(ResultType& result) const {
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
        
        // Evaluate geometry
        _geometry.implementation()->evaluate(argument_map, result_map);
    }
    
    template<class ArgumentType>
    inline typename ArgumentType::Scalar GeometryEvaluation<ArgumentType>::value() const {
        Matrix<typename ArgumentType::Scalar, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    template <class ArgumentType>
    inline bool GeometryEvaluation<ArgumentType>::isZero(double precision) const {
        return this->eval().isZero(precision);
    }
    
    inline GeometryEvaluation<int>::GeometryEvaluation(const Geometry& geometry, int argument) :
        _geometry(geometry), _argument(argument) {}
    
    inline int GeometryEvaluation<int>::rows() const {return _geometry.dimensions();}
    
    inline int GeometryEvaluation<int>::cols() const {return 1;}
    
    template<class ResultType>
    inline void GeometryEvaluation<int>::evalTo(ResultType& result) const {
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
        
        // Evaluate geometry
        _geometry.implementation()->evaluate(argument_map, result_map);
    }
    
    inline double GeometryEvaluation<int>::value() const {
        Matrix<double, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    inline bool GeometryEvaluation<int>::isZero(double precision) const {
        return eval().isZero(precision);
    }
    
    inline GeometryEvaluation<double>::GeometryEvaluation(const Geometry& geometry, double argument) :
        _geometry(geometry), _argument(argument) {}
    
    inline int GeometryEvaluation<double>::rows() const {return _geometry.dimensions();}
    
    inline int GeometryEvaluation<double>::cols() const {return 1;}
    
    template<class ResultType>
    inline void GeometryEvaluation<double>::evalTo(ResultType& result) const {
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
        
        // Evaluate geometry
        _geometry.implementation()->evaluate(argument_map, result_map);
    }
    
    inline double GeometryEvaluation<double>::value() const {
        Matrix<double, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    inline bool GeometryEvaluation<double>::isZero(double precision) const {
        return eval().isZero(precision);
    }
    
    inline GeometryEvaluation<Interval>::GeometryEvaluation(const Geometry& geometry, Interval argument) :
        _geometry(geometry), _argument(argument) {}
    
    inline int GeometryEvaluation<Interval>::rows() const {return _geometry.dimensions();}
    
    inline int GeometryEvaluation<Interval>::cols() const {return 1;}
    
    template<class ResultType>
    inline void GeometryEvaluation<Interval>::evalTo(ResultType& result) const {
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
        
        // Evaluate geometry
        _geometry.implementation()->evaluate(argument_map, result_map);
    }
    
    inline Interval GeometryEvaluation<Interval>::value() const {
        Matrix<Interval, 1, 1> result;
        evalTo(result);
        return result.value();
    }
    
    inline bool GeometryEvaluation<Interval>::isZero(double precision) const {
        return eval().isZero(precision);
    }
}

#endif
