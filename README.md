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
### System Welcome Screen

![RailNest Home Page](data/Images/HomePage.png)

This welcome screen appears when the application starts and introduces **RailNest – a Train Management and Reservation System** built as a console-based application.  
It displays the system banner and waits for the user to press **ENTER** before proceeding to the main menu.

### Main Menu

![Main Menu](data/Images/MainMenu.png)

The main menu acts as the central navigation hub of the system, allowing users to access different modules such as the Admin Panel, Passenger Portal, and Guest View.  
It enables users to select an option to perform administrative tasks, book tickets, explore train information, or exit the application.

### Admin Authentication

![Admin Role](data/Images/Admin_Role.png)

This screen allows administrators to select their role before accessing the admin panel, such as Head or Staff.  
It helps the system organize administrative responsibilities and control access to management features.

### Admin Control Panels

<table>
<tr>
<td align="center">

**Head Admin Panel**

<img src="data/Images/Admin_Head_Ctrl.png" width="450">

</td>
<td align="center">

**Staff Admin Panel**

<img src="data/Images/Admin_Staff_ctrls.png" width="450">

</td>
</tr>
</table>

The **Head Admin Panel** provides full administrative control including staff management and system-level configuration.  
The **Staff Admin Panel** allows operational management such as handling stations, trains, routes, and fare details.  
The key difference is that **Head Admin has higher privileges**, while Staff members have limited operational access.

### Passenger Authentication

![Passenger Authentication](data/Images/Passenger_Authentication.png)

This screen allows passengers to access the Passenger Portal where they can log in to their existing account or create a new account.  
It ensures that only authenticated users can proceed to booking tickets and managing their reservations.

### Passenger Console

![Passenger Console](data/Images/Passenger_ctrls.png)

After successful authentication, passengers access the Passenger Console which provides options to interact with the reservation system.  
From this console, users can view trains and routes, book tickets, check their bookings, cancel tickets, manage their profile, or logout.

### Ticket Generation

![Generated Ticket](data/Images/Ticket.png)

After a successful booking, the system generates a detailed ticket containing passenger information, journey details, seat allocation, and fare breakdown.  
The ticket displays the PNR number and total amount paid, allowing passengers to verify their reservation and print the ticket if needed.

### Guest Console

![Guest Console](data/Images/Guest_ctrls.png)

The Guest Console allows users to explore basic system information without creating an account.  
Guests can view available trains and stations, helping them check routes and services before registering or booking tickets.

### System Sign Off

![System Sign Off](data/Images/SignOff.png)

This screen is displayed when the user exits the application, indicating that the session has ended successfully.  
It thanks the user for using RailNest and provides a friendly closing message before the program terminates.

How to Run:
1. Compile: g++ main.cpp src/domain/*.cpp src/core/*.cpp src/infra/*.cpp src/ui/*.cpp src/Authentication/*.cpp -Iinclude -o train
2. Run: ./train.exe

Author:
Rajeev
GitHub: https://github.com/Rajeevreddy-2006
