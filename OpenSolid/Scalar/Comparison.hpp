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

#ifndef OPENSOLID__COMPARISON_HPP
#define OPENSOLID__COMPARISON_HPP

#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{
    class Comparison
    {
    private:
        Interval _interval;
    public:
        Comparison(double lower, double upper);
        const Interval& interval() const;
    };

    class Zero : public Comparison
    {
    public:
        Zero(double precision = 1e-12);
    };

    class One : public Comparison
    {
    public:
        One(double precision = 1e-12);
    };

    class Approx : public Comparison
    {
    public:
        Approx(double value, double precision = 1e-12);
        Approx(const Interval& value, double precision = 1e-12);
    };

    bool operator==(double value, const Comparison& comparison);
    bool operator!=(double value, const Comparison& comparison);
    bool operator<(double value, const Comparison& comparison);
    bool operator>(double value, const Comparison& comparison);
    bool operator<=(double value, const Comparison& comparison);
    bool operator>=(double value, const Comparison& comparison);

    bool operator==(const Interval& value, const Comparison& comparison);
    bool operator!=(const Interval& value, const Comparison& comparison);
    bool operator<(const Interval& value, const Comparison& comparison);
    bool operator>(const Interval& value, const Comparison& comparison);
    bool operator<=(const Interval& value, const Comparison& comparison);
    bool operator>=(const Interval& value, const Comparison& comparison);

    Comparison operator-(const Comparison& argument);
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Comparison::Comparison(double lower, double upper) : _interval(lower, upper) {}

    inline const Interval& Comparison::interval() const {return _interval;}

    inline Zero::Zero(double precision) : Comparison(-precision, precision) {}

    inline One::One(double precision) : Comparison(1 - precision, 1 + precision) {}

    inline Approx::Approx(double value, double precision) :
        Comparison(value - precision, value + precision) {}

    inline Approx::Approx(const Interval& value, double precision) :
        Comparison(value.lower() - precision, value.upper() + precision) {}

    inline bool operator==(double value, const Comparison& comparison) {
        return comparison.interval().contains(value);
    }

    inline bool operator!=(double value, const Comparison& comparison) {
        return !comparison.interval().contains(value);
    }

    inline bool operator<(double value, const Comparison& comparison) {
        return value < comparison.interval().lower();
    }

    inline bool operator>(double value, const Comparison& comparison) {
        return value > comparison.interval().upper();
    }

    inline bool operator<=(double value, const Comparison& comparison) {
        return value <= comparison.interval().upper();
    }

    inline bool operator>=(double value, const Comparison& comparison) {
        return value >= comparison.interval().lower();
    }

    inline bool operator==(const Interval& value, const Comparison& comparison) {
        return comparison.interval().contains(value);
    }

    inline bool operator!=(const Interval& value, const Comparison& comparison) {
        return !comparison.interval().overlaps(value);
    }

    inline bool operator<(const Interval& value, const Comparison& comparison) {
        return value.upper() < comparison.interval().lower();
    }

    inline bool operator>(const Interval& value, const Comparison& comparison) {
        return value.lower() > comparison.interval().upper();
    }

    inline bool operator<=(const Interval& value, const Comparison& comparison) {
        return value.upper() <= comparison.interval().upper();
    }

    inline bool operator>=(const Interval& value, const Comparison& comparison) {
        return value.lower() >= comparison.interval().lower();
    }

    inline Comparison operator-(const Comparison& argument) {
        return Comparison(-argument.interval().upper(), -argument.interval().lower());
    }
}

#endif
