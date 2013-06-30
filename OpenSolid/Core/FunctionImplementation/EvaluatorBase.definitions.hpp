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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/FunctionImplementation/EvaluatorBase.declarations.hpp>

#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/FunctionImplementation.declarations.hpp>

#include <cstdint>
#include <unordered_map>
#include <utility>

namespace opensolid
{
    class EvaluatorBase
    {
    protected:
        typedef std::pair<const FunctionImplementation*, const double*> KeyXd;
        typedef std::pair<const FunctionImplementation*, const Interval*> KeyXI;

        struct KeyHash
        {
            template <class TScalar>
            std::size_t
            operator()(const std::pair<const FunctionImplementation*, const TScalar*>& key) const;
        };

        template <class TScalar>
        struct Types;

        template <class TScalar>
        friend struct Types;
    };

    template <>
    struct EvaluatorBase::Types<double>
    {
        typedef MapXd Map;
        typedef MapXcd ConstMap;
        typedef MatrixXd Matrix;
        typedef std::pair<const FunctionImplementation*, const double*> Key;
        typedef std::unordered_map<Key, Matrix, EvaluatorBase::KeyHash> Cache;
    };

    template <>
    struct EvaluatorBase::Types<Interval>
    {
        typedef MapXI Map;
        typedef MapXcI ConstMap;
        typedef MatrixXI Matrix;
        typedef std::pair<const FunctionImplementation*, const Interval*> Key;
        typedef std::unordered_map<Key, Matrix, EvaluatorBase::KeyHash> Cache;
    };
}
