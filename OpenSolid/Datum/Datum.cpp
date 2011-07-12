/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <OpenSolid/Datum/Datum.hpp>

namespace OpenSolid
{
    MatrixXd orthogonalBasis(const MatrixXd& vectors) {
        MatrixXd result = vectors.householderQr().householderQ();
        int num_candidate_directions = min(vectors.cols(), vectors.rows() - 1);
        for (int i = 0; i < num_candidate_directions; ++i) {
            if (vectors.col(i).dot(result.col(i)) < 0) {result.col(i) = -result.col(i);}
        }
        if (result.determinant() < 0) {
            result.col(num_candidate_directions) = -result.col(num_candidate_directions);
        }
        return result;
    }
}
