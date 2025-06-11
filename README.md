## 🧠 Dining Philosophers Problem - Multi-Language Solutions

This repository demonstrates various solutions to the classic **Dining Philosophers Problem** using different synchronization primitives:

- 🔒 Mutex (C / POSIX threads)
- 🚦 Semaphore (C / POSIX threads)
- ☕ Monitor (Java)
- 🍎 Swift Playground (Actor)

---

## 📂 Directory Structure

```
.
├── semaphore_4_filsuf.c       # C implementation using POSIX semaphore
├── mutex.c           # C implementation using POSIX mutex
├── solusi_java.java       # Java implementation using synchronized monitor
├── swift\ playground/MyPlayground.playground/
│   └── Contents.swift         # Swift implementation using Actor
├── README.md                  # This file
```

---

## 🔧 Compilation & Run Instructions

### 🔒 Mutex Solution (C)
```bash
gcc -o mutex mutex.c -lpthread
./mutex
```

### 🚦 Semaphore Solution (C)
```bash
gcc -o semaphore_4_filsuf semaphore_4_filsuf.c -lpthread
./semaphore_4_filsuf
```

### ☕ Java Monitor Solution
```bash
javac solusi_java.java
java solusi_java
```

### 🍎 Swift Playground
1. Open `swift\ playground/MyPlayground.playground` in Xcode.
2. Run the playground.

---

## 📌 Problem Overview

**Dining Philosophers Problem**:
Five philosophers sit at a table doing one of three things:
- Thinking 🤔
- Hungry 😋
- Eating 🍽️

Each philosopher needs two forks (shared resources) to eat. The goal is to design a solution that:
- Prevents **deadlock**
- Avoids **starvation**
- Maintains **mutual exclusion**

---

## 🛠️ Solution Strategies

### 🔒 C with Mutex
Each fork is protected with a `pthread_mutex_t`. Philosophers must acquire the **left and right mutex** before eating.

**Potential Issue**: Can lead to **deadlock** if all philosophers grab their left fork and wait indefinitely for the right one.

### 🚦 C with Semaphore
Uses an additional **room semaphore** (count = 4) to ensure only four philosophers can try eating at the same time, breaking the circular wait condition.

**Advantage**: Prevents deadlock by limiting concurrency.

### ☕ Java Monitor
Leverages Java's `synchronized` blocks to control access. Each philosopher tries to pick up forks using condition variables.

**Advantage**: Cleaner and safer syntax with built-in monitor mechanism.

### 🍎 Swift Playground
Implements the logic using `Actor` from to synchronize fork access.

**Advantage**: Demonstrates the problem and solution in Apple ecosystem.

---

## ✅ Why Monitor is Preferred

Monitors provide:
- Built-in **mutual exclusion**
- Easier to reason about compared to semaphores
- Reduced chance of **timing bugs**, such as calling `signal()` before `wait()`

As Per Brinch Hansen (1973) and C.A.R. Hoare (1974) proposed, monitors encapsulate both data and synchronization, reducing programmer error.

---

## 📚 References

- Hansen, P. B. (1973). Operating System Principles. Prentice-Hall, Inc. https://dl.acm.org/doi/10.5555/540365
- Hoare, C. A. R. (1974). Monitors: An Operating System Structuring Concept. Communications of the ACM, 17(10), 549–557. https://doi.org/10.1145/355620.361161
- Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). Operating System Concepts (10th ed.). Wiley.
- [Swift Concurrency – Apple Developer Documentation](https://developer.apple.com/documentation/dispatch/dispatchsemaphore)

---

## ✍️ Author

Ade Dwi Prayitno — iOS Developer  
*Feel free to contribute or fork this repository!*
