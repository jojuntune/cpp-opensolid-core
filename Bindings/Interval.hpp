#include "OpenSolid/Core/Interval.hpp"
#include "OpenSolid/Core/Zero.hpp"

#include <sstream>

class Interval
{
private:
    opensolid::Interval _opensolidInterval;
public:
    inline Interval() :
        _opensolidInterval() {
    }

#ifndef SWIG
    inline Interval(opensolid::Interval opensolidInterval) :
        _opensolidInterval(opensolidInterval) {
    }
#endif

    inline Interval(double value) :
        _opensolidInterval(value) {
    }
    
    inline Interval(double lowerBound, double upperBound) :
        _opensolidInterval(lowerBound, upperBound) {
    }

#ifndef SWIG
    inline opensolid::Interval opensolidInterval() const {
        return _opensolidInterval;
    }
#endif
    
    // Will be converted to LowerBound property
    inline double
    GetLowerBound() const {
        return opensolidInterval().lowerBound();
    }
    
    // Will be converted to UpperBound property
    inline double
    GetUpperBound() const {
        return opensolidInterval().upperBound();
    }
    
    // Will be converted to Median property
    inline double
    GetMedian() const {
        return opensolidInterval().median();
    }
    
    // Will be converted to Width property
    inline double
    GetWidth() const {
        return opensolidInterval().width();
    }
    
    inline double
    RandomValue() const {
        return opensolidInterval().randomValue();
    }

    inline double
    Clamp(double value) const {
        return opensolidInterval().clamp(value);
    }
    
    inline Interval
    Clamp(Interval interval) const {
        return opensolidInterval().clamp(interval.opensolidInterval());
    }
    
    inline double
    Interpolated(double value) const {
        return opensolidInterval().interpolated(value);
    }
    
    inline Interval
    Interpolated(Interval interval) const {
        return opensolidInterval().interpolated(interval.opensolidInterval());
    }
    
    inline Interval
    Squared() const {
        return opensolidInterval().squared();
    }
    
    // Will be converted to IsEmpty property
    inline bool
    GetIsEmpty() const {
        return opensolidInterval().isEmpty();
    }
    
    // Will be converted to IsSingleton property
    inline bool
    GetIsSingleton() const {
        return opensolidInterval().isSingleton();
    }
    
    inline Interval
    Hull(Interval interval) const {
        return opensolidInterval().hull(interval.opensolidInterval());
    }
    
    inline Interval
    Intersection(Interval interval) const {
        return opensolidInterval().intersection(interval.opensolidInterval());
    }
    
    inline bool
    Contains(double value, double tolerance = 1e-12) const {
        return opensolidInterval().contains(value, tolerance);
    }
    
    inline bool
    StrictlyContains(double value, double tolerance = 1e-12) const {
        return opensolidInterval().strictlyContains(value, tolerance);
    }

    inline bool
    Contains(Interval interval, double tolerance = 1e-12) const {
        return opensolidInterval().contains(interval.opensolidInterval(), tolerance);
    }
    
    inline bool
    StrictlyContains(Interval interval, double tolerance = 1e-12) const {
        return opensolidInterval().strictlyContains(interval.opensolidInterval(), tolerance);
    }

    inline bool
    Overlaps(Interval interval, double tolerance = 1e-12) const {
        return opensolidInterval().overlaps(interval.opensolidInterval(), tolerance);
    }
    
    inline bool
    StrictlyOverlaps(Interval interval, double tolerance = 1e-12) const {
        return opensolidInterval().strictlyOverlaps(interval.opensolidInterval(), tolerance);
    }
    
    inline bool
    IsZero(double precision = 1e-12) const {
        return opensolidInterval() == opensolid::Zero(precision);
    }
    
    inline bool
    IsNotZero(double precision = 1e-12) const {
        return opensolidInterval() != opensolid::Zero(precision);
    }
    
    inline bool
    IsLessThanZero(double precision = 1e-12) const {
        return opensolidInterval() < opensolid::Zero(precision);
    }
    
    inline bool
    IsGreaterThanZero(double precision = 1e-12) const {
        return opensolidInterval() > opensolid::Zero(precision);
    }
    
    inline bool
    IsLessThanOrEqualToZero(double precision = 1e-12) const {
        return opensolidInterval() <= opensolid::Zero(precision);
    }
    
    inline bool
    IsGreaterThanOrEqualToZero(double precision = 1e-12) const {
        return opensolidInterval() >= opensolid::Zero(precision);
    }
    
