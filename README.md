# CPU-scheduling-simulator

The process scheduling (also called as CPU scheduler ) is the activity of the process manager that
handles the removal of the running process from the CPU and the selection of another process on
the basis of a particular strategy. A scheduling allows one process to use the CPU while another is
waiting for I/O, thereby making the system more efficient, fast and fair. In a multitasking computer
system, processes may occupy a variety of states (Figure 1). When a new process is created it is
automaticaly admitted the ready state, waiting for the execution on a CPU. Processes that are ready
for the CPU are kept in a ready queue. A process moves into the running state when it is chosen for
execution. The process's instructions are executed by one of the CPUs of the system. A process
transitions to a waiting state when a call to an I/O device occurs. The processes which are blocked
due to unavailability of an I/O device are kept in a device queue. When a required I/O device
becomes idle one of the processes from its device queue is selected and assigned to it. After
completion of I/O, a process switches from the waiting state to the ready state and is moved to the
ready queue. A process may be terminated only from the running state after completing its
execution. Terminated processes are removed from the OS.

Develop a C++ project that simulates the process scheduling described above, in accordance
with the following parameters:

Process Generation Time (PGT) [ms] – time before generation of a new processes (random
variable with exponential distribution and intensity L ) (round to natural number)

CPU Execution Time (CET) [ms] – process execution time in CPU. Random variable with
uniform distribution between <1, 50> [ms] (natural number)

I/O Call Time (IOT) [ms] – time between getting an access to the CPU and an I/O call.
Random variable with uniform distribution between <0, CET-1> [ms] (natural number). In
case of 0, there is no I/O call.

I/O Device (IOD) – indicates which I/O device is requested by the running process.
Random variable with uniform distribution between <0, NIO-1>, where NIO is the number of
I/O devices in the OS.
