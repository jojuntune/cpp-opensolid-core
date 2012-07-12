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

#ifndef PARAM_NODE_H
#define PARAM_NODE_H

#include "graphScript.h"
#include "graphNode.h"
#include "graphParam.h"

namespace opensolid
{

class paramNode : public graphNode
{
    public:

        typedef safePtr<paramNode> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;

        paramNode ( const string& paramName );

        paramNode ( const string& paramName, const string& paramExpr );

        virtual int type();

        string paramValue(); //! Get parameters value.

        void paramValue ( const string& value ); //! Set parameters value.

        //! Evaluate the expression used to define the parameter.
        virtual void evaluate ( graphParamList::sptr paramList );

    private:

        void init();

        graphScript::sptr param_expr;

};

}

#endif
