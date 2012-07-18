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

#ifndef POINT_NODE_H
#define POINT_NODE_H

#include <stk/colour.h>
#include <stk/point.h>
#include <stk/safePtr.h>

using namespace stk;

#include "graphScript.h"
#include "graphNode.h"

namespace opensolid
{

class pointNode : public graphNode
{
    public:

        typedef safePtr<pointNode> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;

        pointNode ( const string& pointName );
        pointNode ( const string& pointName, const string& exprX, const string& exprY,
                    const string& exprZ, const string& exprW );

        void init();

        virtual int type();

        //! Evaluate the expressions used to define the points coordinates.
        virtual void evaluate ( graphParamList::sptr paramList );

        //! Render point to current OpenGL context.
        virtual void render( int renderType );

        //! Return location of point node as stk point object. 
        stk::point location();

        //! Get points colour.
        colour pointColour() const;

        //! Set points colour.
        void pointColour( colour ptColour );

        string x() const; //!< Get X coordinate expression.
        void x ( const string& exprX ); //!< Set X coordinate expression.

        string y () const; //!< Get Y coordinate expression.
        void y ( const string& exprY ); //!< Set Y coordinate expression.
        
        string z () const; //!< Get Z coordinate expression.
        void z ( const string& exprZ ); //!< Set Z coordinate expression.
        
        string w () const; //!< Get W coordinate expression.
        void w ( const string& exprW ); //!< Set W coordinate expression.

    private:

        graphScript::sptr expr_x;
        graphScript::sptr expr_y;
        graphScript::sptr expr_z;
        graphScript::sptr expr_w;

        stk::point  locn; // Evaluated point location.

        colour      pt_colour;

        double      pt_size;
};

}

#endif
