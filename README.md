# Checkers in colsole

## Table of Contents
1. [Introduction](#introduction)
2. [Settings](#settings)
3. [Roadmap](#roadmap)

## Introduction
This is a console game of checkers. You can play here against my bot.

## Getting Started
1. Downlaod repository
2. Open file checkers.sln with Visual Studio
3. Compile
## Settings
In main.cpp is you can change few things.
Depth of counting for engine:
```cpp
const int draw_after_moves = 10;
```
What color do you play
```cpp
int player_color = WHITE;
int bot_color = BLACK;
```
if you want to play from another position, change 
```cpp
bool start_position = false;
```
to true and initialize your own posittion. Where 1=white pawn 2=black pawn 3=white king 4=black king. For example
```cpp
b["f6"] = 2;
b["a5"] = 4;
b["a3"] = 1;
b["c7"] = 1;
b["c5"] = 1;
b["f2"] = 1;
b["d2"] = 1;
b["e7"] = 1;
```
You can change after how many moves with kings there is a draw:
```cpp
const int draw_after_moves = 10; 
```
You can print board upside down by changing false to true in line:
```cpp
const bool turn_board = false; 
```

## Roadmap

- [x] implement legal moves
- [x] working engine
- [ ] better engine

