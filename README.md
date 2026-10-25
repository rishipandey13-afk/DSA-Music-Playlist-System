# Music Playlist Management System (DSA Mini Project)

**Student Details:**
- **Name:** Rishi Pandey
- **ERP No:** 25ET2041025
- **Branch / Year:** Computer Science & Engineering (CSE) - 2nd Year
- **Institution:** Alard University, Pune
- **Course:** Data Structures and Algorithms (DSA)

---

## 📌 Project Overview
The **Music Playlist Management System** is a menu-driven application implemented in C++ simulating modern music players (like Spotify or Apple Music) using fundamental data structures:
1. **Doubly Linked List (DLL)** for bidirectional traversal of tracks (Next song, Previous song, in-place list reversal, dynamic addition and deletion of songs without contiguous memory overhead).
2. **Stack (LIFO)** for maintaining a real-time history of recently played tracks.

---

## ⚙️ Features
- **Dynamic Track Management:** Insert songs at the end, beginning, or any intermediate position.
- **Bidirectional Traversal:** Seamlessly navigate to the **Next** track (`next` pointer) or **Previous** track (`prev` pointer).
- **In-Place Reversal:** Reverse the entire playlist order using pointer manipulation in $O(N)$ time with $O(1)$ extra memory.
- **Search Functionality:** Find tracks by partial title or artist name.
- **Recently Played History:** Stack data structure tracking previously listened tracks.
- **Preloaded Sample Data:** Pre-populated with 5 tracks on startup for immediate demonstration.

---

## 🛠️ Compilation & Execution Instructions

### Prerequisites
- GCC / G++ (v7.0 or higher) with C++17 support.
- Linux, macOS, or Windows (MinGW/WSL).

### Build & Run Using Makefile:
```bash
make
make run
```

### Manual Compilation:
```bash
g++ -std=c++17 -Wall main.cpp -o playlist_system
./playlist_system
```

### Clean Build:
```bash
make clean
```

---

## 📂 File Structure
```
DSA_Music_Playlist_System/
├── main.cpp                # Complete C++ source code
├── Makefile                # Automated build script
├── README.md               # Quick start documentation
└── DSA_PROJECT_REPORT.md   # Complete academic project report
```
