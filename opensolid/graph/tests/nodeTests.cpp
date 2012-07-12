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
#include <stk/NameInUse.h>
#include <stk/NodeNotFound.h>

using namespace stk;

#include <opensolid/Graph/project.h>

using namespace opensolid;

#include <iostream>
using namespace std;

char tc1[] = "testComponent1";
char tc2[] = "testComponent2";
char tc3[] = "testComponent3";

char tf1[] = "testFrag1";
char tf2[] = "testFrag2";
char tf3[] = "testFrag3";

char tf4[] = "testFrag4";
char tf5[] = "testFrag5";
char tf6[] = "testFrag6";

char tf7[] = "testFrag7";
char tf8[] = "testFrag8";
char tf9[] = "testFrag9";


bool testEdgeActionFilter ( project* proj )
{
    // Test edge action filter functionality.

    // Find edge that points to tf1
    opensolid::graphNode::sptr node = proj -> findNode( tf1 );
    graphEdge::sptr edge = node -> edgeAtIndex( 0 );

    // Do not allow find action to traverse edge.
    if ( ! edge.isNull() ) edge -> setActionFilter( graphAction::typeBits( graphAction::FIND_GRAPH_ACTION ) );

    // tf2 should not be found.
    try
    {
        proj -> findNode( tf2 );
        cout << "\tError: testFrag2 should not have been found.\n";
        return false;
    }
    catch( stk::NodeNotFound )
    {
        cout << "\ttestFrag2 not found as expected.\n";
    }

    // Allow find action to traverse edge.
    if ( ! edge.isNull() ) edge -> resetActionFilter( graphAction::typeBits( graphAction::FIND_GRAPH_ACTION ) );

    // tf1 should be found.
    try
    {
        proj -> findNode( tf2 );
        cout << "\ttestFrag2 found as expected.\n";
    }
    catch( stk::NodeNotFound )
    {
        cout << "\tError: testFrag2 should have been found.\n";
        return false;
    }
    
    return true;
}

bool testGenericProject( project* proj )
{
    // Test find functions

    opensolid::graphNode::nodeInfo info;

    // Test find from node name.

    opensolid::graphNode::sptr component;

    try
    {
        component = proj -> findNode( tc1 );

        if ( component -> name() != tc1 )
        {
            cout << "Nodes name is not correct.\n";
            return false;
        }
    }
    catch( ... )
    {
        cout << "Unexpected exception occured during find node from name.\n";
        return false;
    }

    // Test find node from edge ID.

    opensolid::graphNode::nodeInfo fragment;

    try
    {
        fragment = proj -> findNodeFromEdgeId ( (component -> edgeAtIndex(0)) -> id() );

        if ( fragment.edgeId() != (component -> edgeAtIndex(0)) -> id() )
        {
            cout << "Nodes ID is not correct.\n";
            return false;
        }
    }
    catch( ... )
    {
        cout << "Unexpected exception occured during find node from Edge ID.\n";
        return false;
    }

    return true;
}


