#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>

class Tile
{
private:
    int m_num{};

public:
    explicit Tile(int num)
        : m_num{ num } {
    }


    int getNum() const { return m_num; }
    bool isEmpty() const { return m_num == 0; }
};

std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    out << std::setfill(' ') << std::setw(4);
    if (!tile.isEmpty())
        out << tile.getNum();
    return out;
}

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };
constexpr int g_length{ 4 };
constexpr int g_width{ 4 };
// Your code goes here
class Board
{
private:
    std::array<std::array<Tile, g_width>, g_length> m_grid{ {
        {Tile{1}, Tile{2}, Tile{3}, Tile{4}},
        {Tile{5}, Tile{6}, Tile{7}, Tile{8}},
        {Tile{9}, Tile{10}, Tile{11}, Tile{12}},
        {Tile{13}, Tile{14}, Tile{15}, Tile{0}}
    } };

public:
    friend std::ostream& operator<<(std::ostream& out, const Board& board)
    {
        for (int i{ 0 }; i < g_consoleLines; ++i)
            out << '\n';

        for (std::size_t row{ 0 }; row < g_length; ++row)
        {
            for (std::size_t col{ 0 }; col < g_width; ++col)
            {
                out << board.m_grid[row][col];
            }
            out << '\n';
        }
        
        return out;
    }
};

int main()
{
    Board board{};
    std::cout << board;

    return 0;
}