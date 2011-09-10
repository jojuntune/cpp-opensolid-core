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

#ifndef OPENSOLID__STL_HPP
#define OPENSOLID__STL_HPP

#include <utility>
#include <list>
#include <vector>
#include <functional>
#include <iterator>

#include <boost/functional/hash.hpp>

#include <OpenSolid/declarations.hpp>
#include <OpenSolid/Common/Bounds.hpp>

namespace OpenSolid
{
    template <class BoundedType>
    struct Bounds<std::pair<BoundedType, BoundedType>>
    {
        typedef typename Bounds<BoundedType>::Type Type;

        typename Bounds<BoundedType>::Type operator()(
            const std::pair<BoundedType, BoundedType>& argument
        ) const;
    };

    template <class BoundedType, class AllocatorType>
    struct Bounds<std::list<BoundedType, AllocatorType>>
    {
        typedef typename Bounds<BoundedType>::Type Type;

        typename Bounds<BoundedType>::Type operator()(
            const std::list<BoundedType, AllocatorType>& argument
        ) const;
    };

    template <class BoundedType, class AllocatorType>
    struct Bounds<std::vector<BoundedType, AllocatorType>>
    {
        typedef typename Bounds<BoundedType>::Type Type;

        typename Bounds<BoundedType>::Type operator()(
            const std::vector<BoundedType, AllocatorType>& argument
        ) const;
    };
}

