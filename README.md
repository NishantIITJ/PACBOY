# 🎮 PACBOY: IITJ Edition

A PACMAN-inspired terminal-based game built entirely in C with cross-platform support for Windows and macOS. Navigate through an ASCII maze, collect knowledge pellets, and chase high scores with an academic twist on the arcade classic.

---

## ⚙️ Features

- Terminal-based UI using ASCII graphics
- Cross-platform support (Windows and macOS)
- Animated menu screen with clear navigation
- Platform-specific compilation and execution
- Score tracking
- Clear instructions and credits section
- Minimal dependencies

---

## 🚀 How to Run

### 🔧 Prerequisites

- GCC compiler
- A terminal that supports ASCII output
- `ncurses` library (macOS only)
---

## Open Terminal on VS Code and type these commands:
-  Make sure to "maximise the terminal window" for the map to load completely :)
- < folderpath > is the path of the "pacboy" folder in your system. <br>
   example :  ```cd ~/Downloads/pacboy  ```

### 💻 For macOS

```bash
cd < folderpath >
gcc launcher.c -o play -lncurses
gcc mac.c -o pacman_mac -lncurses
./play
```

### 💻 For Windows



```bash
cd < folderpath >
gcc launcher.c -o play.exe 
gcc windows.c -o pacman_windows.exe 
play.exe
```

Choose your platform from the menu and the appropriate version of the game will run automatically.

---

## 📁 Project Structure

```
pacboy/
├── sounds/               # Contains all sound effect files 
├── pacman_launcher.c     # Main menu and platform selector
├── pacman_windows.c      # Windows version of the game
├── pacman_mac.c          # macOS version of the game
└── README.md             # Project description and instructions
```

---

## 🎮 Game Controls

- ↑ – Move Up  
- ← – Move Left  
- ↓ – Move Down  
- → – Move Right  
- `Q` – Quit Game

---

## 📜 Game Rules


**OBJECTIVE:**
- Collect at least 75% of total course percentage
- Collect m (minor) and M (major)
- Avoid the TAs (marked as 'T')

**CONTROLS:**
- Use Arrow keys to move your character (@)
- Press 'q' to quit the game

**ITEMS:**
- (.): Small course percentage (0.02 each)
- 'A': Assignment worth 3.0%
- 'Q': Quiz worth 4.0%
- 'm': Minor worth 10.0% (requires completing A and Q)
- 'M': Major worth 20.0% (requires completing Minor)

**LIVES:**
- You start with 3 chances
- Lose a chance when arguing with a TA
- You Fail when all chances are lost

**GRADES:**
- A*: 100% completion
- A+: 90-99.9% completion
- A: 80-89.9% completion
- B: 75-79.9% completion
- F: Below 75% completion

---

## 👨‍💻 Authors

- Core Game Architecture & Control Flow - **Nishant** 
- Player Mechanics (Movement logic) - **Hanny Rangera** 
- Demon Random Movement Logic - **Adesh Kumar Singh** 
- Menu and Map Design - **Saini Nikhil Rameshkumar** 
- Score Mathematics and Conditions - **Shubhashish Kumar** 

---

## 📝 Credits

- ncurses documentation
- C programming references
- Prompt engineering in some parts

---

## 🗂️ Submission & File Organization

All files are included in a single `.zip` archive named `pacboy.zip`.

### 📦 Folder Structure
```
pacboy/
├── sounds/            # Contains all sound effect (.wav) files
├── pacman_launcher.c  # Main launcher file
├── pacman_windows.c   # Windows-specific implementation
├── pacman_mac.c       # macOS-specific implementation
└── README.md          # Game description and how to run
```

### 📁 Important Notes
- **Do not change the folder structure.**
- Keep all sound files inside the `sounds/` directory.
- The code uses paths like `sounds/start.wav`, so it must be run from within the main folder.

```bash
cd < folderpath >
gcc < file >launcher.c -o play -lncurses
gcc < file >mac.c -o pacman_mac -lncurses
./play
```

---

Enjoy the game. Maybe you will pass the course but will you get an A? or you are the one to get **the A***?