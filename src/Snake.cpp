#include "Snake.h"
#include <random>

Snake::Snake(int grid_width, int grid_height)
{
    srand(0);

    m_Grid_Width = grid_width;
    m_Grid_Height = grid_height;
    m_Length = 3;

    m_Food_x = rand() % grid_width;
    m_Food_y = rand() % grid_height;

    // Adding the elements
    {
        m_Elements_x.push_back((m_Grid_Width / 2) - 1);
        m_Elements_y.push_back((m_Grid_Height / 2) - 1);
        m_Elements_x.push_back((m_Grid_Width / 2) - 1);
        m_Elements_y.push_back(m_Grid_Height / 2);
        m_Elements_x.push_back(m_Grid_Width / 2);
        m_Elements_y.push_back(m_Grid_Height / 2);
    }
}

void Snake::move(char direction)
{
    for (int i = m_Length - 1; i > 0; i--)
    {
        m_Elements_x[i] = m_Elements_x[i - 1];
        m_Elements_y[i] = m_Elements_y[i - 1];
    }
    switch (direction)
    {
    case 'r':
        m_Elements_x[0]++;
        break;
    case 'l':
        m_Elements_x[0]--;
        break;
    case 'u':
        m_Elements_y[0]--;
        break;
    case 'd':
        m_Elements_y[0]++;
        break;
    }
    if (m_Food_x == m_Elements_x[0] && m_Food_y == m_Elements_y[0])
    {
        m_Length++;
        m_Elements_x.push_back(m_Elements_x.back());
        m_Elements_y.push_back(m_Elements_y.back());
        bool correct = false;
        while (!correct)
        {
            correct = true;
            m_Food_x = rand() % m_Grid_Width;
            m_Food_y = rand() % m_Grid_Height;
            for (int i = 0; i < m_Length; i++)
            {
                if (m_Food_x == m_Elements_x[i] && m_Food_y == m_Elements_y[i])
                {
                    correct = false;
                }
            }
        }
    }
}