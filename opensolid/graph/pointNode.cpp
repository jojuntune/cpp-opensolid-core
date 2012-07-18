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

#include <qgl.h>

#include <stk/glMaterial.h>

#include "graphScriptProperty.h"
#include "graphNodeEvents.h"
#include "pointNode.h"
#include "propertyError.h"

namespace opensolid
{

pointNode::pointNode ( const string& pointName )
    : graphNode( pointName )
{
    //! @param pointName New points name.

    init();
}

pointNode::pointNode ( const string& pointName, const string& exprX, const string& exprY,
                       const string& exprZ, const string& exprW )
    : graphNode( pointName )
{
    //! @param pointName New points name.
    //! @param exprX Expression for x component of point.
    //! @param exprY Expression for y component of point.
    //! @param exprZ Expression for z component of point.
    //! @param exprW Expression for w component of point.

    init();
    
    expr_x -> scriptText( exprX );
    expr_y -> scriptText( exprY );
    expr_z -> scriptText( exprZ );
    expr_w -> scriptText( exprW );
}

void pointNode::init()
{
    pt_colour.components( 1.0, 0.5, 0.0, 1.0 ); // Default to orange

    pt_size = 4.0; // Default to 4 pixels in size.
    
    expr_x = graphScript::sptr( new graphScript( "0" ) );
    expr_y = graphScript::sptr( new graphScript( "0" ) );
    expr_z = graphScript::sptr( new graphScript( "0" ) );
    expr_w = graphScript::sptr( new graphScript( "1.0" ) );

    addProperty( new graphScriptProperty<pointNode>( "X", this, &pointNode::x, &pointNode::x ) );
    addProperty( new graphScriptProperty<pointNode>( "Y", this, &pointNode::y, &pointNode::y ) );
    addProperty( new graphScriptProperty<pointNode>( "Z", this, &pointNode::z, &pointNode::z ) );
    addProperty( new graphScriptProperty<pointNode>( "W", this, &pointNode::w, &pointNode::w ) );
}

int pointNode::type()
{
    return POINT;
}

void pointNode::evaluate ( graphParamList::sptr paramList )
{
    //! @param paramList Parameter list for expressions to use.

    try
    {
        locn.x( expr_x -> evaluate( paramList ) );
    }
    catch( graphScript::Error error )
    {
        fireEvent( graphNodePropertyError( propertyError( id(), propertyIndex( "X" ), propertyError::UNKNOWN,
                                           error.lineNumber(), error.message() )));
    }

    try
    {
        locn.y( expr_y -> evaluate( paramList ) );
    }
    catch( graphScript::Error error )
    {
        fireEvent( graphNodePropertyError( propertyError( id(), propertyIndex( "Y" ), propertyError::UNKNOWN,
                                           error.lineNumber(), error.message() )));
    }

    try
    {
        locn.z( expr_z -> evaluate( paramList ) );
    }
    catch( graphScript::Error error )
    {
        fireEvent( graphNodePropertyError( propertyError( id(), propertyIndex( "Z" ), propertyError::UNKNOWN,
                                           error.lineNumber(), error.message() )));
    }

    try
    {
        locn.w( expr_w -> evaluate( paramList ) );
    }
    catch( graphScript::Error error )
    {
        fireEvent( graphNodePropertyError( propertyError( id(), propertyIndex( "W" ), propertyError::UNKNOWN,
                                           error.lineNumber(), error.message() )));
    }
}

void pointNode::render ( int renderType )
{
    if ( renderType == graphNode::RENDER_APPLY )
    {
        bool lightsOn = ( glIsEnabled ( GL_LIGHTING ) == GL_TRUE );  // Save lighting state.

        glDisable ( GL_LIGHTING );

        glMaterial ptMat;

        ptMat.baseColour ( pt_colour );

        ptMat.setupGL();

        glPointSize( pt_size );
        
        glBegin( GL_POINTS );

            glVertex4d( locn.x(), locn.y(), locn.z(), locn.w() );

        glEnd();

        if ( lightsOn ) glEnable ( GL_LIGHTING );  // Restore lighting state.
    }
}

stk::point pointNode::location()
{
    return locn;
}

colour pointNode::pointColour() const
{
    return pt_colour;
}

void pointNode::pointColour( colour ptColour )
{
    pt_colour = ptColour;
}

string pointNode::x() const
{
    //! @return Expression that defines coordinate as a string.

    return expr_x -> scriptText();
}

void pointNode::x ( const string& exprX )
{
    //! @param exprX Expression that specifies X coordinate of point.
    
    expr_x -> scriptText( exprX );

    fireEvent( graphNodeChanged( id() ) );
}

string pointNode::y() const
{
    //! @return Expression that defines coordinate as a string.

    return expr_y -> scriptText();
}

void pointNode::y ( const string& exprY )
{
    //! @param exprY Expression that specifies Y coordinate of point.
    
    expr_y -> scriptText( exprY );
    
    fireEvent( graphNodeChanged( id() ) );
}

string pointNode::z() const
{
    //! @return Expression that defines coordinate as a string.

    return expr_z -> scriptText();
}

void pointNode::z ( const string& exprZ )
{
    //! @param exprZ Expression that specifies Z coordinate of point.
    
    expr_z -> scriptText( exprZ );

    fireEvent( graphNodeChanged( id() ) );
}

string pointNode::w() const
{
    //! @return Expression that defines coordinate as a string.

    return expr_w -> scriptText();
}

void pointNode::w ( const string& exprW )
{
    //! @param exprW Expression that specifies W coordinate of point.
    
    expr_w -> scriptText( exprW );

    fireEvent( graphNodeChanged( id() ) );
}

} // namespace opensolid
