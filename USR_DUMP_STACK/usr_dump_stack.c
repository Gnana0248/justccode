/*H**********************************************************************
* FILENAME         : usr_dump_stack.c
*
* DESCRIPTION      : User space backtrace of any C function
*
* PUBLIC FUNCTIONS : void usr_dump_stack (void)
*
* NOTES            : Implemented to demo the Kernel dump_stack
*                    function in user space.

* AUTHOR           : Gnanaprakash.Selvam   START DATE : 15 August 20201
**H**********************************************************************/
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <stdio.h>
#include "usr_dump_stack.h"

/*******************************************************************
* NAME        :    void usr_dump_stack (void)
*
* DESCRIPTION :     To dump the user process call stack
*
* INPUTS      :     N/A
* OUTPUTS     :     Backtrace with Function_Name SP IP
* RETURN      :     N/A
*
* NOTES       :     In case you like libc function:
*                   https://linux.die.net/man/3/backtrace_symbols
********************************************************************/
void usr_dump_stack (void) {
    /* To dump stack trace number */
    int stack_num = 0;
	/* Unwind backtrace structures */
	unw_cursor_t cursor;
	unw_context_t uc;
	unw_word_t ip, sp;
	/* To get Frame-related registers, such as the stack-pointer, will be stored */
	if (unw_getcontext(&uc) != 0) {
        /* Failed to get the backtrace */
        printf("\nError: Failed to get the backtrace");
		return;
	}
	/* Initial stack frame at which unwinding starts */
	if (unw_init_local(&cursor, &uc) != 0) {
        /* Failed to get the backtrace */
        printf("\nError: Failed to init the stackframe");
		return;
	}
	/* Advances the unwind cursor to the next older (nested stack frame) */
	while (unw_step(&cursor) > 0) {
		/* Function name from stack unwind */
		char func_name[129];
		unw_word_t off;

		int result = unw_get_proc_name (&cursor, func_name, sizeof (func_name) - 1, &off);
		if (result < 0 && result != UNW_ENOMEM) {
            printf("\nError: Failed to get proc name");
            break;
		}
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		unw_get_reg(&cursor, UNW_REG_SP, &sp);
		printf ("#%d ip[0x%lx] sp[0x%lx] [<0x%08x>] %s\n", stack_num++,(long) ip, (long) sp, (unsigned int)off, func_name);
	}
}
