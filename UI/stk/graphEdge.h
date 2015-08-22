// Copyright 2007 Scott A.E. Lanham
// --------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <bitset>
using namespace std;

#include "namedObject.h"
#include "ptrList.h"
#include "safePtr.h"
#include "uniqueObject.h"

namespace stk
{

class graphNode;

typedef bitset<32> actionTypeBitField;

class graphEdge : public namedObject, public uniqueObject
{
    public:

        typedef safePtr<graphEdge> sptr;
        typedef safePtr< ptrList<sptr> > listSptr;

        graphEdge();
        graphEdge ( const string& edgeName, safePtr< graphNode > linkTo );

        safePtr< graphNode > link();

        void setActionFilter ( actionTypeBitField actionTypes ); //! Set a filter for the given action types.
        void resetActionFilter ( actionTypeBitField actionTypes ); //! Reset (remove) a filter for the given action types.

        bool canTraverse ( actionTypeBitField actionType ); //! Query whether action of given type may traverse edge.

    private:

        safePtr< graphNode > link_to; // Child node to link to.

        actionTypeBitField action_filter; //! Bit field. If bit set then associated action is blocked.
};

}

#endif

