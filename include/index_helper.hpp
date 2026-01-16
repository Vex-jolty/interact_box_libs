#pragma once
#include "shared.hpp"
#include <random>

class IndexHelper {
	public:
		template <typename T> static int getRandomIndex(std::vector<T> vector) {
			std::mt19937 generator(std::random_device{}());
			std::uniform_int_distribution<std::size_t> distribution(0, vector.size() - 1);
			int randomNumber = distribution(generator);
			return randomNumber;
		}

		template <typename T> static T getRandomItem(std::vector<T> vector) {
			int index = getRandomIndex(vector);
			return vector[index];
		}
};
