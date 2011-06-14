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

#ifndef OPENSOLID__SCALAR_HPP
#define OPENSOLID__SCALAR_HPP

#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    template <class ScalarType>
    class ScalarValue;
}

namespace Eigen
{
    namespace internal
    {
        template <class ScalarType>
        struct Traits<ScalarValue<ScalarType>>
        {
            typedef ScalarType Scalar;
            typedef Dense StorageKind;
            typedef DenseIndex Index;
            typedef ArrayXpr XprKind;
            enum {
                RowsAtCompileTime = 1,
                ColsAtCompileTime = 1,
                MaxRowsAtCompileTime = 1,
                MaxColsAtCompileTime = 1,
                Flags = LinearAccessBit | LvalueBit | DirectAccessBit | NestByRefBit,
                CoeffReadCost = NumTraits<ScalarType>::ReadCost,
                InnerStrideAtCompileTime = 1,
                OuterStrideAtCompileTime = 1
            };
        };
    }
}

namespace OpenSolid
{
    template <class ScalarType>
    class ScalarValue : public ArrayBase<ScalarValue<ScalarType>>
    {
    private:
        ScalarType _coeff;
    public:
        typedef ArrayBase<ScalarValue<ScalarType>> Base;
        typedef ScalarType Scalar;
        typedef Dense StorageKind;
        typedef DenseIndex Index;
        typedef ArrayXpr XprKind;
        
        ScalarValue(ScalarType coeff);
        
        ScalarType coeff(Index index) const;
        ScalarType coeff(Index row, Index col) const;
        ScalarType& coeffRef(Index index);
        ScalarType& coeffRef(Index row, Index col);
    };
}

////////// Implementation //////////

template <class ScalarType>
inline ScalarValue<ScalarType>::ScalarValue(ScalarType coeff) : _coeff(coeff) {}
        
template <class ScalarType>
inline ScalarType ScalarValue<ScalarType>::coeff(Index index) const {
    
}

template <class ScalarType>
inline ScalarType ScalarValue<ScalarType>::coeff(Index row, Index col) const {
    
}

template <class ScalarType>
inline ScalarType& ScalarValue<ScalarType>::coeffRef(Index index) {
    
}

template <class ScalarType>
inline ScalarType& ScalarValue<ScalarType>::coeffRef(Index row, Index col) {
    
}

#endif
