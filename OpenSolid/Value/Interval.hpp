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

#include <OpenSolid/config.hpp>

#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cassert>
#include <utility>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Bisected.hpp>
#include <OpenSolid/Common/Pair.hpp>
#include "Eigen.hpp"

namespace OpenSolid
{   
    using std::min;
    using std::max;
    using std::abs;
    using std::sqrt;
    using std::sin;
    using std::cos;
    using std::tan;
    using std::asin;
    using std::acos;
    using std::atan;
    using std::exp;
    using std::log;
    
    class Interval
    {
    private:
        double _lower;
        double _upper;
    public:
        Interval();
        Interval(double value);
        Interval(double lower, double upper);
        Interval(const Interval& other);
        
        double& lower();
        double& upper();
        double lower() const;
        double upper() const;
        double median() const;
        double width() const;
        bool empty() const;
        Interval centered() const;
        Bisected<Interval> bisected() const;
        
        const Interval& operator()(int index) const;
        const Interval& operator()(int row, int col) const;
        Interval& operator()(int index);
        Interval& operator()(int row, int col);
        
        Interval squared() const;
        
        bool overlap(double value) const;
        bool overlap(const Interval& other) const;
        bool contain(double value) const;
        bool contain(const Interval& other) const;
        bool adjacent(double value) const;
        bool adjacent(const Interval& other) const;
        
        Interval hull(double value) const;
        Interval hull(const Interval& other) const;
        Interval intersection(double value) const;
        Interval intersection(const Interval& other) const;
        
        Interval& operator+=(double argument);
        Interval& operator+=(const Interval& other);
        Interval& operator-=(double argument);
        Interval& operator-=(const Interval& other);
        Interval& operator*=(double argument);
        Interval& operator*=(const Interval& other);
        Interval& operator/=(double argument);
        Interval& operator/=(const Interval& other);
        
        static Interval Empty();
        static Interval Whole();
    };

    bool operator==(double first_argument, const Interval& second_argument);
    bool operator==(const Interval& first_argument, double second_argument);
    bool operator==(const Interval& first_argument, const Interval& second_argument);
    bool operator!=(double first_argument, const Interval& second_argument);
    bool operator!=(const Interval& first_argument, double second_argument);
    bool operator!=(const Interval& first_argument, const Interval& second_argument);
    bool operator<(double first_argument, const Interval& second_argument);
    bool operator<(const Interval& first_argument, double second_argument);
    bool operator<(const Interval& first_argument, const Interval& second_argument);
    bool operator<=(double first_argument, const Interval& second_argument);
    bool operator<=(const Interval& first_argument, double second_argument);
    bool operator<=(const Interval& first_argument, const Interval& second_argument);
    bool operator>(double first_argument, const Interval& second_argument);
    bool operator>(const Interval& first_argument, double second_argument);
    bool operator>(const Interval& first_argument, const Interval& second_argument);
    bool operator>=(double first_argument, const Interval& second_argument);
    bool operator>=(const Interval& first_argument, double second_argument);
    bool operator>=(const Interval& first_argument, const Interval& second_argument);
    
    Interval operator-(const Interval& argument);
    Interval operator+(double first_argument, const Interval& second_argument);
    Interval operator+(const Interval& first_argument, double second_argument);
    Interval operator+(const Interval& first_argument, const Interval& second_argument);
    Interval operator-(double first_argument, const Interval& second_argument);
    Interval operator-(const Interval& first_argument, double second_argument);
    Interval operator-(const Interval& first_argument, const Interval& second_argument);
    Interval operator*(double first_argument, const Interval& second_argument);
    Interval operator*(const Interval& first_argument, double second_argument);
    Interval operator*(const Interval& first_argument, const Interval& second_argument);
    Interval operator/(double first_argument, const Interval& second_argument);
    Interval operator/(const Interval& first_argument, double second_argument);
    Interval operator/(const Interval& first_argument, const Interval& second_argument);
    
