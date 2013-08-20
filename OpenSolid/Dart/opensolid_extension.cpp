/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
*************************************************************************************/

#include <OpenSolid/Dart/opensolid_extension.hpp>

namespace opensolid
{
    void
    abortIfError(Dart_Handle handle) {
        if (Dart_IsError(handle)) {
            Dart_PropagateError(handle);
        }
    }

    Dart_Handle
    initObject(
        Dart_NativeArguments arguments,
        int index,
        void* object,
        int typeCode,
        Dart_WeakPersistentHandleFinalizer finalizer
    ) {
        Dart_EnterScope();

        // Get handle to argument at given index
        Dart_Handle argumentHandle = Dart_GetNativeArgument(arguments, index);
        if (Dart_IsError(argumentHandle)) {
            return argumentHandle;
        }

        // Handle used for checking for error return codes
        Dart_Handle handle = nullptr;

        // Set object field
        handle = Dart_SetNativeInstanceField(argumentHandle, 0, reinterpret_cast<intptr_t>(object));
        if (Dart_IsError(handle)) {
            return handle;
        }

        // Set type code field
        handle = Dart_SetNativeInstanceField(argumentHandle, 1, typeCode);
        if (Dart_IsError(handle)) {
            return handle;
        }

        // Create new weak persistent handle
        handle = Dart_HandleFromWeakPersistent(
            Dart_NewWeakPersistentHandle(argumentHandle, object, finalizer)
        );
        if (Dart_IsError(handle)) {
            return handle;
        }

        Dart_ExitScope();

        return Dart_Null();
    }

    void*
    getObject(Dart_NativeArguments arguments, int index, int typeCode) {
        Dart_EnterScope();

        // Get handle to argument at given index
        Dart_Handle argumentHandle = Dart_GetNativeArgument(arguments, index);
        abortIfError(argumentHandle);

        Dart_Handle handle = nullptr;
        intptr_t fieldValue = 0;

        // Get type field
        handle = Dart_GetNativeInstanceField(argumentHandle, 1, &fieldValue);
        abortIfError(handle);

        // Check type code
        if (fieldValue != typeCode) {
            assert(false);
            Dart_PropagateError(Dart_NewApiError("OpenSolid internal error: wrong type code"));
        }

        // Get object field
        handle = Dart_GetNativeInstanceField(argumentHandle, 0, &fieldValue);
        abortIfError(handle);

        Dart_ExitScope();

        void* result = reinterpret_cast<void*>(fieldValue);
        if (result == nullptr) {
            assert(false);
            Dart_PropagateError(Dart_NewApiError("OpenSolid internal error: null native field"));
        }
        return result;
    }

    int64_t
    getInt(Dart_NativeArguments arguments, int index) {
        // Get handle to Dart argument at given index
        Dart_Handle argumentHandle = Dart_GetNativeArgument(arguments, index);
        abortIfError(argumentHandle);

        // Get value from argument
        int64_t value = 0;
        Dart_Handle handle = Dart_IntegerToInt64(argumentHandle, &value);
        abortIfError(handle);

        return value;

    }

    double
    getDouble(Dart_NativeArguments arguments, int index) {
        // Get handle to Dart argument at given index
        Dart_Handle argumentHandle = Dart_GetNativeArgument(arguments, index);
        abortIfError(argumentHandle);

        // Get value from argument
        double value = 0.0;
        Dart_Handle handle = Dart_DoubleValue(argumentHandle, &value);
        abortIfError(handle);

        return value;
    }

    Dart_NativeFunction
    resolveZeroName(Dart_Handle name, int argumentCount);

    Dart_NativeFunction
    resolveIntervalName(Dart_Handle name, int argumentCount);

    Dart_NativeFunction
    resolveName(Dart_Handle name, int argumentCount) {
        Dart_NativeFunction result = nullptr;
        if (result = resolveZeroName(name, argumentCount)) {
            return result;
        }
        if (result = resolveIntervalName(name, argumentCount)) {
            return result;
        }
        return result;
    }
}

DART_EXPORT
Dart_Handle
opensolid_extension_Init(Dart_Handle parentLibrary) {
    if (Dart_IsError(parentLibrary)) {
        return parentLibrary;
    }
    Dart_Handle resultCode = Dart_SetNativeResolver(parentLibrary, opensolid::resolveName);
    if (Dart_IsError(resultCode)) {
        return resultCode;
    }
    return Dart_Null();
}
