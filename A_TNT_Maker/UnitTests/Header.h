#pragma once

_declspec(dllexport) char* GetTeam();
_declspec(dllexport) bool SetMaze(const int** data, int width, int height);
_declspec(dllexport) int** GetMaze(int& width, int& height);
_declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos);
_declspec(dllexport) bool SetStart(int xpos, int ypos);
_declspec(dllexport) bool GetStart(int& xpos, int& ypos);
_declspec(dllexport) bool SetEnd(int xpos, int ypos);
_declspec(dllexport) bool GetEnd(int& xpos, int& ypos);