// Copyright 2007 Scott Lanham.
// ----------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#include "graphParamList.h"

namespace opensolid
{

graphParamList::graphParamList()
{
}

void graphParamList::copyParams ( graphParamList& copyFrom )
{
    if ( copyFrom.lock() )
    {
        // Deep copy each parameter.

        graphParam::sptr* param = copyFrom.params.first();

        while ( param )
        {
            params.append( new graphParam::sptr( param, true ), true ); // Take deep copy of graph param.

            param = copyFrom.params.next();
        }

        copyFrom.unlock();
    }
}

graphParamList::graphParamList ( graphParamList& copyFrom )
    : threadedObject( copyFrom )
{
    //! @param copyFrom Param list to take deep copy of.

    copyParams( copyFrom );
}

graphParamList& graphParamList::operator= ( graphParamList& copyFrom )
{
    //! @param copyFrom Param list to take deep copy of.

    params.clear();
    copyParams( copyFrom );

    return *this;
}

double graphParamList::getParam ( const string& paramName )
{
    //! @param paramName Name of parameter to get.
    //! @throws ParamNotFound If no parameter is found that matches paramName.

    { THREAD_SYNC

        graphParam::sptr* param = params.first();

        while ( param )
        {
            if ( (*param) -> hasName( paramName ) )
                return (*param) -> value();

            param = params.next();
        }
    }

    throw ParamNotFound();
}

void graphParamList::setParam ( const string& paramName, double paramValue )
{
    //! @param paramName Name of parameter to set.
    //! @param paramValue Value of parameter being set.
    //! @par Notes
    //!             If the parameter doesn't exist in the list it will be created.

    THREAD_SYNC

    graphParam::sptr* param = params.first();

    while ( param )
    {
        if ( (*param) -> hasName( paramName ) )
        {
            (*param) -> value( paramValue );
            return;
        }

        param = params.next();
    }

    // A new parameter needs to be created.

    graphParam* gParam = new graphParam( paramName, paramValue );

    params.append( new graphParam::sptr( gParam ), true );
}

void graphParamList::setScriptParams( PythonEnvironment& scriptObject )
{
    //! @param scriptObject Script object to set parameters of.

    THREAD_SYNC

    safePtr< graphParam > paramPtr = params.first(); // Copies safe pointer.

    while ( ! paramPtr.isNull() )
    {
        scriptObject.set( paramPtr -> name(), paramPtr -> value() );

        paramPtr = params.next();
    }
}

}
