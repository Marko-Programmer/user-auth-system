
# 🛡️ User Authentication System (C++ & MySQL)

This is a command-line user authentication system built in C++ with MySQL database support. It implements user registration, login, role-based menus, secure password hashing, unit testing with Catch2, modular file structure, and database integration using MySQL Connector/C++.

<br><br>
## ⚙️ Features

- 🔐 User registration with secure password hashing
- 🔑 Login with credential verification via MySQL
- 🛠️ Role-based access: regular users and administrators
- 🧪 Unit testing with [Catch2](https://github.com/catchorg/Catch2)
- 🔄 MySQL database integration using `MySQL Connector/C++`
- 🗂️ Modular multi-file project structure (`include/`, `src/`, `tests/`)
- 🔧 Configurable database connection via `config.txt`

<br><br>
## 🗃️ Database Setup (MySQL)
To set up the database:

1. Create the database manually:

<pre>CREATE DATABASE auth_system;</pre>

<pre>USE auth_system;</pre>

2. Then run the provided schema.sql script to create the users table with the required fields.

🔐 Passwords are stored as hashes.

<br><br>
## 🛠️ Configuration

1. Install MySQL Connector/C++

2. 📄 Setup config.txt
Rename `config_template.txt` to `config.txt`, then fill in your MySQL credentials.

3. Install Catch2 (Catch2 is used for testing. It can be included as a single header or via CMake/vcpkg).

<br><br>
## 🧪 Unit Testing
Unit tests are written using Catch2. The following components are covered:

1. Input validation (utils)

2. User handling logic (creation, authentication, role assignment)

<br> 
To compile and run the tests, use the following command:
<br><br>

1. <pre>g++ tests/test_user.cpp tests/test_utils.cpp src/user.cpp src/utils.cpp -o tests -std=c++17</pre>

2. <pre>./tests</pre>

<br><br>
## 🔐 Security
Passwords are hashed before storing.

All SQL queries use prepared statements (to prevent SQL injection).

Role-based permissions are enforced via a role field in the users table.

<br><br>
## 📌 Requirements

C++17 or newer

MySQL Server

MySQL Connector/C++

Catch2 (for testing).

<br><br>
## 📝 License
See license.txt for license details.

<br><br>
## 🙋‍♂️ Author
**Marko Zhenchuk**
