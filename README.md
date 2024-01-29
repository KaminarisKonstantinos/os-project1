# Operating Systems University Project #1

This project is designed to leverage shared memory and semaphores for efficient workload distribution across multiple CPU cores. The main objective is to demonstrate a simple yet effective way to parallelize computations, specifically the Monte Carlo integration of the function `sin(cos(x))` over the interval [0,1]. 

## Key Points

- **Shared Memory Usage:** The project utilizes shared memory to allow multiple processes to communicate and collaborate on the computational workload.

- **Semaphore Implementation:** Semaphores are employed to synchronize access to shared resources, ensuring proper coordination and avoiding race conditions.

- **Load Balancing:** Computational tasks, in this case, the Monte Carlo integration of `sin(cos(x))`, are divided among multiple CPU cores, promoting parallel processing and optimizing overall performance.

