#include <stdio.h>

#include "usr_dump_stack.h" // Required usr_dump_stack()

int funclose() {
   /* To dump the backtrace */
   usr_dump_stack();
}

int funcreate() {
   funclose();
}

int main(int argc, char **argv)
{
   funcreate();
   return 0;
}
