#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>  // Windows console input/output
#else
#include <unistd.h>
#include <signal.h> //sound(kill)
#include <sys/wait.h> //sound(wait)

#include <ncurses.h>  // For terminal UI
#endif

// Global for sound process (Linux/macOS)
#ifndef _WIN32
pid_t sound_pid = 0;
#endif

int isWindows() {
    #ifdef _WIN32
        return 1;
    #else
        return 0;
    #endif
}

int isMac() {
    if (isWindows()==0){
        return 1;
    }
    return 0;
}

// Start menu sound loop
void startMenuSound() {
    #ifndef _WIN32
    sound_pid = fork();  // Create a child process for sound
    if (sound_pid == 0) {
        if (isMac()) {
            execlp("afplay", "afplay", "sounds/pacman_menu.wav", NULL);
        } else {
            execlp("aplay", "aplay", "-q", "--loop=0", "sounds/pacman_menu.wav", NULL);
        }
        exit(0);  // Just in case execlp fails
    }
    #endif
}

// Stop menu sound
void stopMenuSound() {
    #ifndef _WIN32
    if (sound_pid > 0) {
        kill(sound_pid, SIGTERM);
        waitpid(sound_pid, NULL, 0);
        sound_pid = 0;
    }
    #endif
}

void showStartScreen() {
    #ifdef _WIN32
    system("cls");
    printf(
        "######################################################################\n"
        "#                                                                    #\n"
        "#             Hint: You cannot give Major without minor.             #\n"
        "#        T     _____             ____                       T        #\n"
        "#             |  __ \\           |  _ \\               TM              #\n"
        "#             | |__) |_ _    ___| |_) |   ___  _   _                 #\n"
        "#     T       |  ___/ _` |  / __|  _ <   / _ \\| | | |         T      #\n"
        "#             | |  | (_| | | (__| |_) | | (_) | |_| |                #\n"
        "#             |_|   \\__,_|  \\___|____/   \\___/ \\__, | .iitj          #\n"
        "#                                               __/ |                #\n"
        "#      @                      PRESS            |___/        @        #\n"
        "#                      1  Play on Windows                            #\n"
        "#                      2  Play on MAC/Linux                          #\n"
        "#            T         3  Rules                    T                 #\n"
        "#                      4  Quit                                       #\n"
        "#                                                                    #\n"
        "#    T                       IC PROJECT (R)                 T        #\n"
        "#                   (C) 2024-2028  ShuuKriyans UnLTD.                #\n"
        "#                                                                    #\n"
        "###################################################################### \n\n"
    );
    #else
    clear();
    mvprintw(0, 0,
        "######################################################################\n"
        "#                                                                    #\n"
        "#             Hint: You cannot give Major without minor.             #\n"
        "#        T     _____             ____                       T        #\n"
        "#             |  __ \\           |  _ \\               TM              #\n"
        "#             | |__) |_ _    ___| |_) |   ___  _   _                 #\n"
        "#     T       |  ___/ _` |  / __|  _ <   / _ \\| | | |         T      #\n"
        "#             | |  | (_| | | (__| |_) | | (_) | |_| |                #\n"
        "#             |_|   \\__,_|  \\___|____/   \\___/ \\__, | .iitj          #\n"
        "#                                               __/ |                #\n"
        "#      @                      PRESS            |___/        @        #\n"
        "#                      1  Play on Windows                            #\n"
        "#                      2  Play on MAC/Linux                          #\n"
        "#            T         3  Rules                    T                 #\n"
        "#                      4  Quit                                       #\n"
        "#                                                                    #\n"
        "#    T                       IC PROJECT (R)                 T        #\n"
        "#                   (C) 2024-2028  ShuuKriyans UnLTD.                #\n"
        "#                                                                    #\n"
        "###################################################################### \n\n"
    );
    refresh();
    #endif
}

