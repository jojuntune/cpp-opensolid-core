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

#include <opensolid/core/matrix/Matrix.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace Eigen
{
    template <class MatrixType>
    class MatrixIterator;
    
    template <class MatrixType>
    class ConstMatrixIterator : 
        public boost::iterator_facade<
            ConstMatrixIterator<MatrixType>,
            typename MatrixType::Scalar,
            std::random_access_iterator_tag,
            typename MatrixType::Scalar,
            typename MatrixType::Index
        >
    {
    private:
        typedef typename MatrixType::Index Index;
        
        friend class boost::iterator_core_access;
        friend class MatrixIterator<MatrixType>;
        
        const MatrixType* _matrix;
        Index _index;
        
        typename MatrixType::Scalar dereference() const;
        
        bool equal(const MatrixIterator<MatrixType>& other) const;
        bool equal(const ConstMatrixIterator<MatrixType>& other) const;
        
        Index distance_to(const MatrixIterator<MatrixType>& other) const;
        Index distance_to(const ConstMatrixIterator<MatrixType>& other) const;
        
        void increment();
        void decrement();
        void advance(Index argument);
    public:
        ConstMatrixIterator(const MatrixType& matrix, Index index);
        ConstMatrixIterator(const ConstMatrixIterator<MatrixType>& other);
        ConstMatrixIterator(const MatrixIterator<MatrixType>& other);
    };
    
    template <class MatrixType>
    class MatrixIterator : 
        public boost::iterator_facade<
            MatrixIterator<MatrixType>,
            typename MatrixType::Scalar,
            std::random_access_iterator_tag,
            typename MatrixType::Scalar&,
            typename MatrixType::Index
        >
    {
    private:
        typedef typename MatrixType::Index Index;
        
        friend class boost::iterator_core_access;
        friend class ConstMatrixIterator<MatrixType>;
        
        MatrixType* _matrix;
        Index _index;
        
        typename MatrixType::Scalar& dereference() const;
        
        bool equal(const MatrixIterator<MatrixType>& other) const;
        bool equal(const ConstMatrixIterator<MatrixType>& other) const;
        
        Index distance_to(const MatrixIterator<MatrixType>& other) const;
        Index distance_to(const ConstMatrixIterator<MatrixType>& other) const;
        
        void increment();
        void decrement();
        void advance(Index argument);
    public:
        MatrixIterator(MatrixType& matrix, Index index);
        MatrixIterator(const MatrixIterator<MatrixType>& other);
    };
    
    template <class DerivedType, class MatrixType, class BlockType>
    class MatrixBlockIterator :
        public boost::iterator_facade<
            DerivedType,
            BlockType,
            std::random_access_iterator_tag,
            BlockType,
            typename MatrixType::Index
        >
    {
    protected:
        typedef typename MatrixType::Index Index;
        
        template <class OtherDerived, class OtherMatrixType, class OtherBlockType>
        friend class MatrixBlockIterator;
        
        friend class boost::iterator_core_access;
        
        MatrixType* _matrix;
        Index _index;
        
        BlockType dereference() const;
        
        template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
        bool equal(
            const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
        ) const;
        
        template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
        Index distance_to(
            const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
        ) const;
        
        void increment();
        void decrement();
        void advance(Index argument);

        MatrixBlockIterator(MatrixType& matrix, Index index);
        
        template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
        MatrixBlockIterator(
            const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
        );
    };

    template <class MatrixType>
    class MatrixRowIterator;

    template <class MatrixType>
    class ConstMatrixRowIterator :
        public MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >
    {
    public:
        typedef typename MatrixType::Index Index;
        
        ConstMatrixRowIterator(const MatrixType& matrix, Index index);
        ConstMatrixRowIterator(const ConstMatrixRowIterator<MatrixType>& other);
        ConstMatrixRowIterator(const MatrixRowIterator<MatrixType>& other);
        
        static typename MatrixType::ConstRowXpr block(const MatrixType& matrix, Index index);
    };
    
    template <class MatrixType>
    class MatrixRowIterator :
        public MatrixBlockIterator<
            MatrixRowIterator<MatrixType>,
            MatrixType,
            typename MatrixType::RowXpr
        >
    {
    public:
        typedef typename MatrixType::Index Index;
        
        MatrixRowIterator(MatrixType& matrix, Index index);
        MatrixRowIterator(const MatrixRowIterator<MatrixType>& other);
        
        static typename MatrixType::RowXpr block(MatrixType& matrix, Index index);
    };

    template <class MatrixType>
    class MatrixColIterator;
    
    template <class MatrixType>
    class ConstMatrixColIterator :
        public MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >
    {
    public:
        typedef typename MatrixType::Index Index;
        
        ConstMatrixColIterator(const MatrixType& matrix, Index index);
        ConstMatrixColIterator(const ConstMatrixColIterator<MatrixType>& other);
        ConstMatrixColIterator(const MatrixColIterator<MatrixType>& other);
        
        static typename MatrixType::ConstColXpr block(const MatrixType& matrix, Index index);
    };
    
    template <class MatrixType>
    class MatrixColIterator :
        public MatrixBlockIterator<
            MatrixColIterator<MatrixType>,
            MatrixType,
            typename MatrixType::ColXpr
        >
    {
    public:
        typedef typename MatrixType::Index Index;
        
        MatrixColIterator(MatrixType& matrix, Index index);
        MatrixColIterator(const MatrixColIterator<MatrixType>& other);
        
        static typename MatrixType::ColXpr block(MatrixType& matrix, Index index);
    };
    
    template <class DerivedType>
    ConstMatrixIterator<DerivedType> begin(const DenseBase<DerivedType>& argument);
    
    template <class DerivedType>
    ConstMatrixIterator<DerivedType> end(const DenseBase<DerivedType>& argument);
    
    template <class DerivedType>
    MatrixIterator<DerivedType> begin(DenseBase<DerivedType>& argument);
    
    template <class DerivedType>
    MatrixIterator<DerivedType> end(DenseBase<DerivedType>& argument);
    
    template <class ExpressionType>
    ConstMatrixRowIterator<ExpressionType> begin(
        VectorwiseOp<const ExpressionType, Horizontal> argument
    );
    
    template <class ExpressionType>
    ConstMatrixRowIterator<ExpressionType> end(
        VectorwiseOp<const ExpressionType, Horizontal> argument
    );
    
    template <class ExpressionType>
    MatrixRowIterator<ExpressionType> begin(VectorwiseOp<ExpressionType, Horizontal> argument);
    
    template <class ExpressionType>
    MatrixRowIterator<ExpressionType> end(VectorwiseOp<ExpressionType, Horizontal> argument);
    
    template <class ExpressionType>
    ConstMatrixColIterator<ExpressionType> begin(
        VectorwiseOp<const ExpressionType, Vertical> argument
    );
    
    template <class ExpressionType>
    ConstMatrixColIterator<ExpressionType> end(
        VectorwiseOp<const ExpressionType, Vertical> argument
    );
    
    template <class ExpressionType>
    MatrixColIterator<ExpressionType> begin(VectorwiseOp<ExpressionType, Vertical> argument);
    
    template <class ExpressionType>
    MatrixColIterator<ExpressionType> end(VectorwiseOp<ExpressionType, Vertical> argument);
}

