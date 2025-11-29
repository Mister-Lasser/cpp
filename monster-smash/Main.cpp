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
	bool hasWon() const { return m_level == 20; }

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

std::string askPlayerName()
{
	std::cout << "Enter your name: ";
	std::string name{};
	std::cin >> name;

	return name;
}

char askPlayerChoice()
{
	char choice{};
	do
	{
		std::cout << "(R)un or (F)ight: ";
		std::cin >> choice;
	} while (std::tolower(choice) != 'r' && std::tolower(choice) != 'f');

	return choice;
}

auto attackPlayer(Player& player, Monster& monster)
{
	player.reduceHealth(monster.getDamage());
	std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage()
		<< " damage.\n";
}


auto attackMonster(Player& player, Monster& monster)
{
	monster.reduceHealth(player.getDamage());
	std::cout << "You hit the " << monster.getName() << " for " << player.getDamage()
		<< " damage.\n";
	if (monster.isDead())
	{
		std::cout << "You killed the " << monster.getName() << ".\n";
		player.addGold(monster.getGold());
		player.levelUp();
		return;
	}

	attackPlayer(player, monster);

}

void fightMonster(Player& player, Monster& monster)
{
	char choice{ askPlayerChoice() };

	if (player.isDead())
		return;

	if (choice == 'r')
	{
		bool escaped{ static_cast<bool>(Random::get(0, 1)) };
		
		if (!escaped)
		{
			std::cout << "You failed to flee.\n";
			attackPlayer(player, monster);
			fightMonster(player, monster);
		}
		else
			std::cout << "You successfully fled.\n";
	}
	else
	{
		attackMonster(player, monster);
		if (!monster.isDead())
			fightMonster(player, monster);
	}
}


int main()
{
	Player player{ askPlayerName() };

	std::cout << "Welcome, " << player.getName() << ".\n";

	while (true)
	{
		Monster monster{ Monster::getRandomMonster() };
		std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol()
			<< ").\n";

		fightMonster(player, monster);

		if (player.hasWon())
		{
			std::cout << "Yay! You won with " << player.getGold() << " gold!\n";
			break;
		}

		if (player.isDead())
		{
			std::cout << "Looks like you died at level " << player.getLevel() << " with "
				<< player.getGold() << " gold.\n"
				<< "Too bad you can't take it with you!\n";
			break;
		}
	}
}