#pragma once

#include <iostream>
#include <unordered_map>


class Utility
{
public:
	template<typename T>
	static T proverka(T less, T more);

};

template<typename T>
T Utility::proverka(T less, T more)
{
	T x;
	while ((std::cin >> x).fail() || x > more || x < less)
	{
		std::cout << "Пожалуйста, введите корректные данные! " << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
	return x;
}