    Interval abs(const Interval& argument);
    Interval sqrt(const Interval& argument);
    OPENSOLID_EXPORT Interval sin(const Interval& argument);
    OPENSOLID_EXPORT Interval cos(const Interval& argument);
    OPENSOLID_EXPORT Interval tan(const Interval& argument);
    OPENSOLID_EXPORT Interval asin(const Interval& argument);
    OPENSOLID_EXPORT Interval acos(const Interval& argument);
    OPENSOLID_EXPORT Interval atan(const Interval& argument);
    OPENSOLID_EXPORT Interval exp(const Interval& argument);
    OPENSOLID_EXPORT Interval log(const Interval& argument);

    OPENSOLID_EXPORT std::ostream& operator<<(std::ostream& stream, const Interval& value);
    
    template <>
    struct Bounds<int>
    {
        typedef Interval Type;
        
        static Interval bounds(int value);
    };
    
    template <>
    struct Bounds<double>
    {
        typedef Interval Type;
        
        static Interval bounds(double value);
    };
    
    template <>
    struct Bounds<Interval>
    {
        typedef Interval Type;
        
        static const Interval& bounds(const Interval& value);
    };
    
    template <>
    class Bisected<Interval>
    {
    private:
        const Interval& _argument;
    public:
        Bisected(const Interval& argument);
        
        const Interval& argument() const;
        
        Interval first() const;
        Interval second() const;
    };
    
    template <>
    class Pair<Interval&>
    {
    private:
        Interval& _first_argument;
        Interval& _second_argument;
    public:
        Pair(Interval& first_argument, Interval& second_argument);
        
        void operator=(const Bisected<Interval>& bisected);
    };
    
    template <>
    class Pair<Interval>
    {
    private:
        Interval _first;
        Interval _second;
    public:
        Pair(const Interval& first, const Interval& second);
        Pair(const Bisected<Interval>& bisected);
        
        void operator=(const Bisected<Interval>& bisected);
        
        const Interval& first() const;
        const Interval& second() const;
    };
}
   
////////// Implementation //////////

namespace Eigen
{
    namespace internal
    {
        inline const Interval& conj(const Interval& argument) {return argument;}
    
        inline const Interval& real(const Interval& argument) {return argument;}
    
        inline Interval imag(const Interval&) {return Interval(0.0);}
    
        inline Interval abs2(const Interval& argument) {return argument.squared();}
    
        inline Interval pow(const Interval& x, const Interval& y) {
            return exp(y * log(x));
        }
    
        inline int significant_decimals_default_impl<Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
    }
    
    inline Interval NumTraits<Interval>::epsilon() {return Interval(NumTraits<double>::epsilon());}
    
    inline Interval NumTraits<Interval>::dummy_precision() {
        return Interval(NumTraits<double>::dummy_precision());
    }
    
    inline Interval NumTraits<Interval>::lowest() {return Interval(NumTraits<double>::lowest());}
    
    inline Interval NumTraits<Interval>::highest() {return Interval(NumTraits<double>::highest());}
}

namespace OpenSolid
{
    inline double lowerBound(const Interval& argument) {return argument.lower();}
    
    inline double upperBound(const Interval& argument) {return argument.upper();}
    
    inline Interval::Interval() {}

    inline Interval::Interval(double value) : _lower(value), _upper(value) {}

    inline Interval::Interval(double lower, double upper) : _lower(lower), _upper(upper) {
        assert(lower <= upper);
    }

    inline Interval::Interval(const Interval& other) :
        _lower(other.lower()), _upper(other.upper()) {}
    
    inline double& Interval::lower() {return _lower;}

    inline double& Interval::upper() {return _upper;}
    
    inline double Interval::lower() const {return _lower;}

    inline double Interval::upper() const {return _upper;}
    
    inline double Interval::median() const {return lower() + (upper() - lower()) / 2;}
    
    inline double Interval::width() const {return upper() - lower();}
    
    inline bool Interval::empty() const {return upper() < lower();}
    
    inline Interval Interval::centered() const {return *this - median();}
    
    inline Bisected<Interval> Interval::bisected() const {return Bisected<Interval>(*this);}
        
