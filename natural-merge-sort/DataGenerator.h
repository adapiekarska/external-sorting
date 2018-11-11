#pragma once

#include <random>
#include <iostream>
#include <string>
#include <sstream>

#include "Int32_Vec.h"
#include "globals.h"

/**
 * Class responsible for handling all methods of generating input data in the
 * the program, i.e. randomised generation and user generation.
 */

class DataGenerator
{
public:

	DataGenerator() { };

	~DataGenerator() { };

	/**
	Generates the vector of size n that contains randomly generated pairs of
	two integers.
	*/
	std::vector<Int32_Vec> random_generate(size_t n, int from, int to) const;

	/**
	Interactively guides the user through the process of generating the set of
	records by hand.
	*/
	std::vector<Int32_Vec> user_generate() const;

};

