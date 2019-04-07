// RvalueAndLvalue.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

void sortParallelRef(std::vector<double>&& arr) {
	std::sort(std::execution::par, arr.begin(), arr.end());
}
void sortRef(std::vector<double>&& arr) {
	std::sort(arr.begin(), arr.end());
}
void sortCopy(std::vector<double> arr) {
	std::sort(arr.begin(), arr.end());
}

std::vector<double> randomNumbers() {
	const int nrolls = 10 * 1000000;  // n * 1 million

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(1.0, 100.0);

	std::vector<double> p;

	for (int i = 0; i < nrolls; ++i) {
		p.push_back(distribution(generator));
	}
	std::cout << " vector of " << nrolls << " size elements." << "\n";

	return p;
}

int main()
{
	std::cout << "Start generating random numbers: ";

	auto vettore = randomNumbers();
	auto vettore2 = vettore;

	//std::cout << "Start sortCopy()...";
	//auto start = std::chrono::steady_clock::now();
	//sortCopy(vettore);
	//auto end = std::chrono::steady_clock::now();
	//std::cout << "executed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
	
	std::cout << "Start sortRef()... ";
	auto start = std::chrono::steady_clock::now();
	sortRef(std::move(vettore));
	auto end = std::chrono::steady_clock::now();
	std::cout << "executed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

	std::cout << "Start sortParallelRef()... ";
	start = std::chrono::steady_clock::now();
	sortParallelRef(std::move(vettore2));
	end = std::chrono::steady_clock::now();
	std::cout << "executed in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";


	//Start generating random numbers : vector of 10000000 size elements.
	//	Start sortRef()... executed in 1385 ms
	//	Start sortParallelRef()... executed in 292 ms
}