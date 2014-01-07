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
    template <class TDerived>
    class Transformable;

    template <class T>
    struct IsTransformable;

    template <class TTransformable>
    struct NumDimensions;

    template <class TTransformable>
    struct ScaledType;

    template <class TTransformable>
    struct TranslatedType;

    template <class TTransformable, int iNumResultDimensions>
    struct TransformedType;

    template <class TTransformable, int iNumResultDimensions>
    struct MorphedType;

    template <class TTransformable>
    struct ScalingFunction;

    template <class TTransformable>
    struct TranslationFunction;

    template <class TTransformable, int iNumResultDimensions>
    struct TransformationFunction;

    template <class TTransformable, int iNumResultDimensions>
    struct MorphingFunction;

    template <class TTransformable>
    struct ScaledAboutPointType;

    template <class TTransformable>
    struct TransformedAboutPointType;

    template <class TTransformable, int iNumResultDimensions>
    struct LocalizedType;

    template <class TTransformable, int iNumResultDimensions>
    struct GlobalizedType;

    template <class TTransformable, int iNumResultDimensions>
    struct TransplantedType;
}
