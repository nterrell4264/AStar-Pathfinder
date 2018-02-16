#pragma once

_declspec(dllexport) char* GetTeam();
_declspec(dllexport) void SetMaze(const int** data, int width, int height);
_declspec(dllexport) int** GetMaze(int& width, int& height);
_declspec(dllexport) void GetNextPosition(int& xpos, int& ypos);
_declspec(dllexport) void SetStart(int xpos, int ypos);
_declspec(dllexport) void GetStart(int& xpos, int& ypos);
_declspec(dllexport) void SetEnd(int xpos, int ypos);
_declspec(dllexport) void GetEnd(int& xpos, int& ypos);