# 🔥 SQL Injection Vulnerable - Student Manager 🔥

🚨 **WARNING: This program contains a deliberate SQL Injection vulnerability!** 🚨  

This project is **intentionally vulnerable** to **SQL Injection** for **educational purposes**.  
It is designed for **cybersecurity enthusiasts, ethical hackers, and penetration testers** to **practice SQL Injection attacks** in a controlled environment.  

💡 **If you're interested in learning about security flaws, database exploitation, and ethical hacking, this project is for you!**  

---

## 🛠️ **Features & Vulnerabilities**  

✔️ **Student Management System** with **SQLite3 Database**  <br>
💀 **Deliberate SQL Injection Vulnerability** for testing <br>
🔑 **User Authentication System** (🚨 Vulnerable 🚨) <br>
🐧 **Only Designed for GNU/Linux** (❌ *Does NOT support Windows* ❌) 

---

## 🚀 **How to Install & Run**  

### 1️⃣ **Clone the Repository**  
```bash
git clone https://github.com/Sali-Max/SQL-Injection-Test.git
cd SQL-Injection-Test
```

### 2️⃣ **Compile the Program**  
```bash
g++ main.cpp -o student_manager -lsqlite3
```

### 3️⃣ **Run the Program**  
```bash
./student_manager
```

### 4️⃣ **Login Credentials (Default Users)**  
| Role  | Username | Password |
|-------|---------|----------|
| Normal User | `user` | `user` |
| Admin | `root` | `root` |

💀 **Try SQL Injection Attacks!**  
Use basic SQL Injection payloads to bypass authentication! 

Example:  
```
Username: root' --  
Password: (leave empty)
CodeNumber: (leave empty)
```
💡**You can make modifications as needed in the user search and edit(ROOT) sections** <br>
💡**You can unintentionally escalate a restricted user to an admin user**

---

## 🛑 **WARNING: Security Notice**  
This program is **NOT SECURE** and must **NEVER be used in production**.  
**Do NOT deploy it on public servers!**  

---

## ⭐ **Support & Contributions**  
If you like this project, **give it a star ⭐ on GitHub**.