void displayRules() {
    #ifdef _WIN32
    system("cls");
    printf(
        "######################################################################\n"
        "#                         PACBOY ICS COURSE EDITION                  #\n"
        "#                              GAME RULES                            #\n"
        "######################################################################\n"
        "#                                                                    #\n"
        "# OBJECTIVE:                                                         #\n"
        "# - Collect at least 75%% of total course percentage                  #\n"
        "# - Collect m (minor) and M (major)                                  #\n"
        "# - Avoid the TAs (marked as 'T')                                    #\n"
        "#                                                                    #\n"
        "# CONTROLS:                                                          #\n"
        "# - Use Arrow keys to move your character (@)                        #\n"
        "# - Press 'q' to quit the game                                       #\n"
        "#                                                                    #\n"
        "# ITEMS:                                                             #\n"
        "# - (.): Small course percentage (0.02 each)                         #\n"
        "# - 'A': Assignment worth 3.0 %%                                      #\n"
        "# - 'Q': Quiz worth 4.0 %%                                            #\n"
        "# - 'm': Minor worth 10.0 %%  (requires completing A and Q)           #\n"
        "# - 'M': Major worth 20.0 %%  (requires completing Minor)             #\n"
        "#                                                                    #\n"
        "# LIVES:                                                             #\n"
        "# - You start with 3 chances                                         #\n"
        "# - Lose a chance when arguing with a TA                             #\n"
        "# - You Fail when all chances are lost                               #\n"
        "#                                                                    #\n"
        "# GRADES:                                                            #\n"
        "# - A*: 100%% completion                                              #\n"
        "# - A+: 90-99.9%% completion                                          #\n"
        "# - A: 80-89.9%% completion                                           #\n"
        "# - B: 75-79.9%% completion                                           #\n"
        "# - F: Below 75%% completion                                          #\n"
        "#                                                                    #\n"
        "# Press any key to return to main menu...                            #\n"
        "######################################################################\n"
    );
    getch();
    #else
    clear();
    mvprintw(0, 0,
    "######################################################################\n"
    "#                         PACBOY ICS COURSE EDITION                  #\n"
    "#                              GAME RULES                            #\n"
    "######################################################################\n"
    "#                                                                    #\n"
    "# OBJECTIVE:                                                         #\n"
    "# - Collect at least 75%% of total course percentage                  #\n"
    "# - Collect m (minor) and M (major)                                  #\n"
    "# - Avoid the TAs (marked as 'T')                                    #\n"
    "#                                                                    #\n"
    "# CONTROLS:                                                          #\n"
    "# - Use Arrow keys to move your character (@)                        #\n"
    "# - Press 'q' to quit the game                                       #\n"
    "#                                                                    #\n"
    "# ITEMS:                                                             #\n"
    "# - (.): Small course percentage (0.02 each)                         #\n"
    "# - 'A': Assignment worth 3.0 %%                                      #\n"
    "# - 'Q': Quiz worth 4.0 %%                                            #\n"
    "# - 'm': Minor worth 10.0 %%  (requires completing A and Q)           #\n"
    "# - 'M': Major worth 20.0 %%  (requires completing Minor)             #\n"
    "#                                                                    #\n"
    "# LIVES:                                                             #\n"
    "# - You start with 3 chances                                         #\n"
    "# - Lose a chance when arguing with a TA                             #\n"
    "# - You Fail when all chances are lost                               #\n"
    "#                                                                    #\n"
    "# GRADES:                                                            #\n"
    "# - A*: 100%% completion                                              #\n"
    "# - A+: 90-99.9%% completion                                          #\n"
    "# - A: 80-89.9%% completion                                           #\n"
    "# - B: 75-79.9%% completion                                           #\n"
    "# - F: Below 75%% completion                                          #\n"
    "#                                                                    #\n"
    "# Press any key to return to main menu...                            #\n"
    "######################################################################\n"
    );
    refresh();
    nodelay(stdscr, FALSE); // Wait for key press
    getch();
    nodelay(stdscr, TRUE);  // Resume non-blocking input
    #endif
}

void launchWindowsGame() {
    system("cls");
    printf("Launching Windows version...\n");
    system("pacman_windows.exe");
}

void launchMacGame() {
    #ifndef _WIN32
    endwin();
    system("./pacman_mac");
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    #endif
}

int main() {
    #ifndef _WIN32
    initscr();               // Start ncurses mode
    noecho();                // Don't echo keypresses
    curs_set(FALSE);         // Hide the cursor
    keypad(stdscr, TRUE);    // Enable special keys
    nodelay(stdscr, TRUE);   // Non-blocking input
    #endif

    int running = 1;

    while (running) {
        #ifndef _WIN32
        startMenuSound();  
        #endif
        showStartScreen();

        int choice = 0;
        int ch;

        while (choice == 0) {
            #ifdef _WIN32
            ch = getch();
            #else
            ch = getch();
            #endif

            if (ch >= '1' && ch <= '4') {
                choice = ch - '0';
            } else if (ch == 'q' || ch == 'Q') {
                choice = 4;
            }

            #ifndef _WIN32
            napms(100);  // Slight delay to avoid busy-waiting
            #else
            Sleep(100);  // Windows delay
            #endif
        }

        #ifndef _WIN32
        stopMenuSound();  // Stop sound before action
        #endif

        switch (choice) {
            case 1:
                if (isWindows()) {
                    launchWindowsGame();
                } else {
                    #ifndef _WIN32
                    mvprintw(20, 10, "Windows version cannot run on Mac/Linux! Press any key...");
                    refresh();
                    nodelay(stdscr, FALSE);
                    getch();
                    nodelay(stdscr, TRUE);
                    #endif
                }
                break;

            case 2:
                if (!isWindows()) {
                    launchMacGame();
                } else {
                    system("cls");
                    printf("Mac/Linux version cannot run on Windows! Press any key...\n");
                    getch();
                }
                break;

            case 3:
                displayRules();
                break;

            case 4:
                running = 0;
                break;
        }
    }

    #ifndef _WIN32
    endwin(); // End ncurses
    #endif
    return 0;
}