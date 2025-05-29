// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // used to randomly spawn demons

// Windows-specific libraries for console control and keyboard input
#include <conio.h>
#include <windows.h>

// Game configuration constants
#define MAP_WIDTH 84
#define MAP_HEIGHT 33
#define DELAY 80             // Time interval for demon movement
#define PLAYER_SPEED 16      // Delay between player steps
#define MAX_DEMONS 10     

// Game state variables
char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "####################################################################################",
    "# .................................................................................#",
    "#..................................................................................#",  
    "#..###############....#################......###############....#############......#",
    "#........##..................##....................##................##............#",
    "#........##..................##......#####.........##................##............#",
    "#........##......#.###.#.....##......#####.........##........###.....##.....#.#....#",
    "#........##......#.#Q#.#.....##....................##........###.....##.....#A#....#",
    "#........##......#.....#.....##....##..............##................##.....#.#....#",
    "#........##......#######.....##....##.....###......##................##............#",
    "#........##..................##....##.....###......##..........##....##............#",
    "#........##..................##...........###......##...........##...##............#",
    "#...##############.....###############.............##............##.##.............#",
    "#........................................................................#####.....#",
    "#....####............................#.#####.#.......................... ..........#",
    "#....####.....##################.....#.......#........#################............#",
    "#....####............................### M ###...........................####......#",
    "#......................................#####.......................................#",
    "#..###############......###########..........############.......###########........#",
    "#........##............##....................#........Q.#.......#.........#........#",
    "#........##..........##......................#...####...#.......#....Q....#...##...#",
    "#........##.........##.........#######.......#...####...#.......#.........#...##...#",
    "#...A....##.........##....Q....#. m .#.......#..........#.......#..########...##...#",
    "#........##.........##.........#.....#.......#..#########.......#..#..........##...#",
    "#........##..........##........##...##.......#..................#...#.........##...#",
    "#........##...........##.....................#........####......#.....#............#",
    "#........##............##....................#......########....#.......#..........#",
    "#..###############......###########..........#........####......#.........#........#",
    "#..................................................................................#",
    "#.......##........###.....................###........#####............#########....#",
    "#.......##.........##.....A.....####......###.......#####............##########....#",
    "#.......##.........................................................................#",
    "####################################################################################"
};

int playerX = 1, playerY = 1;
double score = 0.0;
int collectedQ = 0, collectedA = 0, collectedm = 0, collectedM = 0;
int lives = 5;
int demonsX[MAX_DEMONS], demonsY[MAX_DEMONS];
int numDemons = 10;

void initDemons() {
    srand(time(NULL));
    for (int i = 0; i < numDemons; i++) {
        int x, y;// these are the positions of demons
        do {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;     //hash demon problem
        } while (map[y][x] != '.');
        demonsX[i] = x;
        demonsY[i] = y;// if two demon positions are similar still there's no problem as they all are moving differently or rather randomly
    }
}

// Moves the console cursor to (x, y) position for redrawing
void setCursorPos(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);// 
}

void drawMap() {
    setCursorPos(0, 0);
    for(int y=0; y<MAP_HEIGHT; y++) {
        for (int x=0; x<MAP_WIDTH; x++) {
            if (x == playerX && y == playerY) {
                printf("@");
            }
            else{
                int demonPresent = 0;
                for (int i = 0; i < numDemons; i++) {
                    if (x == demonsX[i] && y == demonsY[i]) {
                        printf("T");
                        demonPresent = 1;
                        break;
                    }
                }
                if (!demonPresent)
                    printf("%c", map[y][x]);
            }
        }
        printf("\n");
    }

    printf("Score: %.2f%%  Lives: %d\n", score, lives);
}

// Move player in specified direction and handle scoring
void movePlayer(int key) {
    int newX = playerX;
    int newY = playerY;

    switch (key) {
        case 72: newY--; break;
        case 80: newY++; break;
        case 75: newX--; break;
        case 77: newX++; break;
        default: return;
    }

    if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT)
        return;

    char target = map[newY][newX];
    if (target != '#') {
        playerX = newX;
        playerY = newY;

        if (target == '.') {
            score += 0.02272727;
            map[newY][newX] = ' ';
        } else if (target == 'A') {
            score += 3.0;
            collectedA = 1;
            map[newY][newX] = ' ';
        } else if (target == 'Q') {
            score += 4.0;
            collectedQ = 1;
            map[newY][newX] = ' ';
        } else if (target == 'm') {
            if (collectedA && collectedQ) {
                score += 10.0;
                collectedm = 1;
                map[newY][newX] = ' ';
            }
        } else if (target == 'M') {
            if (collectedm) {
                score += 20.0;
                collectedM = 1;
                map[newY][newX] = ' ';
            }
        }
    }
}

// Move demons randomly (not into walls or goals)
void moveDemons() {
    for (int i = 0; i < numDemons; i++) {
        int dx = (rand() % 3) - 1;
        int dy = (rand() % 3) - 1;                    //check again
        int newX = demonsX[i] + dx;
        int newY = demonsY[i] + dy;
        if (map[newY][newX] != '#' && map[newY][newX] != 'M' && map[newY][newX] != 'm' && map[newY][newX] != 'A' && map[newY][newX] != 'Q') {
            demonsX[i] = newX;
            demonsY[i] = newY;
        }
    }
}

// Check if demon collided with player
int checkCollision() {
    for (int i = 0; i < numDemons; i++) {
        if (abs(playerX - demonsX[i]) <= 1 && abs(playerY - demonsY[i]) <= 1) {
            lives--;
            playerX = 1;
            playerY = 1;
            if (lives <= 0) return -1;
        }
    }
    return 0;
}

// Check if win condition is satisfied
int checkWin() {
    return (score >= 75.0 && collectedm && collectedM);
}

// Show win or loss message with grade
void showEndScreen(const char* message) {
    const char* grade;

    if (score == 100.0) grade = "A*";
    else if (score >= 90.0) grade = "A+";
    else if (score >= 80.0) grade = "A";
    else if (score >= 75.0) grade = "B";
    else grade = "F";

    printf("\n%s\nFinal Score:%.2f%%\nGrade: %s\n", message, score, grade);
    printf("Press any key to exit...");
    _getch();
}

int main() {
    initDemons();   // Place demons randomly

    int currentDirection = 0;
    int demonTimer = 0;

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;  //used to hide the blinking cursor
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    //main game loop
    while (1) {
        drawMap();


        // Capture player input
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) {
                currentDirection = _getch();
            } else if (ch == 'q') {
                break;
            }
        }

        // Move demons after fixed interval
        if (currentDirection)
            movePlayer(currentDirection);


        // Move demons after fixed interval
        if (demonTimer >= DELAY) {
            moveDemons();
            if (checkCollision() == -1) {
                showEndScreen("Game Over!");
                break;
            }
            demonTimer = 0;
        }

        if (checkWin()) {
            showEndScreen("You Win!");
            break;
        }

        Sleep(PLAYER_SPEED);
        demonTimer += PLAYER_SPEED;
    }

    return 0;
}