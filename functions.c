#include "graphics.h"
#include "functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

// these arrays store the original vertices of the triangle facing each direction
const int x_coor_E[3] = {0, 2 * half_square_size, 0};
const int y_coor_E[3] = {0, half_square_size, 2 * half_square_size};

const int x_coor_W[3] = {2 * half_square_size, 0, 2 * half_square_size};
const int y_coor_W[3] = {0, half_square_size, 2 * half_square_size};

const int x_coor_N[3] = {0, half_square_size, square_size};
const int y_coor_N[3] = {square_size, 0, square_size};

const int x_coor_S[3] = {0, half_square_size, square_size};
const int y_coor_S[3] = {0, square_size, 0};

void drawmaze(maze *anymaze)
{
  setWindowSize(width, height);
  background();
  for (int j = 0; j < row; j++)
  {
    for (int i = 0; i < column; i++)
    {
      if (anymaze->grid[j][i] == w)
        setColour(white);
      else if (anymaze->grid[j][i] == g)
        setColour(gray);
      else
      {
        setColour(black);
        anymaze->grid[j][i] = b;
      }
      fillRect(i * square_size, j * square_size, square_size, square_size);
      setColour(black);
      drawLine(i * square_size, j * square_size, width, j * square_size);
      drawLine(i * square_size, j * square_size, i * square_size, height);
    }
  }
}

void printmaze(maze *anymaze) // for debugging and testing purposes
{
  for (int j = 0; j < row; j++)
  {
    for (int i = 0; i < column; i++)
      printf("%d", anymaze->grid[j][i]);
    printf("\n");
  }
}

void arraycopy(int *arr1, const int *arr2)
{
  for (int i = 0; i < 3; i++)
    *(arr1 + i) = *(arr2 + i);
}

void drawBot(int xoff, int yoff, int xarr[], int yarr[])
{
  for (int i = 0; i < 3; i++)
  {
    xarr[i] += xoff;
    yarr[i] += yoff;
  }
  sleep(sleep_time);
  clear();
  fillPolygon(3, xarr, yarr);
}

int canMoveForward(bot *anyBot, maze *anymaze)
{
  int new_x;
  int new_y;
  switch (anyBot->direction)
  {
  case 'E':
    new_x = anyBot->x + square_size;
    new_y = anyBot->y;
    break;
  case 'N':
    new_x = anyBot->x;
    new_y = anyBot->y - square_size;
    break;

  case 'W':
    new_x = anyBot->x - square_size;
    new_y = anyBot->y;
    break;

  case 'S':
    new_x = anyBot->x;
    new_y = anyBot->y + square_size;
    break;
  }
  // convert x y coordinates to grid position
  new_x /= square_size;
  new_y /= square_size;
  if (anymaze->grid[new_y][new_x] == b)
  {
    return false;
  }
  return true;
}

void forward(bot *anyBot)
{
  int x_arr[3];
  int y_arr[3];

  switch ((*anyBot).direction)
  {
  case 'N':
    anyBot->y -= square_size;
    arraycopy(x_arr, x_coor_N);
    arraycopy(y_arr, y_coor_N);
    break;

  case 'S':
    anyBot->y += square_size;
    arraycopy(x_arr, x_coor_S);
    arraycopy(y_arr, y_coor_S);
    break;

  case 'E':
    anyBot->x += square_size;
    arraycopy(x_arr, x_coor_E);
    arraycopy(y_arr, y_coor_E);
    break;

  case 'W':
    anyBot->x -= square_size;
    arraycopy(x_arr, x_coor_W);
    arraycopy(y_arr, y_coor_W);
    break;
  }

  drawBot(anyBot->x, anyBot->y, x_arr, y_arr);
}

void left(bot *anyBot)
{
  int x_arr[3];
  int y_arr[3];
  switch (anyBot->direction)
  {
  case 'E':
    anyBot->direction = 'N';
    arraycopy(x_arr, x_coor_N);
    arraycopy(y_arr, y_coor_N);
    break;

  case 'N':
    anyBot->direction = 'W';
    arraycopy(x_arr, x_coor_W);
    arraycopy(y_arr, y_coor_W);
    break;

  case 'W':
    anyBot->direction = 'S';
    arraycopy(x_arr, x_coor_S);
    arraycopy(y_arr, y_coor_S);
    break;

  case 'S':
    anyBot->direction = 'E';
    arraycopy(x_arr, x_coor_E);
    arraycopy(y_arr, y_coor_E);
    break;
  }

  drawBot(anyBot->x, anyBot->y, x_arr, y_arr);
}

