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
- Ticket Generating using HTML,CSS,JS
- Date-wise seat allocation
- Waiting list management
- Ticket cancellation
- Automatic fare calculation with detailed breakdown

### Admin & System Management
- Admin authentication
- Train and route management
- Station-wise route handling
- Configurable fare rules (Coach-wise rate per km,GST percentage,Reservation charge,Superfast charge,Tatkal charge,Discount percentage)
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

---

## 📂 Project Structure
```text
Railway-Management-Booking-System/
│
├── data/
│ ├── trains.txt
│ ├── stations.txt
│ ├── tickets.txt
│ ├── users.txt
│ ├── staff.txt
│ ├── passengers_auth.txt
│ └── fare_config.txt
│
├── include/
│ ├── ui/
│ ├── core/
│ ├── domain/
│ ├── infra/
│ └── Authentication/
│
├── src/
│ ├── ui/
│ ├── core/
│ ├── domain/
│ ├── infra/
│ └── Authentication/
│
├── main.cpp
├── .gitignore
└── README.md
```

How to Run:
1. Compile: g++ main.cpp src/domain/*.cpp src/core/*.cpp src/infra/*.cpp src/ui/*.cpp src/Authentication/*.cpp -Iinclude -o train
2. Run: ./train.exe

Author:
Rajeev
GitHub: https://github.com/Rajeevreddy-2006
