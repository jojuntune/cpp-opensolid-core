part of opensolid;

class Zero extends NativeFieldWrapperClass2 {
    void _init(double precision) native 'zeroInit';
    bool _equalsDouble(double value) native 'zeroEqualsDouble';
    bool _equalsInterval(Interval value) native 'zeroEqualsInterval';
    bool _lessThanDouble(double value) native 'zeroLessThanDouble';
    bool _lessThanInterval(Interval value) native 'zeroLessThanInterval';
    bool _greaterThanDouble(double value) native 'zeroGreaterThanDouble';
    bool _greaterThanInterval(Interval value) native 'zeroGreaterThanInterval';
    bool _lessThanOrEqualToDouble(double value) native 'zeroLessThanOrEqualToDouble';
    bool _lessThanOrEqualToInterval(Interval value) native 'zeroLessThanOrEqualToInterval';
    bool _greaterThanOrEqualToDouble(double value) native 'zeroGreaterThanOrEqualToDouble';
    bool _greaterThanOrEqualToInterval(Interval value) native 'zeroGreaterThanOrEqualToInterval';

    Zero([double precision=1e-12]) {
        _init(precision);
    }

    double get precision native 'zeroPrecision';

    bool operator ==(var other) {
        if (other is num) {
            return _equalsDouble(other.toDouble())
        } else if (other is Interval) {
            return _equalsInterval(other)
        } else {
            return false;
        }
    }

    bool operator <(var other) {
        if (other is num) {
            return _lessThanDouble(other.toDouble())
        } else if (other is Interval) {
            return _lessThanInterval(other)
        } else {
            return false;
        }
    }
    
    bool operator >(var other) {
        if (other is num) {
            return _greaterThanDouble(other.toDouble())
        } else if (other is Interval) {
            return _greaterThanInterval(other)
        } else {
            return false;
        }
    }

    bool operator <=(var other) {
        if (other is num) {
            return _lessThanOrEqualToDouble(other.toDouble())
        } else if (other is Interval) {
            return _lessThanOrEqualToInterval(other)
        } else {
            return false;
        }
    }

    bool operator >=(var other) {
        if (other is num) {
            return _greaterThanOrEqualToDouble(other.toDouble())
        } else if (other is Interval) {
            return _greaterThanOrEqualToInterval(other)
        } else {
            return false;
        }
    }
}
