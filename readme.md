# Bulls and Cows
## A Julian McNeill Game
Based on the clever word game "Mastermind", players must correctly guess the
word that the computer is thinking of. Each turn, the computer will give the
player a **bull** if the player correctly guesses a letter of the hidden word
in the right position, a **cow** if the player correctly guesses a letter but
it's in the wrong position, or nothing at all. For example,

Mystery word: **visual**

Let's say the player enters: `player`. **l** and **a** are both in **visual**,
but not in those exact spots. So for that turn, the player receives
**0 bulls, 2 cows**.

On turn 2, the player enters: `virtue`. **v** and **i** are both in **visual**,
in those exact spots, so the player gets **2 bulls**. **u** is also in
**visual**, but not in that exact spot, so the player gets **1 cow**. For this
turn, the player receives **2 bulls, 1 cow**!

All the words the computer thinks of will be *isograms*, which means none of
the letters will repeat in that word (so no **apple**, **exceed**, **boombox**,
or anything like that). The player will have a certain amount of tries to guess
the word, or they lose.


### How to Play
Just type in the word when prompted using the keyboard.

### About this Game
This game is Section 2 of Unreal Developer by GameDev.tv on Udemy. The new features that I implemented were:
+ Over 100 words to guess
+ Three difficulty modes to choose from
