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

#ifndef GRAPH_LISTACTION_H
#define GRAPH_LISTACTION_H

#include "graphAction.h"
#include "graphNode.h"

namespace opensolid
{

class listGraphAction : public graphAction
{
    public:

        virtual ~listGraphAction();

        listGraphAction();

        listGraphAction ( listGraphAction& copyFrom );
        listGraphAction& operator= ( listGraphAction& copyFrom );

        listGraphAction ( int listType );

        virtual listGraphAction* clone(); //!< Create a deep copy of this object.

        graphNode::listSptr nodesFound(); //!< Retrieve list of nodes that were found.

    protected:

        virtual int _type();

        virtual void process ( graphNode::nodeInfo& info, int traversalType );

        void init();

        void copy_from ( listGraphAction& copyFrom ); //!< Deep copy the given object.

    private:

        int         type_to_list;

        graphNode::listSptr list;
};

}

#endif

