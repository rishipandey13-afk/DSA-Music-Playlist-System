#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Structure representing a single Song node in the Doubly Linked List
struct Song {
    int id;
    string title;
    string artist;
    double duration; // in minutes e.g., 3.45 min
    Song* prev;
    Song* next;

    Song(int songId, string songTitle, string songArtist, double songDuration) {
        id = songId;
        title = songTitle;
        artist = songArtist;
        duration = songDuration;
        prev = nullptr;
        next = nullptr;
    }
};

// Node structure for Recently Played Stack (LIFO data structure)
struct HistoryNode {
    string title;
    string artist;
    HistoryNode* next;

    HistoryNode(string t, string a) : title(t), artist(a), next(nullptr) {}
};

// Stack implementation to track recently played songs
class RecentlyPlayedStack {
private:
    HistoryNode* top;
    int count;
    const int MAX_HISTORY = 10;

public:
    RecentlyPlayedStack() {
        top = nullptr;
        count = 0;
    }

    ~RecentlyPlayedStack() {
        while (top != nullptr) {
            HistoryNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const string& title, const string& artist) {
        HistoryNode* newNode = new HistoryNode(title, artist);
        newNode->next = top;
        top = newNode;
        count++;

        // If history exceeds limit, trim oldest entry
        if (count > MAX_HISTORY) {
            HistoryNode* curr = top;
            while (curr->next && curr->next->next) {
                curr = curr->next;
            }
            if (curr->next) {
                delete curr->next;
                curr->next = nullptr;
                count--;
            }
        }
    }

    void displayHistory() const {
        if (top == nullptr) {
            cout << "\n[!] No songs played yet. History is empty.\n";
            return;
        }

        cout << "\n=======================================================\n";
        cout << "           RECENTLY PLAYED HISTORY (STACK - LIFO)      \n";
        cout << "=======================================================\n";
        HistoryNode* curr = top;
        int index = 1;
        while (curr != nullptr) {
            cout << " " << index++ << ". " << curr->title << " - " << curr->artist << "\n";
            curr = curr->next;
        }
        cout << "=======================================================\n";
    }
};

// Doubly Linked List for Music Playlist Management
class MusicPlaylist {
private:
    Song* head;
    Song* tail;
    Song* currentSong;
    int nextId;
    int totalCount;
    RecentlyPlayedStack history;

public:
    MusicPlaylist() {
        head = nullptr;
        tail = nullptr;
        currentSong = nullptr;
        nextId = 101;
        totalCount = 0;
    }