bool moveFragmentsAround ( project* proj )
{
    opensolid::graphNode::sptr tc1;
    opensolid::graphNode::sptr tc2;
    opensolid::graphNode::sptr tc3;

    try
    {
        tc1 = proj -> findNode( "testComponent1" );
        tc2 = proj -> findNode( "testComponent2" );
        tc3 = proj -> findNode( "testComponent3" );

        cout << "\tFound Components.\n";

        // Move all nodes to testComponent2.
        
        graphEdge::listSptr edges = tc1 -> getEdgeList();

        graphEdge::sptr edge = edges -> last();

        while ( ! edge.isNull() )
        {
            proj -> moveNode( edge -> id(), tc2 -> id(), 0 );
            edge = edges -> prev();
        }

        cout << "\tMoved all testComponent1 nodes to testComponent2.\n";

        edges = tc3 -> getEdgeList();

        edge = edges -> first();

        int startIndex = 6;

        while ( ! edge.isNull() )
        {
            proj -> moveNode( edge -> id(), tc2 -> id(), startIndex ++ );
            edge = edges -> next();
        }

        cout << "\tMoved all testComponent3 nodes to testComponent2.\n";

        // Make sure fragment structure is as expected.

        opensolid::graphNode::listSptr childList = tc2 -> getChildList();

        if ( ! (*( childList -> atIndex(0) )) -> hasName( tf1 ) ) return false;
        if ( ! (*( childList -> atIndex(1) )) -> hasName( tf2 ) ) return false;
        if ( ! (*( childList -> atIndex(2) )) -> hasName( tf3 ) ) return false;
        if ( ! (*( childList -> atIndex(3) )) -> hasName( tf4 ) ) return false;
        if ( ! (*( childList -> atIndex(4) )) -> hasName( tf5 ) ) return false;
        if ( ! (*( childList -> atIndex(5) )) -> hasName( tf6 ) ) return false;
        if ( ! (*( childList -> atIndex(6) )) -> hasName( tf7 ) ) return false;
        if ( ! (*( childList -> atIndex(7) )) -> hasName( tf8 ) ) return false;
        if ( ! (*( childList -> atIndex(8) )) -> hasName( tf9 ) ) return false;

        cout << "\tAll fragments are in correct positions.\n";

        // Move fragments into a three level hierachy.

        edges = tc2 -> getEdgeList();

        edge = edges -> atIndex(0); // tf1
        proj -> moveNode( edge -> id(), tc1 -> id(), 0 );
        graphEdge::sptr prevEdge = edge;
        edge = edges -> atIndex(1); // tf2
        proj -> moveNode( edge -> id(), ( prevEdge -> link() ) -> id(), 0 ); // tf1 -> tf2
        prevEdge = edge;
        edge = edges -> atIndex(2); // tf3
        proj -> moveNode( edge -> id(), ( prevEdge -> link() ) -> id(), 0 ); // tf2 -> tf3

        edge = edges -> atIndex(3); // tf4
        proj -> moveNode( edge -> id(), tc2 -> id(), 0 );
        prevEdge = edge;
        edge = edges -> atIndex(4); // tf5
        proj -> moveNode( edge -> id(), ( prevEdge -> link() ) -> id(), 0 ); // tf4 -> tf5
        prevEdge = edge;
        edge = edges -> atIndex(5); // tf6
        proj -> moveNode( edge -> id(), ( prevEdge -> link() ) -> id(), 0 ); // tf5 -> tf6

        edge = edges -> atIndex(6); // tf7
        proj -> moveNode( edge -> id(), tc3 -> id(), 0 );
        prevEdge = edge;
        edge = edges -> atIndex(7); // tf8
        proj -> moveNode( edge -> id(), ( prevEdge -> link() ) -> id(), 0 ); // tf7 -> tf8
        prevEdge = edge;
        edge = edges -> atIndex(8); // tf9
        proj -> moveNode( edge -> id(), ( prevEdge -> link() ) -> id(), 0 ); // tf8 -> tf9

        cout << "\tMoved all fragments into 3 level structure.\n";
        
        // Make sure fragment structure is as expected.

        if ( tc1 -> childCount() != 1 ) return false;
        opensolid::graphNode::sptr node = tc1 -> childAtIndex( 0 ); // tf1
        if ( node -> childCount() != 1 || ! node -> hasName( tf1 ) ) return false;
        node = node -> childAtIndex( 0 ); // tf2
        if ( node -> childCount() != 1 || ! node -> hasName( tf2 ) ) return false;
        node = node -> childAtIndex( 0 ); // tf3
        if ( node -> childCount() != 0 || ! node -> hasName( tf3 ) ) return false;

        if ( tc2 -> childCount() != 1 ) return false;
        node = tc2 -> childAtIndex( 0 ); // tf4
        if ( node -> childCount() != 1 || ! node -> hasName( tf4 ) ) return false;
        node = node -> childAtIndex( 0 ); // tf5
        if ( node -> childCount() != 1 || ! node -> hasName( tf5 ) ) return false;
        node = node -> childAtIndex( 0 ); // tf6
        if ( node -> childCount() != 0 || ! node -> hasName( tf6 ) ) return false;

        if ( tc3 -> childCount() != 1 ) return false;
        node = tc3 -> childAtIndex( 0 ); // tf7
        if ( node -> childCount() != 1 || ! node -> hasName( tf7 ) ) return false;
        node = node -> childAtIndex( 0 ); // tf8
        if ( node -> childCount() != 1 || ! node -> hasName( tf8 ) ) return false;
        node = node -> childAtIndex( 0 ); // tf9
        if ( node -> childCount() != 0 || ! node -> hasName( tf9 ) ) return false;

        cout << "\tAll fragments are in correct positions.\n";
    }
    catch(...)
    {
        cout << "Unexpected exception occured while adding fragments.";
        return false;
    }
    
    return true;
}

