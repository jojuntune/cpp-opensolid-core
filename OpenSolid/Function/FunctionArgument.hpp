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

#ifndef OPENSOLID__FUNCTIONARGUMENT_HPP
#define OPENSOLID__FUNCTIONARGUMENT_HPP

#include <boost/mpl/if.hpp>

#include <OpenSolid/Value/Eigen.hpp>
#include <OpenSolid/Value/Interval.hpp>

namespace OpenSolid
{
    template<class Type>
    class FunctionArgument
    {
    private:
        typename boost::mpl::if_c<
            Eigen::internal::has_direct_access<Type>::ret,
            const Type&,
            typename Type::PlainObject
        >::type _argument;
    public:
        FunctionArgument(const Type& argument);
        
        const typename Type::Scalar* data() const;
        int rows() const;
        int cols() const;
        int outerStride() const;
        int innerStride() const;
    };
    
    template<>
    class FunctionArgument<int>
    {
    private:
        double _value;
    public:
        FunctionArgument(int argument);
        
        const double* data() const;
        int rows() const;
        int cols() const;
        int outerStride() const;
        int innerStride() const;
    };
    
    template<>
    class FunctionArgument<double>
    {
    private:
        double _value;
    public:
        FunctionArgument(double argument);
        
        const double* data() const;
        int rows() const;
        int cols() const;
        int outerStride() const;
        int innerStride() const;
    };
    
    template<>
    class FunctionArgument<Interval>
    {
    private:
        const Interval& _value;
    public:
        FunctionArgument(const Interval& argument);
        
        const Interval* data() const;
        int rows() const;
        int cols() const;
        int outerStride() const;
        int innerStride() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template<class Type>
    inline FunctionArgument<Type>::FunctionArgument(const Type& argument) : _argument(argument) {}
    
    template<class Type>
    inline const typename Type::Scalar* FunctionArgument<Type>::data() const {
        return _argument.data();
    }
    
    template<class Type>
    inline int FunctionArgument<Type>::rows() const {return _argument.rows();}
    
    template<class Type>
    inline int FunctionArgument<Type>::cols() const {return _argument.cols();}
    
    template<class Type>
    inline int FunctionArgument<Type>::outerStride() const {
        return (Type::Flags & RowMajorBit) ? _argument.innerStride() : _argument.outerStride();
    }
    
    template<class Type>
    inline int FunctionArgument<Type>::innerStride() const {
        return (Type::Flags & RowMajorBit) ? _argument.outerStride() : _argument.innerStride();
    }
    
    inline FunctionArgument<int>::FunctionArgument(int argument) : _value(argument) {}
    
    inline const double* FunctionArgument<int>::data() const {return &_value;}
    
    inline int FunctionArgument<int>::rows() const {return 1;}
    
    inline int FunctionArgument<int>::cols() const {return 1;}
    
    inline int FunctionArgument<int>::outerStride() const {return 1;}
    
    inline int FunctionArgument<int>::innerStride() const {return 1;}
    
    inline FunctionArgument<double>::FunctionArgument(double argument) : _value(argument) {}
    
    inline const double* FunctionArgument<double>::data() const {return &_value;}
    
    inline int FunctionArgument<double>::rows() const {return 1;}
    
    inline int FunctionArgument<double>::cols() const {return 1;}
    
    inline int FunctionArgument<double>::outerStride() const {return 1;}
    
    inline int FunctionArgument<double>::innerStride() const {return 1;}
    
    inline FunctionArgument<Interval>::FunctionArgument(const Interval& argument) :
        _value(argument) {}
    
    inline const Interval* FunctionArgument<Interval>::data() const {return &_value;}
    
    inline int FunctionArgument<Interval>::rows() const {return 1;}
    
    inline int FunctionArgument<Interval>::cols() const {return 1;}
    
    inline int FunctionArgument<Interval>::outerStride() const {return 1;}
    
    inline int FunctionArgument<Interval>::innerStride() const {return 1;}
}

#endif
