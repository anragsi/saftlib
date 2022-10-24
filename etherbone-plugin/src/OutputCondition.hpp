/** Copyright (C) 2011-2016 GSI Helmholtz Centre for Heavy Ion Research GmbH 
 *
 *  @author Wesley W. Terpstra <w.terpstra@gsi.de>
 *
 *******************************************************************************
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
 */
#ifndef EB_PLUGIN_OUTPUT_CONDITION_HPP
#define EB_PLUGIN_OUTPUT_CONDITION_HPP

#include "Owned.hpp"
#include "Condition.hpp"

// @saftbus-include
#include <Time.hpp>

#include <saftbus/service.hpp>

#include <functional>

namespace eb_plugin {

class OutputCondition_Service;

class OutputCondition : public Owned, public Condition 
{
public:
	OutputCondition(ActionSink *sink, unsigned number, bool active, uint64_t id, uint64_t mask, int64_t offset, uint32_t tag, saftbus::Container *container);

    // this typedef is needed for the ActionSink::NewCondition template function
    typedef OutputCondition_Service ServiceType;
};

}

#endif
