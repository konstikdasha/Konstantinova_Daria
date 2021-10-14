#pragma once
#include <iostream>

template <typename T>
void TryInput(T& input, std::string inputText)
{
	std::cout << inputText;
	while ((std::cin >> input).fail() || input < 0) {
		std::cout << "Неверный ввод :( Пожалуйста, попробуйте снова:\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
}