#include <iostream>

class Tile
{
private:
    int m_num{};

public:
    Tile(int num)
        : m_num{ num } {
    }


    int getNum() const { return m_num; }
    bool isEmpty() const { return m_num == 0; }
};

std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    if (tile.isEmpty())
        out << "    ";
    else
        out << " " << tile.getNum() << "  ";
    return out;
}

int main()
{
    Tile tile1{ 10 };
    Tile tile2{ 8 };
    Tile tile3{ 0 }; // the missing tile
    Tile tile4{ 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';

    return 0;
}