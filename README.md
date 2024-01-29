# Parallel Monte Carlo Integration using Shared Memory and Semaphores - OS University Project #1

This project is designed to leverage shared memory and semaphores for efficient workload distribution across multiple CPU cores. The main objective is to demonstrate a simple yet effective way to parallelize computations, specifically the Monte Carlo integration of the function `sin(cos(x))` over the interval [0,1]. 

## Key Points

- **Shared Memory Usage:** The project utilizes shared memory to allow multiple processes to communicate and collaborate on the computational workload.

- **Semaphore Implementation:** Semaphores are employed to synchronize access to shared resources, ensuring proper coordination and avoiding race conditions.

- **Load Balancing:** Computational tasks, in this case, the Monte Carlo integration of `sin(cos(x))`, are divided among multiple CPU cores, promoting parallel processing and optimizing overall performance.

## Files

- **integral_mc_seq.c:** The initial implementation of Monte Carlo integration without parallel processing.

- **integral_mc_shm.c:** In this version, each process-child writes to its dedicated memory address. After completing their calculations, the process-parent aggregates the results to determine the final outcome.

- **integral_mc_shm_sem.c:** This version employs shared memory, with each process-child writing to the same memory address. To ensure proper coordination and prevent conflicts, a semaphore is used to synchronize access between processes.

## Performance Testing with Varying Numbers of CPU Cores

<p align="center">
<img align="center" alt="chebotko" width="80%" src="./images/shm.png?raw=true" />
</p>
<p align="center">
<img align="center" alt="chebotko" width="80%" src="./images/shm_sem.png?raw=true" />
</p>

> Note: The tests were conducted on a 4-core CPU, and as a result, performance does not improve when attempting to utilize more than 4 processes.

## Documentation in Greek

For detailed information in Greek, refer to the following documents:

- **Original Assignment:** Find the original project assignment in Greek within Part 2 of the `Project1-OS-2023-2024_final.pdf` file.

- **Project Report:** Access my detailed report, written in Greek, in Part 2 of the `OS-Report1.pdf` file.
