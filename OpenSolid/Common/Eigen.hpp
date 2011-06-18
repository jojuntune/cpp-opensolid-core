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
 
#ifndef OPENSOLID__EIGEN_HPP
#define OPENSOLID__EIGEN_HPP

#include <OpenSolid/config.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/functional/hash.hpp>

#include <OpenSolid/Scalar/Double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DENSEBASE_PLUGIN <OpenSolid/Matrix/DenseBasePlugin.hpp>

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include "DenseBasePlugin.hpp"
#endif

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
            typename MatrixType::Scalar
        >
    {
    private:
        friend class boost::iterator_core_access;
        friend class MatrixIterator<MatrixType>;
        
        const MatrixType* _matrix;
        int _index;
        
        typename MatrixType::Scalar dereference() const;
        
        bool equal(const MatrixIterator<MatrixType>& other) const;
        bool equal(const ConstMatrixIterator<MatrixType>& other) const;
        
        int distance_to(const MatrixIterator<MatrixType>& other) const;
        int distance_to(const ConstMatrixIterator<MatrixType>& other) const;
        
        void increment();
        void decrement();
        void advance(int argument);
    public:
        ConstMatrixIterator(const MatrixType& matrix, int index);
        ConstMatrixIterator(const ConstMatrixIterator<MatrixType>& other);
        ConstMatrixIterator(const MatrixIterator<MatrixType>& other);
    };
    
    template <class MatrixType>
    class MatrixIterator : 
        public boost::iterator_facade<
            MatrixIterator<MatrixType>,
            typename MatrixType::Scalar,
            std::random_access_iterator_tag,
            typename MatrixType::Scalar&
        >
    {
    private:
        friend class boost::iterator_core_access;
        friend class ConstMatrixIterator<MatrixType>;
        
        MatrixType* _matrix;
        int _index;
        
        typename MatrixType::Scalar& dereference() const;
        
        bool equal(const MatrixIterator<MatrixType>& other) const;
        bool equal(const ConstMatrixIterator<MatrixType>& other) const;
        
        int distance_to(const MatrixIterator<MatrixType>& other) const;
        int distance_to(const ConstMatrixIterator<MatrixType>& other) const;
        
        void increment();
        void decrement();
        void advance(int argument);
    public:
        MatrixIterator(MatrixType& matrix, int index);
        MatrixIterator(const MatrixIterator<MatrixType>& other);
    };
    
    template <class DerivedType, class MatrixType, class BlockType>
    class MatrixBlockIterator :
        public boost::iterator_facade<
            DerivedType,
            BlockType,
            std::random_access_iterator_tag,
            BlockType
        >
    {
    protected:
        template <class OtherDerived, class OtherMatrixType, class OtherBlockType>
        friend class MatrixBlockIterator;
        
        friend class boost::iterator_core_access;
        
        MatrixType* _matrix;
        int _index;
        
        BlockType dereference() const;
        
        template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
        bool equal(
            const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
        ) const;
        
        template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
        int distance_to(
            const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
        ) const;
        
        void increment();
        void decrement();
        void advance(int argument);

        MatrixBlockIterator(MatrixType& matrix, int index);
        
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
        ConstMatrixRowIterator(const MatrixType& matrix, int index);
        ConstMatrixRowIterator(const ConstMatrixRowIterator<MatrixType>& other);
        ConstMatrixRowIterator(const MatrixRowIterator<MatrixType>& other);
        
        static typename MatrixType::ConstRowXpr block(const MatrixType& matrix, int index);
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
        MatrixRowIterator(MatrixType& matrix, int index);
        MatrixRowIterator(const MatrixRowIterator<MatrixType>& other);
        
        static typename MatrixType::RowXpr block(MatrixType& matrix, int index);
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
        ConstMatrixColIterator(const MatrixType& matrix, int index);
        ConstMatrixColIterator(const ConstMatrixColIterator<MatrixType>& other);
        ConstMatrixColIterator(const MatrixColIterator<MatrixType>& other);
        
        static typename MatrixType::ConstColXpr block(const MatrixType& matrix, int index);
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
        MatrixColIterator(MatrixType& matrix, int index);
        MatrixColIterator(const MatrixColIterator<MatrixType>& other);
        
        static typename MatrixType::ColXpr block(MatrixType& matrix, int index);
    };
    
    struct LowerOperation()
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct UpperOperation()
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct MedianOperation()
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct WidthOperation()
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct HullOperation()
    {
        typedef OpenSolid::Interval result_type;
        
        template <class ScalarType>
        OpenSolid::Interval operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct IntersectionOperation()
    {
        typedef OpenSolid::Interval result_type;
        
        template <class ScalarType>
        OpenSolid::Interval operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct HashVisitor
    {
        std::size_t result;
        
        template <class ScalarType>
        inline void init(ScalarType argument, int, int);
        
        template <class ScalarType>
        inline void operator()(ScalarType argument, int, int);
    };
}

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

#endif
