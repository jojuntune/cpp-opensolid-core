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

#ifndef EVALUATE_GRAPHACTION_H
#define EVALUATE_GRAPHACTION_H

#include "graphAction.h"
#include "graphNode.h"
#include "graphParamList.h"

namespace opensolid
{

//! Action for evaluation of expressions.

class evaluateGraphAction : public graphAction
{
    public:

        evaluateGraphAction();

        evaluateGraphAction ( evaluateGraphAction& copyFrom ); //!< Copy constructor.

        virtual evaluateGraphAction* clone(); //!< Create a deep copy of this object.
    
    protected:

        virtual int _type();

        virtual void process ( graphNode::nodeInfo& info, int traversalType );

    private:

        graphParamList::sptr paramList;
};

}

#endif
