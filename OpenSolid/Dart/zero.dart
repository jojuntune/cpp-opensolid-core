part of opensolid;

class Zero extends NativeFieldWrapperClass1 {
    _init(double precision) native 'zero_init';

    Zero([double precision=1e-12]) => _init(precision);

    double precision() native 'zero_precision';

    bool _equalsDouble(double value) native 'zero_equals_double';
    bool _equalsInterval(Interval value) native 'zero_equals_interval';

    bool operator ==(other) {
        if (other is num) {
            return _equalsDouble(other.toDouble())
        } else if (other is Interval) {
            return _equalsInterval(other)
        } else {
            return false;
        }
    }

    bool _lessThanDouble(double value) native 'zero_less_than_double';
    bool _lessThanInterval(Interval value) native 'zero_less_than_interval';

    bool operator <(other) {
        if (other is num) {
            return _lessThanDouble(other.toDouble())
        } else if (other is Interval) {
            return _lessThanInterval(other)
        } else {
            return false;
        }
    }

    bool _greaterThanDouble(double value) native 'zero_greater_than_double';
    bool _greaterThanInterval(Interval value) native 'zero_greater_than_interval';
    
    bool operator >(other) {
        if (other is num) {
            return _greaterThanDouble(other.toDouble())
        } else if (other is Interval) {
            return _greaterThanInterval(other)
        } else {
            return false;
        }
    }

    bool _lessThanOrEqualToDouble(double value) native 'zero_less_than_or_equal_to_double';
    bool _lessThanOrEqualToInterval(Interval value) native 'zero_less_than_or_equal_to_interval';

    bool operator <=(other) {
        if (other is num) {
            return _lessThanOrEqualToDouble(other.toDouble())
        } else if (other is Interval) {
            return _lessThanOrEqualToInterval(other)
        } else {
            return false;
        }
    }

    bool _greaterThanOrEqualToDouble(double value) native 'zero_greater_than_or_equal_to_double';
    bool _greaterThanOrEqualToInterval(Interval value) native 'zero_greater_than_or_equal_to_interval';
    
    bool operator >=(other) {
        if (other is num) {
            return _greaterThanOrEqualToDouble(other.toDouble())
        } else if (other is Interval) {
            return _greaterThanOrEqualToInterval(other)
        } else {
            return false;
        }
    }
}
