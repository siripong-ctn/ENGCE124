# ENGCE124
## Data Structures and Algorithms

---

# Course Overview

ENGCE124 (Data Structures and Algorithms) introduces fundamental concepts of organizing, storing, processing, and managing data efficiently. The course focuses on algorithm design, complexity analysis, and the implementation of common data structures used in computer engineering and software development.

The primary objective is to develop problem-solving skills by selecting appropriate data structures and designing efficient algorithms.

---

# Course Objectives

After completing this course, students should be able to:

- Understand fundamental data structures
- Analyze algorithm efficiency
- Apply algorithmic problem-solving techniques
- Implement linear and non-linear data structures
- Analyze time and space complexity
- Design recursive and iterative algorithms
- Select appropriate data structures for specific problems
- Perform searching and sorting operations efficiently
- Understand graph and tree structures
- Develop optimized software solutions

---

# Why Data Structures Matter

Data structures help organize data for efficient access and modification.

Examples:

```text
Social Media     → Graph
File System      → Tree
Undo Operation   → Stack
Task Scheduling  → Queue
Database Index   → Tree
Navigation Map   → Graph
```

Efficient data structures significantly improve:

- Performance
- Memory Usage
- Scalability
- Maintainability

---

# Algorithm Fundamentals

An algorithm is a finite sequence of well-defined instructions used to solve a computational problem.

Characteristics of a Good Algorithm:

- Correctness
- Efficiency
- Simplicity
- Scalability
- Maintainability

Example:

```text
Input Number N
Read N
Calculate N²
Display N²
End
```

---

# Algorithm Design Process

```text
Problem Analysis
        ↓
Algorithm Design
        ↓
Pseudocode
        ↓
Implementation
        ↓
Testing
        ↓
Optimization
```

---

# Pseudocode

Pseudocode provides a language-independent way to describe algorithms.

Example:

```text
START

READ A
READ B

SUM ← A + B

DISPLAY SUM

END
```

---

# Time Complexity

Time complexity measures how execution time grows as the input size increases.

Notation:

```text
O(1)
O(log n)
O(n)
O(n log n)
O(n²)
O(2ⁿ)
```

---

## Constant Time

```text
O(1)
```

Example:

```c
x = array[0];
```

---

## Linear Time

```text
O(n)
```

Example:

```c
for(i=0;i<n;i++)
```

---

## Quadratic Time

```text
O(n²)
```

Example:

```c
for(i=0;i<n;i++)
{
    for(j=0;j<n;j++)
    {
    }
}
```

---

# Space Complexity

Space complexity measures memory usage during algorithm execution.

Examples:

```text
Array
Linked List
Graph
Tree
Hash Table
```

---

# Abstract Data Types (ADT)

An Abstract Data Type defines behavior rather than implementation.

Examples:

```text
Stack
Queue
List
Tree
Graph
```

Benefits:

- Encapsulation
- Modularity
- Reusability

---

# Arrays

Arrays store elements in contiguous memory locations.

Example:

```c
int data[5];
```

Visualization:

```text
Index

0  1  2  3  4
│  │  │  │  │
10 20 30 40 50
```

Advantages:

- Fast random access
- Easy implementation

Disadvantages:

- Fixed size
- Expensive insertions and deletions

---

# Linked Lists

A linked list consists of nodes connected by pointers.

Visualization:

```text
[10|•] → [20|•] → [30|NULL]
```

Types:

- Singly Linked List
- Doubly Linked List
- Circular Linked List

Advantages:

- Dynamic size
- Easy insertion and deletion

Disadvantages:

- Sequential access
- Additional memory for pointers

---

# Stacks

A stack follows the LIFO principle.

```text
Last In First Out
```

Operations:

```text
Push
Pop
Peek
IsEmpty
```

Visualization:

```text
Top
 │
 ▼
+---+
| 5 |
+---+
| 4 |
+---+
| 3 |
+---+
```

Applications:

- Function Calls
- Undo Operations
- Expression Evaluation
- Backtracking Algorithms

---

# Queues

A queue follows the FIFO principle.

```text
First In First Out
```

Operations:

```text
Enqueue
Dequeue
Front
Rear
```

Visualization:

```text
Front           Rear

10 → 20 → 30 → 40
```

Applications:

- Process Scheduling
- Printers
- Networking
- Simulation Systems

---

# Trees

A tree is a hierarchical data structure.

Visualization:

```text
        A
      /   \
     B     C
    / \
   D   E
```

Terminology:

- Root
- Parent
- Child
- Leaf
- Height
- Depth

---

# Binary Tree

A binary tree allows at most two children per node.

```text
      10
     /  \
    5    15
```

---

# Binary Search Tree (BST)

Property:

```text
Left Child < Parent < Right Child
```

Example:

```text
       50
      /  \
    25    75
   / \    / \
 10 30 60 90
```

Operations:

- Insert
- Delete
- Search

Average Complexity:

```text
O(log n)
```

---

# Heap

A Heap is a complete binary tree.

Min Heap:

```text
Parent ≤ Child
```

