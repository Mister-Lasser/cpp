#include "Random.h"
#include <iostream>
#include <string>
#include <string_view>

class Creature
{
public:
	Creature(std::string_view name, char symbol, int health, int damage, int gold)
		: m_name{ name }
		, m_symbol{ symbol }
		, m_health{ health }
		, m_damage{ damage }
		, m_gold{ gold }
	{
	}

	void reduceHealth(int n) { m_health -= n; }
	bool isDead() { return m_health <= 0; }
	void addGold(int n) { m_gold += n; }

	const std::string& getName() const { return m_name; }
	char getSymbol() const { return m_symbol; }
	int getHealth() const { return m_health; }
	int getDamage() const { return m_damage; }
	int getGold() const { return m_gold; }
protected:
	std::string m_name{ "???" };
	char m_symbol{ '?' };
	int m_health{};
	int m_damage{};
	int m_gold{};
};

class Player : public Creature
{
public:
	Player(std::string_view name = "???")
		: Creature(name, '@', 10, 1, 0)
	{
	}

	void levelUp() { ++m_level; ++m_damage; }
	int getLevel() const { return m_level; }
	bool hasWon() const { m_level == 20; }

private:
	int m_level{ 1 };
};

class Monster : public Creature
{
public:
	enum Type
	{
		dragon, orc, slime,
		max_types,
	};

	static inline Creature monster[] {
		{"dragon", 'D', 20, 4, 100},
		{"orc", 'o', 4, 2, 25},
		{"slime", 's', 1, 1, 10}
	};
	static_assert(std::size(monster) == max_types);

	Monster(Type type)
		: Creature(monster[type])
	{
	}

	static Monster getRandomMonster()
	{
		return Monster{ static_cast<Type>(Random::get(0, max_types - 1)) };
	}

};

int main()
{
	for (int i{ 0 }; i < 10; ++i)
	{
		Monster m{ Monster::getRandomMonster() };
		std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	}

	return 0;
}