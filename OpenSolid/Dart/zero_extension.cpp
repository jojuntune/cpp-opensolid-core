/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include <OpenSolid/Core/Zero.hpp>
#include <OpenSolid/Dart/opensolid_extension.hpp>

#include <string>

namespace opensolid
{
    void
    zeroInit(Dart_NativeArguments arguments) {
        Dart_EnterScope();

        double precision = getDouble(arguments, 1);

        // Initialize object
        initObject(arguments, 0, new Zero(precision));

        // Return null
        Dart_SetReturnValue(arguments, Dart_Null());

        Dart_ExitScope();
    }

    void
    zeroEqualsDouble(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroEqualsInterval(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroLessThanDouble(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroLessThanInterval(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroGreaterThanDouble(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroGreaterThanInterval(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroLessThanOrEqualToDouble(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroLessThanOrEqualToInterval(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroGreaterThanOrEqualToDouble(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroGreaterThanOrEqualToInterval(Dart_NativeArguments arguments) {
        Dart_SetReturnValue(arguments, Dart_False());
    }

    void
    zeroPrecision(Dart_NativeArguments arguments) {
        Zero* zero = getObject<Zero>(arguments, 0);

        Dart_SetReturnValue(arguments, Dart_NewDouble(zero->precision()));
    }

    Dart_NativeFunction
    resolveZeroName(Dart_Handle nameHandle, int argumentCount) {
        if (!Dart_IsStringLatin1(nameHandle)) {
            return nullptr;
        }
        
        // Get function name as std::string
        const char* buffer;
        Dart_Handle handle = Dart_StringToCString(nameHandle, &buffer);
        if (Dart_IsError(handle)) {
            Dart_PropagateError(handle);
        }
        std::string name(buffer);

        // Map function name to function pointer
        if (name == "zeroInit" ) {
            return zeroInit;
        } else if (name == "zeroEqualsDouble" ) {
            return zeroEqualsDouble;
        } else if (name == "zeroEqualsInterval" ) {
            return zeroEqualsInterval;
        } else if (name == "zeroLessThanDouble" ) {
            return zeroLessThanDouble;
        } else if (name == "zeroLessThanInterval" ) {
            return zeroLessThanInterval;
        } else if (name == "zeroGreaterThanDouble" ) {
            return zeroGreaterThanDouble;
        } else if (name == "zeroGreaterThanInterval" ) {
            return zeroGreaterThanInterval;
        } else if (name == "zeroLessThanOrEqualToDouble" ) {
            return zeroLessThanOrEqualToDouble;
        } else if (name == "zeroLessThanOrEqualToInterval" ) {
            return zeroLessThanOrEqualToInterval;
        } else if (name == "zeroGreaterThanOrEqualToDouble" ) {
            return zeroGreaterThanOrEqualToDouble;
        } else if (name == "zeroGreaterThanOrEqualToInterval" ) {
            return zeroGreaterThanOrEqualToInterval;
        } else if (name == "zeroPrecision" ) {
            return zeroPrecision;
        } else {
            return nullptr;
        }
    }
}
