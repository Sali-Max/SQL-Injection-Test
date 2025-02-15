# 🔥 Student Management System - SQL Injection Vulnerable 🔥  

🚨 **WARNING: This program contains a deliberate SQL Injection vulnerability!** 🚨  

This project is **intentionally vulnerable** to **SQL Injection** for **educational purposes**.  
It is designed for **cybersecurity enthusiasts, ethical hackers, and penetration testers** to **practice SQL Injection attacks** in a controlled environment.  

💡 **If you're interested in learning about security flaws, database exploitation, and ethical hacking, this project is for you!**  

---

## ⚠️ **Disclaimer** ⚠️  
**This program is for educational and research purposes only.**  
**The author is NOT responsible for any misuse.**  
Use it **only in legal and ethical ways** to improve security knowledge!  

---

## 🛠️ **Features & Vulnerabilities**  

✔️ **Student Management System** with **SQLite3 Database**  
✔️ **Deliberate SQL Injection Vulnerability** for testing  
✔️ **User Authentication System** (🚨 Vulnerable 🚨)  
✔️ **Two Predefined Users in the Database**:  
   - 👤 **Normal User** → `user` / `1234`  
   - 🔑 **Admin User** → `root` / `root`  
✔️ **Test & Improve Your SQL Injection Skills**  
✔️ **Designed for GNU/Linux** (❌ *Does NOT support Windows* ❌)  

---

## 🚀 **How to Install & Run**  

### 1️⃣ **Clone the Repository**  
```bash
git clone https://github.com/YOUR_GITHUB/Student-SQLi-Vulnerable.git
cd Student-SQLi-Vulnerable
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
| Normal User | `user` | `1234` |
| Admin | `root` | `root` |

📌 **Try SQL Injection Attacks!**  
Use basic SQL Injection payloads to bypass authentication!  

Example:  
```
Username: admin' --  
Password: (leave empty)
```

---

## 🎯 **Why Use This Project?**  

🔸 **Test SQL Injection vulnerabilities** in a **real-world-like scenario**  
🔸 **Learn how attackers exploit weak authentication systems**  
🔸 **Practice SQL Injection techniques** like `' OR 1=1 --`  
🔸 **Understand database security and how to prevent attacks**  

🚀 **Perfect for security researchers, ethical hackers, and cybersecurity learners!**  

---

## 🛑 **WARNING: Security Notice**  
This program is **NOT SECURE** and must **NEVER be used in production**.  
**Do NOT deploy it on public servers!**  

---

## ⭐ **Support & Contributions**  
If you like this project, **give it a star ⭐ on GitHub** and share it with your friends!  
