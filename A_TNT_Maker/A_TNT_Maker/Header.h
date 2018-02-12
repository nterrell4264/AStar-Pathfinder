#pragma once

char* GetTeam();
void SetMaze(const int** data, int length);
int** GetMaze();
void GetNextPosition(int& xpos, int& ypos);
void SetStart(int xpos, int ypos);
void GetStart(int& xpos, int& ypos);
void SetEnd(int xpos, int ypos);
void GetEnd(int& xpos, int& ypos);