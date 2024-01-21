# Main Objective
As stated in the russianRoullete-Game.py file, the objective for this project was to use what I learned in the first semester in Python to create a simple yet interesting game that is meant to be played on the terminal (since I am unable to create front-end at the time of making this project).
During the creation of this project I came across [Buckshot Roulette by Mikie Klubnika](https://mikeklubnika.itch.io/buckshot-roulette) and thought that it would be interesting for me to try to recreate the core gameplay loop seen in that game, in python. Note that even tho the game was inspired by Buckshot Roulette, the entire code is original and written entirely by me.

![imagem_2024-01-18_214738156](https://github.com/HugoNogueira05/FEUP-Projects/assets/126121324/0a71284c-7544-4140-9df8-48a5da10b661)

## The Coding process:
**Note that this is still a work in progress**
### Core mechanics:
As stated before the focus is to create a game that resembles the russian roulette where the player can play against an "AI" that is in fact just an algorithm that works based on the odds of success.
Therefore the main mechanics are:
* Shooting:
  - You can pick to either shoot yourself or the opponent.
  - Just like in Buckshot Roulette if you pick to shoot yourself and it is a blank you get to shoot again.
  - Shooting or getting shot decreases the life of whoever got shot.
  - To pick if the next bullet is real or blank, the weapon is represented as a list of booleans where _False_ represents a blank and _True_ represents a real bullet, then using .pop at a random index getting a random bullet
* Reloading:
  - Everytime the gun runs out of bullets, it reloads randomly adding another bullet, but making sure there is always at least 1 blank and 1 real bullet.
    - This is achieved using random.randint
### The "AI":
As stated before the "AI" is nothing more than an algorithm that calculates odds based on knowledge that the player can also obtain it only counts the amount of blanks and real bullets and then calculates the odd of the next bullet being real.
If the odd is 0.5 or above it chooses to shoot the player, else it chooses to shoot himself.
After implementing powers the odds might change.