#pragma once

struct Stats
{
	int hp{ 0 };
	int hp_regen{ 0 };
	int mana{ 0 };
	int mana_regen{ 0 };

	int damage{ 0 };
	int magic{ 0 };

	int armor{ 0 };
	int magic_armor{ 0 };

	float attack_range{ 0.f };
	float attack_speed{ 0.f };

	float speed{ 0.f };

	Stats operator+(const Stats& stats) const
	{
		Stats result;

		result.hp = hp + stats.hp;
		result.hp_regen = hp_regen + stats.hp_regen;
		result.mana = mana + stats.mana;
		result.mana_regen = mana_regen + stats.mana_regen;

		result.damage = damage + stats.damage;
		result.magic = magic + stats.magic;

		result.armor = armor + stats.armor;
		result.magic_armor = magic_armor + stats.magic_armor;

		result.attack_range = attack_range + stats.attack_range;
		result.attack_speed = attack_speed + stats.attack_speed;

		result.speed = speed + stats.speed;

		return result;
	}

	Stats& operator+= (const Stats& stats)
	{
		hp += stats.hp;
		hp_regen += stats.hp_regen;
		mana += stats.mana;
		mana_regen += stats.mana_regen;

		damage += stats.damage;
		magic += stats.magic;

		armor += stats.armor;
		magic_armor += stats.magic_armor;

		attack_range += stats.attack_range;
		attack_speed += stats.attack_speed;

		speed += stats.speed;

		return *this;
	}
};