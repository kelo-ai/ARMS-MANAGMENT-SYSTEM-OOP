# 🚦 Traffic Management & Routing Simulation (C++)

This project simulates a **smart traffic management system** using a grid-based model, Dijkstra’s algorithm for shortest path routing, and dynamic traffic signal control. It mimics how vehicles are routed through intersections with varying signal states and traffic loads.

---

## 🧠 Core Concepts

- 📍 **Graph-Based Grid**: Intersections are represented as graph nodes; roads are edges with weights (distances or travel times).
- 🛣️ **Dijkstra's Algorithm**: Computes the shortest path from a selected source node to all other nodes.
- 🚦 **Traffic Signal Logic**: Manages green/red light switching dynamically over time using a time-based model.
- 🚗 **Vehicle Queues**: Simulates vehicle flow through the intersection. Vehicles are split into shortest path and alternate route queues.

---

## 🎮 Features

- Input custom grid size and road connections
- Input multiple test cases
- Visualize shortest paths from a given source
- Simulate dynamic signal updates (Green/Red switch after time)
- Route vehicles depending on current signal status
- Split cars into priority queue (shortest path) and reroute queue

---

## 💻 How It Works

1. **User Input**:
   - Grid size
   - Number of test cases
   - Number of roads and their connections with weights
   - Source node for pathfinding
   - Traffic intersection to simulate

2. **Shortest Path Calculation**:
   - Dijkstra's algorithm computes distances from source node.

3. **Traffic Simulation**:
   - A queue of 10 cars is split: 5 for shortest path, 5 for alternate path.
   - At each time unit:
     - If the signal is green → Cars from shortest path queue move
     - If red → Cars from alternate path queue move

---

## 📁 File Overview

- `main.cpp` – Complete simulation logic
- `Queue` – Custom array-based queue used for vehicle simulation
- `traffic` – Class managing traffic signal state and timing
- `dijkstra` – Function implementing Dijkstra’s shortest path algorithm

---
HOW TO RUN
Enter the Grid size
3
Enter the Test-cases
1
Enter the number of roads:
4
Enter the roads in format {start_node end_node weight}:
1 2 5
2 3 2
1 3 9
2 4 4
Enter the source node: 1
Shortest distance from node 1 :
Node 1: 0
Node 2: 5
Node 3: 7
Node 4: 9
Enter the intersection of node to manage traffic:
2
The number of cars can enter are 5 the other will be rerouted
...
