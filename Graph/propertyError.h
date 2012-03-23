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

#ifndef OS_GRAPH_PROPERTY_ERROR_H
#define OS_GRAPH_PROPERTY_ERROR_H

#include <string>

namespace opensolid
{

class propertyError
{
    public:

        //! Construct PropertyError.
        //! @param nodeId Node that contains property that caused error.
        //! @param propertyIndex Index within node of property that caused error.
        //! @param errorType Type of error that occurred.
        //! @param lineNumber For multi-line properties, line number where error occurred.
        //! @param message General message associated with error. Usually from exception that caused error.

        propertyError ( int nodeId, int propertyIndex, int errorType, int lineNumber, std::string message )
            : node_id( nodeId ), property_index( propertyIndex ), error_type( errorType ),
              line_number( lineNumber ), _message( message ) {}

        int nodeId() const { return node_id; } //!< Get Node ID of node that caused error.
        int propertyIndex() const { return property_index; } //!< Get index of property within node that caused error.
        int errorType() const { return error_type; } //!< Get error type of error that occurred.
        int lineNumber() const { return line_number; } //!< Get line number within property where error occurred.
        std::string message() const { return _message; } //!< Get general message associated with the error.

        enum errorTypes
        {
            UNKNOWN,
            SYNTAX_ERROR
        };

    private:

        int     node_id;
        int     property_index;
        int     error_type;
        int     line_number;

        std::string   _message;
};

}

#endif
