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

#ifndef OS_GRAPH_SCRIPT_H
#define OS_GRAPH_SCRIPT_H

#include <opensolid/Matrix.hpp>

#include <stk/Exception.h>
#include <stk/namedObject.h>
#include <stk/threadedObject.h>

#include "graphParamList.h"

namespace opensolid
{

//! Object for encapsulating a script.

class graphScript : public stk::namedObject, public stk::threadedObject
{
    public:

        typedef safePtr<graphScript> sptr;

        ~graphScript();
        graphScript();
        graphScript ( const string& scriptText );

        void scriptText ( const string& scriptString ); //!< Set script text.
        string scriptText() const; //!< Get script text.

        double evaluate ( graphParamList::sptr paramList ); //!< Evaluate ( invoke ) script.

        bool hasError(); //!< Return true if any error is associated with this script.

        // Exceptions.

        class Error : public stk::Exception
        {
            public:

                Error ( const string& message, int lineNumber ) : Exception( message ), line_number( lineNumber ){};

                int lineNumber() { return line_number; } //!< Get line number where error occurred.

            private:

                int line_number;
        };

    private:

        void init();

        string script_text;

        bool eval_ok; //!< True if expression has been successfully evaluated.
};

}

#endif

