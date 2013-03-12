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

#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
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
}

////////// Implementation //////////

namespace opensolid
{
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
