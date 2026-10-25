# VIVA VOCE PREPARATION GUIDE: DATA STRUCTURES & ALGORITHMS (DSA)
## Project: Music Playlist Management System
**Student:** Rishi Pandey | **ERP No:** 25ET2041025 | **Institution:** Alard University, Pune

---

### Q1: Why did you choose a Doubly Linked List (DLL) instead of a Singly Linked List (SLL) or Array for a Music Playlist?
**Answer:**
- **Array:** Has a fixed size or high reallocation overhead. Deleting or inserting a song in the middle requires shifting $O(N)$ elements.
- **Singly Linked List:** Can easily go forward (`next`), but moving to the previous song requires traversing all the way from the `head` node, taking $O(N)$ time.
- **Doubly Linked List:** Each node contains both `next` and `prev` pointers. This allows constant time $O(1)$ bidirectional playback (`Next Song` and `Previous Song`) and $O(1)$ insertion/deletion once the position pointer is known.

---

### Q2: What is the node structure of your Doubly Linked List?
**Answer:**
```cpp
struct Song {
    int id;              // Unique track identifier
    string title;        // Track name
    string artist;       // Artist/Band name
    double duration;     // Duration in minutes
    Song* prev;          // Pointer to preceding track node
    Song* next;          // Pointer to succeeding track node
};
```

---

### Q3: What is the time and space complexity of your core operations?
**Answer:**
| Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| Play Next Song | $O(1)$ | $O(1)$ |
| Play Previous Song | $O(1)$ | $O(1)$ |
| Add Song at End | $O(1)$ (using `tail` pointer) | $O(1)$ |
| Add Song at Head | $O(1)$ (using `head` pointer) | $O(1)$ |
| Add at Position $K$ | $O(K) \approx O(N)$ | $O(1)$ |
| Delete Song by ID | $O(N)$ search + $O(1)$ relink | $O(1)$ |
| In-place List Reversal | $O(N)$ | $O(1)$ auxiliary |
| Search by Title/Artist | $O(N)$ linear scan | $O(1)$ |

---

### Q4: How does your in-place playlist reversal algorithm work?
**Answer:**
Instead of copying elements into an auxiliary array or creating new nodes, we traverse the list and swap the `next` and `prev` pointers of each node:
```cpp
Song* curr = head;
Song* temp = nullptr;
while (curr != nullptr) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev; // Moves to the original next node
}
if (temp != nullptr) {
    tail = head;
    head = temp->prev;
}
```
This runs in $O(N)$ time and requires $O(1)$ additional memory.

---

### Q5: How and why did you implement the Recently Played Songs feature?
**Answer:**
- We implemented a **Stack** using dynamic linked nodes (`HistoryNode`).
- A stack operates on **LIFO (Last-In, First-Out)** principle.
- Whenever a user plays a song (via `playCurrent`, `playNext`, or `playPrevious`), that song's metadata is pushed to the top of the stack in $O(1)$ time.
- When viewing history, the most recently played songs appear at the top, perfectly matching real-world media player behavior.

---

### Q6: What edge cases did you handle in your code?
**Answer:**
1. **Empty Playlist:** Checking `head == nullptr` before attempting to play, delete, or traverse.
2. **Single Song Playlist:** Deleting the only song correctly sets both `head` and `tail` to `nullptr`.
3. **Deleting the Current Song:** If the playing song is deleted, `currentSong` gracefully shifts to `next` (or `prev`).
4. **Circular Wrap-around:** When playing `Next` at the end of the playlist, it wraps around to `head`; when playing `Previous` at `head`, it wraps around to `tail`.
5. **Input Validation:** Safe handling of non-numeric inputs using `cin.clear()` and `cin.ignore()` to prevent infinite input loops.

---

### Q7: What are the memory trade-offs of a Doubly Linked List?
**Answer:**
- **Advantage:** Dynamic memory allocation; nodes are created on-demand on the heap and freed immediately when deleted (preventing internal fragmentation).
- **Disadvantage:** Extra pointer overhead. Each node requires two 64-bit pointers (16 bytes on modern systems) in addition to the data payload.

---

### Q8: How would you extend this project for a production scenario?
**Answer:**
1. **File Persistence:** Read and write songs from a CSV or JSON file on disk so the playlist persists across restarts.
2. **Audio Decoding:** Integrate an audio library like `SDL2_mixer` or `miniaudio` to play actual audio streams.
3. **Search Optimization:** Use a Trie or Hash Map to achieve $O(1)$ or $O(L)$ instant song search by prefix.
