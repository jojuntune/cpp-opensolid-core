%module opensolid_python

// Rename functionName to function_name
%rename("%(undercase)s", %$isfunction) "";

// Declare special operator functions
%extend Interval {
    %pythoncode {
        def __add__(self, other):
            return self.add(other);

        def __sub__(self, other):
            return self.sub(other);

        def __mul__(self, other):
            return self.mul(other);

        def __div__(self, other):
            return self.div(other);

        def __str__(self):
            return self.str();
    }
}

// Include OpenSolid common interface
%include "common.i"