    ~MusicPlaylist() {
        Song* curr = head;
        while (curr != nullptr) {
            Song* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    // Insert song at the end of playlist - O(1) time
    void addSongEnd(const string& title, const string& artist, double duration) {
        Song* newSong = new Song(nextId++, title, artist, duration);
        if (head == nullptr) {
            head = tail = currentSong = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        totalCount++;
        cout << "\n[+] Successfully added \"" << title << "\" to the end of playlist.\n";
    }

    // Insert song at the beginning of playlist - O(1) time
    void addSongBeginning(const string& title, const string& artist, double duration) {
        Song* newSong = new Song(nextId++, title, artist, duration);
        if (head == nullptr) {
            head = tail = currentSong = newSong;
        } else {
            newSong->next = head;
            head->prev = newSong;
            head = newSong;
        }
        totalCount++;
        cout << "\n[+] Successfully added \"" << title << "\" at the beginning of playlist.\n";
    }

    // Insert song at specific position (1-based index) - O(N) time
    void addSongAtPosition(int pos, const string& title, const string& artist, double duration) {
        if (pos < 1 || pos > totalCount + 1) {
            cout << "\n[-] Invalid position! Playlist currently has " << totalCount << " songs.\n";
            return;
        }
        if (pos == 1) {
            addSongBeginning(title, artist, duration);
            return;
        }
        if (pos == totalCount + 1) {
            addSongEnd(title, artist, duration);
            return;
        }

        Song* curr = head;
        for (int i = 1; i < pos - 1; i++) {
            curr = curr->next;
        }

        Song* newSong = new Song(nextId++, title, artist, duration);
        newSong->next = curr->next;
        newSong->prev = curr;
        curr->next->prev = newSong;
        curr->next = newSong;
        totalCount++;

        cout << "\n[+] Successfully inserted \"" << title << "\" at position " << pos << ".\n";
    }

    // Delete song by Song ID - O(N) time
    void deleteSongById(int id) {
        if (head == nullptr) {
            cout << "\n[-] Playlist is empty. Nothing to delete.\n";
            return;
        }

        Song* curr = head;
        while (curr != nullptr && curr->id != id) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            cout << "\n[-] Song with ID #" << id << " not found in the playlist.\n";
            return;
        }

        // If deleting current playing song, update currentSong pointer
        if (curr == currentSong) {
            currentSong = (curr->next != nullptr) ? curr->next : curr->prev;
        }

        // Adjust links
        if (curr == head && curr == tail) {
            head = tail = nullptr;
        } else if (curr == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (curr == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        cout << "\n[-] Successfully deleted \"" << curr->title << "\" (ID: #" << curr->id << ").\n";
        delete curr;
        totalCount--;
    }

    // Play currently selected song
    void playCurrent() {
        if (currentSong == nullptr) {
            cout << "\n[!] Playlist is empty. Add songs first.\n";
            return;
        }
        history.push(currentSong->title, currentSong->artist);
        cout << "\n=======================================================\n";
        cout << "                 >>> NOW PLAYING <<<                   \n";
        cout << " Track ID  : #" << currentSong->id << "\n";
        cout << " Title     : " << currentSong->title << "\n";
        cout << " Artist    : " << currentSong->artist << "\n";
        cout << " Duration  : " << fixed << setprecision(2) << currentSong->duration << " mins\n";
        cout << "=======================================================\n";
    }

    // Play next song (Forward traversal in DLL)
    void playNext() {
        if (currentSong == nullptr) {
            cout << "\n[!] Playlist is empty.\n";
            return;
        }
        if (currentSong->next != nullptr) {
            currentSong = currentSong->next;
            playCurrent();
        } else {
            cout << "\n[!] You have reached the END of the playlist!\n";
            cout << "    Restarting from first song...\n";
            currentSong = head;
            playCurrent();
        }
    }

    // Play previous song (Backward traversal in DLL)
    void playPrevious() {
        if (currentSong == nullptr) {
            cout << "\n[!] Playlist is empty.\n";
            return;
        }
        if (currentSong->prev != nullptr) {
            currentSong = currentSong->prev;
            playCurrent();
        } else {
            cout << "\n[!] You are at the FIRST song of the playlist!\n";
            cout << "    Wrapping around to the last song...\n";
            currentSong = tail;
            playCurrent();
        }
    }

    // Display all songs in table format
    void displayPlaylist() const {
        if (head == nullptr) {
            cout << "\n[!] The playlist is currently empty.\n";
            return;
        }

        cout << "\n===============================================================================\n";
        cout << "                         CURRENT MUSIC PLAYLIST                                \n";
        cout << "===============================================================================\n";
        cout << left << setw(8) << "ID"
             << setw(26) << "Title"
             << setw(22) << "Artist"
             << setw(12) << "Duration"
             << "Status" << "\n";
        cout << "-------------------------------------------------------------------------------\n";

        Song* curr = head;
        while (curr != nullptr) {
            cout << left << setw(8) << curr->id
                 << setw(26) << curr->title.substr(0, 24)
                 << setw(22) << curr->artist.substr(0, 20)
                 << fixed << setprecision(2) << setw(12) << curr->duration;

            if (curr == currentSong) {
                cout << "[* PLAYING]";
            } else {
                cout << "   -";
            }
            cout << "\n";
            curr = curr->next;
        }
        cout << "===============================================================================\n";
        cout << " Total Songs: " << totalCount << " | Total Duration: " << fixed << setprecision(2) 
             << getTotalDuration() << " mins\n";
    }

    // Search song by title or artist keyword
    void searchSong(const string& query) const {
        if (head == nullptr) {
            cout << "\n[!] Playlist is empty.\n";
            return;
        }

        bool found = false;
        cout << "\n--- Search Results for \"" << query << "\" ---\n";
        Song* curr = head;
        while (curr != nullptr) {
            // Check case-insensitive or substring match
            string titleLower = curr->title;
            string queryLower = query;
            for (char &c : titleLower) c = tolower(c);
            for (char &c : queryLower) c = tolower(c);

            string artistLower = curr->artist;
            for (char &c : artistLower) c = tolower(c);

            if (titleLower.find(queryLower) != string::npos || artistLower.find(queryLower) != string::npos) {
                cout << "  - [ID #" << curr->id << "] \"" << curr->title 
                     << "\" by " << curr->artist << " (" << curr->duration << " mins)\n";
                found = true;
            }
            curr = curr->next;
        }

        if (!found) {
            cout << "  No matching songs found.\n";
        }
    }

    // Reverse playlist in-place by swapping next and prev pointers - O(N) time
    void reversePlaylist() {
        if (head == nullptr || head->next == nullptr) {
            cout << "\n[!] Playlist needs at least 2 songs to reverse.\n";
            return;
        }

        Song* curr = head;
        Song* temp = nullptr;

        while (curr != nullptr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev; // moves to next original node
        }

        if (temp != nullptr) {
            tail = head;
            head = temp->prev;
        }

        cout << "\n[+] Playlist order successfully reversed in-place!\n";
    }

    // View recently played history
    void viewHistory() const {
        history.displayHistory();
    }

    double getTotalDuration() const {
        double total = 0.0;
        Song* curr = head;
        while (curr != nullptr) {
            total += curr->duration;
            curr = curr->next;
        }
        return total;
    }

    int getSongCount() const {
        return totalCount;
    }

    // Preload default songs for demonstration
    void preloadSampleSongs() {
        addSongEnd("Bohemian Rhapsody", "Queen", 5.55);
        addSongEnd("Hotel California", "Eagles", 6.30);
        addSongEnd("Shape of You", "Ed Sheeran", 3.53);
        addSongEnd("Kesariya", "Arijit Singh", 4.28);
        addSongEnd("Starboy", "The Weeknd", 3.50);
    }
};

// Helper function to safely read integer
int getIntInput() {
    int val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a valid number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

// Helper function to safely read double
double getDoubleInput() {
    double val;
    while (!(cin >> val) || val <= 0.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a positive duration (e.g. 3.45): ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

int main() {
    MusicPlaylist playlist;

    // Load initial songs so the evaluator can test right away
    playlist.preloadSampleSongs();

    int choice = 0;
    do {
        cout << "\n=======================================================\n";
        cout << "         MUSIC PLAYLIST MANAGEMENT SYSTEM (DSA)        \n";
        cout << "   Student: Rishi Pandey | ERP No: 25ET2041025         \n";
        cout << "             Alard University, Pune                    \n";
        cout << "=======================================================\n";
        cout << " 1. Display Current Playlist\n";
        cout << " 2. Play Current Song\n";
        cout << " 3. Play Next Song (Next Pointer)\n";
        cout << " 4. Play Previous Song (Prev Pointer)\n";
        cout << " 5. Add Song to Playlist (End)\n";
        cout << " 6. Add Song to Playlist (Beginning / Position)\n";
        cout << " 7. Delete Song (by ID)\n";
        cout << " 8. Search Song (by Title / Artist)\n";
        cout << " 9. View Recently Played History (Stack)\n";
        cout << " 10. Reverse Playlist Order (In-Place Pointer Swap)\n";
        cout << " 11. Exit\n";
        cout << "=======================================================\n";
        cout << "Enter your choice (1-11): ";

        choice = getIntInput();

        switch (choice) {
            case 1:
                playlist.displayPlaylist();
                break;
            case 2:
                playlist.playCurrent();
                break;
            case 3:
                playlist.playNext();
                break;
            case 4:
                playlist.playPrevious();
                break;
            case 5: {
                string title, artist;
                double duration;
                cout << "Enter Song Title  : ";
                getline(cin, title);
                cout << "Enter Artist Name : ";
                getline(cin, artist);
                cout << "Enter Duration (mins): ";
                duration = getDoubleInput();
                playlist.addSongEnd(title, artist, duration);
                break;
            }
            case 6: {
                cout << "Choose Insert Option:\n";
                cout << "  1. Add at Beginning\n";
                cout << "  2. Add at Specific Position\n";
                cout << "Enter sub-choice: ";
                int subChoice = getIntInput();
                string title, artist;
                double duration;
                cout << "Enter Song Title  : ";
                getline(cin, title);
                cout << "Enter Artist Name : ";
                getline(cin, artist);
                cout << "Enter Duration (mins): ";
                duration = getDoubleInput();

                if (subChoice == 1) {
                    playlist.addSongBeginning(title, artist, duration);
                } else if (subChoice == 2) {
                    cout << "Enter position (1 to " << playlist.getSongCount() + 1 << "): ";
                    int pos = getIntInput();
                    playlist.addSongAtPosition(pos, title, artist, duration);
                } else {
                    cout << "[-] Invalid sub-choice!\n";
                }
                break;
            }
            case 7: {
                cout << "Enter Song ID to delete: ";
                int id = getIntInput();
                playlist.deleteSongById(id);
                break;
            }
            case 8: {
                cout << "Enter keyword to search: ";
                string query;
                getline(cin, query);
                playlist.searchSong(query);
                break;
            }
            case 9:
                playlist.viewHistory();
                break;
            case 10:
                playlist.reversePlaylist();
                playlist.displayPlaylist();
                break;
            case 11:
                cout << "\nThank you for using Music Playlist Management System!\n";
                cout << "Developed by: Rishi Pandey (ERP: 25ET2041025)\n";
                cout << "Department of Computer Science & Engineering, Alard University Pune\n\n";
                break;
            default:
                cout << "\n[-] Invalid option! Please select between 1 and 11.\n";
                break;
        }

    } while (choice != 11);

    return 0;
}
