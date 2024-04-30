# C-Man
This project is a recreation of Namco's 1980 arcade game "Pac-Man", consisting of Pac-Man (The player), and four colored ghosts that chase the player

## Rules
1. The objective of the game is to eat all of the dots placed in the maze while avoiding four colored ghosts—Blinky (red), Pinky (pink), Inky (cyan), and Clyde (orange)—who pursue Pac-Man.

2. When Pac-Man eats all of the dots, the player advances to the next level. Levels are indicated by fruit icons at the center of the maze.

3. If Pac-Man is caught by a ghost, he loses a life; the game ends when all lives are lost.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Points
Points can be earned a variety of ways, either through the **Pac-Dots**, **Power Pellets**, eating **Ghosts**, or eating the **Bonus Fruit**. 

* **Pac-Dots** are worth 10 points

* **Power Pellets** are worth 50 points

* **Ghosts** are worth 200 points x the number of ghosts you have killed in a single super dot

* **Bonus Fruit**
    - **Cherry**: 100 points
    - **Strawberry**: 300 points
    - **Orange**: 500 points
    - **Apple**: 700 points
    - **Melon**: 1000 points
    - **Space ship**: 2000 points
    - **Bell**: 3000 points
    - **Key**: 5000 points

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Ghosts

There are four ghosts that will chase Pac-Man throughout the game, each arriving at different times and each having different movment patterns

- **Blinky** (Red)
- **Pinky** (Pink)
- **Inky** (Cyan)
- **Clyde** (Orange)


Ghosts will continue to chase the player unless the player has eaten a **Power Pellet**
- When eaten the ghosts will enter "scatter mode" and flee from the player.
- Ghosts will become blue and will flash white when turning back into their normal forms.
- If ghosts are eaten during the scatter mode, their eyes will remain and will return to the "house", the box within the center of the maze, to respawn.

## Blinky, The Red Ghost

Blinky will start chasing the player at the beginning of the game.

Blinky's A.I. based movement is to chase the player based on their current position.



## Pinky, The Pink Ghost

Pinky will start within the house but will also chase the player at the beginning.

Pinky's A.I. based movement will chase the player based on their tiles in front of them.



## Inky, The Cyan Ghost

Inky will start within the "house" but will not leave until the player has eaten 1/3rd of the Pac-Dots.

Inky's A.I. based movement will draw a vector based on Blinky's position and the player's position and chase the tiles in front of that vector.



## Clyde, The Orange Ghost

Clyde will start within the "house" but will not leave until the player has eaten 2/3rds of the Pac-Dots.

Clyde's A.I. based movement is based on position to the player. If Clyde is within 8 tiles to the player, he will not chase. When he is more than 8 tiles from the player, he will begin to chase equivalent to Blinky's chase pattern.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Movement

Pac-Man can be controlled through the arrow keys **UP**, **DOWN**, **LEFT**, and **RIGHT**.

Each key will choose the direction the sprite will go, while the sprite will move that direction automatically, until faced with a wall.

When in contact with a wall, a buffer has been implemented that will stop the player from moving to allow a choice of which direction to go.

"Warp Tunnels" have also been implemented that are located on the left and right side of the maze
- Taking a warp tunnel will teleport the player to the location of the other warp tunnel to allow for more traversal options.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

