//This file is part of Bertini 2.
//
//amp_criteria.hpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//amp_criteria.hpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with amp_criteria.hpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2015, 2016 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
// daniel brake, university of notre dame


#ifndef BERTINI_AMP_CRITERIA_HPP
#define BERTINI_AMP_CRITERIA_HPP

/**
\file amp_criteria.hpp

\brief Provides the Adaptive Multiple Precision criteria functions.

*/

#include "bertini2/tracking/tracking_config.hpp"

namespace bertini{
	namespace tracking{
		namespace amp{



			using AdaptiveMultiplePrecisionConfig = config::AdaptiveMultiplePrecisionConfig;


			/**
			\brief Check AMP Criterion A.

			From \cite AMP1, \cite AMP2.

			True means the check passed, and the precision is all good.  False means something's gotta change, stepsize or precision.
			
			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param AMP_config The settings for adaptive multiple precision.
			
			\tparam RealType The real number type

			\return True if criteria satisfied, false if violated and precision or step length should be adjusted.
			*/
			template<typename RealType>
			bool CriterionA(RealType const& norm_J, RealType const& norm_J_inverse, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				return NumTraits<RealType>::NumDigits()  > AMP_config.safety_digits_1 + log10(norm_J_inverse * RealType(AMP_config.epsilon) * (norm_J + RealType(AMP_config.Phi) ) );
			}
			


			/**
			\brief Compute the expression \f$D\f$ from the AMP papers \cite AMP1, \cite AMP2.

			\tparam RealType The real number type

			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param AMP_config The settings for adaptive multiple precision.
			*/
			template <typename RealType>
			RealType D(RealType const& norm_J, RealType const& norm_J_inverse, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				return log10(norm_J_inverse*( (RealType(2)+RealType(AMP_config.epsilon))*norm_J + RealType(AMP_config.epsilon)*RealType(AMP_config.Phi)) + RealType(1));
			}

			/**
			\brief Evaluate the right hand side of the inequality of Criterion B

			From \cite AMP1, \cite AMP2.
			
			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param num_newton_iterations_remaining The number of iterations which have yet to perform.
			\param tracking_tolerance The tightness to which the path should be tracked.  This is the raw tracking tolerance (for now)
			\param latest_newton_residual The norm of the length of the most recent Newton step.
			\param AMP_config The settings for adaptive multiple precision.
			
			\tparam RealType the real number type.

			\return The value of the right hand side of Criterion B
			*/
			template<typename RealType>
			RealType CriterionBRHS(RealType const& norm_J, RealType const& norm_J_inverse, unsigned num_newton_iterations_remaining, RealType const& tracking_tolerance, RealType const& norm_of_latest_newton_residual, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				return AMP_config.safety_digits_1 + D(norm_J, norm_J_inverse, AMP_config) + (-log10(tracking_tolerance) + log10(norm_of_latest_newton_residual)) / (num_newton_iterations_remaining);
			}


			/**
			\brief Check AMP Criterion B
			
			This is Criterion B from \cite AMP1, \cite AMP2.
			True means the check passed, and the precision is all good.  False means something's gotta change, stepsize or precision.
			
			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param num_newton_iterations_remaining The number of iterations which have yet to perform.
			\param tracking_tolerance The tightness to which the path should be tracked.  This is the raw tracking tolerance (for now)
			\param latest_newton_residual The norm of the length of the most recent Newton step.
			\param AMP_config The settings for adaptive multiple precision.
			
			\tparam RealType the real number type.

			\return True if criteria satisfied, false if violated and precision or step length should be adjusted.
			*/
			template<typename RealType>
			bool CriterionB(RealType const& norm_J, RealType const& norm_J_inverse, unsigned num_newton_iterations_remaining, RealType const& tracking_tolerance, RealType const& norm_of_latest_newton_residual, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				return NumTraits<RealType>::NumDigits() > CriterionBRHS(norm_J, norm_J_inverse, num_newton_iterations_remaining, tracking_tolerance,  norm_of_latest_newton_residual, AMP_config);
			}


			


			/**
			\brief Evaluate the right hand side of Criterion C

			This is Criterion C, from \cite AMP1, \cite AMP2.

			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param tracking_tolerance The tightness to which the path should be tracked.  This is the raw tracking tolerance
			\param norm_z The norm of the current space point.
			\param AMP_config The settings for adaptive multiple precision.
			
			\tparam RealType the real number type.

			\return The value of the right hand side of the inequality from Criterion C.
			*/
			template<typename RealType>
			RealType CriterionCRHS(RealType const& norm_J_inverse, RealType const& norm_z, RealType tracking_tolerance, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				return AMP_config.safety_digits_2 + -log10(tracking_tolerance) + log10(norm_J_inverse*RealType(AMP_config.Psi) + norm_z);
			}



			/**
			\brief Evaluate the right hand side of Criterion C

			This is Criterion C from \cite AMP1, \cite AMP2.

			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param tracking_tolerance The tightness to which the path should be tracked.  This is the raw tracking tolerance
			\param z The current space point. 
			\param AMP_config The settings for adaptive multiple precision.

			\return The value of the right hand side of the inequality from Criterion C.
			*/
			template<typename RealType, typename Derived>
			RealType CriterionCRHS(RealType const& norm_J_inverse, const Eigen::MatrixBase<Derived>& z, RealType tracking_tolerance, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				using ComplexType = typename Derived::Scalar;
				static_assert(std::is_same<typename Eigen::NumTraits<RealType>::Real, typename Eigen::NumTraits<ComplexType>::Real>::value,"underlying complex type and the type for comparisons must match");

				return CriterionCRHS(norm_J_inverse, z.norm(), tracking_tolerance, AMP_config);
			}


			/**
			\brief Check AMP Criterion C

			This is Criterion C from \cite AMP1.

			True means the check passed, and the precision is all good.  False means something's gotta change, stepsize or precision.
			
			\param norm_J The matrix norm of the Jacoabian matrix
			\param norm_J_inverse An estimate on the norm of the inverse of the Jacobian matrix.
			\param tracking_tolerance The tightness to which the path should be tracked.  This is the raw tracking tolerance
			\param z The current space point. 
			\param AMP_config The settings for adaptive multiple precision.
			*/
			template<typename RealType, typename Derived>
			bool CriterionC(RealType const& norm_J_inverse, const Eigen::MatrixBase<Derived>& z, RealType tracking_tolerance, AdaptiveMultiplePrecisionConfig const& AMP_config)
			{
				using ComplexType = typename Derived::Scalar;
				static_assert(std::is_same<typename Eigen::NumTraits<RealType>::Real, typename Eigen::NumTraits<ComplexType>::Real>::value,"underlying complex type and the type for comparisons must match");

				return NumTraits<RealType>::NumDigits() > CriterionCRHS(norm_J_inverse, z, tracking_tolerance, AMP_config);
			}
		}
	}
	
}


#endif

