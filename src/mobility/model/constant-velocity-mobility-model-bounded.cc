/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006, 2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "constant-velocity-mobility-model-bounded.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (ConstantVelocityMobilityModelBounded);

TypeId ConstantVelocityMobilityModelBounded::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ConstantVelocityMobilityModelBounded")
    .SetParent<MobilityModel> ()
    .SetGroupName ("Mobility")
    .AddConstructor<ConstantVelocityMobilityModelBounded> ()
    .AddAttribute ("Bounds", "The 2d bounding area",
                   RectangleValue (Rectangle (0, 2600, 0, 10)),
                   MakeRectangleAccessor (&ConstantVelocityMobilityModelBounded::m_bounds),
                   MakeRectangleChecker ())
    ;
  return tid;
}

ConstantVelocityMobilityModelBounded::ConstantVelocityMobilityModelBounded ()
{
}

ConstantVelocityMobilityModelBounded::~ConstantVelocityMobilityModelBounded ()
{
}

void
ConstantVelocityMobilityModelBounded::SetVelocity (const Vector &speed)
{
  m_helper.Update ();
  m_helper.SetVelocity (speed);
  m_helper.Unpause ();
  NotifyCourseChange ();
}


Vector
ConstantVelocityMobilityModelBounded::DoGetPosition (void) const
{
  m_helper.UpdateWithWrappingBounds (m_bounds);
  return m_helper.GetCurrentPosition ();
}
void 
ConstantVelocityMobilityModelBounded::DoSetPosition (const Vector &position)
{
  m_helper.SetPosition (position);
  NotifyCourseChange ();
}
Vector
ConstantVelocityMobilityModelBounded::DoGetVelocity (void) const
{
  return m_helper.GetVelocity ();
}

} // namespace ns3