    inline const Interval& Interval::operator()(int index) const {
        assert(index == 0);
        return *this;
    }
    
    inline const Interval& Interval::operator()(int row, int col) const {
        assert(row == 0 && col == 0);
        return *this;
    }
    
    inline Interval& Interval::operator()(int index) {
        assert(index == 0);
        return *this;   
    }
    
    inline Interval& Interval::operator()(int row, int col) {
        assert(row == 0 && col == 0);
        return *this;
    }
    
    inline Interval Interval::squared() const {
        if (lower() >= 0) {
            return Interval(lower() * lower(), upper() * upper());
        } else if (upper() <= 0) {
            return Interval(upper() * upper(), lower() * lower());
        } else {
            return Interval(0.0, max(lower() * lower(), upper() * upper()));
        }
    };
    
    inline bool Interval::overlap(double value) const {return lower() <= value && value <= upper();}
    
    inline bool Interval::overlap(const Interval& other) const {
        return lower() <= other.upper() && other.lower() <= upper();
    }
    
    inline bool Interval::contain(double value) const {return lower() <= value && value <= upper();}
    
    inline bool Interval::contain(const Interval& other) const {
        return lower() <= other.lower() && other.upper() <= upper();
    }
    
    inline bool Interval::adjacent(double value) const {
        return value == lower() || value == upper();
    }
    
    inline bool Interval::adjacent(const Interval& other) const {
        return other.lower() == upper() || other.upper() == lower();
    }
        
    inline Interval Interval::hull(double value) const {
        return Interval(min(value, lower()), max(value, upper()));
    }
    
    inline Interval Interval::hull(const Interval& other) const {
        return Interval(min(lower(), other.lower()), max(upper(), other.upper()));
    }
    
    inline Interval Interval::intersection(double value) const {
        return Interval(min(lower(), value), max(upper(), value));
    }
    
    inline Interval Interval::intersection(const Interval& other) const {
        return Interval(max(lower(), other.lower()), min(upper(), other.upper()));
    }

    inline Interval& Interval::operator+=(double argument) {
        _lower += argument;
        _upper += argument;
        return *this;
    }

    inline Interval& Interval::operator+=(const Interval& other) {
        _lower += other.lower();
        _upper += other.upper();
        return *this;
    }

    inline Interval& Interval::operator-=(double argument) {
        _lower -= argument;
        _upper -= argument;
        return *this;
    }

    inline Interval& Interval::operator-=(const Interval& other) {
        _lower -= other.upper();
        _upper -= other.lower();
        return *this;
    }

    inline Interval& Interval::operator*=(double argument) {
        if (argument >= 0) {
            _lower *= argument;
            _upper *= argument;
        } else {
            double temp = lower() * argument;
            _lower = upper() * argument;
            _upper = temp;
        }
        return *this;
    }

    inline Interval& Interval::operator*=(const Interval& other) {
        if (other.lower() == other.upper()) {
            return operator*=(other.lower());
        }
        double temp1 = lower() * other.lower();
        double temp2 = lower() * other.upper();
        double temp3 = upper() * other.lower();
        double temp4 = upper() * other.upper();
        _lower = min(min(temp1, temp2), min(temp3, temp4));
        _upper = max(max(temp1, temp2), max(temp3, temp4));
        return *this;
    }

    inline Interval& Interval::operator/=(double argument) {
        assert(argument != 0);
        if (argument > 0) {
            _lower /= argument;
            _upper /= argument;
        } else {
            double temp = lower() / argument;
            _lower = upper() / argument;
            _upper = temp;
        }
        return *this;
    }

    inline Interval& Interval::operator/=(const Interval& other) {
        if (other.lower() == other.upper()) {
            return operator/=(other.lower());
        }
        assert(!other.contain(0));
        double temp1 = _lower / other.lower();
        double temp2 = _lower / other.upper();
        double temp3 = _upper / other.lower();
        double temp4 = _upper / other.upper();
        _lower = min(min(temp1, temp2), min(temp3, temp4));
        _upper = max(max(temp1, temp2), max(temp3, temp4));
        return *this;
    }
    
