#ifdef SWIG
%typemap(javacode) JInterval %{

public static final Interval UNIT = new Interval(0.0, 1.0);
public static final Interval EMPTY = new Interval(Double.POSITIVE_INFINITY, Double.NEGATIVE_INFINITY);
public static final Interval WHOLE = new Interval(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);

%}

%typemap(cscode) JInterval %{

public static readonly Interval UNIT = new Interval(0.0, 1.0);
public static readonly Interval EMPTY = new Interval(System.Double.PositiveInfinity, System.Double.NegativeInfinity);
public static readonly Interval WHOLE = new Interval(System.Double.NegativeInfinity, System.Double.PositiveInfinity);

static public Interval operator-(Interval interval)
{
    return interval.negated();
}

static public Interval operator+(Interval firstInterval, Interval secondInterval)
{
    return firstInterval.sum(secondInterval);
}

static public Interval operator+(Interval interval, double value)
{
    return interval.sum(value);
}

static public Interval operator+(double value, Interval interval)
{
    return interval.sum(value);
}

static public Interval operator-(Interval firstInterval, Interval secondInterval)
{
    return firstInterval.difference(secondInterval);
}

static public Interval operator-(Interval interval, double value)
{
    return interval.difference(value);
}

static public Interval operator-(double value, Interval interval)
{
    return difference(value, interval);
}

static public Interval operator*(Interval firstInterval, Interval secondInterval)
{
    return firstInterval.product(secondInterval);
}

static public Interval operator*(Interval interval, double value)
{
    return interval.product(value);
}

static public Interval operator*(double value, Interval interval)
{
    return interval.product(value);
}

static public Interval operator/(Interval firstInterval, Interval secondInterval)
{
    return firstInterval.quotient(secondInterval);
}

static public Interval operator/(Interval interval, double value)
{
    return interval.quotient(value);
}

static public Interval operator/(double value, Interval interval)
{
    return quotient(value, interval);
}

static public implicit operator Interval(double value)
{
    return new Interval(value);
}

public override string ToString()
{
    return toString();
}

%}
#endif

#include "OpenSolid/Core/Interval.hpp"
#include "OpenSolid/Core/Zero.hpp"

#include <sstream>

#ifndef SWIG
using namespace opensolid;
#endif

class JInterval
{
private:
    Interval _interval;
public:
#ifndef SWIG
    inline
    JInterval(Interval interval) :
        _interval(interval) {
    }

    inline Interval
    interval() const {
        return _interval;
    }
#endif

    inline
    JInterval() :
        _interval() {
    }

    inline
    JInterval(double value) :
        _interval(value) {
    }
    
    inline
    JInterval(double lowerBound, double upperBound) :
        _interval(lowerBound, upperBound) {
    }
    
    inline double
    getLowerBound() const {
        return interval().lowerBound();
    }
    
    inline double
    getUpperBound() const {
        return interval().upperBound();
    }
    
    inline double
    getMedian() const {
        return interval().median();
    }
    
    inline double
    getWidth() const {
        return interval().width();
    }
    
    inline double
    randomValue() const {
        return interval().randomValue();
    }

    inline double
    clamp(double value) const {
        return interval().clamp(value);
    }
    
    inline double
    interpolated(double value) const {
        return interval().interpolated(value);
    }
    
    inline JInterval
    interpolated(JInterval other) const {
        return interval().interpolated(other.interval());
    }
    
    inline JInterval
    squared() const {
        return interval().squared();
    }
    
    inline bool
    isEmpty() const {
        return interval().isEmpty();
    }
    
    inline bool
    isSingleton() const {
        return interval().isSingleton();
    }

    inline JInterval
    hull(double value) const {
        return interval().hull(value);
    }
    
    inline JInterval
    hull(JInterval other) const {
        return interval().hull(other.interval());
    }
    
    inline JInterval
    intersection(JInterval other) const {
        return interval().intersection(other.interval());
    }
    
    inline bool
    contains(double value, double tolerance = 1e-12) const {
        return interval().contains(value, tolerance);
    }
    
    inline bool
    strictlyContains(double value, double tolerance = 1e-12) const {
        return interval().strictlyContains(value, tolerance);
    }

