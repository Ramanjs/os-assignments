# Dining Philosophers Problem

## Part A

1. **Problem 1**: Since Philosopher 1 and Philosopher 4 can eat at the same time, they are scheduled together. Similarly for Philosopher 2 and Philosopher 5. After they finish eating, Philosopher 3 is scheduled at the end. This algorithm is using strict ordering of resources.

2. **Problem 2**: We have used 5 semaphores to implement synchronisation. A philosopher first checks if the left fork and right fork both are available. Then it acquires both semaphores and begins to eat. After eating, the philosopher releases the forks so others can use them.

## Part B

1. **Problem 1**: Similar to problem 1 of part a, philosopher 1 and philosopher 4 can use bowl 1 and bowl 2 at the same time respectively. 

2. **Problem 2**: Here two additional semaphores for bowls are used in the philosopher algorithm. First a philosopher checks if any of the two bowls is available, then picks it up and begins eating. After they are finished eating, they release both the forks and the bowl.
