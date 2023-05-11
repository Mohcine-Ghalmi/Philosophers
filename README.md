# Philosophers

<img src="https://i.insider.com/5811064b362ca478258b4dd0?width=1136&format=jpeg"/>

## What Is Philosophers?

The simulation consists of a group of philosophers sitting at a round table with a large bowl of spaghetti in the middle of the table. The philosophers alternate between eating, thinking, and sleeping.

While a philosopher is eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, while sleeping, they are not eating nor thinking.

There are also forks on the table. There are as many forks as philosophers, and a philosopher takes their right and left forks to eat, one in each hand. If there is only one philosopher, there should be only one fork on the table. Once they have finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again.

The simulation stops when a philosopher dies of starvation. Every philosopher needs to eat and should never starve. Philosophers don't speak with each other, and they don't know if another philosopher is about to die. Therefore, they should avoid dying.

## Explaining The Problem

There are 5 philosophers sitting around a round table eating spaghetti and each of them has one chopstick between them. All 5 of them sit around the table and pick up the chopstick placed towards their right. But, here’s the problem. To eat the spaghetti they need both the chopsticks and since everyone picked up the chopstick to their right, nobody gets the left chopstick and hence, nobody can eat.


![Alt text](https://static.javatpoint.com/operating-system/images/os-dining-philosophers-problem.gif)<br>
Logically thinking, this problem isn’t really a problem in real life scenario. The philosophers could have asked for a few extra pairs of chopsticks, or they could have eaten using their hands 😂 .

Jokes apart, but the dining philosophers problem is an excellent example to explain the concept of deadlock while resource sharing in OS.

Consider the philosophers to be processes and the chopsticks to be a shared resource. Every process needs two resources out of which one it has already acquired and the other is acquired by some other process. Till the other process does not free the resource, this process cannot proceed. Similarly, the other process is dependent on another process for its resource. Since every process is dependent on each other, it forms a circular-wait and the system goes into a deadlock condition (```a situation in which more than one process is blocked because it is holding a resource and also requires some resource that is acquired by some other process```).

## Function Used In The Project

<img src="Screen Shot 2023-05-05 at 12.17.15 PM.png">

* `memset` - fill a bytes string with a bytes value

* `printf` - prints its arguments

* `malloc` - memory allocation

* `free` - memory deallocation

* `write` - write to a file descriptor

* `usleep` - suspend thread execution for an interval measured in microseconds

* `gettimeofday` - get date and time 

* `pthread_create` - creat a new thread

* `pthread_detach` - detach a thread 

* `pthread_join` - wait for thread termination 

* `pthread_mutex_init` - initializes the mutex object 

* `pthread_mutex_destroy` - destroy a mutex object 

* `pthread_mutex_lock` - locks the given mutex

* `pthread_mutex_unlock` - unlock the given mutex

## What Is Threads

> A thread is a basic unit of CPU Utilization. Like processes, threads are a mechanism that permits an application to perform multiple tasks concurrently. A single process can contain multiple threads, All of these thread are independently executing the same program, and they all share the same globale memory.
<br>Threads themselves can be created either on the stack or on the heap, depending on how they are created. but we use `pthread_create()` function, so the thread's stack is typically allocated on the heap by the operating system. <br>However, you can also create threads with a stack allocated on the stack of the main thread. Regardless of where the thread's stack is allocated, the thread itself will share the same process address space as other threads in the process. <br>This means that threads can share data and communicate with each other using shared variables, regardless of where the memory for those variables is allocated.
<br>When a program is started, the resulting process consists of a single thread, called the initial or main thread.
<img src="Screen Shot 2023-05-06 at 12.12.58 PM 1.png">

## Threads Versus Processes

* Sharing data between threads is easy. By contrast, sharing data between processes requires more work (e.g., creating a shared memory segment or using a pipe).

* Thread creation is faster than process creation; context-switch time may be lower for threads than for processes.

* A bug in one thread (e.g., modifying memory via an incorrect pointer) can damage all of the threads in the process, since they share the same address space and other attributes. By contrast, processes are more isolated from one another.

* In a multithreaded application, all threads must be running the same program (although perhaps in different functions). In a multiprocess application, different processes can run different programs.

* Aside from data, threads also share certain other information (e.g., file descriptors, signal dispositions, current working directory, and user and group IDs). This may be an advantage or a disadvantage, depending on the application.

## Threads Synchronization (mutex `mutual exclusion`)

> Mutexes allow threads to synchronize their use of a shared resource, so that, for example, one thread doesn’t try to access a shared variable at the same time as another thread is modifying it.

>simple example of a problems that can occur when shared resources are not accessed atomically. This program creates two threads, each of which executes the same function. The function executes a loop that repeatedly increments a global variable, `glob`, by copying `glob` into the local variable `loc`, incrementing `loc`, and copying `loc` back to `glob`. (Since `loc` is an automatic variable allocated on the perthread stack, each thread has its own copy of this variable.) The number of iterations of the loop is determined by the command-line argument supplied to the program, or by a default value, if no argument is supplied.<br><img src="Screen Shot 2023-05-07 at 6.03.26 PM.png">

>To avoid the problems that can occur when threads try to update a shared vari- able, we must use a mutex to ensure that only one thread at a time can access the variable. <br> A mutex has two states: locked and unlocked. At any moment, at most one thread may hold the lock on a mutex. When a thread locks a mutex, it becomes the owner of that mutex. Only the mutex owner can unlock the mutex.<br><img src="Screen Shot 2023-05-07 at 8.01.29 PM.png">

## Problems Why We Need mutex

<h3>1- Race condition</h3>
A race condition occurs when two or more threads can access shared data and try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the
change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data.

<h3>2- Deadlock</h3>

A deadlock happens when two threads/processes cannot make progress because each one waits for the other to release a lock, as illustrated in the following diagram.<br>
<img src="https://prepinsta.com/wp-content/uploads/2023/01/Deadlock-in-Operating-System-1.webp">