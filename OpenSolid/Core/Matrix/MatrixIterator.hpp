/************************************************************************************
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

#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Interval.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace Eigen
{   
    template <class TMatrix>
    class ConstMatrixIterator : 
        public boost::iterator_facade<
            ConstMatrixIterator<TMatrix>,
            typename TMatrix::Scalar,
            std::random_access_iterator_tag,
            typename TMatrix::Scalar,
            typename TMatrix::Index
        >
    {
    private:
        typedef typename TMatrix::Index Index;
        
        friend class boost::iterator_core_access;
        friend class MatrixIterator<TMatrix>;
        
        const TMatrix* _matrixPtr;
        Index _index;
        
        typename TMatrix::Scalar
        dereference() const;
        
        bool
        equal(const MatrixIterator<TMatrix>& other) const;
        
        bool
        equal(const ConstMatrixIterator<TMatrix>& other) const;
        
        Index
        distance_to(const MatrixIterator<TMatrix>& other) const;
        
        Index
        distance_to(const ConstMatrixIterator<TMatrix>& other) const;
        
        void
        increment();
        
        void
        decrement();
        
        void
        advance(Index argument);
    public:
        ConstMatrixIterator(const TMatrix& matrix, Index index);

        ConstMatrixIterator(const ConstMatrixIterator<TMatrix>& other);

        ConstMatrixIterator(const MatrixIterator<TMatrix>& other);
    };
    
    template <class TMatrix>
    class MatrixIterator : 
        public boost::iterator_facade<
            MatrixIterator<TMatrix>,
            typename TMatrix::Scalar,
            std::random_access_iterator_tag,
            typename TMatrix::Scalar&,
            typename TMatrix::Index
        >
    {
    private:
        typedef typename TMatrix::Index Index;
        
        friend class boost::iterator_core_access;
        friend class ConstMatrixIterator<TMatrix>;
        
        TMatrix* _matrixPtr;
        Index _index;
        
        typename TMatrix::Scalar&
        dereference() const;
        
        bool
        equal(const MatrixIterator<TMatrix>& other) const;
        
        bool
        equal(const ConstMatrixIterator<TMatrix>& other) const;
        
        Index
        distance_to(const MatrixIterator<TMatrix>& other) const;
        
        Index
        distance_to(const ConstMatrixIterator<TMatrix>& other) const;
        
        void
        increment();
        
        void
        decrement();
        
        void
        advance(Index argument);
    public:
        MatrixIterator(TMatrix& matrix, Index index);
        
        MatrixIterator(const MatrixIterator<TMatrix>& other);
    };
    
    template <class TDerived, class TMatrix, class TBlock>
    class MatrixBlockIterator :
        public boost::iterator_facade<
            TDerived,
            TBlock,
            std::random_access_iterator_tag,
            TBlock,
            typename TMatrix::Index
        >
    {
    protected:
        typedef typename TMatrix::Index Index;
        
        template <class OtherDerived, class TOtherMatrix, class TOtherBlock>
        friend class MatrixBlockIterator;
        
        friend class boost::iterator_core_access;
        
        TMatrix* _matrixPtr;
        Index _index;
        
        TBlock
        dereference() const;
        
        template <class TOtherDerived, class TOtherMatrix, class TOtherBlock>
        bool
        equal(
            const MatrixBlockIterator<TOtherDerived, TOtherMatrix, TOtherBlock>& other
        ) const;
        
        template <class TOtherDerived, class TOtherMatrix, class TOtherBlock>
        Index
        distance_to(
            const MatrixBlockIterator<TOtherDerived, TOtherMatrix, TOtherBlock>& other
        ) const;
        
        void
        increment();
        
        void
        decrement();
        
        void
        advance(Index argument);

        MatrixBlockIterator(TMatrix& matrix, Index index);
        
        template <class TOtherDerived, class TOtherMatrix, class TOtherBlock>
        MatrixBlockIterator(
            const MatrixBlockIterator<TOtherDerived, TOtherMatrix, TOtherBlock>& other
        );
    };

    template <class TMatrix>
    class MatrixRowIterator;

    template <class TMatrix>
    class ConstMatrixRowIterator :
        public MatrixBlockIterator<
            ConstMatrixRowIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstRowXpr
        >
    {
    public:
        typedef typename TMatrix::Index Index;
        
        ConstMatrixRowIterator(const TMatrix& matrix, Index index);

        ConstMatrixRowIterator(const ConstMatrixRowIterator<TMatrix>& other);

        ConstMatrixRowIterator(const MatrixRowIterator<TMatrix>& other);
        
        static typename TMatrix::ConstRowXpr
        block(const TMatrix& matrix, Index index);
    };
    
    template <class TMatrix>
    class MatrixRowIterator :
        public MatrixBlockIterator<MatrixRowIterator<TMatrix>, TMatrix, typename TMatrix::RowXpr>
    {
    public:
        typedef typename TMatrix::Index Index;
        
        MatrixRowIterator(TMatrix& matrix, Index index);

        MatrixRowIterator(const MatrixRowIterator<TMatrix>& other);
        
        static typename TMatrix::RowXpr
        block(TMatrix& matrix, Index index);
    };

    template <class TMatrix>
    class MatrixColIterator;
    
    template <class TMatrix>
    class ConstMatrixColIterator :
        public MatrixBlockIterator<
            ConstMatrixColIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstColXpr
        >
    {
    public:
        typedef typename TMatrix::Index Index;
        
        ConstMatrixColIterator(const TMatrix& matrix, Index index);

        ConstMatrixColIterator(const ConstMatrixColIterator<TMatrix>& other);

        ConstMatrixColIterator(const MatrixColIterator<TMatrix>& other);
        
        static typename TMatrix::ConstColXpr
        block(const TMatrix& matrix, Index index);
    };
    
    template <class TMatrix>
    class MatrixColIterator :
        public MatrixBlockIterator<MatrixColIterator<TMatrix>, TMatrix, typename TMatrix::ColXpr>
    {
    public:
        typedef typename TMatrix::Index Index;
        
        MatrixColIterator(TMatrix& matrix, Index index);

        MatrixColIterator(const MatrixColIterator<TMatrix>& other);
        
        static typename TMatrix::ColXpr
        block(TMatrix& matrix, Index index);
    };
    
    template <class TDerived>
    ConstMatrixIterator<TDerived>
    begin(const DenseBase<TDerived>& argument);
    
    template <class TDerived>
    ConstMatrixIterator<TDerived>
    end(const DenseBase<TDerived>& argument);
    
    template <class TDerived>
    MatrixIterator<TDerived>
    begin(DenseBase<TDerived>& argument);
    
    template <class TDerived>
    MatrixIterator<TDerived>
    end(DenseBase<TDerived>& argument);
    
    template <class TExpression>
    ConstMatrixRowIterator<TExpression>
    begin(VectorwiseOp<const TExpression, Horizontal> argument);
    
    template <class TExpression>
    ConstMatrixRowIterator<TExpression>
    end(VectorwiseOp<const TExpression, Horizontal> argument);
    
    template <class TExpression>
    MatrixRowIterator<TExpression>
    begin(VectorwiseOp<TExpression, Horizontal> argument);
    
    template <class TExpression>
    MatrixRowIterator<TExpression>
    end(VectorwiseOp<TExpression, Horizontal> argument);
    
    template <class TExpression>
    ConstMatrixColIterator<TExpression>
    begin(VectorwiseOp<const TExpression, Vertical> argument);
    
    template <class TExpression>
    ConstMatrixColIterator<TExpression>
    end(VectorwiseOp<const TExpression, Vertical> argument);
    
    template <class TExpression>
    MatrixColIterator<TExpression>
    begin(VectorwiseOp<TExpression, Vertical> argument);
    
    template <class TExpression>
    MatrixColIterator<TExpression>
    end(VectorwiseOp<TExpression, Vertical> argument);
}

////////// Implementation //////////

namespace Eigen
{
    template <class TMatrix>
    inline
    typename TMatrix::Scalar
    ConstMatrixIterator<TMatrix>::dereference() const {
        return (*_matrixPtr)(_index);
    }
    
    template <class TMatrix>
    inline
    bool
    ConstMatrixIterator<TMatrix>::equal(const ConstMatrixIterator<TMatrix>& other) const {
        return _index == other._index;
    }
    
    template <class TMatrix>
    inline
    bool
    ConstMatrixIterator<TMatrix>::equal(const MatrixIterator<TMatrix>& other) const {
        return _index == other._index;
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::Index
    ConstMatrixIterator<TMatrix>::distance_to(const ConstMatrixIterator<TMatrix>& other) const {
        return other._index - _index;
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::Index
    ConstMatrixIterator<TMatrix>::distance_to(const MatrixIterator<TMatrix>& other) const {
        return other._index - _index;
    }
    
    template <class TMatrix>
    inline
    void
    ConstMatrixIterator<TMatrix>::increment() {
        ++_index;
    }
    
    template <class TMatrix>
    inline
    void
    ConstMatrixIterator<TMatrix>::decrement() {
        --_index;
    }
    
    template <class TMatrix>
    inline
    void
    ConstMatrixIterator<TMatrix>::advance(typename TMatrix::Index argument) {
        _index += argument;
    }
    
    template <class TMatrix>
    inline
    ConstMatrixIterator<TMatrix>::ConstMatrixIterator(
        const TMatrix& matrix,
        typename TMatrix::Index index
    ) : _matrixPtr(&matrix),
        _index(index) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixIterator<TMatrix>::ConstMatrixIterator(const ConstMatrixIterator<TMatrix>& other) :
        _matrixPtr(other._matrixPtr),
        _index(other._index) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixIterator<TMatrix>::ConstMatrixIterator(const MatrixIterator<TMatrix>& other) :
        _matrixPtr(other._matrixPtr),
        _index(other._index) {
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::Scalar&
    MatrixIterator<TMatrix>::dereference() const {
        return (*_matrixPtr)(_index);
    }
    
    template <class TMatrix>
    inline
    bool
    MatrixIterator<TMatrix>::equal(const MatrixIterator<TMatrix>& other) const {
        return _index == other._index;
    }
    
    template <class TMatrix>
    inline
    bool
    MatrixIterator<TMatrix>::equal(const ConstMatrixIterator<TMatrix>& other) const {
        return _index == other._index;
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::Index
    MatrixIterator<TMatrix>::distance_to(const MatrixIterator<TMatrix>& other) const {
        return other._index - _index;
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::Index
    MatrixIterator<TMatrix>::distance_to(const ConstMatrixIterator<TMatrix>& other) const {
        return other._index - _index;
    }
    
    template <class TMatrix>
    inline
    void
    MatrixIterator<TMatrix>::increment() {
        ++_index;
    }
    
    template <class TMatrix>
    inline
    void
    MatrixIterator<TMatrix>::decrement() {
        --_index;
    }
    
    template <class TMatrix>
    inline
    void
    MatrixIterator<TMatrix>::advance(typename TMatrix::Index argument) {
        _index += argument;
    }
    
    template <class TMatrix>
    inline
    MatrixIterator<TMatrix>::MatrixIterator(TMatrix& matrix, typename TMatrix::Index index) :
        _matrixPtr(&matrix),
        _index(index) {
    }
    
    template <class TMatrix>
    inline
    MatrixIterator<TMatrix>::MatrixIterator(const MatrixIterator<TMatrix>& other) :
        _matrixPtr(other._matrixPtr),
        _index(other._index) {
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    inline
    TBlock
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::dereference() const {
        return TDerived::block(*_matrixPtr, _index);
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    template <class TOtherDerived, class TOtherMatrix, class TOtherBlock>
    inline
    bool
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::equal(
        const MatrixBlockIterator<TOtherDerived, TOtherMatrix, TOtherBlock>& other
    ) const {
        return _index == other._index;
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    template <class TOtherDerived, class TOtherMatrix, class TOtherBlock>
    inline
    typename TMatrix::Index
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::distance_to(
        const MatrixBlockIterator<TOtherDerived, TOtherMatrix, TOtherBlock>& other
    ) const {
        return other._index - _index;
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    inline
    void
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::increment() {
        ++_index;
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    inline
    void
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::decrement() {
        --_index;
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    inline
    void
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::advance(typename TMatrix::Index argument) {
        _index += argument;
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    inline
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::MatrixBlockIterator(
        TMatrix& matrix,
        typename TMatrix::Index index
    ) : _matrixPtr(&matrix),
        _index(index) {
    }
    
    template <class TDerived, class TMatrix, class TBlock>
    template <class TOtherDerived, class TOtherMatrix, class TOtherBlock>
    inline
    MatrixBlockIterator<TDerived, TMatrix, TBlock>::MatrixBlockIterator(
        const MatrixBlockIterator<TOtherDerived, TOtherMatrix, TOtherBlock>& other
    ) : _matrixPtr(other._matrixPtr),
        _index(other._index) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixRowIterator<TMatrix>::ConstMatrixRowIterator(
        const TMatrix& matrix,
        typename TMatrix::Index index
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstRowXpr
        >(matrix, index) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixRowIterator<TMatrix>::ConstMatrixRowIterator(
        const ConstMatrixRowIterator<TMatrix>& other
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstRowXpr
        >(other) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixRowIterator<TMatrix>::ConstMatrixRowIterator(
        const MatrixRowIterator<TMatrix>& other
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstRowXpr
        >(other) {
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::ConstRowXpr
    ConstMatrixRowIterator<TMatrix>::block(const TMatrix& matrix, typename TMatrix::Index index) {
        return matrix.row(index);
    }
    
    template <class TMatrix>
    inline
    MatrixRowIterator<TMatrix>::MatrixRowIterator(TMatrix& matrix, typename TMatrix::Index index) :
        MatrixBlockIterator<
            MatrixRowIterator<TMatrix>,
            TMatrix,
            typename TMatrix::RowXpr
        >(matrix, index) {
    }
    
    template <class TMatrix>
    inline
    MatrixRowIterator<TMatrix>::MatrixRowIterator(const MatrixRowIterator<TMatrix>& other) :
        MatrixBlockIterator<
            MatrixRowIterator<TMatrix>,
            TMatrix,
            typename TMatrix::RowXpr
        >(other) {
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::RowXpr
    MatrixRowIterator<TMatrix>::block(TMatrix& matrix, typename TMatrix::Index index) {
        return matrix.row(index);
    }
    
    template <class TMatrix>
    inline
    ConstMatrixColIterator<TMatrix>::ConstMatrixColIterator(
        const TMatrix& matrix,
        typename TMatrix::Index index
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstColXpr
        >(matrix, index) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixColIterator<TMatrix>::ConstMatrixColIterator(
        const ConstMatrixColIterator<TMatrix>& other
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstColXpr
        >(other) {
    }
    
    template <class TMatrix>
    inline
    ConstMatrixColIterator<TMatrix>::ConstMatrixColIterator(
        const MatrixColIterator<TMatrix>& other
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<TMatrix>,
            const TMatrix,
            typename TMatrix::ConstColXpr
        >(other) {
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::ConstColXpr
    ConstMatrixColIterator<TMatrix>::block(const TMatrix& matrix, typename TMatrix::Index index) {
        return matrix.col(index);
    }
    
    template <class TMatrix>
    inline
    MatrixColIterator<TMatrix>::MatrixColIterator(TMatrix& matrix, typename TMatrix::Index index) :
        MatrixBlockIterator<
            MatrixColIterator<TMatrix>,
            TMatrix,
            typename TMatrix::ColXpr
        >(matrix, index) {
    }
    
    template <class TMatrix>
    inline
    MatrixColIterator<TMatrix>::MatrixColIterator(const MatrixColIterator<TMatrix>& other) :
        MatrixBlockIterator<
            MatrixColIterator<TMatrix>,
            TMatrix,
            typename TMatrix::ColXpr
        >(other) {
    }
    
    template <class TMatrix>
    inline
    typename TMatrix::ColXpr
    MatrixColIterator<TMatrix>::block(TMatrix& matrix, typename TMatrix::Index index) {
        return matrix.col(index);
    }
    
    template <class TDerived>
    ConstMatrixIterator<TDerived>
    begin(const DenseBase<TDerived>& argument) {
        return ConstMatrixIterator<TDerived>(argument.derived(), 0);
    }
    
    template <class TDerived>
    ConstMatrixIterator<TDerived>
    end(const DenseBase<TDerived>& argument) {
        return ConstMatrixIterator<TDerived>(argument.derived(), argument.size());
    }
    
    template <class TDerived>
    MatrixIterator<TDerived>
    begin(DenseBase<TDerived>& argument) {
        return MatrixIterator<TDerived>(argument.derived(), 0);
    }
    
    template <class TDerived>
    MatrixIterator<TDerived>
    end(DenseBase<TDerived>& argument) {
        return MatrixIterator<TDerived>(argument.derived(), argument.size());
    }
    
    template <class TExpression>
    ConstMatrixRowIterator<TExpression>
    begin(VectorwiseOp<const TExpression, Horizontal> argument) {
        return ConstMatrixRowIterator<TExpression>(argument._expression(), 0);
    }
    
    template <class TExpression>
    ConstMatrixRowIterator<TExpression>
    end(VectorwiseOp<const TExpression, Horizontal> argument) {
        return ConstMatrixRowIterator<TExpression>(
            argument._expression(),
            argument._expression().rows()
        );
    }
    
    template <class TExpression>
    MatrixRowIterator<TExpression>
    begin(VectorwiseOp<TExpression, Horizontal> argument) {
        return MatrixRowIterator<TExpression>(const_cast<TExpression&>(argument._expression()), 0);
    }
    
    template <class TExpression>
    MatrixRowIterator<TExpression>
    end(VectorwiseOp<TExpression, Horizontal> argument) {
        return MatrixRowIterator<TExpression>(
            const_cast<TExpression&>(argument._expression()),
            argument._expression().rows()
        );
    }
    
    template <class TExpression>
    ConstMatrixColIterator<TExpression>
    begin(VectorwiseOp<const TExpression, Vertical> argument) {
        return ConstMatrixColIterator<TExpression>(argument._expression(), 0);
    }
    
    template <class TExpression>
    ConstMatrixColIterator<TExpression>
    end(VectorwiseOp<const TExpression, Vertical> argument) {
        return ConstMatrixColIterator<TExpression>(
            argument._expression(),
            argument._expression().cols()
        );
    }
    
    template <class TExpression>
    MatrixColIterator<TExpression>
    begin(VectorwiseOp<TExpression, Vertical> argument) {
        return MatrixColIterator<TExpression>(const_cast<TExpression&>(argument._expression()), 0);
    }
    
    template <class TExpression>
    MatrixColIterator<TExpression>
    end(VectorwiseOp<TExpression, Vertical> argument) {
        return MatrixColIterator<TExpression>(
            const_cast<TExpression&>(argument._expression()),
            argument._expression().cols()
        );
    }
}
