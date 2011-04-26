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

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Bisected.hpp>
#include <OpenSolid/Collection/FixedSizeCollection.hpp>

#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DENSEBASE_PLUGIN <OpenSolid/Value/DenseBasePlugin.hpp>

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include "DenseBasePlugin.hpp"
#endif

namespace OpenSolid
{
    class Interval;
    
    Interval abs(const Interval& argument);
    Interval sqrt(const Interval& argument);
    OPENSOLID_EXPORT Interval exp(const Interval& argument);
    OPENSOLID_EXPORT Interval log(const Interval& argument);
    OPENSOLID_EXPORT Interval sin(const Interval& argument);
    OPENSOLID_EXPORT Interval cos(const Interval& argument);
    
    double lowerBound(const Interval& argument);
    double upperBound(const Interval& argument);
}

namespace Eigen
{
    using OpenSolid::Interval;
    using OpenSolid::Bounds;
    using OpenSolid::Bisected;
    using OpenSolid::FixedSizeCollection;
    
    namespace internal
    {
        using OpenSolid::abs;
        using OpenSolid::sqrt;
        using OpenSolid::exp;
        using OpenSolid::log;
        using OpenSolid::sin;
        using OpenSolid::cos;
        
        const Interval& conj(const Interval& argument);
        const Interval& real(const Interval& argument);
        Interval imag(const Interval&);
        Interval abs2(const Interval& argument);
        Interval pow(const Interval& x, const Interval& y); 
    
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;
        
        template <>
        struct significant_decimals_default_impl<Interval, false>
        {
            static inline int run();
        };
    }
    
    template <class Type>
    struct NumTraits;
    
    template <>
    struct NumTraits<Interval>
    {
        typedef Interval Real;
        typedef Interval NonInteger;
        typedef Interval Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static Interval epsilon();
        static Interval dummy_precision();
        static Interval lowest();
        static Interval highest();
    };
    
    template <class DerivedType, class MatrixType, class BlockType>
    class MatrixBlockIterator :
        public boost::iterator_facade<
            DerivedType,
            BlockType,
            boost::random_access_traversal_tag,
            BlockType
        >
    {
    protected:
        template <class OtherDerived, class OtherMatrixType, class OtherBlockType>
        friend class MatrixBlockIterator;
        
        friend class boost::iterator_core_access;
        
        MatrixType& _matrix;
        int _index;
        
        BlockType dereference() const;
        
        template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
        bool equal(
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
    
    template <class DerivedType>
    class MatrixListAdapter : public FixedSizeCollection<MatrixListAdapter<DerivedType> >
    {
    private:
        const DerivedType& _matrix;
    public:
        typedef typename DerivedType::ConstColIterator Iterator;
        
        MatrixListAdapter(const DerivedType& matrix);
        
        int size() const;
        bool empty() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        typename Bounds<typename DerivedType::ConstColXpr::PlainObject>::Type bounds() const;
        
        Iterator begin() const;
        Iterator end() const;
        
        typename DerivedType::ConstColXpr front() const;
        typename DerivedType::ConstColXpr back() const;
        
        typename DerivedType::ConstColXpr operator[](int index) const;
    };
    
    struct ContainOperation
    {
        typedef bool result_type;
        
        bool operator()(const Interval& first_argument, const Interval& second_argument) const;
        bool operator()(double first_argument, double second_argument) const;
    };
    
    struct OverlapOperation
    {
        typedef bool result_type;
        
        bool operator()(const Interval& first_argument, const Interval& second_argument) const;
        bool operator()(double first_argument, double second_argument) const;
    };
    
    struct AdjacentOperation
    {
        typedef bool result_type;
        
        bool operator()(const Interval& first_argument, const Interval& second_argument) const;
        bool operator()(double first_argument, double second_argument) const;
    };
    
    struct HullOperation
    {
        typedef Interval result_type;
        
        Interval operator()(const Interval& first_argument, const Interval& second_argument) const;
        Interval operator()(double first_argument, double second_argument) const;
    };
    
    struct IntersectionOperation
    {
        typedef Interval result_type;
        
        Interval operator()(const Interval& first_argument, const Interval& second_argument) const;
        Interval operator()(double first_argument, double second_argument) const;
    };
    
    struct LowerOperation
    {
        typedef double result_type;
        
        double operator()(const Interval& argument) const;
        double operator()(double argument) const;
    };
    
    struct UpperOperation
    {
        typedef double result_type;
        
        double operator()(const Interval& argument) const;
        double operator()(double argument) const;
    };
    
    struct MedianOperation
    {
        typedef double result_type;
        
        double operator()(const Interval& argument) const;
        double operator()(double argument) const;
    };
    
    struct WidthOperation
    {
        typedef double result_type;
        
        double operator()(const Interval& argument) const;
        double operator()(double argument) const;
    };
    
    struct CenteredOperation
    {
        typedef Interval result_type;
        
        Interval operator()(const Interval& argument) const;
        Interval operator()(double argument) const;
    };
}

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace OpenSolid
{
    using namespace Eigen;
}

#endif
