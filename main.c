
#include "functions.h"
#include <time.h>
#include <stdlib.h>

int main()
{
  srand(time(NULL));
  bot myBot;
  myBot.direction = 'N';
  maze mymaze;
  while (1)
  {
    generate_recursive(&mymaze);
    drawmaze(&mymaze);
    spawnbot(&myBot, &mymaze);
    solver(&myBot, &mymaze);
  }
  return 0;
}