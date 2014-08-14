/**
 * \file
 * \brief idleThreadControlBlock object definition
 *
 * \author Copyright (C) 2014 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2014-08-14
 */

#include "distortos/scheduler/idleThreadControlBlock.hpp"

#include "distortos/scheduler/Thread.hpp"

namespace distortos
{

namespace scheduler
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// size of idle thread's stack, bytes
constexpr size_t idleThreadStackSize_ {128};

/// idle thread's stack
uint64_t idleThreadStack_[idleThreadStackSize_ / sizeof(uint64_t)];

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Idle thread's main function
 */

void idleThread_()
{
	volatile uint64_t i {};

	while (1)
	{
		++i;
	}
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global objects
+---------------------------------------------------------------------------------------------------------------------*/

Thread<void (&)()> idleThreadControlBlock = makeThread(idleThreadStack_, sizeof(idleThreadStack_), 0, idleThread_);

}	// namespace scheduler

}	// namespace distortos
