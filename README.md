# 🚆 Railway Management & Train Booking System (C++)

A modular, console-based **Railway Management System** built in **C++** using
robust **Object-Oriented Programming (OOP)** principles.

The system not only handles **ticket booking and cancellation**, but also
**manages trains, routes, fares, users, and authentication**, simulating how
a real-world railway reservation and management backend operates.

This project emphasizes **clean architecture, scalability, and system design**
over simple procedural coding.

---

## ✨ Core Capabilities

### Passenger Operations
- Passenger authentication
- Source → Destination based ticket booking
- Date-wise seat allocation
- Waiting list management
- Ticket cancellation
- Automatic fare calculation with detailed breakdown

### Admin & System Management
- Admin authentication
- Train and route management
- Station-wise route handling
- Configurable fare rules (base fare, train charges, GST, discounts)
- User and staff data management
- Persistent storage of all system data using files

---

## 🏗️ System Architecture

The project follows a **layered and modular architecture**, similar to
real backend systems:

- **UI Layer**  
  Handles user interaction and menus

- **Domain Layer**  
  Core entities such as Train, Route, Ticket, User, and Fare

- **Core Layer**  
  Business logic including booking flow, seat allocation, cancellation,
  and fare computation

- **Infrastructure Layer**  
  File handling and persistent data storage

- **Authentication Module**  
  Role-based access control for Admin and Passenger

This separation ensures the system is **maintainable, extensible, and testable**.

---

## 🛠️ Technologies & Concepts Used

- Language: **C++**
- Object-Oriented Programming:
  - Encapsulation
  - Abstraction
  - Inheritance
  - Polymorphism
- STL containers and algorithms
- File Handling for persistence
- Basic thread safety using `mutex` for booking consistency

---

## 📂 Project Structure
Railway Management & Booking System
│
├── UI Layer
│   ├── include/ui/
│   └── src/ui/
│   └── Handles menus, input/output, and user interaction flow
│
├── Core (Business Logic) Layer
│   ├── include/core/
│   └── src/core/
│   └── Booking flow, seat allocation, cancellation, fare calculation
│
├── Domain (Model) Layer
│   ├── include/domain/
│   └── src/domain/
│   └── Train, Route, Ticket, User, Coach, FareResult entities
│
├── Authentication Module
│   ├── include/Authentication/
│   └── src/Authentication/
│   └── Admin and Passenger authentication logic
│
├── Infrastructure (Persistence) Layer
│   ├── include/infra/
│   └── src/infra/
│   └── File handling, repositories, configuration loaders
│
├── Data Layer (Persistent Storage)
│   └── data/
│       ├── trains.txt
│       ├── stations.txt
│       ├── tickets.txt
│       ├── users.txt
│       ├── staff.txt
│       ├── passengers_auth.txt
│       └── fare_config.txt
│
├── Application Entry Point
│   └── main.cpp
│
├── Configuration & Metadata
│   ├── .gitignore
│   └── README.md

How to Run:
1. Compile: g++ main.cpp src/domain/*.cpp src/core/*.cpp src/infra/*.cpp src/ui/*.cpp src/Authentication/*.cpp -Iinclude -o train
2. Run: ./train.exe

Author:
Rajeev
GitHub: https://github.com/Rajeevreddy-2006
