# Philosophers

<p align="center">
<img src="https://i.insider.com/5811064b362ca478258b4dd0?width=1136&format=jpeg" align="center"/>
</p>

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

