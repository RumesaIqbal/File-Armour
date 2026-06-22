# 🔐 File Armour – Secure File Encryption & Authentication System

File Armour is a C-based console application that provides secure user authentication along with file encryption and decryption features. It includes password strength checking, machine-generated passwords, security questions, emergency access, and a file-locking mechanism after multiple failed attempts.

---

## 🚀 Features

### 👤 User Management
- Create new user accounts
- Store username, password, security question & answer, emergency code
- Secure login system
- Sign out functionality
- Login activity logging with timestamps

---

### 🔑 Password System
- Strong password validation (uppercase, lowercase, digits, symbols)
- Password strength meter (1–5 scale)
- Machine-generated secure passwords
- Password reset using security questions

---

### 🔐 File Encryption & Decryption
- XOR-based encryption algorithm
- Encrypt any external file using a password
- Decrypt file after successful authentication
- Password-protected file access system

---

### 🚨 Security Features
- Maximum 3 login attempts allowed
- File lock system with countdown timer
- Emergency access using emergency code
- Password reset after failed attempts

---

### 📂 File Handling
- userdata.txt → stores user credentials
- encrypted.bin → encrypted file output
- decrypted.txt → decrypted file output
- username.txt → login logs per user

---

## 🛠️ Technologies Used
- C Language
- File Handling (stdio.h)
- String Handling (string.h)
- Time Functions (time.h)
- Process Control (unistd.h)
- Random Number Generation (stdlib.h)
- Character Type Functions (ctype.h)

---

## 📁 Project Structure

File-Armour/
<br>
│
<br>
├── main.c              # Source code
<br>
├── userdata.txt        # User database file
<br>
├── encrypted.bin       # Encrypted output file
<br>
├── decrypted.txt       # Decrypted output file
<br>
└── logs/               # User login logs
<br>

---

## ⚙️ How to Run

### Compile Code
gcc main.c -o file_armour

### Run Program
./file_armour

---

## 📌 Menu Options

1) Create Account
2) Sign In
3) Sign Out
4) Emergency Access
5) Exit

---

## 🔒 Encryption Logic

- Uses XOR Cipher Encryption
- Same function used for encryption and decryption
- Password acts as repeating key
- Output stored in binary format (encrypted.bin)

---

## 🚨 Security Mechanism

- After 3 wrong password attempts:
  - File is locked temporarily
  - Countdown timer starts
- Users can reset password using:
  - Security question
  - Emergency verification code

---

## ⚠️ Limitations

- No database integration (uses text files)
- Basic encryption (not cryptographically secure)
- Console-based interface only
- Limited error handling

---

## 📈 Future Improvements

- GUI-based version
- AES-level encryption
- Database integration
- Cloud storage support
- Multi-user system
- Role-based access control

---

## 👨‍💻 Author

Rumesa Iqbal  
BSCS Student – FAST University Karachi  

---

## 📜 License

Educational use only
