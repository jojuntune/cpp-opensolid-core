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

#include <OpenSolid/Core/Simplex/TetrahedronEdges.hpp>

namespace opensolid
{
    detail::TetrahedronEdges
    ScalingFunction<detail::TetrahedronEdges>::operator()(
        const detail::TetrahedronEdges& tetrahedronEdges,
        double scale
    ) const {
        return scalingFunction(tetrahedronEdges.tetrahedron(), scale).edges();
    }

    detail::TetrahedronEdges
    TranslationFunction<detail::TetrahedronEdges>::operator()(
        const detail::TetrahedronEdges& tetrahedronEdges,
        const Vector3d& vector
    ) const {
        return translationFunction(tetrahedronEdges.tetrahedron(), vector).edges();
    }

    detail::TetrahedronEdges
    TransformationFunction<detail::TetrahedronEdges, 3>::operator()(
        const detail::TetrahedronEdges& tetrahedronEdges,
        const Matrix3d& matrix
    ) const {
        return transformationFunction(tetrahedronEdges.tetrahedron(), matrix).edges();
    }

    detail::TetrahedronEdges
    MorphingFunction<detail::TetrahedronEdges, 3>::operator()(
        const detail::TetrahedronEdges& tetrahedronEdges,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        return morphingFunction(tetrahedronEdges.tetrahedron(), morphingExpression).edges();
    }
}
