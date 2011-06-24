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

#ifndef OPENSOLID__DOUBLE_HPP
#define OPENSOLID__DOUBLE_HPP

#include <boost/functional/hash.hpp>

#include <OpenSolid/Value/ValueBase.hpp>

namespace OpenSolid
{
    class Interval;
    
    class Double : public ValueBase<Double>
    {
    private:
        double _value;
    public:
        typedef Interval Bounds;
        
        Double(int argument);
        Double(float argument);
        Double(double argument);
        
        double value() const;
        
        Double* data();
        const Double* data() const;
        
        Index rows() const;
        Index cols() const;
        
        Double lower() const;
        Double upper() const;
        Double width() const;
        Double median() const;
        
        Double cwiseLower() const;
        Double cwiseUpper() const;
        Double cwiseWidth() const;
        Double cwiseMedian() const;
        
        Double cwiseProduct(const Double& argument) const;
        Interval cwiseProduct(const Interval& argument) const;
        Double cwiseQuotient(const Double& argument) const;
        Interval cwiseQuotient(const Interval& argument) const;
        
        template <class FunctionType>
        auto unaryExpr(const FunctionType& function = FunctionType()) const -> function(Double());
        
        template <class FunctionType, class DerivedType, class ScalarType>
        auto binaryExpr(
            const FunctionType& function = FunctionType(),
            const Double& argument
        ) const -> function(Double(), Double());
        
        template <class FunctionType, class DerivedType, class ScalarType>
        auto binaryExpr(
            const FunctionType& function = FunctionType(),
            const Interval& argument
        ) const -> function(Double(), Interval());
        
        Double dot(const Double& argument) const;
        Interval dot(const Interval& argument) const;
        
        Double inverse() const;
        Double determinant() const;
        
        Double squared() const;

        Double norm() const;
        Double normalized() const;

        Interval bounds() const;
        std::size_t hashValue() const;
        
        Double transposedProduct(const Double& argument) const;
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
    };
}

////////// Implementation //////////

#include "Interval.hpp"

namespace OpenSolid
{
    inline Double::Double(int argument) : _value(argument) {}
    
    inline Double::Double(float argument) : _value(argument) {}
    
    inline Double::Double(double argument) : _value(argument) {}
    
    inline double Double::value() const {return _value;}
        
    inline Double* Double::data() {return this;}
    
    inline const Double* Double::data() const {return this;}
    
    inline Index Double::rows() const {return 1;}
    
    inline Index Double::cols() const {return 1;}
    
    inline Double Double::cwiseLower() const {return *this;}
    
    inline Double Double::cwiseUpper() const {return *this;}
    
    inline Double Double::cwiseWidth() const {return 0;}
    
    inline Double Double::cwiseMedian() const {return *this;}
    
    inline Double Double::cwiseProduct(const Double& argument) const {return *this * argument;}
    
    inline Interval Double::cwiseProduct(const Interval& argument) const {return *this * argument;}
    
    inline Double Double::cwiseQuotient(const Double& argument) const {return *this / argument;}
    
    inline Interval Double::cwiseQuotient(const Interval& argument) const {return *this / argument;}
    
    template <class FunctionType>
    inline auto Double::unaryExpr(
        const FunctionType& function = FunctionType()
    ) const -> function(Double()) {return function(*this);}
    
    template <class FunctionType, class DerivedType, class ScalarType>
    inline auto Double::binaryExpr(
        const FunctionType& function = FunctionType(),
        const Double& argument
    ) const -> function(Double(), Double()) {return function(*this, argument);}
    
    template <class FunctionType, class DerivedType, class ScalarType>
    inline auto Double::binaryExpr(
        const FunctionType& function = FunctionType(),
        const Interval& argument
    ) const -> function(Double(), Interval()) {return function(*this, argument);}
    
    inline Double Double::dot(const Double& argument) const {return *this * argument;}
    
    inline Interval Double::dot(const Interval& argument) const {return *this * argument;}
    
