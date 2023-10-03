#define b 0
#define w 1
#define g 2
#define u 3
#define square_size 40
#define width 800
#define height 800
#define row height / square_size
#define column width / square_size
#define half_square_size square_size / 2
#define sleep_time 150

const int x_coor_E[3];
const int y_coor_E[3];

const int x_coor_W[3];
const int y_coor_W[3];

const int x_coor_N[3];
const int y_coor_N[3];

const int x_coor_S[3];
const int y_coor_S[3];

typedef struct
{
  int x, y; // x y coordinates of upper left corner of grid square. divide by square_size to get grid position in maze
  char direction;
} bot;

typedef struct
{
  int grid[row][column];
  int entrace;
  int exit;
} maze;

void drawmaze(maze *anymaze);
void printmaze(maze *anymaze);
void arraycopy(int *arr1, const int *arr2);
void drawBot(int xoff, int yoff, int xarr[], int yarr[]);
void forward(bot *anyBot);
void left(bot *anyBot);
void right(bot *anyBot);
void spawnbot(bot *anyBot, maze *anymaze);
int atMarker(bot *anyBot, maze *anymaze);
void solver(bot *anyBot, maze *anymaze);
int canMoveForward(bot *anyBot, maze *anymaze);
void generate_recursive(maze *anymaze);
void initialise_maze(maze *anymaze);
void recursive_backtracker(int x, int y, maze *anymaze);
void choose_neighbour(int *x, int *y, int list[]);
int check_neighbours(int list[], int val);
void fill_maze(maze *anymaze);