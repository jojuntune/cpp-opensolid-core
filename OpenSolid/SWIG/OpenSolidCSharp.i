%module OpenSolidCSharp

// Rename functionName to FunctionName
%rename("%(camelcase)s", %$isfunction) "";

// Declare special functions and operators
%typemap(cscode) Interval %{
    public override String ToString() {
        return Str();
    }

    static public Interval operator+(Interval firstInterval, Interval secondInterval) {
        return firstInterval.Add(secondInterval);
    }

    static public Interval operator+(Interval interval, double value) {
        return interval.Add(value);
    }
%}

// Include OpenSolid common interface
%include "common.i"
