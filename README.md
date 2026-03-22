Welcome to your personal **To-Do List Manager**, a command-line based task management application written in **C**.  
It allows you to organize, update, and track your tasks with ease — complete with secure password access and file persistence.

---

## 🚀 Features

- 🔐 **Admin Login** with password hashing 
- ➕ **Add Tasks** with unique IDs
- ✅ **Mark Tasks as Completed**
- 🔍 **Search Tasks** with case-insensitive keyword matching
- 📊 **Priority Levels** (Low / Medium / High)
- 📂 **View Tasks** filtered by status: All, Completed, Incomplete
- ✏️ **Update** description, status, or priority
- 🔄 **Reindexing** of IDs after deletion
- 🗑️ **Delete Tasks** individually or in bulk
- 💾 **Backup & Restore** from separate binary files
- 📤 **Export to CSV** for spreadsheet viewing
- 📉 **Sort Tasks** by priority (Asc / Desc)
- 💾 **Persistent Storage** via binary file I/O
- 🧠 **Dynamic Memory Allocation** used throughout

## 🧑‍💻 How to Compile & Run

Make sure you have GCC installed.

```bash
gcc sourcecode.c -o sourcecode.exe
./sourcecode

## 📂 File Structure

📁 Student-Management-System/
│
├── sourcecode.c            ← Main source code 🧠
├── sourcecode.exe          ← Executable file (Windows) ⚙️
├── hash_generator.c        ← 🔐 Helper to generate password hash
├── README.md               ← This beautiful documentation (You're reading it) ✨
│
├── exportcsv.csv         ← Auto-created after CSV export [NOT shared]
├── to-do-list.bin        ← Auto-created after saving records [NOT shared]
├── backup.bin      ← Auto-created after backup [NOT shared]


------------ Main Menu ------------
1 - Add Task
2 - View & Filter Tasks by Status
3 - Update Task
4 - Mark a Task as Completed
5 - Search Tasks
6 - Sort Tasks by Priority
7 - Delete a Task
8 - Delete All Tasks
9 - Delete All Completed Tasks
10 - Backup All Tasks to File
11 - Restore Tasks from Backup
12 - Export All Tasks to CSV
13 - Save Tasks
14 - Exit

📌 Notes:

- Task IDs auto-increment and reindex after deletion.
- Tasks are stored persistently using binary file handling.
- Priority levels are labeled and sortable.
- Secure file operations with user confirmations.
- Case-insensitive substring search supported.

### ⚠️ Only `sourcecode.c`,`hash_generater.c` and `sourcecode.exe` are included in the repository. for functionality and customization.   
### Your personal `.csv` and `.bin` files remain on your system and are never shared.

🔐 Admin Login with Hashed Password
This project includes a **secure admin login system** using a **custom hashing function**.

When the program starts, users must enter the correct admin password.  
The entered password is hashed using the `simplehash()` function and compared with a pre-defined hash value.

✅ Default Password
Password: admin@g139

(Used only for demo; can be changed using the helper below)

🔒 Internally stored as:
#define password_hash 8246073859955783634

## 🔑 Changing the Admin Password

To change the password, you'll need to calculate the hash of your new password using the same hashing method used in the program (`simplehash()`).

Instead of modifying the full project, you can generate the hash using a small helper C program.

🛠️ A file called `hash_generator.c` is included in this repository. Compile and run it to get the hashed value of your desired password:

```bash
gcc hash_generator.c -o hash_generater
./hash_generater
Enter your new password when needed, and it will give you a hash like:

Hashed value: 7639281883728628837
Now, go to your main C file and update this line:
#define password_hash 8246073859955783634
with:
#define password_hash 7639281883728628837
Recompile and you're done!
✅ This makes your new password active without storing it in plain text.

🏗️ Project Structure (Inside the Code)
struct task contains: ID, description, status, priority

File I/O with binary format for efficiency

Modular functions for each operation

Uses malloc, realloc, and free to manage memory

Friendly UI prompts with confirmations before destructive actions

## 🤝 Contributing

This is a solo project for learning and showcasing C skills. In future versions, contributions or suggestions 
are welcome!

📜 License
This project is for personal learning and portfolio use only.
Please do not copy or redistribute without permission.

Note: This program auto-generates `to-do-list.bin', `backup.bin`, and `exportcsv.csv` files on first use. 
These files are local to your system and are not shared publicly or stored in this repository.

**Author**
**RIYA CHALERIA**❤️
