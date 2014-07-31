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

#ifndef GRAPH_PARAM_H
#define GRAPH_PARAM_H

#include <stk/safePtr.h>
#include <stk/namedObject.h>
using namespace stk;

namespace opensolid
{

//! Named parameter value.

class graphParam : public stk::namedObject
{
    public:

        typedef safePtr<graphParam> sptr;

        graphParam ( const string& name, double value );

        graphParam ( const graphParam& copyFrom );

        graphParam& operator= ( const graphParam& copyFrom );

        double value();
        void value( double paramValue );

    private:

        double _value; // Parameters value.
};

}

#endif
