# Philosophers

<img src="https://i.insider.com/5811064b362ca478258b4dd0?width=1136&format=jpeg"/>

## What Is Philosophers?

The simulation consists of a group of philosophers sitting at a round table with a large bowl of spaghetti in the middle of the table. The philosophers alternate between eating, thinking, and sleeping.

While a philosopher is eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, while sleeping, they are not eating nor thinking.

There are also forks on the table. There are as many forks as philosophers, and a philosopher takes their right and left forks to eat, one in each hand. If there is only one philosopher, there should be only one fork on the table. Once they have finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again.

The simulation stops when a philosopher dies of starvation. Every philosopher needs to eat and should never starve. Philosophers don't speak with each other, and they don't know if another philosopher is about to die. Therefore, they should avoid dying.

## Explaining The Problem

There are 5 philosophers sitting around a round table eating spaghetti and each of them has one chopstick between them. All 5 of them sit around the table and pick up the chopstick placed towards their right. But, here’s the problem. To eat the spaghetti they need both the chopsticks and since everyone picked up the chopstick to their right, nobody gets the left chopstick and hence, nobody can eat.

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

* `pthread_join` - join with a terminated thread 

* `pthread_mutex_init` - initializes the mutex object 

* `pthread_mutex_destroy` - destroy a mutex object 

* `pthread_mutex_lock` - locks the given mutex

* `pthread_mutex_unlock` - unlock the given mutex

## What Is Threads

> A thread is a basic unit of CPU Utilization.

>Like processes, threads are a mechanism that permits an application to perform multiple tasks concurrently.

>A single process can contain multiple threads, All of these thread are independently executing the same program, and they all share the same globale memory.

<img src="Screen Shot 2023-05-06 at 12.12.58 PM 1.png">