    inline Double Double::inverse() const {return 1 / *this;}
    
    inline Double Double::determinant() const {return *this;}
    
    inline Double Double::squared() const {return *this * *this;}

    inline Double Double::norm() const {return abs(*this);}
    
    inline Double Double::normalized() const {
        assert(!isZero());
        return 1.0;
    }

    inline Interval Double::bounds() const {return *this;}
    
    inline std::size_t Double::hashValue() const {return boost::hash_value(_value);}
    
    inline Double Double::transposedProduct(const Double& argument) const {
        return *this * argument;
    }
    
    inline Interval Double::transposedProduct(const Interval& argument) const {
        return *this * argument;
    }
        
    inline bool Double::empty() const {return false;}
    
    inline bool Double::singleton() const {return true;}
    
    inline Interval Double::hull(const Double& argument) const {
        return *this <= argument ? Interval(*this, argument) : Interval(argument, *this);
    }
    
    inline Interval Double::hull(const Interval& argument) const {
        if (*this < argument.lower()) {
            return Interval(*this, argument.upper());
        } else if (argument.upper() < *this) {
            return Interval(argument.lower(), *this);
        } else {
            return argument;
        }
    }
    
    inline Interval Double::intersection(const Double& argument) const {
        return *this == argument ? Interval(*this) : Interval::Empty();
    }
    
    inline Interval Double::intersection(const Interval& argument) const {
        if (*this >= argument.lower() && *this <= argument.upper()) {
            return Interval(*this);
        } else {
            return Interval::Empty();
        }
    }
        
    inline bool Double::isZero(double precision) const {return std::abs(_value) < precision;}
    
    inline bool Double::isEqualTo(const Double& argument, double precision) const {
        return std::abs(_value - argument._value) < precision;
    }
    
    inline bool Double::isEqualTo(const Interval& argument, double precision) const {
        return this->isEqualTo(argument.lower(), precision) &&
            this->isEqualTo(argument.upper(), precision);
    }
    
    inline bool Double::isLessThan(const Double& argument, double precision) const {
        return _value < argument._value - precision;
    }
    
    inline bool Double::isLessThan(const Interval& argument, double precision) const {
        return this->isLessThan(argument.lower(), precision);
    }
    
    inline bool Double::isGreaterThan(const Double& argument, double precision) const {
        return _value > argument._value + precision;
    }
    
    inline bool Double::isGreaterThan(const Interval& argument, double precision) const {
        return this->isGreaterThan(argument.upper(), precision);
    }

    inline bool Double::isLessThanOrEqualTo(const Double& argument, double precision) const {
        return _value < argument._value + precision;
    }

    inline bool Double::isLessThanOrEqualTo(const Interval& argument, double precision) const {
        return this->isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Double::isGreaterThanOrEqualTo(const Double& argument, double precision) const {
        return _value > argument._value - precision;
    }

    inline bool Double::isGreaterThanOrEqualTo(const Interval& argument, double precision) const {
        return this->isGreaterThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Double::overlaps(const Double& argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::overlaps(const Interval& argument, double precision) const {
        this->isGreaterThanOrEqualTo(argument.lower(), precision) &&
            this->isLessThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Double::isSubsetOf(const Double& argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isSubsetOf(const Interval& argument, double precision) const {
        return this->overlaps(argument, precision);
    }

    inline bool Double::isProperSubsetOf(const Double& argument, double precision) const {
        return false;
    }

    inline bool Double::isProperSubsetOf(const Interval& argument, double precision) const {
        return this->isGreaterThan(argument.lower(), precision) &&
            this->isLessThan(argument.upper(), precision);
    }

    inline bool Double::isSupersetOf(const Double& argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isSupersetOf(const Interval& argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isProperSupersetOf(const Double& argument, double precision) const {
        return false;
    }

    inline bool Double::isProperSupersetOf(const Interval& argument, double precision) const {
        return false;
    }
}

#endif
