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

#include <stk/graphAction.h>
#include <stk/graphEdge.h>
#include <stk/NodeNotFound.h>
#include <stk/point.h>

using namespace stk;

#include <graph/paramNode.h>
#include <graph/pointNode.h>
#include <graph/project.h>
#include <graph/propertyError.h>

using namespace opensolid;

#include <iostream>
using namespace std;

class graphNodeEvents : public graphNodeEventListener
{
private:
    bool property_error;
    std::string error_message;
public:
    graphNodeEvents() : property_error( false ) {
    }

    virtual void graphNodePropertyError ( const propertyError& error ) {
        property_error = true;
        error_message = error.message();
    }
    
    bool propertyErrorOccurred() {
        return property_error;
    }

    std::string errorMessage() {
        return error_message;
    }

    void reset() {
        property_error = false;
    }
};

bool testParamScoping ( project* proj )
{
    opensolid::graphNode::nodeInfo comp1;
    opensolid::graphNode::nodeInfo comp2;

    opensolid::graphNode::nodeInfo param1;

    opensolid::graphNode::nodeInfo point1;
    opensolid::graphNode::nodeInfo point2;

    pointNode::sptr point;

    try {
        comp1 = proj -> addNewComponent( NO_PARENT );
        param1 = proj -> addNewParam( comp1.nodeId() );
        point1 = proj -> addNewPoint( comp1.nodeId() );

        paramNode::sptr param = param1.node();
        param -> paramValue( "0.1" );

        point = point1.node();
        point -> x( "param1" );

        comp2 = proj -> addNewComponent( NO_PARENT );
        point2 = proj -> addNewPoint( comp2.nodeId() );

        point = point2.node();
        point -> x( "-param1" );
    } catch( ... ) {
        cout << "An unexpected exception occured ";
        cout << "while creating param scope isolation graph structure.\n";
        return false;
    }

    // Check that the points initial values are correct.

    point = point1.node();
    stk::point locn = point -> location();

    if ( locn.x() != 0.1 ) {
        cout << "Error in point1 location.\n";
        return false;
    }

    point = point2.node();
    locn = point -> location();

    if ( locn.x() != 0.0 ) {
        cout << "Error in point2 location.\n";
        return false;
    }

    // Move param1 to comp2 and re-check evaluated point coordinates.
    
    try {
        param1 = proj -> moveNode ( param1.edgeId(), comp2.nodeId(), 0 );
    } catch( ... ) {
        cout << "An unexpected exception occured while moving param1 to comp2.\n";
        return false;
    }

    point = point1.node();
    locn = point -> location();

    if ( locn.x() != 0.1 ) {
        // There should be an error in evaluation and the coordinate will remain unchanged.
        cout << "Error in point1 location after move.\n";
        return false;
    }

    point = point2.node();
    locn = point -> location();

    if ( locn.x() != -0.1 ) {
        cout << "Error in point2 location after move.\n";
        return false;
    }

    return true;
}

bool testParam ( project* proj ) {
    // Test parameter propagation down graph.

    // Create nodes.

    opensolid::graphNode::nodeInfo param1;
    opensolid::graphNode::nodeInfo param2;
    opensolid::graphNode::nodeInfo param3;
    opensolid::graphNode::nodeInfo param4;
    
    opensolid::graphNode::nodeInfo frag1;
    opensolid::graphNode::nodeInfo frag2;

    opensolid::graphNode::nodeInfo point1;
    opensolid::graphNode::nodeInfo point2;
    opensolid::graphNode::nodeInfo point3;

    graphNodeEvents events;

    try {
        param1 = proj -> addNewParam( "param1", NO_PARENT, "5" );
        (param1.node()) -> addEventListener( &events );
        
        frag1 = proj -> addNewFragment( "frag1", NO_PARENT );

        param2 = proj -> addNewParam( "param2", frag1.nodeId(), "param1 + 5" );
        (param2.node()) -> addEventListener( &events );

        point1 = proj -> addNewPoint( "point1", frag1.nodeId(), "param1", "param2",
                                      "param1 + param2", "1" );
        (point1.node()) -> addEventListener( &events );

        param3 = proj -> addNewParam( "param3", frag1.nodeId(), "param2 - 2" );
        (param3.node()) -> addEventListener( &events );

        point2 = proj -> addNewPoint( "point2", frag1.nodeId(), "param1", "param2", "param3", "1" );
        (point2.node()) -> addEventListener( &events );

        frag2 = proj -> addNewFragment( "frag2", NO_PARENT );

        param4 = proj -> addNewParam( "param4", frag2.nodeId(), "param1 + 2" );
        (param4.node()) -> addEventListener( &events );

        point3 = proj -> addNewPoint( "point3", frag2.nodeId(), "param1", "param4",
                                      "param1 + param4", "1" );
        (point3.node()) -> addEventListener( &events );
    } catch( ... ) {
        cout << "An unexpected exception occured while creating param tests graph structure.\n";
        return false;
    }

    // Make sure points coordinates are correct.

    pointNode::sptr ptNode = point1.node();
    stk::point locn = ptNode -> location();

    if ( locn.x() != 5 || locn.y() != 10 || locn.z() != 15 ) {
        cout << "\terror: point1 coordinates incorrect.\n";
        return false;
    }

    cout << "\tpoint1 coordinates correct.\n";

    ptNode = point2.node();
    locn = ptNode -> location();

    if ( locn.x() != 5 || locn.y() != 10 || locn.z() != 8 ) {
        cout << "\terror: point2 coordinates incorrect.\n";
        return false;
    }

    cout << "\tpoint2 coordinates correct.\n";
    
    ptNode = point3.node();
    locn = ptNode -> location();

    if ( locn.x() != 5 || locn.y() != 7 || locn.z() != 12 ) {
        cout << "\terror: point3 coordinates incorrect.\n";
        return false;
    }

    cout << "\tpoint3 coordinates correct.\n";

    return true;
}