    inline static Interval
    Unit() {
        return opensolid::Interval::Unit();
    }
    
    inline static Interval
    Hull(double firstValue, double secondValue) {
        return opensolid::Interval::Hull(firstValue, secondValue);
    }
    
    inline static Interval
    Empty() {
        return opensolid::Interval::Empty();
    }
    
    inline static Interval
    Whole() {
        return opensolid::Interval::Whole();
    }

    // Will be converted to unary operator-
    inline static Interval
    OpNegate(Interval interval) {
        return -interval.opensolidInterval();
    }
    
    // Will be converted to operator+
    inline static Interval
    OpAdd(Interval firstInterval, Interval secondInterval) {
        return firstInterval.opensolidInterval() + secondInterval.opensolidInterval();
    }
    
    // Will be converted to operator+
    inline static Interval
    OpAdd(Interval interval, double value) {
        return interval.opensolidInterval() + value;
    }

    // Will be converted to operator+
    inline static Interval
    OpAdd(double value, Interval interval) {
        return value + interval.opensolidInterval();
    }
    
    // Will be converted to operator-
    inline static Interval
    OpSubtract(Interval firstInterval, Interval secondInterval) {
        return firstInterval.opensolidInterval() - secondInterval.opensolidInterval();
    }
    
    // Will be converted to operator-
    inline static Interval
    OpSubtract(Interval interval, double value) {
        return interval.opensolidInterval() - value;
    }

    // Will be converted to operator-
    inline static Interval
    OpSubtract(double value, Interval interval) {
        return value - interval.opensolidInterval();
    }
    
    // Will be converted to operator*
    inline static Interval
    OpMultiply(Interval firstInterval, Interval secondInterval) {
        return firstInterval.opensolidInterval() * secondInterval.opensolidInterval();
    }
    
    // Will be converted to operator*
    inline static Interval
    OpMultiply(Interval interval, double value) {
        return interval.opensolidInterval() * value;
    }

    // Will be converted to operator*
    inline static Interval
    OpMultiply(double value, Interval interval) {
        return value * interval.opensolidInterval();
    }
    
    // Will be converted to operator/
    inline static Interval
    OpDivide(Interval firstInterval, Interval secondInterval) {
        return firstInterval.opensolidInterval() / secondInterval.opensolidInterval();
    }
    
    // Will be converted to operator/
    inline static Interval
    OpDivide(Interval interval, double value) {
        return interval.opensolidInterval() / value;
    }

    // Will be converted to operator/
    inline static Interval
    OpDivide(double value, Interval interval) {
        return value / interval.opensolidInterval();
    }

    // Will be converted to ToString
    inline static std::string
    Stringify(Interval interval) {
        std::stringstream stream;
        stream << interval.opensolidInterval();
        return stream.str();
    }

    inline static Interval
    Abs(Interval interval) {
        return abs(interval.opensolidInterval());
    }

    inline static Interval
    Sqrt(Interval interval) {
        return sqrt(interval.opensolidInterval());
    }

    inline static Interval
    Sin(Interval interval) {
        return sin(interval.opensolidInterval());
    }
    
    inline static Interval
    Cos(Interval interval) {
        return cos(interval.opensolidInterval());
    }
    
    inline static Interval
    Tan(Interval interval) {
        return tan(interval.opensolidInterval());
    }
    
    inline static Interval
    Asin(Interval interval) {
        return asin(interval.opensolidInterval());
    }
    
    inline static Interval
    Acos(Interval interval) {
        return acos(interval.opensolidInterval());
    }
    
    inline static Interval
    Atan(Interval interval) {
        return atan(interval.opensolidInterval());
    }
    
    inline static Interval
    Atan2(Interval yInterval, Interval xInterval) {
        return atan2(yInterval.opensolidInterval(), xInterval.opensolidInterval());
    }
    
    inline static Interval
    Exp(Interval interval) {
        return exp(interval.opensolidInterval());
    }
    
    inline static Interval
    Log(Interval interval) {
        return log(interval.opensolidInterval());
    }
    
    inline static Interval
    Pow(Interval baseInterval, int exponentValue) {
        return pow(baseInterval.opensolidInterval(), exponentValue);
    }
    
    inline static Interval
    Pow(Interval baseInterval, double exponentValue) {
        return pow(baseInterval.opensolidInterval(), exponentValue);
    }
    
    inline static Interval
    Pow(Interval baseInterval, Interval exponentInterval) {
        return pow(baseInterval.opensolidInterval(), exponentInterval.opensolidInterval());
    }
};