    inline bool
    contains(JInterval other, double tolerance = 1e-12) const {
        return interval().contains(other.interval(), tolerance);
    }
    
    inline bool
    strictlyContains(JInterval other, double tolerance = 1e-12) const {
        return interval().strictlyContains(other.interval(), tolerance);
    }

    inline bool
    overlaps(JInterval other, double tolerance = 1e-12) const {
        return interval().overlaps(other.interval(), tolerance);
    }
    
    inline bool
    strictlyOverlaps(JInterval other, double tolerance = 1e-12) const {
        return interval().strictlyOverlaps(other.interval(), tolerance);
    }
    
    static inline JInterval
    hull(double firstValue, double secondValue) {
        return Interval::hull(firstValue, secondValue);
    }

    inline std::string
    toString() const {
        std::stringstream stream;
        stream << interval();
        return stream.str();
    }
    
    inline bool
    isZero(double precision = 1e-12) const {
        return interval() == Zero(precision);
    }
    
    inline bool
    isLessThanZero(double precision = 1e-12) const {
        return interval() < Zero(precision);
    }
    
    inline bool
    isGreaterThanZero(double precision = 1e-12) const {
        return interval() > Zero(precision);
    }
    
    inline bool
    isLessThanOrEqualToZero(double precision = 1e-12) const {
        return interval() <= Zero(precision);
    }
    
    inline bool
    isGreaterThanOrEqualToZero(double precision = 1e-12) const {
        return interval() >= Zero(precision);
    }

    inline JInterval
    negated() const {
        return -interval();
    }

    inline JInterval
    sum(JInterval other) const {
        return interval() + other.interval();
    }

    inline JInterval
    sum(double value) const {
        return interval() + value;
    }
    
    inline JInterval
    difference(JInterval other) const {
        return interval() - other.interval();
    }
    
    inline JInterval
    difference(double value) const {
        return interval() - value;
    }

    static inline JInterval
    difference(double value, JInterval interval) {
        return value - interval.interval();
    }
    
    inline JInterval
    product(JInterval other) const {
        return interval() * other.interval();
    }
    
    inline JInterval
    product(double value) const {
        return interval() * value;
    }
    
    inline JInterval
    quotient(JInterval other) const {
        return interval() / other.interval();
    }
    
    inline JInterval
    quotient(double value) const {
        return interval() / value;
    }

    static inline JInterval
    quotient(double value, JInterval interval) {
        return value / interval.interval();
    }

    static inline JInterval
    abs(JInterval interval) {
        return opensolid::abs(interval.interval());
    }

    static inline JInterval
    sqrt(JInterval interval) {
        return opensolid::sqrt(interval.interval());
    }

    static inline JInterval
    sin(JInterval interval) {
        return opensolid::sin(interval.interval());
    }
    
    static inline JInterval
    cos(JInterval interval) {
        return opensolid::cos(interval.interval());
    }
    
    static inline JInterval
    tan(JInterval interval) {
        return opensolid::tan(interval.interval());
    }
    
    static inline JInterval
    asin(JInterval interval) {
        return opensolid::asin(interval.interval());
    }
    
    static inline JInterval
    acos(JInterval interval) {
        return opensolid::acos(interval.interval());
    }
    
    static inline JInterval
    atan(JInterval interval) {
        return opensolid::atan(interval.interval());
    }
    
    static inline JInterval
    atan2(JInterval yInterval, JInterval xInterval) {
        return opensolid::atan2(yInterval.interval(), xInterval.interval());
    }
    
    static inline JInterval
    exp(JInterval interval) {
        return opensolid::exp(interval.interval());
    }
    
    static inline JInterval
    log(JInterval interval) {
        return opensolid::log(interval.interval());
    }
    
    static inline JInterval
    pow(JInterval baseInterval, int exponentValue) {
        return opensolid::pow(baseInterval.interval(), exponentValue);
    }
    
    static inline JInterval
    pow(JInterval baseInterval, double exponentValue) {
        return opensolid::pow(baseInterval.interval(), exponentValue);
    }
    
    static inline JInterval
    pow(JInterval baseInterval, JInterval exponentInterval) {
        return opensolid::pow(baseInterval.interval(), exponentInterval.interval());
    }
};