////////// Implementation //////////

namespace Eigen
{
    template <class MatrixType>
    inline typename MatrixType::Scalar ConstMatrixIterator<MatrixType>::dereference() const {
        return (*_matrix)(_index);
    }
    
    template <class MatrixType>
    inline bool ConstMatrixIterator<MatrixType>::equal(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline bool ConstMatrixIterator<MatrixType>::equal(
        const MatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline typename MatrixType::Index ConstMatrixIterator<MatrixType>::distance_to(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline typename MatrixType::Index ConstMatrixIterator<MatrixType>::distance_to(
        const MatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline void ConstMatrixIterator<MatrixType>::increment() {++_index;}
    
    template <class MatrixType>
    inline void ConstMatrixIterator<MatrixType>::decrement() {--_index;}
    
    template <class MatrixType>
    inline void ConstMatrixIterator<MatrixType>::advance(typename MatrixType::Index argument) {
        _index += argument;
    }
    
    template <class MatrixType>
    inline ConstMatrixIterator<MatrixType>::ConstMatrixIterator(
        const MatrixType& matrix,
        typename MatrixType::Index index
    ) : _matrix(&matrix), _index(index) {}
    
    template <class MatrixType>
    inline ConstMatrixIterator<MatrixType>::ConstMatrixIterator(
        const ConstMatrixIterator<MatrixType>& other
    ) : _matrix(other._matrix), _index(other._index) {}
    
    template <class MatrixType>
    inline ConstMatrixIterator<MatrixType>::ConstMatrixIterator(
        const MatrixIterator<MatrixType>& other
    ) : _matrix(other._matrix), _index(other._index) {}
    
    template <class MatrixType>
    inline typename MatrixType::Scalar& MatrixIterator<MatrixType>::dereference() const {
        return (*_matrix)(_index);
    }
    
    template <class MatrixType>
    inline bool MatrixIterator<MatrixType>::equal(
        const MatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline bool MatrixIterator<MatrixType>::equal(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline typename MatrixType::Index MatrixIterator<MatrixType>::distance_to(
        const MatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline typename MatrixType::Index MatrixIterator<MatrixType>::distance_to(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline void MatrixIterator<MatrixType>::increment() {++_index;}
    
    template <class MatrixType>
    inline void MatrixIterator<MatrixType>::decrement() {--_index;}
    
    template <class MatrixType>
    inline void MatrixIterator<MatrixType>::advance(typename MatrixType::Index argument) {
        _index += argument;
    }
    
    template <class MatrixType>
    inline MatrixIterator<MatrixType>::MatrixIterator(
        MatrixType& matrix,
        typename MatrixType::Index index
    ) : _matrix(&matrix), _index(index) {}
    
    template <class MatrixType>
    inline MatrixIterator<MatrixType>::MatrixIterator(const MatrixIterator<MatrixType>& other) :
        _matrix(other._matrix), _index(other._index) {}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline BlockType MatrixBlockIterator<DerivedType, MatrixType, BlockType>::dereference() const {
        return DerivedType::block(*_matrix, _index);
    }
    
    template <class DerivedType, class MatrixType, class BlockType>
    template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
    inline bool MatrixBlockIterator<DerivedType, MatrixType, BlockType>::equal(
        const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
    ) const {return _index == other._index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
    inline typename MatrixType::Index
    MatrixBlockIterator<DerivedType, MatrixType, BlockType>::distance_to(
        const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
    ) const {return other._index - _index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline void MatrixBlockIterator<DerivedType, MatrixType, BlockType>::increment() {++_index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline void MatrixBlockIterator<DerivedType, MatrixType, BlockType>::decrement() {--_index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline void MatrixBlockIterator<DerivedType, MatrixType, BlockType>::advance(
        typename MatrixType::Index argument
    ) {_index += argument;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline MatrixBlockIterator<DerivedType, MatrixType, BlockType>::MatrixBlockIterator(
        MatrixType& matrix,
        typename MatrixType::Index index
    ) : _matrix(&matrix), _index(index) {}
    
    template <class DerivedType, class MatrixType, class BlockType>
    template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
    inline MatrixBlockIterator<DerivedType, MatrixType, BlockType>::MatrixBlockIterator(
        const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
    ) : _matrix(other._matrix), _index(other._index) {}
    
    template <class MatrixType>
    inline ConstMatrixRowIterator<MatrixType>::ConstMatrixRowIterator(
        const MatrixType& matrix,
        typename MatrixType::Index index
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline ConstMatrixRowIterator<MatrixType>::ConstMatrixRowIterator(
        const ConstMatrixRowIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >(other) {}
    
    template <class MatrixType>
    inline ConstMatrixRowIterator<MatrixType>::ConstMatrixRowIterator(
        const MatrixRowIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::ConstRowXpr ConstMatrixRowIterator<MatrixType>::block(
        const MatrixType& matrix,
        typename MatrixType::Index index
    ) {return matrix.row(index);}
    
    template <class MatrixType>
    inline MatrixRowIterator<MatrixType>::MatrixRowIterator(
        MatrixType& matrix,
        typename MatrixType::Index index
    ) : MatrixBlockIterator<
            MatrixRowIterator<MatrixType>,
            MatrixType,
            typename MatrixType::RowXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline MatrixRowIterator<MatrixType>::MatrixRowIterator(
        const MatrixRowIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            MatrixRowIterator<MatrixType>,
            MatrixType,
            typename MatrixType::RowXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::RowXpr MatrixRowIterator<MatrixType>::block(
        MatrixType& matrix,
        typename MatrixType::Index index
    ) {return matrix.row(index);}
    
    template <class MatrixType>
    inline ConstMatrixColIterator<MatrixType>::ConstMatrixColIterator(
        const MatrixType& matrix,
        typename MatrixType::Index index
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline ConstMatrixColIterator<MatrixType>::ConstMatrixColIterator(
        const ConstMatrixColIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >(other) {}
    
    template <class MatrixType>
    inline ConstMatrixColIterator<MatrixType>::ConstMatrixColIterator(
        const MatrixColIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::ConstColXpr ConstMatrixColIterator<MatrixType>::block(
        const MatrixType& matrix,
        typename MatrixType::Index index
    ) {return matrix.col(index);}
    
    template <class MatrixType>
    inline MatrixColIterator<MatrixType>::MatrixColIterator(
        MatrixType& matrix, 
        typename MatrixType::Index index
    ) : MatrixBlockIterator<
            MatrixColIterator<MatrixType>,
            MatrixType,
            typename MatrixType::ColXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline MatrixColIterator<MatrixType>::MatrixColIterator(
        const MatrixColIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            MatrixColIterator<MatrixType>,
            MatrixType,
            typename MatrixType::ColXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::ColXpr MatrixColIterator<MatrixType>::block(
        MatrixType& matrix,
        typename MatrixType::Index index
    ) {return matrix.col(index);}
    
    template <class DerivedType>
    ConstMatrixIterator<DerivedType> begin(const DenseBase<DerivedType>& argument) {
        return ConstMatrixIterator<DerivedType>(argument.derived(), 0);
    }
    
    template <class DerivedType>
    ConstMatrixIterator<DerivedType> end(const DenseBase<DerivedType>& argument) {
        return ConstMatrixIterator<DerivedType>(argument.derived(), argument.size());
    }
    
    template <class DerivedType>
    MatrixIterator<DerivedType> begin(DenseBase<DerivedType>& argument) {
        return MatrixIterator<DerivedType>(argument.derived(), 0);
    }
    
    template <class DerivedType>
    MatrixIterator<DerivedType> end(DenseBase<DerivedType>& argument) {
        return MatrixIterator<DerivedType>(argument.derived(), argument.size());
    }
    
    template <class ExpressionType>
    ConstMatrixRowIterator<ExpressionType> begin(
        VectorwiseOp<const ExpressionType, Horizontal> argument
    ) {return ConstMatrixRowIterator<ExpressionType>(argument._expression(), 0);}
    
    template <class ExpressionType>
    ConstMatrixRowIterator<ExpressionType> end(
        VectorwiseOp<const ExpressionType, Horizontal> argument
    ) {
        return ConstMatrixRowIterator<ExpressionType>(
            argument._expression(),
            argument._expression().rows()
        );
    }
    
    template <class ExpressionType>
    MatrixRowIterator<ExpressionType> begin(VectorwiseOp<ExpressionType, Horizontal> argument) {
        return MatrixRowIterator<ExpressionType>(
            const_cast<ExpressionType&>(argument._expression()),
            0
        );
    }
    
    template <class ExpressionType>
    MatrixRowIterator<ExpressionType> end(VectorwiseOp<ExpressionType, Horizontal> argument) {
        return MatrixRowIterator<ExpressionType>(
            const_cast<ExpressionType&>(argument._expression()),
            argument._expression().rows()
        );
    }
    
    template <class ExpressionType>
    ConstMatrixColIterator<ExpressionType> begin(
        VectorwiseOp<const ExpressionType, Vertical> argument
    ) {return ConstMatrixColIterator<ExpressionType>(argument._expression(), 0);}
    
    template <class ExpressionType>
    ConstMatrixColIterator<ExpressionType> end(
        VectorwiseOp<const ExpressionType, Vertical> argument
    ) {
        return ConstMatrixColIterator<ExpressionType>(
            argument._expression(),
            argument._expression().cols()
        );
    }
    
    template <class ExpressionType>
    MatrixColIterator<ExpressionType> begin(VectorwiseOp<ExpressionType, Vertical> argument) {
        return MatrixColIterator<ExpressionType>(
            const_cast<ExpressionType&>(argument._expression()),
            0
        );
    }
    
    template <class ExpressionType>
    MatrixColIterator<ExpressionType> end(VectorwiseOp<ExpressionType, Vertical> argument) {
        return MatrixColIterator<ExpressionType>(
            const_cast<ExpressionType&>(argument._expression()),
            argument._expression().cols()
        );
    }
}
