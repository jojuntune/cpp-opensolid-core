// Copyright 2008 Scott Lanham.
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

#include "graphNodeEvents.h"
#include "graphScriptProperty.h"
#include "paramNode.h"
#include "propertyError.h"

namespace opensolid
{

paramNode::paramNode ( const string& paramName )
    : graphNode( paramName )
{
    init();
}

paramNode::paramNode ( const string& paramName, const string& paramExpr )
    : graphNode( paramName )
{
    init();

    param_expr -> scriptText( paramExpr );
}

void paramNode::init()
{
    param_expr = graphScript::sptr( new graphScript( "0" ) );

    addProperty( new graphScriptProperty<paramNode>( "Parameter Value", this, &paramNode::paramValue,
                                                   &paramNode::paramValue ) );
}

int paramNode::type()
{
    return PARAMETER;
}

string paramNode::paramValue() const
{
    //! @return Parameters current value.

    return param_expr -> scriptText();
}

void paramNode::paramValue ( const string& value )
{
    //! @param value New value to set parameter to.
    //! @par Notes May throw exceptions related to underlying scripting engine.

    param_expr -> scriptText( value );

    fireEvent( graphNodeChanged( id() ) );
}

void paramNode::evaluate ( graphParamList::sptr paramList )
{
    //! @param paramList Parameter list for expressions to use.

    try
    {
        double paramVal = param_expr -> evaluate( paramList );

        paramList -> setParam( name(), paramVal );
    }
    catch( graphScript::Error error )
    {
        fireEvent( graphNodePropertyError( propertyError( id(), 0, propertyError::UNKNOWN,
                                           error.lineNumber(), error.message() )));
    }
}

}

