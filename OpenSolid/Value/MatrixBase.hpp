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

#ifndef OPENSOLID__MATRIXBASE_HPP
#define OPENSOLID__MATRIXBASE_HPP

#include <type_traits>

#include <OpenSolid/Value/ValueBase.hpp>

namespace OpenSolid
{
    template <class DerivedType, class ScalarType>
    class MatrixBase : public ValueBase<DerivedType, ScalarType>
    {
    private:
        static ScalarType* allocate(Index size);
    protected:
        Eigen::Map<Eigen::Matrix<ScalarType, Eigen::Dynamic, Eigen::Dynamic>, Eigen::Aligned> _map;
    public:
        MatrixBase(Index rows, Index cols);
        
        ~MatrixBase();
        
        ScalarType* data();
        const ScalarType* data() const;
        
        Index rows() const;
        Index cols() const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Value/Memory.hpp>

namespace OpenSolid
{
    template <class DerivedType, class ScalarType>
    inline ScalarType* MatrixBase<DerivedType, ScalarType>::allocate(Index size) {
        return static_cast<ScalarType*>(Memory::allocate(std::size_t(sizeof(ScalarType) * size)));
    }
    
    template <class DerivedType, class ScalarType>
    MatrixBase<DerivedType, ScalarType>::MatrixBase(Index rows, Index cols) :
        _map(allocate(rows * cols), rows, cols) {}
    
    template <class DerivedType, class ScalarType>
    MatrixBase<DerivedType, ScalarType>::~MatrixBase() {
        if (data()) {Memory::free(data(), sizeof(ScalarType) * rows() * cols());}
    }
    
    template <class DerivedType, class ScalarType>
    ScalarType* MatrixBase<DerivedType, ScalarType>::data() {return _map.data();}
    
    template <class DerivedType, class ScalarType>
    const ScalarType* MatrixBase<DerivedType, ScalarType>::data() const {return _map.data();}
    
    template <class DerivedType, class ScalarType>
    Index MatrixBase<DerivedType, ScalarType>::rows() const {return _map.rows();}
    
    template <class DerivedType, class ScalarType>
    Index MatrixBase<DerivedType, ScalarType>::cols() const {return _map.cols();}
}

#endif
