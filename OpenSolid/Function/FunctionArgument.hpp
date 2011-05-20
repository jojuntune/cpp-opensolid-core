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

#include <OpenSolid/Value/Interval.hpp>
#include <OpenSolid/Value/Matrix.hpp>

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
}

#endif