namespace std
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct hash<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>> :
        public std::unary_function<
            Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>,
            size_t
        >
    {
        size_t operator()(
            const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
        ) const;
    };

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct equal_to<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>> :
        public binary_function<
            Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>,
            Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>,
            bool
        >
    {
        bool operator()(
            const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& first,
            const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& second
        ) const;
    };

    template <>
    struct hash<OpenSolid::Interval> : public unary_function<OpenSolid::Interval, size_t>
    {
        std::size_t operator()(const OpenSolid::Interval& argument) const;
    };

    template <>
    struct equal_to<OpenSolid::Interval> :
        public binary_function<OpenSolid::Interval, OpenSolid::Interval, bool>
    {
        bool operator()(
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
        ) const;
    };

    template <class Type, class BoundsFunctionType>
    struct hash<OpenSolid::Set<Type, BoundsFunctionType>> :
        public unary_function<OpenSolid::Set<Type, BoundsFunctionType>, size_t>
    {
        size_t operator()(const OpenSolid::Set<Type, BoundsFunctionType>& argument) const;
    };

    template <class Type, class BoundsFunctionType>
    struct equal_to<OpenSolid::Set<Type, BoundsFunctionType>> :
        public binary_function<
            OpenSolid::Set<Type, BoundsFunctionType>,
            OpenSolid::Set<Type, BoundsFunctionType>,
            bool
        >
    {
        bool operator()(
            const OpenSolid::Set<Type, BoundsFunctionType>& first_argument,
            const OpenSolid::Set<Type, BoundsFunctionType>& second_argument
        ) const;
    };

    template <int dimensions_>
    struct hash<OpenSolid::Axis<dimensions_>> :
        public unary_function<OpenSolid::Axis<dimensions_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Axis<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Axis<dimensions_>> :
        public binary_function<OpenSolid::Axis<dimensions_>, OpenSolid::Axis<dimensions_>, bool>
    {
        bool operator()(
            const OpenSolid::Axis<dimensions_>& first_argument,
            const OpenSolid::Axis<dimensions_>& second_argument
        ) const;
    };

    template <int dimensions_, int axes_>
    struct hash<OpenSolid::CoordinateSystem<dimensions_, axes_>> :
        public unary_function<OpenSolid::CoordinateSystem<dimensions_, axes_>, size_t>
    {
        std::size_t operator()(
            const OpenSolid::CoordinateSystem<dimensions_, axes_>& argument
        ) const;
    };

    template <int dimensions_, int axes_>
    struct equal_to<OpenSolid::CoordinateSystem<dimensions_, axes_>> :
        public binary_function<
            OpenSolid::CoordinateSystem<dimensions_, axes_>,
            OpenSolid::CoordinateSystem<dimensions_, axes_>,
            bool
        >
    {
        bool operator()(
            const OpenSolid::CoordinateSystem<dimensions_, axes_>& first_argument,
            const OpenSolid::CoordinateSystem<dimensions_, axes_>& second_argument
        ) const;
    };

    template <int dimensions_, int axes_>
    struct hash<OpenSolid::Datum<dimensions_, axes_>> :
        public unary_function<OpenSolid::Datum<dimensions_, axes_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Datum<dimensions_, axes_>& argument) const;
    };

    template <int dimensions_, int axes_>
    struct equal_to<OpenSolid::Datum<dimensions_, axes_>> :
        public binary_function<
            OpenSolid::Datum<dimensions_, axes_>,
            OpenSolid::Datum<dimensions_, axes_>,
            bool
        >
    {
        bool operator()(
            const OpenSolid::Datum<dimensions_, axes_>& first_argument,
            const OpenSolid::Datum<dimensions_, axes_>& second_argument
        ) const;
    };
    
    template <int dimensions_>
    struct hash<OpenSolid::Frame<dimensions_>> :
        public unary_function<OpenSolid::Frame<dimensions_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Frame<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Frame<dimensions_>> :
        public binary_function<OpenSolid::Frame<dimensions_>, OpenSolid::Frame<dimensions_>, bool>
    {
        bool operator()(
            const OpenSolid::Frame<dimensions_>& first_argument,
            const OpenSolid::Frame<dimensions_>& second_argument
        ) const;
    };
    
    template <int dimensions_>
    struct hash<OpenSolid::Plane<dimensions_>> :
        public unary_function<OpenSolid::Plane<dimensions_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Plane<dimensions_>& argument) const;
    };

    template <int dimensions_>
    struct equal_to<OpenSolid::Plane<dimensions_>> :
        public binary_function<OpenSolid::Plane<dimensions_>, OpenSolid::Plane<dimensions_>, bool>
    {
        bool operator()(
            const OpenSolid::Plane<dimensions_>& first_argument,
            const OpenSolid::Plane<dimensions_>& second_argument
        ) const;
    };
    
    template <int dimensions_, int size_>
    struct hash<OpenSolid::Simplex<dimensions_, size_>> :
        public unary_function<OpenSolid::Simplex<dimensions_, size_>, size_t>
    {
        size_t operator()(const OpenSolid::Simplex<dimensions_, size_>& argument) const;
    };
    
    template <>
    struct hash<OpenSolid::Function> : public unary_function<OpenSolid::Function, size_t>
    {
        size_t operator()(const OpenSolid::Function& argument) const;
    };

    template <>
    struct equal_to<OpenSolid::Function> :
        public binary_function<OpenSolid::Function, OpenSolid::Function, bool>
    {
        bool operator()(
            const OpenSolid::Function& first_argument,
            const OpenSolid::Function& second_argument
        ) const;
    };

    template <>
    struct hash<OpenSolid::Domain> : public unary_function<OpenSolid::Domain, size_t>
    {
        size_t operator()(const OpenSolid::Domain& argument) const;
    };

    template <>
    struct equal_to<OpenSolid::Domain> :
        public binary_function<OpenSolid::Domain, OpenSolid::Domain, bool>
    {
        bool operator()(
            const OpenSolid::Domain& first_argument,
            const OpenSolid::Domain& second_argument
        ) const;
    };
    
    template <>
    struct hash<OpenSolid::Geometry> : public unary_function<OpenSolid::Geometry, size_t>
    {
        size_t operator()(const OpenSolid::Geometry& argument) const;
    };

    template <>
    struct equal_to<OpenSolid::Geometry> :
        public binary_function<OpenSolid::Geometry, OpenSolid::Geometry, bool>
    {
        bool operator()(
            const OpenSolid::Geometry& first_argument,
            const OpenSolid::Geometry& second_argument
        ) const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{
    template <class BoundedType>
    inline typename Bounds<BoundedType>::Type
    Bounds<std::pair<BoundedType, BoundedType>>::operator()(
        const std::pair<BoundedType, BoundedType>& argument
    ) const {
        Bounds<BoundedType> bounds_function;
        typename Bounds<BoundedType>::Type result = bounds_function(argument.first);
        result = result.hull(bounds_function(argument.second));
        return result;
    }

    namespace
    {
        template <class IteratorType>
        inline typename Bounds<typename IteratorType::value_type>::Type rangeBounds(
            IteratorType begin,
            IteratorType end
        ) {
            typedef typename std::iterator_traits<IteratorType>::value_type ValueType;
            typedef typename Bounds<ValueType>::Type BoundsType;
            if (begin == end) {
                return BoundsType();
            } else {
                Bounds<ValueType> bounds_function;
                BoundsType result = bounds_function(*begin);
                while (++begin != end) {
                    result = result.hull(bounds_function(*begin));
                }
                return result;
            }
        }
    }
    
    template <class BoundedType, class AllocatorType>
    inline typename Bounds<BoundedType>::Type
    Bounds<std::list<BoundedType, AllocatorType>>::operator()(
        const std::list<BoundedType, AllocatorType>& argument
    ) const {return rangeBounds(argument.begin(), argument.end());}
    
    template <class BoundedType, class AllocatorType>
    inline typename Bounds<BoundedType>::Type
    Bounds<std::vector<BoundedType, AllocatorType>>::operator()(
        const std::vector<BoundedType, AllocatorType>& argument
    ) const {return rangeBounds(argument.begin(), argument.end());}
}

namespace std
{
    namespace
    {
        struct HashVisitor
        {
            std::size_t result;
        
            template <class ScalarType>
            inline void init(const ScalarType& argument, int, int) {
                result = 0;
                boost::hash_combine(result, std::hash<ScalarType>()(argument));
            }
        
            template <class ScalarType>
            inline void operator()(const ScalarType& argument, int, int) {
                boost::hash_combine(result, std::hash<ScalarType>()(argument));
            }
        };
    }

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline size_t hash<
        Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
    >::operator()(
        const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
    ) const {
        HashVisitor visitor;
        argument.visit(visitor);
        return visitor.result;
    }

    namespace
    {
        struct EqualVisitor
        {
            typedef bool result_type;

            template <class ScalarType>
            inline bool operator()(
                const ScalarType& first_argument,
                const ScalarType& second_argument
            ) const {return std::equal_to<ScalarType>()(first_argument, second_argument);}
        };
    }

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline bool equal_to<
        Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
    >::operator()(
        const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& first,
        const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& second
    ) const {return first.binaryExpr(second, EqualVisitor()).all();}

    inline std::size_t hash<OpenSolid::Interval>::operator()(
        const OpenSolid::Interval& argument
    ) const {
        size_t result = 0;
        boost::hash_combine(result, boost::hash_value(argument.lower()));
        boost::hash_combine(result, boost::hash_value(argument.upper()));
        return result;
    }

    inline bool equal_to<OpenSolid::Interval>::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    template <class Type, class BoundsFunctionType>
    inline size_t hash<OpenSolid::Set<Type, BoundsFunctionType>>::operator()(
        const OpenSolid::Set<Type, BoundsFunctionType>& argument
    ) const {return boost::hash_value(argument.root());}

    template <class Type, class BoundsFunctionType>
    inline bool equal_to<OpenSolid::Set<Type, BoundsFunctionType>>::operator()(
        const OpenSolid::Set<Type, BoundsFunctionType>& first_argument,
        const OpenSolid::Set<Type, BoundsFunctionType>& second_argument
    ) const {return first_argument.root() == second_argument.root();}

    template <int dimensions_>
    inline size_t hash<OpenSolid::Axis<dimensions_>>::operator()(
        const OpenSolid::Axis<dimensions_>& argument
    ) const {return hash<OpenSolid::Datum<dimensions_, 1>>()(argument);}

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Axis<dimensions_>>::operator()(
        const OpenSolid::Axis<dimensions_>& first_argument,
        const OpenSolid::Axis<dimensions_>& second_argument
    ) const {return equal_to<OpenSolid::Datum<dimensions_, 1>>()(first_argument, second_argument);}
    
    template <int dimensions_, int axes_>
    inline size_t hash<OpenSolid::CoordinateSystem<dimensions_, axes_>>::operator()(
        const OpenSolid::CoordinateSystem<dimensions_, axes_>& argument
    ) const {return hash<OpenSolid::Datum<dimensions_, axes_>>()(argument);}

    template <int dimensions_, int axes_>
    inline bool equal_to<OpenSolid::CoordinateSystem<dimensions_, axes_>>::operator()(
        const OpenSolid::CoordinateSystem<dimensions_, axes_>& first_argument,
        const OpenSolid::CoordinateSystem<dimensions_, axes_>& second_argument
    ) const {
        return equal_to<OpenSolid::Datum<dimensions_, axes_>>()(first_argument, second_argument);
    }

    template <int dimensions_, int axes_>
    inline size_t hash<OpenSolid::Datum<dimensions_, axes_>>::operator()(
        const OpenSolid::Datum<dimensions_, axes_>& argument
    ) const {
        size_t result = 0;
        boost::hash_combine(
            result,
            hash<Eigen::Matrix<double, dimensions_, 1>>()(argument.origin())
        );
        boost::hash_combine(
            result,
            hash<Eigen::Matrix<double, dimensions_, axes_>>()(argument.basis())
        );
        return result;
    }

    template <int dimensions_, int axes_>
    inline bool equal_to<OpenSolid::Datum<dimensions_, axes_>>::operator()(
        const OpenSolid::Datum<dimensions_, axes_>& first_argument,
        const OpenSolid::Datum<dimensions_, axes_>& second_argument
    ) const {
        return first_argument.origin() == second_argument.origin() &&
            first_argument.basis() == second_argument.basis();
    }
    
    template <int dimensions_>
    inline size_t hash<OpenSolid::Frame<dimensions_>>::operator()(
        const OpenSolid::Frame<dimensions_>& argument
    ) const {return hash<OpenSolid::Datum<dimensions_, dimensions_>>()(argument);}

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Frame<dimensions_>>::operator()(
        const OpenSolid::Frame<dimensions_>& first_argument,
        const OpenSolid::Frame<dimensions_>& second_argument
    ) const {
        return equal_to<OpenSolid::Datum<dimensions_, dimensions_>>()(
            first_argument,
            second_argument
        );
    }
    
    template <int dimensions_>
    inline size_t hash<OpenSolid::Plane<dimensions_>>::operator()(
        const OpenSolid::Plane<dimensions_>& argument
    ) const {
        return hash<
            OpenSolid::Datum<
                dimensions_,
                dimensions_ == Eigen::Dynamic ? Eigen::Dynamic : dimensions_ - 1
            >
        >()(argument);
    }

    template <int dimensions_>
    inline bool equal_to<OpenSolid::Plane<dimensions_>>::operator()(
        const OpenSolid::Plane<dimensions_>& first_argument,
        const OpenSolid::Plane<dimensions_>& second_argument
    ) const {
        return equal_to<
            OpenSolid::Datum<
                dimensions_,
                dimensions_ == Eigen::Dynamic ? Eigen::Dynamic : dimensions_ - 1
            >
        >()(first_argument, second_argument);
    }

    template <int dimensions_, int size_>
    inline size_t hash<OpenSolid::Simplex<dimensions_, size_>>::operator()(
        const OpenSolid::Simplex<dimensions_, size_>& argument
    ) const {
        return hash<typename OpenSolid::Simplex<dimensions_, size_>::Vertices>()(
            argument.vertices()
        );
    }
    
    inline size_t hash<OpenSolid::Function>::operator()(const OpenSolid::Function& argument) const {
        return boost::hash_value(argument.implementation());
    }

    inline bool equal_to<OpenSolid::Function>::operator()(
        const OpenSolid::Function& first_argument,
        const OpenSolid::Function& second_argument
    ) const {return first_argument.implementation() == second_argument.implementation();}
    
    inline size_t hash<OpenSolid::Domain>::operator()(const OpenSolid::Domain& argument) const {
        return hash<OpenSolid::Set<OpenSolid::Geometry>>()(argument.boundaries());
    }

    inline bool equal_to<OpenSolid::Domain>::operator()(
        const OpenSolid::Domain& first_argument,
        const OpenSolid::Domain& second_argument
    ) const {
        return equal_to<OpenSolid::Set<OpenSolid::Geometry>>()(
            first_argument.boundaries(),
            second_argument.boundaries()
        );
    }
    
    inline size_t hash<OpenSolid::Geometry>::operator()(const OpenSolid::Geometry& argument) const {
        size_t result = 0;
        boost::hash_combine(result, hash<OpenSolid::Function>()(argument.function()));
        boost::hash_combine(result, hash<OpenSolid::Domain>()(argument.domain()));
        return result;
    }

    inline bool equal_to<OpenSolid::Geometry>::operator()(
        const OpenSolid::Geometry& first_argument,
        const OpenSolid::Geometry& second_argument
    ) const {
        return equal_to<OpenSolid::Function>()(
            first_argument.function(),
            second_argument.function()
        ) && equal_to<OpenSolid::Domain>()(
            first_argument.domain(),
            second_argument.domain()
        );
    }
}

#endif