Max Heap:

```text
Parent ≥ Child
```

Applications:

- Priority Queues
- Scheduling Systems
- Heap Sort

---

# Hash Tables

Hash tables store data using key-value pairs.

Structure:

```text
Key → Hash Function → Index
```

Example:

```text
Student ID → Student Information
```

Average Search Time:

```text
O(1)
```

---

# Graphs

A graph consists of vertices and edges.

Visualization:

```text
A ----- B
|       |
|       |
C ----- D
```

Components:

- Vertex
- Edge
- Weight
- Path
- Cycle

---

# Graph Traversal

## Breadth First Search (BFS)

Uses:

```text
Queue
```

Applications:

- Shortest Path
- Network Analysis
- Social Networks

Complexity:

```text
O(V + E)
```

---

## Depth First Search (DFS)

Uses:

```text
Stack
Recursion
```

Applications:

- Maze Solving
- Cycle Detection
- Graph Exploration

Complexity:

```text
O(V + E)
```

---

# Searching Algorithms

---

## Linear Search

Checks every element.

Complexity:

```text
O(n)
```

---

## Binary Search

Requires sorted data.

Complexity:

```text
O(log n)
```

Example:

```text
Middle Comparison
↓
Left Half
↓
Right Half
```

---

# Sorting Algorithms

---

## Bubble Sort

Complexity:

```text
O(n²)
```

---

## Selection Sort

Complexity:

```text
O(n²)
```

---

## Insertion Sort

Complexity:

```text
O(n²)
```

---

## Merge Sort

Complexity:

```text
O(n log n)
```

Uses:

```text
Divide and Conquer
```

---

## Quick Sort

Average Complexity:

```text
O(n log n)
```

Worst Case:

```text
O(n²)
```

Applications:

- Large datasets
- High-performance applications

---

# Recursion

Recursion occurs when a function calls itself.

Example:

```text
factorial(n)

factorial(5)
↓
5 × factorial(4)
↓
4 × factorial(3)
```

Base Case:

```text
factorial(0) = 1
```

---

# Divide and Conquer

Strategy:

```text
Divide
    ↓
Solve
    ↓
Combine
```

Examples:

- Merge Sort
- Quick Sort
- Binary Search

---

# Dynamic Programming

Dynamic Programming solves complex problems by storing previously computed results.

Benefits:

- Reduces repetition
- Improves performance
- Optimizes recursive solutions

Applications:

- Fibonacci Sequence
- Knapsack Problem
- Shortest Path Algorithms

---

# Development Environment

## Visual Studio Code (VS Code)

Recommended Editor for ENGCE124.

Features:

- Syntax Highlighting
- Code Navigation
- Debugging
- Git Integration

---

# Recommended Extensions

### C/C++

```text
Microsoft C/C++ Extension
```

Provides:

- IntelliSense
- Debugging
- Syntax Highlighting
- Code Completion

---

### Code Runner

Run code directly from VS Code.

Supported Languages:

- C
- C++
- Python
- Java

---

### Error Lens

Displays errors directly in the source code.

---

### GitLens

Enhanced Git support within VS Code.

---

# GCC Compiler

Compile C Programs

```bash
gcc main.c -o main
```

Run

Linux

```bash
./main
```

Windows

```powershell
main.exe
```

---

# Git and GitHub

Git is a version control system used to manage source code.

GitHub provides cloud-based repository hosting.

---

## Basic Git Commands

Clone Repository

```bash
git clone <repository-url>
```

Check Status

```bash
git status
```

Add Files

```bash
git add .
```

Commit

```bash
git commit -m "Update Project"
```

Push

```bash
git push
```

---

# Repository Contents

This repository contains laboratory exercises and implementations related to:

```text
Arrays
Linked Lists
Stacks
Queues
Trees
Binary Search Trees
Graphs
Searching Algorithms
Sorting Algorithms
Recursion
Algorithm Analysis
```

The exercises emphasize practical understanding of algorithm design and efficient data organization techniques.

---

# Learning Outcomes

After completing ENGCE124, students will be able to:

- Analyze algorithm performance using Big-O notation
- Implement fundamental data structures
- Design efficient algorithms
- Solve engineering problems systematically
- Compare alternative algorithmic approaches
- Apply recursive and iterative strategies
- Process large datasets efficiently
- Use industry-standard development tools
- Prepare for advanced courses in software engineering, databases, operating systems, artificial intelligence, and computer architecture

---

# References

1. Mark Allen Weiss, *Data Structures and Algorithm Analysis*.
2. Thomas H. Cormen et al., *Introduction to Algorithms (CLRS)*.
3. Robert Lafore, *Data Structures and Algorithms in C++*.
4. Michael T. Goodrich, *Data Structures and Algorithms in Java*.
5. GCC Documentation.
6. Git Documentation.
7. Visual Studio Code Documentation.

---

**Course:** ENGCE124 – Data Structures and Algorithms  
**Focus Areas:** Algorithm Analysis, Problem Solving, Data Structures, Searching, Sorting, Trees, Graphs, and Software Development
