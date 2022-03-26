#include "Hamiltonian.h"
#include <iostream>

Hamiltonian::Hamiltonian(int grid_width, int grid_height)
{
    m_Grid_Height = grid_height;
    m_Grid_Width = grid_width;
    map = (char *)malloc(grid_width * grid_height);
    for (int i = 0; i < grid_width; i++)
    {
        for (int j = 0; j < grid_height; j++)
        {
            char output = 'l';
            if (j % 2)
            {
                output = 'r';
                if (i == (grid_height - 2) && j != (grid_width - 1))
                {
                    output = 'd';
                }
            }
            else if (i == 0)
            {
                output = 'd';
            }
            if (i == (grid_height - 1))
            {
                output = 'u';
            }
            map[i + j * grid_width] = output;
        }
    }
    map[grid_height - 1] = 'l';
    // for (int i = 0; i < grid_width; i++)
    // {
    //     for (int j = 0; j < grid_height; j++)
    //     {
    //         std::cout << map[i + j * grid_width] << " ";
    //     }
    //     std::cout << "\n";
    // }
}

char Hamiltonian::getMove(int x, int y)
{
    char output = map[x + y * m_Grid_Width];
    return output;
}

int Hamiltonian::getDistance(int x, int y, int destinationx, int destinationy)
{
    int output = 0;
    while (x != destinationx || y != destinationy)
    {
        output++;
        switch (getMove(x, y))
        {
        case 'r':
            x++;
            break;

        case 'l':
            x--;
            break;

        case 'u':
            y--;
            break;

        case 'd':
            y++;
            break;
        }
    }
    return output;
}
