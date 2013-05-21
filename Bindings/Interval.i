%{
#include "Interval.hpp"   
%}

// Make special functions private
%csmethodmodifiers Interval::OpAdd "private";
%csmethodmodifiers Interval::OpSubtract "private";
%csmethodmodifiers Interval::OpMultiply "private";
%csmethodmodifiers Interval::OpDivide "private";
%csmethodmodifiers Interval::Stringify "private";
%csmethodmodifiers Interval::GetLowerBound "private";
%csmethodmodifiers Interval::GetUpperBound "private";
%csmethodmodifiers Interval::GetMedian "private";
%csmethodmodifiers Interval::GetWidth "private";
%csmethodmodifiers Interval::GetIsEmpty "private";
%csmethodmodifiers Interval::GetIsSingleton "private";

// Add arithmetic operators, implicit conversion from double, and ToString
%typemap(cscode) Interval %{
static public Interval operator+(Interval firstInterval, Interval secondInterval)
{
    return OpAdd(firstInterval, secondInterval);
}

static public Interval operator+(Interval interval, double value)
{
    return OpAdd(interval, value);
}

static public Interval operator+(double value, Interval interval)
{
    return OpAdd(value, interval);
}

static public Interval operator-(Interval firstInterval, Interval secondInterval)
{
    return OpSubtract(firstInterval, secondInterval);
}

static public Interval operator-(Interval interval, double value)
{
    return OpSubtract(interval, value);
}

static public Interval operator-(double value, Interval interval)
{
    return OpSubtract(value, interval);
}

static public Interval operator*(Interval firstInterval, Interval secondInterval)
{
    return OpMultiply(firstInterval, secondInterval);
}

static public Interval operator*(Interval interval, double value)
{
    return OpMultiply(interval, value);
}

static public Interval operator*(double value, Interval interval)
{
    return OpMultiply(value, interval);
}

static public Interval operator/(Interval firstInterval, Interval secondInterval)
{
    return OpDivide(firstInterval, secondInterval);
}

static public Interval operator/(Interval interval, double value)
{
    return OpDivide(interval, value);
}

static public Interval operator/(double value, Interval interval)
{
    return OpDivide(value, interval);
}

static public implicit operator Interval(double value)
{
    return new Interval(value);
}

public override string ToString()
{
    return Stringify(this);
}
%}

// Add properties
%attribute(Interval, double, LowerBound, GetLowerBound);
%attribute(Interval, double, UpperBound, GetUpperBound);
%attribute(Interval, double, Median, GetMedian);
%attribute(Interval, double, Width, GetWidth);
%attribute(Interval, double, IsEmpty, GetIsEmpty);
%attribute(Interval, double, IsSingleton, GetIsSingleton);

%include "Interval.hpp"

