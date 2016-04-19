//This file is part of Bertini 2.
//
//fixed_prec_powerseries_endgame.hpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//fixed_prec_powerseries_endgame.hpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with fixed_prec_powerseries_endgame.hpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2015, 2016 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
// daniel brake, university of notre dame
// Tim Hodges, Colorado State University




#pragma once

/**
\file fixed_prec_powerseries_endgame.hpp

\brief Contains the fixed precision power series endgame type.
*/


namespace bertini{ namespace tracking { namespace endgame {

template<class TrackerT>
class FixedPrecPowerSeriesEndgame : public PowerSeriesEndgame<TrackerT,typename TrackerT::BaseComplexType>
{

}; // class FixedPrecPowerSeriesEndgame



}}} // re: namespaces
