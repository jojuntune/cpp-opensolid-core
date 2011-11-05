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

#ifndef OPENSOLID__BOOST_HPP
#define OPENSOLID__BOOST_HPP

#include <boost/functional/hash.hpp>

#if BOOST_VERSION >= 104700
#include <boost/geometry.hpp>
#endif

#include <OpenSolid/Support/declarations.hpp>
#include <OpenSolid/Support/STL.hpp>

namespace boost
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct hash<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>> :
        public std::hash<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>
    {
    };

    template <>
    struct hash<OpenSolid::Interval> : public std::hash<OpenSolid::Interval>
    {
    };

    template <class Type>
    struct hash<OpenSolid::Set<Type>> : public std::hash<OpenSolid::Set<Type>>
    {
    };

    template <int dimensions_>
    struct hash<OpenSolid::Axis<dimensions_>> : public std::hash<OpenSolid::Axis<dimensions_>>
    {
    };

    template <int dimensions_, int axes_>
    struct hash<OpenSolid::CoordinateSystem<dimensions_, axes_>> :
        public std::hash<OpenSolid::CoordinateSystem<dimensions_, axes_>>
    {
    };
    
    template <int dimensions_, int axes_>
    struct hash<OpenSolid::Datum<dimensions_, axes_>> :
        public std::hash<OpenSolid::Datum<dimensions_, axes_>>
    {
    };

    template <int dimensions_>
    struct hash<OpenSolid::Frame<dimensions_>> : public std::hash<OpenSolid::Frame<dimensions_>>
    {
    };
    
    template <int dimensions_>
    struct hash<OpenSolid::Plane<dimensions_>> : public std::hash<OpenSolid::Plane<dimensions_>>
    {
    };
    
    template <int dimensions_, int size_>
    struct hash<OpenSolid::Simplex<dimensions_, size_>> :
        public std::hash<OpenSolid::Simplex<dimensions_, size_>>
    {
    };

    template <>
    struct hash<OpenSolid::Function> : public std::hash<OpenSolid::Function>
    {
    };
    
    template <>
    struct hash<OpenSolid::Domain> : public std::hash<OpenSolid::Domain>
    {
    };
    
    template <>
    struct hash<OpenSolid::Geometry> : public std::hash<OpenSolid::Geometry>
    {
    };

    #if BOOST_VERSION >= 104700
    namespace geometry
    {
        namespace traits
        {
            template <>
            struct tag<Eigen::Matrix<double, 2, 1, 0, 2, 1>>
            {
                typedef boost::geometry::point_tag type;
            };
            
            template <>
            struct tag<Eigen::Matrix<double, 3, 1, 0, 3, 1>>
            {
                typedef boost::geometry::point_tag type;
            };

            template <>
            struct coordinate_type<Eigen::Matrix<double, 2, 1, 0, 2, 1>>
            {
                typedef double type;
            };

            template <>
            struct coordinate_type<Eigen::Matrix<double, 3, 1, 0, 3, 1>>
            {
                typedef double type;
            };

            template <>
            struct coordinate_system<Eigen::Matrix<double, 2, 1, 0, 2, 1>>
            {
                typedef cs::cartesian type;
            };

            template <>
            struct coordinate_system<Eigen::Matrix<double, 3, 1, 0, 3, 1>>
            {
                typedef cs::cartesian type;
            };

            template <>
            struct dimension<Eigen::Matrix<double, 2, 1, 0, 2, 1>> : public mpl::int_<2>
            {
            };

            template <>
            struct dimension<Eigen::Matrix<double, 3, 1, 0, 3, 1>> : public mpl::int_<3>
            {
            };

            template<std::size_t dimension_>
            struct access<Eigen::Matrix<double, 2, 1, 0, 2, 1>, dimension_>
            {
                static double get(const Eigen::Matrix<double, 2, 1, 0, 2, 1>& argument);
                static void set(Eigen::Matrix<double, 2, 1, 0, 2, 1>& argument, double value);
            };

            template<std::size_t dimension_>
            struct access<Eigen::Matrix<double, 3, 1, 0, 3, 1>, dimension_>
            {
                static double get(const Eigen::Matrix<double, 3, 1, 0, 3, 1>& argument);
                static void set(Eigen::Matrix<double, 3, 1, 0, 3, 1>& argument, double value);
            };

            template <>
            struct tag<Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>>
            {
                typedef box_tag type;
            };

            template <>
            struct tag<Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>>
            {
                typedef box_tag type;
            };

            template <>
            struct point_type<Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>>
            {
                typedef Eigen::Matrix<double, 2, 1, 0, 2, 1> type;
            };

            template <>
            struct point_type<Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>>
            {
                typedef Eigen::Matrix<double, 3, 1, 0, 3, 1> type;
            };

            template <std::size_t dimension_>
            struct indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>,
                min_corner,
                dimension_
            >
            {
                static double get(
                    const Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument
                );

                static void set(
                    Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument,
                    double value
                );
            };

            template <std::size_t dimension_>
            struct indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>, max_corner, dimension_
            >
            {
                static double get(
                    const Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument
                );

                static void set(
                    Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument,
                    double value
                );
            };

            template <std::size_t dimension_>
            struct indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>, min_corner, dimension_
            >
            {
                static double get(
                    const Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument
                );

                static void set(
                    Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument,
                    double value
                );
            };

            template <std::size_t dimension_>
            struct indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>, max_corner, dimension_
            >
            {
                static double get(
                    const Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument
                );

                static void set(
                    Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument,
                    double value
                );
            };

            template <>
            struct tag<OpenSolid::Simplex<2, 2>>
            {
                typedef segment_tag type;
            };

            template <>
            struct tag<OpenSolid::Simplex<3, 2>>
            {
                typedef segment_tag type;
            };

            template <>
            struct point_type<OpenSolid::Simplex<2, 2>>
            {
                typedef Eigen::Matrix<double, 2, 1, 0, 2, 1> type;
            };

            template <>
            struct point_type<OpenSolid::Simplex<3, 2>>
            {
                typedef Eigen::Matrix<double, 3, 1, 0, 3, 1> type;
            };

            template <std::size_t index_, std::size_t dimension_>
            struct indexed_access<OpenSolid::Simplex<2, 2>, index_, dimension_>
            {
                static double get(const OpenSolid::Simplex<2, 2>& argument);
                static inline void set(OpenSolid::Simplex<2, 2>& argument, double value);
            };

            template <std::size_t index_, std::size_t dimension_>
            struct indexed_access<OpenSolid::Simplex<3, 2>, index_, dimension_>
            {
                static double get(const OpenSolid::Simplex<3, 2>& argument);
                static inline void set(OpenSolid::Simplex<3, 2>& argument, double value);
            };
        }
    }
    #endif
}

