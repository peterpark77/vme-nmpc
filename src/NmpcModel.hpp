/* This file is part of vme-nmpc.
 *
 * Copyright (C) 2015 Timothy A.V. Teatro - All rights Reserved
 *
 * vme-nmpc is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * vme-nmpc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * vme-nmpc. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VME_NMPC_SRC_NMPCMODEL_HPP_
#define VME_NMPC_SRC_NMPCMODEL_HPP_

#include "Obstacle.hpp"
#include "linear.hpp"

/**
 * This template class provides an interface which must be offered by all plant
 * models which are to be compatible with the other objects in the NMPC
 * calculation.
 *
 * The template parameters specify the data structure that will be used to relay
 * the current state estimate to the model in order to seed the NMPC computation
 * and close the feedback loop.
 */
template <typename seedType, typename cmdType>
class NmpcModel {
 public:
  virtual ~NmpcModel() = default;
  virtual void seed(seedType &) = 0;
  virtual void compute_forecast() noexcept = 0;
  virtual void compute_path_potential_gradient(
      ObstacleContainer &obstacles) noexcept = 0;
  virtual void compute_tracking_errors() noexcept = 0;
  virtual void compute_gradient() noexcept = 0;
  virtual cmdType retrieve_command(int) const = 0;
  virtual unsigned get_horizonSize() const = 0;
};

#endif  // VME_NMPC_SRC_NMPCMODEL_HPP_
