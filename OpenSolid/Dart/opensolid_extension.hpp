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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Zero.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>

#include "dart_api.h"

namespace opensolid
{
    enum
    {
        INVALID = 0,
        ZERO,
        INTERVAL
    };

    template <class TType>
    struct TypeCode;

    template <>
    struct TypeCode<Zero>
    {
        static const int value = ZERO;
    };

    template <>
    struct TypeCode<Interval>
    {
        static const int value = INTERVAL;
    };

    void
    abortIfError(Dart_Handle handle);

    template <class TObject>
    void
    initObject(Dart_NativeArguments argument, int index, TObject* object);

    Dart_Handle
    initObject(
        Dart_NativeArguments arguments,
        int index,
        void* object,
        int typeCode,
        Dart_WeakPersistentHandleFinalizer finalizer
    );

    template <class TObject>
    void
    deletionCallback(Dart_WeakPersistentHandle handle, void* zero);

    template <class TObject>
    TObject*
    getObject(Dart_NativeArguments arguments, int index);

    void*
    getObject(Dart_NativeArguments arguments, int index, int typeCode);

    int64_t
    getInt(Dart_NativeArguments arguments, int index);

    double
    getDouble(Dart_NativeArguments arguments, int index);
}

////////// Implementation //////////

namespace opensolid
{

    template <class TObject>
    void
    initObject(Dart_NativeArguments arguments, int index, TObject* object) {
        Dart_Handle handle = initObject(
            arguments,
            index,
            object,
            TypeCode<TObject>::value,
            deletionCallback<TObject>
        );
        if (Dart_IsError(handle)) {
            delete object;
            Dart_PropagateError(handle);
        }
    }

    template <class TObject>
    void
    deletionCallback(Dart_WeakPersistentHandle handle, void* object) {
        delete static_cast<TObject*>(object);
    }

    template <class TObject>
    TObject*
    getObject(Dart_NativeArguments arguments, int index) {
        return static_cast<TObject*>(getObject(arguments, index, TypeCode<TObject>::value));
    }
}
