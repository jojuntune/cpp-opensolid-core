// Include OpenSolid Zero header
%{
    #include "OpenSolid/Core/Zero.hpp"  
%}

// Make special functions private
%csmethodmodifiers Zero::Equal "private";
%csmethodmodifiers Zero::NotEqual "private";
%csmethodmodifiers Zero::LessThan "private";
%csmethodmodifiers Zero::GreaterThan "private";
%csmethodmodifiers Zero::LessOrEqual "private";
%csmethodmodifiers Zero::GreaterOrEqual "private";

// Add arithmetic operators
%typemap(cscode) Zero %{
    static public bool operator==(double value, Zero zero)
    {
        return Equal(value, zero);
    }

    static public bool operator!=(double value, Zero zero)
    {
        return NotEqual(value, zero);
    }

    static public bool operator<(double value, Zero zero)
    {
        return LessThan(value, zero);
    }

    static public bool operator>(double value, Zero zero)
    {
        return GreaterThan(value, zero);
    }

    static public bool operator<=(double value, Zero zero)
    {
        return LessOrEqual(value, zero);
    }

    static public bool operator>=(double value, Zero zero)
    {
        return GreaterOrEqual(value, zero);
    }
%}

// Make property getters private
%csmethodmodifiers Zero::GetPrecision "private";

// Add properties
%attribute(Zero, double, Precision, GetPrecision);

%inline %{
    class Zero
    {
    private:
        opensolid::Zero _zero;

        Zero(opensolid::Zero zero) :
            _zero(zero) {
        }
    public:
        Zero(double precision = 1e-12) :
            _zero(precision) {
        }

        // Will be converted to Precision property
        double
        GetPrecision() const {
            return _zero.precision();
        }

        // Will be converted to operator==
        static bool
        Equal(double value, Zero zero) {
            return value == zero._zero;
        }
    
        // Will be converted to operator!=
        static bool
        NotEqual(double value, Zero zero) {
            return value != zero._zero;
        }
        
        // Will be converted to operator<
        static bool
        LessThan(double value, Zero zero) {
            return value < zero._zero;
        }
        
        // Will be converted to operator>
        static bool
        GreaterThan(double value, Zero zero) {
            return value > zero._zero;
        }
        
        // Will be converted to operator<=
        static bool
        LessOrEqual(double value, Zero zero) {
            return value <= zero._zero;
        }
        
        // Will be converted to operator>=
        static bool
        GreaterOrEqual(double value, Zero zero) {
            return value >= zero._zero;
        }
    };
%}