////////// Implementation //////////

#include <OpenSolid/Simplex/Simplex.hpp>

#if BOOST_VERSION >= 104700
namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template<std::size_t dimension_>
            inline double access<Eigen::Matrix<double, 2, 1, 0, 2, 1>, dimension_>::get(
                const Eigen::Matrix<double, 2, 1, 0, 2, 1>& argument
            ) {return argument(dimension_);}

            template<std::size_t dimension_>
            inline void access<Eigen::Matrix<double, 2, 1, 0, 2, 1>, dimension_>::set(
                Eigen::Matrix<double, 2, 1, 0, 2, 1>& argument,
                double value
            ) {argument(dimension_) = value;}

            template<std::size_t dimension_>
            inline double access<Eigen::Matrix<double, 3, 1, 0, 3, 1>, dimension_>::get(
                const Eigen::Matrix<double, 3, 1, 0, 3, 1>& argument
            ) {return argument(dimension_);}

            template<std::size_t dimension_>
            inline void access<Eigen::Matrix<double, 3, 1, 0, 3, 1>, dimension_>::set(
                Eigen::Matrix<double, 3, 1, 0, 3, 1>& argument,
                double value
            ) {argument(dimension_) = value;}

            template <std::size_t dimension_>
            inline double indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>,
                min_corner,
                dimension_
            >::get(const Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument) {
                return argument(dimension_).lower();
            }

            template <std::size_t dimension_>
            inline void indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>,
                min_corner,
                dimension_
            >::set(Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument, double value) {
                *reinterpret_cast<double*>(&argument.coeffRef(dimension_)) = value;
            }

            template <std::size_t dimension_>
            inline double indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>,
                max_corner,
                dimension_
            >::get(const Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument) {
                return argument(dimension_).upper();
            }

            template <std::size_t dimension_>
            inline void indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>,
                max_corner,
                dimension_
            >::set(Eigen::Matrix<OpenSolid::Interval, 2, 1, 0, 2, 1>& argument, double value) {
                *(reinterpret_cast<double*>(&argument.coeffRef(dimension_)) + 1) = value;
            }

            template <std::size_t dimension_>
            inline double indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>,
                min_corner,
                dimension_
            >::get(const Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument) {
                return argument(dimension_).lower();
            }

            template <std::size_t dimension_>
            inline void indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>,
                min_corner,
                dimension_
            >::set(Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument, double value) {
                *reinterpret_cast<double*>(&argument.coeffRef(dimension_)) = value;
            }

            template <std::size_t dimension_>
            inline double indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>,
                max_corner,
                dimension_
            >::get(const Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument) {
                return argument(dimension_).upper();
            }

            template <std::size_t dimension_>
            inline void indexed_access<
                Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>,
                max_corner,
                dimension_
            >::set(Eigen::Matrix<OpenSolid::Interval, 3, 1, 0, 3, 1>& argument, double value) {
                *(reinterpret_cast<double*>(&argument.coeffRef(dimension_)) + 1) = value;    
            }

            template <std::size_t index_, std::size_t dimension_>
            double indexed_access<OpenSolid::Simplex<2, 2>, index_, dimension_>::get(
                const OpenSolid::Simplex<2, 2>& argument
            ) {return argument.vertex(index_)(dimension_);}

            template <std::size_t index_, std::size_t dimension_>
            void indexed_access<OpenSolid::Simplex<2, 2>, index_, dimension_>::set(
                OpenSolid::Simplex<2, 2>& argument,
                double value
            ) {argument.vertex(index_)(dimension_) = value;}

            template <std::size_t index_, std::size_t dimension_>
            double indexed_access<OpenSolid::Simplex<3, 2>, index_, dimension_>::get(
                const OpenSolid::Simplex<3, 2>& argument
            ) {return argument.vertex(index_)(dimension_);}

            template <std::size_t index_, std::size_t dimension_>
            void indexed_access<OpenSolid::Simplex<3, 2>, index_, dimension_>::set(
                OpenSolid::Simplex<3, 2>& argument,
                double value
            ) {argument.vertex(index_)(dimension_) = value;}
        }
    }
}
#endif

#endif
