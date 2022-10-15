# Connect4 

Project done for the course CS F211: Data Structures and Algorithms

## Description
Solving Connect 4 can be seen as finding the best path in a decision tree where each node is a Position. At each node the player has to choose one move leading to one of the possible next positions. When it is your turn, you want to choose the best possible move that will maximize your score. But next turn your opponent will try himself to maximize his score, thus minimizing yours.
This leads to a recursive algorithm to score a position. At each step:
  * When it’s your turn, the score is the maximum score of any of the next possible positions (you will play the move that maximizes your score)
  * When it’s your opponent’s turn, the score is the minimum score of next possible positions (your opponent will play the move that minimizes your score, and maximizes his)

We will primarily be using trees and 2D vectors in our implementation of the AI.

## Collaborators
[Bharath Variar](https://github.com/bharathvariar) \
[Adit Danewa](https://github.com/ad0711)
