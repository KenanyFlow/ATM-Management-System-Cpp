# Bank-Management-System-Cpp

## Overview
The **Bank Management System** is a console-based C++ application that provides robust features for **client management, user authentication, financial transactions, and permission-based access control**. This system allows administrators to manage users and their roles while ensuring secure banking operations for clients. The system also logs the currently logged-in user for tracking purposes.

## Features
### 1. Client Management
- Add new clients with unique account numbers.
- Update client information (name, phone, PIN, balance).
- Delete clients securely with confirmation prompts.
- Search and retrieve client details.

### 2. User Authentication & Role Management
- Secure login system with username and password verification.
- Different user roles (Admin, Employee, Cashier) with permission-based access control.
- Ability to add, update, delete, and manage system users.
- Default admin user creation on first run.
- Logs the currently logged-in user for security and auditing.

### 3. Transactions Handling
- Deposit Money: Add funds to client accounts.
- Withdraw Money: Withdraw funds with balance validation.
- View Total Balances: Display all client balances and calculate total funds.

### 4. Security & Access Control
- Role-based access: Admins can manage users, while employees can access limited client operations.
- Prevent unauthorized access to sensitive operations.
- Users can only perform actions allowed by their permissions.
- Tracks and logs the active user for auditing.

### 5. Persistent Data Storage
- Client and user information is stored in text files (`Clients_Data.txt`, `Users_Data.txt`).
- Ensures data retention between sessions.
- Creates required files automatically if missing.
- Maintains a log of the currently logged-in user in a file.

## How It Works
1. The program starts with a login screen where users enter their credentials.
2. Based on the user's role, they will have different levels of access to system features.
3. Users can manage clients, handle transactions, or manage users depending on their permissions.
4. The system logs the currently logged-in user to track access and enhance security.
5. All changes (clients, users, balances) are saved to external files for data persistence.

## Technologies Used
- C++ (for logic and implementation)
- File Handling (to store client and user data)
- Authentication System (for login security)
- Permissions System (to restrict access based on roles)
- Console-Based UI (for user interaction)
- User Logging (to track active users)

## Installation & Usage
### 1. Clone the Repository
```bash
git clone https://github.com/KenanyFlow/Bank-Management-System-Cpp.git
```

### 2. Compile and Run the Program
Using g++:
```bash
g++ main.cpp -o BankingSystem
./BankingSystem
```
Using Visual Studio:
- Open the `.sln` file and build the project.

## Future Improvements
- Implement a GUI for better user experience.
- Use databases (e.g., MySQL) instead of text files for data storage.
- Encrypt stored passwords for better security.
- Add multi-user support for simultaneous transactions.
- Enhance user logging with timestamps and activity tracking.

---

This project provides a strong foundation for a secure banking system. Feel free to contribute, suggest improvements, or use it for learning purposes.

