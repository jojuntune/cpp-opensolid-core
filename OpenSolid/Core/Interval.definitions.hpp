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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Interval.declarations.hpp>
 
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <ostream>
#include <utility>

namespace opensolid
{
    class Interval :
        public Convertible<Interval>
    {
    private:
        double _lowerBound;
        double _upperBound;
    public:
        Interval();

        Interval(double value);
        
        Interval(double lowerBound, double upperBound);
        
        double
        lowerBound() const;
        
        double
        upperBound() const;
        
        double
        median() const;
        
        double
        width() const;
        
        double
        randomValue() const;

        double
        clamp(double value) const;
        
        Interval
        clamp(Interval interval) const;
        
        double
        interpolated(double value) const;
        
        Interval
        interpolated(Interval interval) const;
        
        Interval
        squared() const;
        
        bool
        isEmpty() const;
        
        bool
        isSingleton() const;
        
        std::pair<Interval, Interval>
        bisected() const;
        
        Interval
        hull(Interval interval) const;
        
        Interval
        intersection(Interval interval) const;
        
        bool
        contains(double value, double tolerance = 1e-12) const;
        
        bool
        strictlyContains(double value, double tolerance = 1e-12) const;

        bool
        contains(Interval interval, double tolerance = 1e-12) const;
        
        bool
        strictlyContains(Interval interval, double tolerance = 1e-12) const;

        bool
        overlaps(Interval interval, double tolerance = 1e-12) const;
        
        bool
        strictlyOverlaps(Interval interval, double tolerance = 1e-12) const;
        
        Interval&
        operator+=(double value);
        
        Interval&
        operator+=(Interval interval);
        
        Interval&
        operator-=(double value);
        
        Interval&
        operator-=(Interval interval);
        
        Interval&
        operator*=(double value);
        
        Interval&
        operator/=(double value);
        
        OPENSOLID_CORE_EXPORT Interval&
        operator*=(Interval interval);
        
        OPENSOLID_CORE_EXPORT Interval&
        operator/=(Interval interval);
        
        static Interval
        Unit();
        
        static Interval
        Hull(double firstValue, double secondValue);
        
        static Interval
        Empty();
        
        static Interval
        Whole();
    };

    double
    infinity();

    bool
    operator==(double value, Interval interval);
    
    bool
    operator==(Interval interval, double value);
    
    bool
    operator==(Interval firstInterval, Interval secondInterval);

    bool
    operator!=(double value, Interval interval);
    
    bool
    operator!=(Interval interval, double value);
    
    bool
    operator!=(Interval firstInterval, Interval secondInterval);

    bool
    operator<(double value, Interval interval);
    
    bool
    operator<(Interval interval, double value);
    
    bool
    operator<(Interval firstInterval, Interval secondInterval);

    bool
    operator>(double value, Interval interval);
    
    bool
    operator>(Interval interval, double value);
    
    bool
    operator>(Interval firstInterval, Interval secondInterval);

    bool
    operator<=(double value, Interval interval);
    
    bool
    operator<=(Interval interval, double value);
    
    bool
    operator<=(Interval firstInterval, Interval secondInterval);

    bool
    operator>=(double value, Interval interval);
    
    bool
    operator>=(Interval interval, double value);
    
    bool
    operator>=(Interval firstInterval, Interval secondInterval);
    
    bool
    operator==(Interval interval, Zero zero);
    
    bool
    operator!=(Interval interval, Zero zero);
    
    bool
    operator<(Interval interval, Zero zero);
    
    bool
    operator>(Interval interval, Zero zero);
    
    bool
    operator<=(Interval interval, Zero zero);
    
    bool
    operator>=(Interval interval, Zero zero);
        
    Interval
    operator-(Interval argument);

    Interval
    operator+(double value, Interval interval);
    
    Interval
    operator+(Interval interval, double value);
    
    Interval
    operator+(Interval firstInterval, Interval secondInterval);

    Interval
    operator-(double value, Interval interval);
    
    Interval
    operator-(Interval interval, double value);
    
    Interval
    operator-(Interval firstInterval, Interval secondInterval);

    Interval
    operator*(double value, Interval interval);
    
    Interval
    operator*(Interval interval, double value);
    
    OPENSOLID_CORE_EXPORT Interval
    operator*(Interval firstInterval, Interval secondInterval);

    Interval
    operator/(Interval interval, double value);

    OPENSOLID_CORE_EXPORT Interval
    operator/(double value, Interval interval);

    OPENSOLID_CORE_EXPORT Interval
    operator/(Interval firstInterval, Interval secondInterval);

    Interval
    abs(Interval interval);

    Interval
    sqrt(Interval interval);

    OPENSOLID_CORE_EXPORT Interval
    sin(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    cos(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    tan(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    asin(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    acos(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    atan(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    atan2(Interval yInterval, Interval xInterval);
    
    OPENSOLID_CORE_EXPORT Interval
    exp(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    log(Interval interval);
    
    OPENSOLID_CORE_EXPORT Interval
    pow(Interval baseInterval, int exponentValue);
    
    OPENSOLID_CORE_EXPORT Interval
    pow(Interval baseInterval, double exponentValue);
    
    OPENSOLID_CORE_EXPORT Interval
    pow(Interval baseInterval, Interval exponentInterval);

    Interval
    conj(Interval interval);
    
    Interval
    real(Interval interval);
    
    Interval
    imag(Interval interval);
    
    Interval
    abs2(Interval interval);

    OPENSOLID_CORE_EXPORT std::ostream&
    operator<<(std::ostream& stream, Interval interval);
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct BoundsType<Interval>
    {
        typedef Interval Type;
    };

    template <>
    struct BoundsFunction<Interval>
    {
        Interval
        operator()(Interval interval) const;
    };
}
