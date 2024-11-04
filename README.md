# Philosophers 🤔

This project is part of the 42 school curriculum and simulates the dining philosophers problem, exploring concepts of threading, process management, and resource sharing.

## Contents 📚

1. [Problem Description](#problem-description)
2. [Project Structure](#project-structure)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Implementation Details](#implementation-details)

## Problem Description 📖

The dining philosophers problem is a classic computer science problem that illustrates synchronization issues and techniques for resolving them:

- Philosophers sit at a round table
- There is a bowl of spaghetti in the middle
- There are as many forks as philosophers
- Each philosopher needs two forks to eat
- Philosophers alternate between eating, thinking, and sleeping
- If a philosopher doesn't eat within a specified timeframe, they die

## Project Structure 🗂️

```
philosophers/
├── philo/          # Mandatory part (threads & mutexes)
└── philo_bonus/    # Bonus part (processes & semaphores)
```

## Installation 🛠️

```bash
# Clone the repository
git clone https://github.com/yourusername/philosophers.git

# Build mandatory part
cd philo
make

# Build bonus part
cd ../philo_bonus
make
```

## Usage 💻

### Mandatory Part
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Bonus Part
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments 📝

- `number_of_philosophers`: The number of philosophers and forks
- `time_to_die`: Time (ms) after which a philosopher dies if they haven't eaten
- `time_to_eat`: Time (ms) it takes for a philosopher to eat
- `time_to_sleep`: Time (ms) a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: [Optional] Program stops when all philosophers eat this many times

### Example Usage 🎯
```bash
# 5 philosophers, 800ms death time, 200ms eat time, 200ms sleep time
./philo 5 800 200 200

# With optional meals parameter (7 meals)
./philo 5 800 200 200 7
```

## Implementation Details 🔧

### Mandatory Part Features
- Threads for each philosopher
- Mutexes for fork management
- Death monitoring
- Thread-safe state printing

### Bonus Part Features
- Processes for each philosopher
- Semaphores for fork management
- Inter-process communication
- Process monitoring and cleanup

## Error Cases ⚠️

The program handles various error cases:
- Invalid numbers of philosophers
- Invalid time values
- Memory allocation failures
- Thread/process creation failures
- Mutex/semaphore initialization failures

## Allowed Functions 📋

### Mandatory Part
- memset
- printf
- malloc
- free
- write
- usleep
- gettimeofday
- pthread_create
- pthread_detach
- pthread_join
- pthread_mutex_init
- pthread_mutex_destroy
- pthread_mutex_lock
- pthread_mutex_unlock

### Bonus Part
Additionally includes:
- fork
- kill
- exit
- waitpid
- sem_open
- sem_close
- sem_post
- sem_wait
- sem_unlink

## Author 👤
- Alabar (hluiz-ma)

## Acknowledgments 🙏
- 42 School
- Fellow 42 students
