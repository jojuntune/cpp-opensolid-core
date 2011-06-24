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

#ifndef OPENSOLID__INTERVAL_HPP
#define OPENSOLID__INTERVAL_HPP

#include <boost/numeric/interval.hpp>
#include <boost/functional/hash.hpp>

#include <OpenSolid/Value/ValueBase.hpp>

namespace OpenSolid
{
    typedef boost::numeric::interval_lib::policies<
        boost::numeric::interval_lib::save_state_nothing<
            boost::numeric::interval_lib::rounded_transc_exact<double,
                boost::numeric::interval_lib::rounded_arith_exact<double>
            >
        >,
        boost::numeric::interval_lib::checking_base<double>
    > IntervalPolicies;
    
    typedef boost::numeric::interval<IntervalPolicies> BoostInterval;
    
    class Double;
    
    class Interval : public ValueBase<Interval>
    {
    private:
        BoostInterval _value;
    public:
        typedef Interval Bounds;
        
        Interval();
        Interval(const BoostInterval& argument);
        Interval(const Double& argument);
        Interval(const Double& lower, const Double& upper);
        
        const BoostInterval& value() const;
        
        Interval* data();
        const Interval* data() const;
        
        Index rows() const;
        Index cols() const;
        
        Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        Double cwiseLower() const;
        Double cwiseUpper() const;
        Double cwiseWidth() const;
        Double cwiseMedian() const;
        
        Interval cwiseProduct(const Double& argument) const;
        Interval cwiseProduct(const Interval& argument) const;
        Interval cwiseQuotient(const Double& argument) const;
        Interval cwiseQuotient(const Interval& argument) const;
        
        template <class FunctionType>
        auto unaryExpr(const FunctionType& function = FunctionType()) const -> function(Interval());
        
        template <class FunctionType, class DerivedType, class ScalarType>
        auto binaryExpr(
            const FunctionType& function = FunctionType(),
            const Double& argument
        ) const -> function(Interval(), Double());
        
        template <class FunctionType, class DerivedType, class ScalarType>
        auto binaryExpr(
            const FunctionType& function = FunctionType(),
            const Interval& argument
        ) const -> function(Interval(), Interval());
        
        Interval dot(const Double& argument) const;
        Interval dot(const Interval& argument) const;
        
        Interval inverse() const;
        Interval determinant() const;
        
        Interval squared() const;

        Interval norm() const;
        Double normalized() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        Interval transposedProduct(const Double& argument) const;
        Interval transposedProduct(const Interval& argument) const;
        
        bool empty() const;
        bool singleton() const;
        
        Interval hull(const Double& argument) const;
        Interval hull(const Interval& argument) const;
        Interval intersection(const Double& argument) const;
        Interval intersection(const Interval& argument) const;
        
        bool isZero(double precision = OPENSOLID_PRECISION) const;
        
        bool isEqualTo(const Double& argument, double precision = OPENSOLID_PRECISION) const;
        bool isEqualTo(const Interval& argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isLessThan(const Double& argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThan(const Interval& argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isGreaterThan(const Double& argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThan(const Interval& argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isLessThanOrEqualTo(
            const Double& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThanOrEqualTo(
            const Interval& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThanOrEqualTo(
            const Double& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThanOrEqualTo(
            const Interval& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool overlaps(const Double& argument, double precision = OPENSOLID_PRECISION) const;
        bool overlaps(const Interval& argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isSubsetOf(const Double& argument, double precision = OPENSOLID_PRECISION) const;
        bool isSubsetOf(const Interval& argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isProperSubsetOf(
            const Double& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isProperSubsetOf(
            const Interval& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isSupersetOf(const Double& argument, double precision = OPENSOLID_PRECISION) const;
        bool isSupersetOf(const Interval& argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isProperSupersetOf(
            const Double& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isProperSupersetOf(
            const Interval& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        static Interval Empty();
        static Interval Whole();
        
    };
}

////////// Implementation //////////

#include <OpenSolid/Scalar/Double.hpp>

namespace OpenSolid
{
    
}

#endif
