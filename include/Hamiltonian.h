#pragma once
class Hamiltonian
{
public:
    int m_Grid_Height;
    int m_Grid_Width;

public:
    Hamiltonian(int grid_width, int grid_height);
    char *map;
    char getMove(int, int);
    int getDistance(int, int, int, int);
};