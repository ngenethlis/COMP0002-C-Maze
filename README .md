# C Coursework
---
## What the program does:
Creates a **bot and maze struct**. 
Bot is **given a direction**. 

**Maze grid is initialised and filled with randomly generated walls which are then connected**. 

It's **entrance and exit are randomly generated , saved** and **drawn**. 

The **Bot is spawned at the entrance** of the maze and **tries to find the exit** marked by a grey square. 

The program **generates a new maze** for the bot to solve when it **reaches the exit.**   

---
### Hard-Coding the Maze and Changing sizes

The **maze can be hardcoded**, in the main file using mymaze.grid={..} but the **entrance and exit must also be defined** mymaze.entrace=...  mymaze.exit=... in the main file.
If **maze is hardcoded the generate_maze function must be removed** from main() in the main file
The **size of the maze, size of the squares** and **sleep time** can be changed from the functions.h file

---
#### Definitions:
0. b is black/wall 
1. w is white/path
2. g is grey/exit
3. u is unvisited and used for maze generation.
---

## How to run:
type
```bash
gcc -o main main.c functions.c graphics.c && ./main |java -jar drawapp-2.0.jar
```
in the terminal while in the directory that stores all files including graphics and drawapp.
