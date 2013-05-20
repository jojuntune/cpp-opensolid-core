// Include OpenSolid Interval header
%{
    #include "OpenSolid/Core/Interval.hpp"  

    #include <sstream>
%}

// Make special functions private
%csmethodmodifiers Interval::Add "private";
%csmethodmodifiers Interval::Subtract "private";
%csmethodmodifiers Interval::Multiply "private";
%csmethodmodifiers Interval::Divide "private";
%csmethodmodifiers Interval::Stringify "private";

// Add arithmetic operators, implicit conversion from double, and ToString
%typemap(cscode) Interval %{
    static public Interval operator+(Interval firstInterval, Interval secondInterval)
    {
        return Add(firstInterval, secondInterval);
    }

    static public Interval operator+(Interval interval, double value)
    {
        return Add(interval, value);
    }

    static public Interval operator+(double value, Interval interval)
    {
        return Add(value, interval);
    }

    static public Interval operator-(Interval firstInterval, Interval secondInterval)
    {
        return Subtract(firstInterval, secondInterval);
    }

    static public Interval operator-(Interval interval, double value)
    {
        return Subtract(interval, value);
    }

    static public Interval operator-(double value, Interval interval)
    {
        return Subtract(value, interval);
    }

    static public Interval operator*(Interval firstInterval, Interval secondInterval)
    {
        return Multiply(firstInterval, secondInterval);
    }

    static public Interval operator*(Interval interval, double value)
    {
        return Multiply(interval, value);
    }

    static public Interval operator*(double value, Interval interval)
    {
        return Multiply(value, interval);
    }

    static public Interval operator/(Interval firstInterval, Interval secondInterval)
    {
        return Divide(firstInterval, secondInterval);
    }

    static public Interval operator/(Interval interval, double value)
    {
        return Divide(interval, value);
    }

    static public Interval operator/(double value, Interval interval)
    {
        return Divide(value, interval);
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

// Make property getters private
%csmethodmodifiers Interval::GetLowerBound "private";
%csmethodmodifiers Interval::GetUpperBound "private";
%csmethodmodifiers Interval::GetMedian "private";
%csmethodmodifiers Interval::GetWidth "private";
%csmethodmodifiers Interval::GetIsEmpty "private";
%csmethodmodifiers Interval::GetIsSingleton "private";

// Add properties
%attribute(Interval, double, LowerBound, GetLowerBound);
%attribute(Interval, double, UpperBound, GetUpperBound);
%attribute(Interval, double, Median, GetMedian);
%attribute(Interval, double, Width, GetWidth);
%attribute(Interval, double, IsEmpty, GetIsEmpty);
%attribute(Interval, double, IsSingleton, GetIsSingleton);


%inline %{
    class Interval
    {
    private:
        opensolid::Interval _interval;

        Interval(opensolid::Interval interval) :
            _interval(interval) {
        }
    public:
        Interval() :
            _interval() {
        }

        Interval(double value) :
            _interval(value) {
        }
        
        Interval(double lowerBound, double upperBound) :
            _interval(lowerBound, upperBound) {
        }
        
        // Will be converted to LowerBound property
        double
        GetLowerBound() const {
            return _interval.lowerBound();
        }
        
        // Will be converted to UpperBound property
        double
        GetUpperBound() const {
            return _interval.upperBound();
        }
        
        // Will be converted to Median property
        double
        GetMedian() const {
            return _interval.median();
        }
        
        // Will be converted to Width property
        double
        GetWidth() const {
            return _interval.width();
        }
        
        double
        RandomValue() const {
            return _interval.randomValue();
        }

        double
        Clamp(double value) const {
            return _interval.clamp(value);
        }
        
        Interval
        Clamp(Interval interval) const {
            return _interval.clamp(interval._interval);
        }
        
        double
        Interpolated(double value) const {
            return _interval.interpolated(value);
        }
        
        Interval
        Interpolated(Interval interval) const {
            return _interval.interpolated(interval._interval);
        }
        
        Interval
        Squared() const {
            return _interval.squared();
        }
        
        // Will be converted to IsEmpty property
        bool
        GetIsEmpty() const {
            return _interval.isEmpty();
        }
        
        // Will be converted to IsSingleton property
        bool
        GetIsSingleton() const {
            return _interval.isSingleton();
        }
        
        Interval
        Hull(Interval interval) const {
            return _interval.hull(interval._interval);
        }
        
        Interval
        Intersection(Interval interval) const {
            return _interval.intersection(interval._interval);
        }
        
        bool
        Contains(double value, double tolerance = 1e-12) const {
            return _interval.contains(value, tolerance);
        }
        
        bool
        StrictlyContains(double value, double tolerance = 1e-12) const {
            return _interval.strictlyContains(value, tolerance);
        }

        bool
        Contains(Interval interval, double tolerance = 1e-12) const {
            return _interval.contains(interval._interval, tolerance);
        }
        
        bool
        StrictlyContains(Interval interval, double tolerance = 1e-12) const {
            return _interval.strictlyContains(interval._interval, tolerance);
        }

        bool
        Overlaps(Interval interval, double tolerance = 1e-12) const {
            return _interval.overlaps(interval._interval, tolerance);
        }
        
        bool
        StrictlyOverlaps(Interval interval, double tolerance = 1e-12) const {
            return _interval.strictlyOverlaps(interval._interval, tolerance);
        }
        
        static Interval
        Unit() {
            return opensolid::Interval::Unit();
        }
        
        static Interval
        Hull(double firstValue, double secondValue) {
            return opensolid::Interval::Hull(firstValue, secondValue);
        }
        
        static Interval
        Empty() {
            return opensolid::Interval::Empty();
        }
        
        static Interval
        Whole() {
            return opensolid::Interval::Whole();
        }
        
        // Will be converted to operator+
        static Interval
        Add(Interval firstInterval, Interval secondInterval) {
            return firstInterval._interval + secondInterval._interval;
        }
        
        // Will be converted to operator+
        static Interval
        Add(Interval interval, double value) {
            return interval._interval + value;
        }

        // Will be converted to operator+
        static Interval
        Add(double value, Interval interval) {
            return value + interval._interval;
        }
        
        // Will be converted to operator-
        static Interval
        Subtract(Interval firstInterval, Interval secondInterval) {
            return firstInterval._interval - secondInterval._interval;
        }
        
        // Will be converted to operator-
        static Interval
        Subtract(Interval interval, double value) {
            return interval._interval - value;
        }

        // Will be converted to operator-
        static Interval
        Subtract(double value, Interval interval) {
            return value - interval._interval;
        }
        
        // Will be converted to operator*
        static Interval
        Multiply(Interval firstInterval, Interval secondInterval) {
            return firstInterval._interval * secondInterval._interval;
        }
        
        // Will be converted to operator*
        static Interval
        Multiply(Interval interval, double value) {
            return interval._interval * value;
        }

        // Will be converted to operator*
        static Interval
        Multiply(double value, Interval interval) {
            return value * interval._interval;
        }
        
        // Will be converted to operator/
        static Interval
        Divide(Interval firstInterval, Interval secondInterval) {
            return firstInterval._interval / secondInterval._interval;
        }
        
        // Will be converted to operator/
        static Interval
        Divide(Interval interval, double value) {
            return interval._interval / value;
        }

        // Will be converted to operator/
        static Interval
        Divide(double value, Interval interval) {
            return value / interval._interval;
        }

        // Will be converted to ToString
        static std::string
        Stringify(Interval interval) {
            std::stringstream stream;
            stream << interval._interval;
            return stream.str();
        }
    };
%}
