# Stack Backtracing in User Mode
- Added changes similar to Kernel dump_stack().

- User mode libc is already gave a API, In case if you want to try it out: https://man7.org/linux/man-pages/man3/backtrace.3.html

- Included Unwind functions to un wind the backtrace of User process.

- Needed for gcc compilation to use unwind library: `sudo apt-get install libunwind`

- To compile the code to use unwind library: `gcc <file.c> usr_dump_stack.c -o <file.o> -lunwind

- Created a test.c file and have invoked to two fucntion to dump the backtrace.

```
	int funclose() {
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
```
- Backtrace output:

```
#0 ip[0x5593ea985216] sp[0x7ffce0ad5100] [<0x0000000d>] funclose
#1 ip[0x5593ea98522b] sp[0x7ffce0ad5110] [<0x00000012>] funcreate
#2 ip[0x5593ea98524b] sp[0x7ffce0ad5120] [<0x0000001d>] main
#3 ip[0x7f06d542a0b3] sp[0x7ffce0ad5140] [<0x000000f3>] __libc_start_main
#4 ip[0x5593ea98514e] sp[0x7ffce0ad5210] [<0x0000002e>] _start
```