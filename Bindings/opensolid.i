%module OpenSolid

%{
#include "JInterval.hpp"
%}

// Include automatic conversions for std::string
%include "std_string.i"

// Strip leading 'J' from class names
%rename("%(strip:[J])s", %$isclass) "";

// Add static initialization code to OpenSolidJNI class to load native libraries
%pragma(java) jniclasscode=%{
    static {
        try {
            System.loadLibrary("OpenSolidCore");
            System.loadLibrary("OpenSolidJNI");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }
%}

%include "JInterval.hpp"