bool testPoint ( project* proj ) {
    opensolid::graphNode::nodeInfo pt1NodeInfo;
    opensolid::graphNode::nodeInfo pt2NodeInfo;
    opensolid::graphNode::nodeInfo pt3NodeInfo;
    
    try {
        pt1NodeInfo =
            proj -> addNewPoint ( "testPoint1", NO_PARENT, "4", "5", "6", "1" );
        pt2NodeInfo =
            proj -> addNewPoint ( "testPoint2", NO_PARENT, "2*3", "5+2", "48/6", "3^3/3" );

        proj -> evaluate();
    } catch( graphScript::Error ) {
        cout << "A script error occured while generating points.\n";
        return false;
    } catch(...) {
        cout << "An unexpected exception occured while testing point evaluation.\n";
        return false;
    }

    // Make sure points have expected coordinates.

    pointNode::sptr ptNode = pt1NodeInfo.node();
    
    stk::point locn = ptNode -> location();

    if ( locn.x() != 4 || locn.y() != 5 || locn.z() != 6 || locn.w() != 1 ) {
        cout << "testPoint1 coordinates incorrect.\n";
        return false;
    }

    ptNode = pt2NodeInfo.node();
    locn = ptNode -> location();

    if ( locn.x() != 6 || locn.y() != 7 || locn.z() != 8 || locn.w() != 9 ) {
        cout << "testPoint2 coordinates incorrect.\n";
        return false;
    }

    // Deliberately cause a script error.
    
    try {
        pt3NodeInfo = proj -> addNewPoint ( "testPoint3", NO_PARENT, "2*/1", "1", "2", "3" );

        graphNodeEvents events;

        (pt3NodeInfo.node()) -> addEventListener( &events );
        
        proj -> evaluate();

        if ( ! events.propertyErrorOccurred() )
        {
            cout << "Script error wasn't generated.\n";
        
            return false;
        }
    } catch(...) {
        cout << "An unexpected exception occured while testing script error generation.\n";
        return false;
    }

    // Deliberately pass an empty expression to see if it causes a script error.

    try {
        ptNode = pt2NodeInfo.node();

        graphNodeEvents events;

        ptNode -> addEventListener( &events );
        
        ptNode -> x( "" );
    } catch(...) {
        cout << "An unexpected exception occured while testing script error generation.\n";
        return false;
    }
    
    return true;
}

void dumpGraph( project* proj ) {
    // Dump graph structure to std out.

    proj -> dump();
}

int main() {
    bool success = true;

    project* proj1 = 0;
    project* proj2 = 0;
    project* proj3 = 0;

    try {
        proj1 = new project( "testProject1" );
        proj2 = new project( "testProject2" );
        proj3 = new project( "testProject3" );
    } catch(...) {
        cout << "Unexpected exception occured during project construction.";
        success = false;
    }

    if ( success ) {
        cout << "Testing Point Evaluation:\n";
        success = testPoint( proj1 );
        if ( ! success ) cout << "*** Point Evaluation Failed ***\n";
    }
    
    if ( success ) {
        cout << "Testing Parameter Propagation:\n";
        success = testParam( proj2 );
        if ( ! success ) {
            cout << "*** Parameter Propagation Failed ***\n";
            dumpGraph( proj2 );
        }
    }

    if ( success ) {
        cout << "Testing Parameter Scope Isolation:\n";
        success = testParamScoping( proj3 );
        if ( ! success ) {
            cout << "*** Parameter Scope IsolationFailed ***\n";
            dumpGraph( proj3 );
        }
    }
    
    //if ( ! success && proj1 ) dumpGraph( proj1 );

    if ( proj1 ) delete proj1;
    if ( proj2 ) delete proj2;
    if ( proj3 ) delete proj3;

    if ( success )
        return 0;
    else
        return 1;
}
