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

#include <opensolid/core/common/Error.hpp>
#include <opensolid/python/PythonEnvironment.hpp>

#include "graphScript.h"

namespace opensolid
{

typedef Error ScriptError;

graphScript::~graphScript()
{
}

graphScript::graphScript()
{
    init();
}

graphScript::graphScript ( const string& scriptString )
{
    init();

    scriptText( scriptString );
}

void graphScript::init()
{
    eval_ok = true; // Don't flag a problem until the script causes a ScriptError exception.
}

void graphScript::scriptText ( const string& scriptText )
{
    //! @param scriptText Script text to execute.

    eval_ok = true;

    script_text = scriptText;
}

string graphScript::scriptText() const
{
    //! @return Text of script.

    return script_text;
}

double graphScript::evaluate ( graphParamList::sptr paramList )
{
    PythonEnvironment scriptObject;

    paramList -> setScriptParams( scriptObject );

    double retVal = 0.0;

    try
    {
        retVal = scriptObject.get<double>( script_text );
    }
    catch( ScriptError sError )
    {
        eval_ok = false;

        string errorMessage = scriptObject.formattedTraceback();

        // switch( sError.expected() )
        // {
        //     case ScriptError::SCRIPTING_CAST_FAILED :
        //         errorMessage = "Scripting typecast failed.";
        //         break;
        // 
        //     case ScriptError::SCRIPTING_NIL_RETURN :
        //         errorMessage = "Null value returned from script.";
        //         break;
        // 
        //     case ScriptError::SCRIPTING_RUNTIME_ERROR :
        //         errorMessage = "Script runtime error.";
        //         break;
        // 
        //     case ScriptError::SCRIPTING_SYNTAX_ERROR :
        //         errorMessage = "Script syntax error.";
        //         break;
        // }

        //throw Error( sError.message(), sError.lineNumber() );
        //throw Error( errorMessage, 0 ); // No line numbers yet.
    }

    eval_ok = true;

    return retVal;
}

bool graphScript::hasError()
{
    return ! eval_ok;
}

} // namespace opensolid