bool addFragments ( project* proj )
{
    opensolid::graphNode::sptr tc1;
    opensolid::graphNode::sptr tc2;
    opensolid::graphNode::sptr tc3;
    
    try
    {
        tc1 = proj -> findNode( "testComponent1" );
        tc2 = proj -> findNode( "testComponent2" );
        tc3 = proj -> findNode( "testComponent3" );

        proj -> addNewFragment( tf2, tc1 -> id() );
        proj -> addNewFragment( tf1, tc1 -> id(), 0 );
        proj -> addNewFragment( tf3, tc1 -> id() );

        proj -> addNewFragment( tf6, tc2 -> id() );
        proj -> addNewFragment( tf5, tc2 -> id(), 0 );
        proj -> addNewFragment( tf4, tc2 -> id(), 0 );

        proj -> addNewFragment( tf9, tc3 -> id() );
        proj -> addNewFragment( tf7, tc3 -> id(), 0 );
        proj -> addNewFragment( tf8, tc3 -> id(), 1 );

        // Check structure of fragments.

        opensolid::graphNode::listSptr childList = tc1 -> getChildList();

        if ( ! (*( childList -> atIndex(0) )) -> hasName( tf1 ) ) return false;
        if ( ! (*( childList -> atIndex(1) )) -> hasName( tf2 ) ) return false;
        if ( ! (*( childList -> atIndex(2) )) -> hasName( tf3 ) ) return false;

        childList = tc2 -> getChildList();

        if ( ! (*( childList -> atIndex(0) )) -> hasName( tf4 ) ) return false;
        if ( ! (*( childList -> atIndex(1) )) -> hasName( tf5 ) ) return false;
        if ( ! (*( childList -> atIndex(2) )) -> hasName( tf6 ) ) return false;

        childList = tc3 -> getChildList();

        if ( ! (*( childList -> atIndex(0) )) -> hasName( tf7 ) ) return false;
        if ( ! (*( childList -> atIndex(1) )) -> hasName( tf8 ) ) return false;
        if ( ! (*( childList -> atIndex(2) )) -> hasName( tf9 ) ) return false;
    }
    catch(...)
    {
        cout << "Unexpected exception occured while adding fragments.";
        return false;
    }

    return true;
}

bool testDuplicateName ( project* proj )
{
    // Test whether duplicate node name is caught correctly.

    try
    {
        proj -> addNewComponent ( "testComponent1", NO_PARENT );
    }
    catch( stk::NameInUse )
    {
        return true;
    }
    catch(...)
    {
        cout << "Unexpected exception occured while checking for duplicate name detection.";
        return false;
    }
    
    return false; // If NameInUse wasn't thrown then it is an error.
}

bool addComponents ( project* proj )
{
    // Add components to root of graph.
    
    try
    {
        // Insert components out of order.
        
        proj -> addNewComponent ( "testComponent2", NO_PARENT );
        proj -> addNewComponent ( "testComponent1", NO_PARENT, 0 );
        proj -> addNewComponent ( "testComponent3", NO_PARENT );

        cout << "\tAdded all test components.\n";

        // See whether the component structure is correct.
        
        componentNode::listSptr components = proj -> getComponentList();

        componentNode::sptr comp = components -> atIndex( 0 );
        if ( ! comp -> hasName( "testComponent1") ) return false;
        cout << "\ttestComponent1 correct.\n";

        comp = components -> atIndex( 1 );
        if ( ! comp -> hasName( "testComponent2") ) return false;
        cout << "\ttestComponent2 correct.\n";

        comp = components -> atIndex( 2 );
        if ( ! comp -> hasName( "testComponent3") ) return false;
        cout << "\ttestComponent3 correct.\n";
        
    }
    catch(...)
    {
        cout << "Unexpected exception occured while adding components.";
        return false;
    }

    return true;
}

void dumpGraph( project* proj )
{
    // Dump graph structure to std out.

    proj -> dump();
}

int main()
{
    bool success = true;

    project* proj = 0;

    try
    {
        proj = new project( "testProject" );;
    }
    catch(...)
    {
        cout << "Unexpected exception occured during project construction.";
        success = false;
    }

    // Manipulate graphs.

    if ( success )
    {
        cout << "Invoking addComponents:\n";
        success = addComponents( proj );
        if ( ! success ) cout << "*** addComponents failed ***\n";
    }

    if ( success )
    {
        cout << "Invoking testDuplicateName:\n";
        success = testDuplicateName( proj );
        if ( ! success ) cout << "*** testDuplicateName failed ***\n";
    }

    if ( success )
    {
        cout << "Invoking addFragments:\n";
        success = addFragments( proj );
        if ( ! success ) cout << "*** addFragments failed ***\n";
    }

    if ( success )
    {
        cout << "Invoking testGenericProject:\n";
        success = testGenericProject( proj );
        if ( ! success ) cout << "*** testGenericProject failed ***\n";
    }

    if ( success )
    {
        cout << "Invoking moveFragmentsAround:\n";
        success = moveFragmentsAround( proj );
        if ( ! success ) cout << "*** moveFragmentsAround failed ***\n";
    }

    if ( success )
    {
        cout << "Invoking testEdgeActionFilter:\n";
        success = testEdgeActionFilter( proj );
        if ( ! success ) cout << "*** testEdgeActionFilter failed ***\n";
    }

    if ( ! success ) dumpGraph( proj );

    // Clean up.

    if ( proj ) delete proj;

    if ( success )
        return 0;
    else
        return 1;
}

