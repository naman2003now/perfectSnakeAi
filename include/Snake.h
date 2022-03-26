#pragma once
#include <vector>

class Snake
{
private:
    int m_Grid_Width;
    int m_Grid_Height;
    int m_Length;

    std::vector<int> m_Elements_x;
    std::vector<int> m_Elements_y;

    int m_Food_x;
    int m_Food_y;

public:
    Snake(int, int);

    inline int getLength() { return m_Length; }

    inline int getElementx(int i) { return m_Elements_x[i]; }
    inline int getElementy(int i) { return m_Elements_y[i]; }

    inline int getFoodx() { return m_Food_x; }
    inline int getFoody() { return m_Food_y; }

    void move(char direction);
};