void right(bot *anyBot)
{
  int x_arr[3];
  int y_arr[3];
  switch (anyBot->direction)
  {
  case 'E':
    anyBot->direction = 'S';
    arraycopy(x_arr, x_coor_S);
    arraycopy(y_arr, y_coor_S);
    break;

  case 'N':
    anyBot->direction = 'E';
    arraycopy(x_arr, x_coor_E);
    arraycopy(y_arr, y_coor_E);
    break;

  case 'W':
    anyBot->direction = 'N';
    arraycopy(x_arr, x_coor_N);
    arraycopy(y_arr, y_coor_N);
    break;

  case 'S':
    anyBot->direction = 'W';
    arraycopy(x_arr, x_coor_W);
    arraycopy(y_arr, y_coor_W);
    break;
  }

  drawBot(anyBot->x, anyBot->y, x_arr, y_arr);
}

void spawnbot(bot *anyBot, maze *anymaze)
{
  foreground();
  setColour(yellow);
  anyBot->x = 0;
  anyBot->y = anymaze->entrace * square_size;
  right(anyBot);
}

int atMarker(bot *anyBot, maze *anymaze)
{
  int x = anyBot->x;
  int y = anyBot->y;
  x /= square_size;
  y /= square_size;
  if (anymaze->grid[y][x] == g)
    return 1;
  return 0;
}

void solver(bot *anyBot, maze *anymaze) // rudementary maze search forward and turn right else turn left.
{
  if (atMarker(anyBot, anymaze))
    return;
  else
  {
    if (canMoveForward(anyBot, anymaze))
    {
      forward(anyBot);
      right(anyBot);
    }
    else
      left(anyBot);
    solver(anyBot, anymaze);
  }
}

int check_neighbours(int list[], int val)
{
  return (list[0] == val || list[1] == val || list[2] == val || list[3] == val);
}

void choose_neighbour(int *x, int *y, int list[])
{
  int k; // in scope of while loop
  do
  {
    k = rand() % 4;
  } while (list[k] != u); // until unvisited neighbour found
  switch (k)
  {
  case 0:
    if (*y > 0)
      (*y)--;
    break;
  case 1:
    if (*x < column - 1)
      (*x)++;
    break;
  case 2:
    if (*y < row - 1)
      (*y)++;
    break;
  case 3:
    if (*x > 0)
      (*x)--;
    break;
  }
}

void fill_maze(maze *anymaze) // connects singular blocks of wall
{
  int start;
  int finish;
  int counter;
  for (int j = 1; j < row - 1; j++)
  {
    counter = 0;
    start = 0;
    finish = 0;
    for (int i = 1; i < column - 1; i++)
    {
      if (anymaze->grid[j][i] == b)
      {
        switch (counter % 2)
        {
        case 0:
          start = i;
          break;
        case 1:
          finish = i;
          break;
        }
        counter++;
        if (i > start && i == finish && j != anymaze->entrace && j != anymaze->exit) // chooses when to connect
        {
          for (int k = start + 1; k < finish - 1; k++)
            if (k < column - 2) // makes it impossible to make a whole row wall so maze is solvable
              anymaze->grid[j][k] = b;
        }
      }
      if (j == anymaze->entrace || j == anymaze->exit)
        anymaze->grid[j][i] = w;
    }
  }
}

void generate_recursive(maze *anymaze)
{

  anymaze->entrace = rand() % (row - 2) + 1;
  anymaze->exit = rand() % (row - 2) + 1; // this makes sure that corners are never chosen
  initialise_maze(anymaze);               // edges wall centre unvisited
  recursive_backtracker(rand() % column, rand() % row, anymaze);
  fill_maze(anymaze);
  anymaze->grid[anymaze->entrace][0] = w;
  anymaze->grid[anymaze->entrace][1] = w;
  anymaze->grid[anymaze->exit][column - 2] = w;
  anymaze->grid[anymaze->exit][column - 1] = g; // makes entrace,exit and block connecting them to the maze path.
  drawmaze(anymaze);
}

void initialise_maze(maze *anymaze)
{
  for (int j = 0; j < row; j++)
  {
    for (int i = 0; i < column; i++)
    {
      if (j == 0 || j == row - 1 || i == 0 || i == column - 1)
      {
        anymaze->grid[j][i] = b; // edges are wall
      }
      else
        anymaze->grid[j][i] = u; // make inner maze unvisited.
    }
  }
}

void recursive_backtracker(int x, int y, maze *anymaze)
{
  while (1)
  {
    anymaze->grid[y][x] = b;
    int neighbours[4] = {anymaze->grid[y - 1][x], anymaze->grid[y][x + 1], anymaze->grid[y + 1][x], anymaze->grid[y][x - 1]}; // values of N E S W squares of current position
    if (check_neighbours(neighbours, u) == false)                                                                             // if all visited
    {
      if (check_neighbours(neighbours, b) == false && anymaze->grid[y][x] != b) // if all wall and current isnt wall
      {
        anymaze->grid[y][x] = b;
      }
      else if (check_neighbours(neighbours, b) == true)
      {
        anymaze->grid[y][x] = w;
      }
      break;
    }
    // choose random unvisited neighbour
    choose_neighbour(&x, &y, neighbours);
    recursive_backtracker(x, y, anymaze);
  }
  anymaze->grid[y][x] = w;
  return; // backtracks to previous square
}
