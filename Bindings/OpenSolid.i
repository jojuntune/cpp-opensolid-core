%module OpenSolid

%{
    #include "OpenSolid/Core/Interval.hpp"  

    #include <sstream>
%}

// Declare special member functions as private so they can be wrapped with public functions
// following normal C# conventions
%csmethodmodifiers Add "private";
%csmethodmodifiers Sub "private";
%csmethodmodifiers Mul "private";
%csmethodmodifiers Div "private";
%csmethodmodifiers Str "private";

// Declare special functions and operators wrapping the above special functions
%typemap(cscode) Interval %{
    public override string ToString()
    {
        return Str();
    }

    static public Interval operator+(Interval firstInterval, Interval secondInterval)
    {
        return firstInterval.Add(secondInterval);
    }

    static public Interval operator+(Interval interval, double value)
    {
        return interval.Add(value);
    }

    static public Interval operator+(double value, Interval interval)
    {
        return interval.Add(value);
    }
%}

%include "std_string.i"

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
        
        double
        LowerBound() const {
            return _interval.lowerBound();
        }
        
        double
        UpperBound() const {
            return _interval.upperBound();
        }
        
        double
        Median() const {
            return _interval.median();
        }
        
        double
        Width() const {
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
        
        bool
        IsEmpty() const {
            return _interval.isEmpty();
        }
        
        bool
        IsSingleton() const {
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
        
        Interval
        Add(double value) const {
            return _interval + value;
        }
        
        Interval
        Add(Interval interval) const {
            return _interval + interval._interval;
        }
        
        Interval
        Sub(double value) const {
            return _interval - value;
        }
        
        Interval
        Sub(Interval interval) const {
            return _interval - interval._interval;
        }
        
        Interval
        Mul(double value) const {
            return _interval * value;
        }
        
        Interval
        Div(double value) const {
            return _interval / value;
        }
        
        Interval
        Mul(Interval interval) const {
            return _interval * interval._interval;
        }
        
        Interval
        Div(Interval interval) const {
            return _interval / interval._interval;
        }

        std::string
        Str() const {
            std::stringstream stream;
            stream << _interval;
            return stream.str();
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
    };
%}

