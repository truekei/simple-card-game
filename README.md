# Simple Card Game Using Linked List in C Language
This is a simple project that me and my classmate created for our Data Structure final project.
In this project, we used the [Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list) concept to structure the card deck for every player.
## Requirements
1. Windows Operating System
2. Mingw-w64
## Installation
If you want to try the project, you can do the following:
1. Clone the repository with `git clone https://github.com/truekei/simple-card-game.git`
2. Compile the source code with `gcc main.c -o card_game.exe`
3. Run the **card_game.exe** file
## How to Play
The language in this game is a mixed of English and Bahasa Indonesia, below I provided the instructions to play the game in English.
1. After you run **card_game.exe**, you can type '1' to start the game or '2' to set the players total HP (Input any integer in `Masukan HP yang akan digunakan:`, default is 25)
2. Press [ENTER] if Player 1 is ready to play a card
3. Player 1 can choose any of the available card by pressing any number beside the card's element (Fire/Water/Nature/Earth)
4. Then press [ENTER] if Player 2 is ready to play a card
5. Player 2 can choose any available card just like Player 1 before
6. After two players have chosen their card, the next action will show either Player 1 is attacking Player 2 (`Kartu PLAYER 1 menyerang PLAYER 2`) or vice versa. You can see the remaining HP of the player that has been attacked in `Sisa HP PLAYER`
7. Press [ENTER] to continue the game until one of the player has been defeated
8. If the both of the player's deck are empty, next round will draw a total of 5 cards to both players
