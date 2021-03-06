/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of FreeOSEK.
 *
 * FreeOSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Linking FreeOSEK statically or dynamically with other modules is making a
 * combined work based on FreeOSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of FreeOSEK give
 * you permission to combine FreeOSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with FreeOSEK solely through the FreeOSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for FreeOSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of FreeOSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * FreeOSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \brief FreeOSEK Internal Arch Implementation File
 **
 ** \file arm7/Osek_Internal_Arch.c
 ** \arch arm7
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Internal
 ** @{ */


/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090330 v0.1.1 MaCe add NO_EVENTS and NON_PREEMPTIVE evaluation and
 *								improvement of FIQ_Routine
 * 20081116 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Osek_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void* Osek_NewTaskPtr_Arch;

void* Osek_OldTaskPtr_Arch;

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void IRQ_Routine
(
	void
)
{
   while (1);
}

void FIQ_Routine
(
	void
)
{
#if (ALARMS_COUNT != 0)
	/* to save the context during the interrupt */
	ContextType context;
	/* counter increment */
	static CounterIncrementType CounterIncrement = 1;

	/* increment the disable interrupt conter to avoid enable the interrupts */
	SuspendAllInterrupts_Counter++;

	/* save actual context */
	context = GetCallingContext();

	/* set context to CONTEXT_SYS */
	SetActualContext(CONTEXT_DBG);

	/* call counter interrupt handler */
	CounterIncrement = IncrementCounter(0, 1 /* CounterIncrement */);

	/* interrupt has to be called first after so many CounterIncrement */
	/* SetCounterTime(CounterIncrement); */

	/* set context back */
	SetActualContext(context);

	/* set the disable interrupt conter back */
	SuspendAllInterrupts_Counter--;
#endif /* #if (ALARMS_COUNT != 0) */

	/* enable counter interrupt again */
	T0IR |= 1;

#if 0 /* TODO */
#if (NON_PREEMPTIVE == DISABLE)
		/* check if interrupt a Task Context */
		if ( GetCallingContext() ==  CONTEXT_TASK )
		{
			if ( TasksConst[GetRunningTask()].ConstFlags.Preemtive )
			{
				/* \req TODO Rescheduling shall take place only if interrupt a
				 * preemptable task. */
				(void)Schedule();
			}
		}
#endif /* #if (NON_PREEMPTIVE == ENABLE) */
#endif
}

void SWI_Routine
(
	void
)
{
   while (1);
}

void UNDEF_Routine
(
	void
)
{
	volatile uint8 foo = 1;

   while (foo);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

