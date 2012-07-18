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

#ifndef OS_GRAPH_PARAMLIST_H
#define OS_GRAPH_PARAMLIST_H

#include <stk/safePtr.h>
#include <stk/ptrList.h>
#include <stk/threadedObject.h>
using namespace stk;

#include "Exception.h"
#include "graphParam.h"

namespace opensolid
{

//! List of named graph parameter values.

class PythonEnvironment;

class graphParamList : public threadedObject
{
    public:

        typedef safePtr<graphParamList> sptr;

        graphParamList();

        graphParamList ( graphParamList& copyFrom ); //!< Deep copy constructor.

        graphParamList& operator= ( graphParamList& copyFrom ); //!< Assignment.

        double getParam ( const string& paramName ); //!< Get parameter value.
        void setParam ( const string& paramName, double paramValue ); //!< Set parameter value.

        void setScriptParams( PythonEnvironment& scriptObject ); //!< Set Script object parameters from this list.

        // Exceptions
        
        //! Requested parameter was not found.
        class ParamNotFound : public stk::Exception {};

    private:

        ptrList< graphParam::sptr > params;

        void copyParams ( graphParamList& copyFrom );
};

}

#endif

