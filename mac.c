// Include necessary libraries
#include <stdlib.h>     // For rand, srand, malloc, system
#include <string.h>     // For string operations like strlen
#include <ncurses.h>    // For terminal-based graphics
#include <time.h>       // For random time seeding (to spawn ghost at random locations)
#include <unistd.h>     // For usleep(adds pauses, to make game smoother)



// Define game map dimensions, delay, number of enemies, and total score
#define MAP_WIDTH 84
#define MAP_HEIGHT 33
#define DELAY 100000 //controls game speed
#define MAX_GHOST 10

// The game map: '#' = wall, '.' = collectible, letters = special items
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

// Game state variables
int playerX=1, playerY=1;            // Player's starting position
double score=0.0;                      // Score based on collected items
int collectedQ = 0, collectedA = 0;        // Check if colect q and a
int collectedm = 0, collectedM = 0;        // Check q and a again
int chances = 5;                           // Player's chances

// Demon enemy positions
int ghostX[MAX_GHOST], ghostY[MAX_GHOST];
int numGhost = 10;                      // Total number of ghost

// Movement direction variables for the player
int dirX = 1, dirY = 0;                  


// Sound functions (macOS)  // looked on Stack Overflow
void playStartSound() {
    system("afplay sounds/pacman_start.wav &");
}
void playDeathSound() {
    system("afplay sounds/pacman_death.wav &");
}

void playFruitSound() {
    system("afplay sounds/pacman_eatghost.wav & ");
}

void playWinSound() {
    system("afplay sounds/pacman_eatghost.wav &");
}

 

void initGhost() {
    srand(time(NULL));
    for(int i=0; i<numGhost; i++){
        int x, y;
        do {
            x=rand() % MAP_WIDTH;
            y=rand() % MAP_HEIGHT;
        } while (map[y][x] != '.');
        ghostX[i] = x;
        ghostY[i] = y;
    }
}

// Draws the full game map, including player and ghost
void drawMap(){
    clear();                                          // Clear the screen for redrawing
    for(int y=0; y<MAP_HEIGHT; y++){
        for(int x=0; x<MAP_WIDTH; x++){
            if(x == playerX && y == playerY){
                mvaddch(y, x, '@');                         // Draws player
            }
            else{
                int demonPresent = 0;
                for(int i=0; i<numGhost; i++){
                    if(x == ghostX[i] && y == ghostY[i]){
                        attron(COLOR_PAIR(2));
                        mvaddch(y, x, 'T');  // Draws demon
                        attroff(COLOR_PAIR(2));      
                        demonPresent = 1;
                        break;
                    }
                }
                if(!demonPresent){
                    if(map[y][x] == '#'){
                        attron(COLOR_PAIR(1));
                        mvaddch(y, x, '#');
                        attroff(COLOR_PAIR(1));
                    }else{
                        mvaddch(y, x, map[y][x]);
                        }
                }
            }
        }
    }

    // Calculate and display course score and remaining chances
    mvprintw(MAP_HEIGHT, 0, "Course Percentage completed: %.2f%%  Chances: %d", score, chances);
    refresh(); // Update screen with new drawing
}


// Handles player's movement with smooth step control
void movePlayer(){
    int newX = playerX, newY = playerY;

    // Control continuous movement
    if (dirX != 0) {
    newX = playerX + dirX;
    } 
    else if (dirY != 0) {
    newY = playerY + dirY;
    }

    char target = map[newY][newX];
    if (target != '#') { // Can't move into walls
        playerX = newX;
        playerY = newY;

        // Scoring and objective handling
        if (target == '.') {
            score += 0.02272727;
            map[newY][newX] = ' ';
        } else if (target == 'A') {
            score += 3.0;
            collectedA = 1;
            map[newY][newX] = ' ';
            playFruitSound();
        } else if (target == 'Q') {
            score += 4.0;
            collectedQ = 1;
            map[newY][newX] = ' ';
            playFruitSound();
        } else if (target == 'm') {
            if (collectedA && collectedQ) {
                score += 10.0;
                collectedm = 1;
                map[newY][newX] = ' ';
                playFruitSound();
            }
        } else if(target == 'M'){
            if (collectedm && !collectedM){ // !collectedM can be removed
                score += 20.0;
                collectedM = 1;
                map[newY][newX] = ' ';
                playWinSound();
            }
        }
    }
}

// Random demon movement logic
void moveGhost() {
    for (int i=0;i<numGhost;i++) {
        int dx=0, dy=0;
        int direction=rand()%4;

        switch (direction) {
            case 0: dx=-1; break;
            case 1: dx=1; break;
            case 2: dy=-1; break;
            case 3: dy=1; break;
        }

        int newX = ghostX[i] + dx;
        int newY = ghostY[i] + dy;

        if (map[newY][newX] != '#' && !(newX == playerX && newY == playerY)) {
            ghostX[i] = newX;
            ghostY[i] = newY;
        }
    }
}


// Check if player has collided with any demon
int checkCollision() {
    for(int i=0;i<numGhost;i++){
        if (abs(playerX-ghostX[i]) <= 1 && abs(playerY-ghostY[i]) <= 1) {
            chances--;
            playDeathSound();  // Play sound every time life is lost
            playerX = 1; //Respawn
            playerY = 1;
            if(chances==0){
                return -1;
            }
        }
    }
    return 0;
}


int checkWin(){
    return (score>=75.0 && collectedm && collectedM);
}

void showEndScreen(const char* message){
    char* grade;

    if(score>=99.0) grade = "A*";
    else if(score>=90.0) grade = "A+";
    else if(score>=80.0) grade = "A";
    else if(score>=75.0) grade = "B";
    else grade = "F";

    clear();
    mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH - strlen(message)) / 2, "%s", message);
    mvprintw(MAP_HEIGHT / 2 + 1, (MAP_WIDTH - 20) / 2, "Total Score: %.2f%%",score);
    mvprintw(MAP_HEIGHT / 2 + 2, (MAP_WIDTH - 10) / 2, "Grade: %s", grade);
    mvprintw(MAP_HEIGHT / 2 + 3, (MAP_WIDTH - 24) / 2, "Press any key to exit.");
    refresh();
    nodelay(stdscr, FALSE); //blocking input
    getch();
}

int main() {
    initscr();         // Initialize ncurses
    curs_set(FALSE);   // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys input
    nodelay(stdscr, TRUE); // Non-blocking input

    //color
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Yellowish brown for '#'
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Red for 'T'
    

    playStartSound();
    initGhost();

    // Main game loop
    while(1){
        drawMap();

        int ch=getch();
        switch (ch) {
            case KEY_UP: dirX = 0; dirY=-1; break;
            case KEY_DOWN: dirX = 0; dirY=1; break;
            case KEY_LEFT: dirX = -1; dirY=0; break;
            case KEY_RIGHT: dirX = 1; dirY=0; break;
            case 'q': endwin(); return 0;
        }

        movePlayer();
        moveGhost();

        if(checkCollision()==-1) {
            drawMap();  // Update final course score
            showEndScreen("Game Over!");
            break;
        }

        if(checkWin()){
            drawMap(); // Update final course score
            showEndScreen("You Win!");
            break;
        }

        usleep(DELAY);
    }

    endwin();
    return 0;
}