    inline Interval Interval::Empty() {
        return Interval(
            std::numeric_limits<double>::infinity(),
            -std::numeric_limits<double>::infinity()
        );
    }
    
    inline Interval Interval::Whole() {
        return Interval(
            -std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity()
        );
    }

    inline bool operator==(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() &&
            first_argument == second_argument.upper();
    }

    inline bool operator==(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument &&
            first_argument.upper() == second_argument;
    }

    inline bool operator==(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.upper() &&
            first_argument.upper() == second_argument.lower();
    }

    inline bool operator!=(double first_argument, const Interval& second_argument) {
        return first_argument < second_argument.lower() || first_argument > second_argument.upper();
    }

    inline bool operator!=(const Interval& first_argument, double second_argument) {
        return first_argument.upper() < second_argument || first_argument.lower() > second_argument;
    }

    inline bool operator!=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() > second_argument.upper() ||
            first_argument.upper() < second_argument.lower();
    }

    inline bool operator<(double first_argument, const Interval& second_argument) {
        return first_argument < second_argument.lower();
    }

    inline bool operator<(const Interval& first_argument, double second_argument) {
        return first_argument.upper() < second_argument;
    }

    inline bool operator<(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.upper() < second_argument.lower();
    }

    inline bool operator<=(double first_argument, const Interval& second_argument) {
        return first_argument <= second_argument.lower();
    }

    inline bool operator<=(const Interval& first_argument, double second_argument) {
        return first_argument.upper() <= second_argument;
    }

    inline bool operator<=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.upper() <= second_argument.lower();
    }

    inline bool operator>(double first_argument, const Interval& second_argument) {
        return first_argument > second_argument.upper();
    }

    inline bool operator>(const Interval& first_argument, double second_argument) {
        return first_argument.lower() > second_argument;
    }

    inline bool operator>(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() > second_argument.upper();
    }

    inline bool operator>=(double first_argument, const Interval& second_argument) {
        return first_argument >= second_argument.upper();
    }

    inline bool operator>=(const Interval& first_argument, double second_argument) {
        return first_argument.lower() >= second_argument;
    }

    inline bool operator>=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() >= second_argument.upper();
    }
        
    inline Interval operator-(const Interval& argument) {
        return Interval(-argument.upper(), -argument.lower());
    }

    inline Interval operator+(double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument + second_argument.lower(),
            first_argument + second_argument.upper()
        );
    }

    inline Interval operator+(const Interval& first_argument, double second_argument) {
        return Interval(
            first_argument.lower() + second_argument,
            first_argument.upper() + second_argument
        );
    }

    inline Interval operator+(const Interval& first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.lower() + second_argument.lower(),
            first_argument.upper() + second_argument.upper()
        );
    }

    inline Interval operator-(double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument - second_argument.upper(),
            first_argument - second_argument.lower()
        );
    }

    inline Interval operator-(const Interval& first_argument, double second_argument) {
        return Interval(
            first_argument.lower() - second_argument,
            first_argument.upper() - second_argument
        );
    }

    inline Interval operator-(const Interval& first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.lower() - second_argument.upper(),
            first_argument.upper() - second_argument.lower()
        );
    }

    inline Interval operator*(double first_argument, const Interval& second_argument) {
        if (first_argument >= 0) {
            return Interval(
                first_argument * second_argument.lower(),
                first_argument * second_argument.upper()
            );
        } else {
            return Interval(
                first_argument * second_argument.upper(),
                first_argument * second_argument.lower()
            );
        }
    }

    inline Interval operator*(const Interval& first_argument, double second_argument) {
        if (second_argument >= 0) {
            return Interval(
                second_argument * first_argument.lower(),
                second_argument * first_argument.upper()
            );
        } else {
            return Interval(
                second_argument * first_argument.upper(),
                second_argument * first_argument.lower()
            );
        }
    }

    inline Interval operator*(const Interval& first_argument, const Interval& second_argument) {
        double temp1 = first_argument.lower() * second_argument.lower();
        double temp2 = first_argument.lower() * second_argument.upper();
        double temp3 = first_argument.upper() * second_argument.lower();
        double temp4 = first_argument.upper() * second_argument.upper();
        return Interval(
            min(min(temp1, temp2), min(temp3, temp4)),
            max(max(temp1, temp2), max(temp3, temp4))
        );
    }

    inline Interval operator/(double first_argument, const Interval& second_argument) {
        assert(!second_argument.contain(0.0));
        if (first_argument >= 0) {
            return Interval(
                first_argument / second_argument.upper(),
                first_argument / second_argument.lower()
            );
        } else {
            return Interval(
                first_argument / second_argument.lower(),
                first_argument / second_argument.upper()
            );
        }
    }

    inline Interval operator/(const Interval& first_argument, double second_argument) {
        assert(second_argument != 0.0);
        if (second_argument > 0) {
            return Interval(
                first_argument.lower() / second_argument,
                first_argument.upper() / second_argument
            );
        } else {
            return Interval(
                first_argument.upper() / second_argument,
                first_argument.lower() / second_argument
            );
        }
    }

    inline Interval operator/(const Interval& first_argument, const Interval& second_argument) {
        assert(!second_argument.contain(0.0));
        double temp1 = first_argument.lower() / second_argument.lower();
        double temp2 = first_argument.lower() / second_argument.upper();
        double temp3 = first_argument.upper() / second_argument.lower();
        double temp4 = first_argument.upper() / second_argument.upper();
        return Interval(
            min(min(temp1, temp2), min(temp3, temp4)),
            max(max(temp1, temp2), max(temp3, temp4))
        );
    }

    inline Interval abs(const Interval& argument) {
        if (argument.lower() >= 0) {
            return Interval(abs(argument.lower()), abs(argument.upper()));
        } else if (argument.upper() <= 0) {
            return Interval(abs(argument.upper()), abs(argument.lower()));
        } else {
            return Interval(0.0, max(abs(argument.lower()), abs(argument.upper())));
        }
    }

    inline Interval sqrt(const Interval& argument) {
        assert(argument.lower() >= 0);
        return Interval(sqrt(argument.lower()), sqrt(argument.upper()));
    }
    
    inline Interval Bounds<int>::bounds(int value) {return Interval(value);}
    
    inline Interval Bounds<double>::bounds(double value) {return Interval(value);}
    
    inline const Interval& Bounds<Interval>::bounds(const Interval& value) {return value;}
    
    inline Bisected<Interval>::Bisected(const Interval& argument) : _argument(argument) {}
    
    inline const Interval& Bisected<Interval>::argument() const {return _argument;}
    
    inline Interval Bisected<Interval>::first() const {
        return Interval(_argument.lower(), _argument.median());
    }
    
    inline Interval Bisected<Interval>::second() const {
        return Interval(_argument.median(), _argument.upper());
    }
    
    inline Pair<Interval&>::Pair(Interval& first_argument, Interval& second_argument) :
        _first_argument(first_argument), _second_argument(second_argument) {}
        
    inline void Pair<Interval&>::operator=(const Bisected<Interval>& bisected) {
        double median = bisected.argument().median();
        _first_argument.lower() = bisected.argument().lower();
        _first_argument.upper() = median;
        _second_argument.lower() = median;
        _second_argument.upper() = bisected.argument().upper();
    }
    
    inline Pair<Interval>::Pair(const Interval& first, const Interval& second) :
        _first(first), _second(second) {}
    
    inline Pair<Interval>::Pair(const Bisected<Interval>& bisected) {
        Pair<Interval&>(_first, _second) = bisected;
    }
        
    inline void Pair<Interval>::operator=(const Bisected<Interval>& bisected) {
        Pair<Interval&>(_first, _second) = bisected;
    }
        
    inline const Interval& Pair<Interval>::first() const {return _first;}
    
    inline const Interval& Pair<Interval>::second() const {return _second;}
}

#endif
