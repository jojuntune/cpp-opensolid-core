%{
    #include "OpenSolid/Core/Interval.hpp"  

    #include <sstream>
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
        lowerBound() const {
            return _interval.lowerBound();
        }
        
        double
        upperBound() const {
            return _interval.upperBound();
        }
        
        double
        median() const {
            return _interval.median();
        }
        
        double
        width() const {
            return _interval.width();
        }
        
        double
        randomValue() const {
            return _interval.randomValue();
        }

        double
        clamp(double value) const {
            return _interval.clamp(value);
        }
        
        Interval
        clamp(Interval interval) const {
            return _interval.clamp(interval._interval);
        }
        
        double
        interpolated(double value) const {
            return _interval.interpolated(value);
        }
        
        Interval
        interpolated(Interval interval) const {
            return _interval.interpolated(interval._interval);
        }
        
        Interval
        squared() const {
            return _interval.squared();
        }
        
        bool
        isEmpty() const {
            return _interval.isEmpty();
        }
        
        bool
        isSingleton() const {
            return _interval.isSingleton();
        }
        
        Interval
        hull(Interval interval) const {
            return _interval.hull(interval._interval);
        }
        
        Interval
        intersection(Interval interval) const {
            return _interval.intersection(interval._interval);
        }
        
        bool
        contains(double value, double tolerance = 1e-12) const {
            return _interval.contains(value, tolerance);
        }
        
        bool
        strictlyContains(double value, double tolerance = 1e-12) const {
            return _interval.strictlyContains(value, tolerance);
        }

        bool
        contains(Interval interval, double tolerance = 1e-12) const {
            return _interval.contains(interval._interval, tolerance);
        }
        
        bool
        strictlyContains(Interval interval, double tolerance = 1e-12) const {
            return _interval.strictlyContains(interval._interval, tolerance);
        }

        bool
        overlaps(Interval interval, double tolerance = 1e-12) const {
            return _interval.overlaps(interval._interval, tolerance);
        }
        
        bool
        strictlyOverlaps(Interval interval, double tolerance = 1e-12) const {
            return _interval.strictlyOverlaps(interval._interval, tolerance);
        }
        
        Interval
        add(double value) const {
            return _interval + value;
        }
        
        Interval
        add(Interval interval) const {
            return _interval + interval._interval;
        }
        
        Interval
        sub(double value) const {
            return _interval - value;
        }
        
        Interval
        sub(Interval interval) const {
            return _interval - interval._interval;
        }
        
        Interval
        mul(double value) const {
            return _interval * value;
        }
        
        Interval
        div(double value) const {
            return _interval / value;
        }
        
        Interval
        mul(Interval interval) const {
            return _interval * interval._interval;
        }
        
        Interval
        div(Interval interval) const {
            return _interval / interval._interval;
        }

        std::string
        str() const {
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
