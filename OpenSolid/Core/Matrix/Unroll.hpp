/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iCount>
        struct Unroll
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                for (std::int64_t index = 0; index < iCount; ++index) {
                    function(index);
                }
            }
        };

        template <>
        struct Unroll<0>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
            }
        };

        template <>
        struct Unroll<1>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
            }
        };

        template <>
        struct Unroll<2>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
            }
        };

        template <>
        struct Unroll<3>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
            }
        };

        template <>
        struct Unroll<4>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
                function(3);
            }
        };

        template <>
        struct Unroll<5>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
                function(3);
                function(4);
            }
        };

        template <>
        struct Unroll<6>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
                function(3);
                function(4);
                function(5);
            }
        };

        template <>
        struct Unroll<7>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
                function(3);
                function(4);
                function(5);
                function(6);
            }
        };

        template <>
        struct Unroll<8>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
                function(3);
                function(4);
                function(5);
                function(6);
                function(7);
            }
        };

        template <>
        struct Unroll<9>
        {
            template <class TFunction>
            inline
            Unroll(TFunction function) {
                function(0);
                function(1);
                function(2);
                function(3);
                function(4);
                function(5);
                function(6);
                function(7);
                function(8);
            }
        };
    }
}
