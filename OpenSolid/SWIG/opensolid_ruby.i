%module opensolid_ruby

%begin %{
    #include <ruby.h>
    #undef _
    #undef __
%}

// Rename functionName to function_name
%rename("%(undercase)s", %$isfunction) "";
%rename("__str__") "str";

// Include OpenSolid common interface
%include "common.i"
