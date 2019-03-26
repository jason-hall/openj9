/*******************************************************************************
 * Copyright (c) 2019, 2019 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#include "RealtimeSchedulerDelegate.hpp"

#if defined(J9VM_GC_REALTIME)

#include "EnvironmentRealtime.hpp"
#include "GCExtensions.hpp"
#include "Heap.hpp"

void
MM_RealtimeSchedulerDelegate::reportStopGCIncrement(MM_EnvironmentRealtime *env)
{
	OMRPORT_ACCESS_FROM_ENVIRONMENT(env);
	MM_GCExtensions *extensions = MM_GCExtensions::getExtensions(env);
	TRIGGER_J9HOOK_MM_PRIVATE_METRONOME_INCREMENT_END(extensions->privateHookInterface, env->getOmrVMThread(), omrtime_hires_clock(), J9HOOK_MM_PRIVATE_METRONOME_INCREMENT_END,
		extensions->heap->getApproximateActiveFreeMemorySize(),
		0,
		extensions->globalGCStats.metronomeStats.classLoaderUnloadedCount,
		extensions->globalGCStats.metronomeStats.classesUnloadedCount,
		extensions->globalGCStats.metronomeStats.anonymousClassesUnloadedCount,
		extensions->globalGCStats.metronomeStats.nonDeterministicSweepCount,
		extensions->globalGCStats.metronomeStats.nonDeterministicSweepConsecutive,
		extensions->globalGCStats.metronomeStats.nonDeterministicSweepDelay,
		extensions->markJavaStats._weakReferenceStats._cleared,
		extensions->markJavaStats._softReferenceStats._cleared,
		extensions->getMaxSoftReferenceAge(),
		extensions->getDynamicMaxSoftReferenceAge(),
		extensions->markJavaStats._phantomReferenceStats._cleared,
		extensions->markJavaStats._unfinalizedEnqueued,
		extensions->globalGCStats.metronomeStats.getWorkPacketOverflowCount(),
		extensions->globalGCStats.metronomeStats.getObjectOverflowCount()
	);
}

#endif /* defined(J9VM_GC_REALTIME) */

