# Garage Management System

A robust, terminal-based simulation and management system for an automotive garage. Built entirely in C++ with a strong emphasis on advanced data structures, custom memory management, and data persistence.

## Technology & Architecture
- **Language**: C++17
- **Data Structures**: 
  - Dynamic singly-linked lists for managing Workstations and active repair queues.
  - Binary Search Trees (BST) for cataloging historic repair data, providing fast $O(\log n)$ lookup and dynamic sorting.
- **Memory Management**: Extensive use of modern C++ smart pointers (`std::unique_ptr`) to ensure strict memory safety, automatically handling linked node deallocation and preventing memory leaks in deep nested tree structures.
- **Data Persistence**: Custom text-based state serialization and deserialization. The entire application state (including dynamic tree topologies) can be recursively saved to a raw data file and accurately rebuilt across runtime sessions.
- **Testing Methodology**: Verified through continuous fuzz testing and a comprehensive isolated test suite utilizing the Catch2 framework.

## The Team
This project was engineered and developed by:
- **Renato Pêssego** – *Team Leader, Lead Developer & Architect*
- **Paulo Alves** – *Developer*
- **Francisco Afonseca** – *Developer*

## Features
- **Scalable Workstations**: Dynamically add or safely remove mechanic workstations without disrupting the core data flows. Each workstation tracks its active repair load, capacity limits, revenue, and historic performance metrics.
- **Advanced Wait Queue Logic**: Vehicles are routed organically into priority queues, balancing algorithmic constraints across maximum acceptable repair times and the overall operational bandwidth of the garage.
- **Interactive UI**: A highly robust, error-resistant terminal user interface with clean navigational loops and graceful fallbacks.

## Building & Running
To compile and run the project, ensure you have CMake installed on your local environment.

```bash
# Clone the repository
git clone https://github.com/RenatoPessego/GarageManager.git
cd GarageManager

# Generate build files and compile
cmake -S . -B build
cmake --build build

# Run the system
./build/Debug/GarageManager.exe
```
