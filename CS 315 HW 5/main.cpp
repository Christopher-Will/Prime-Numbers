// Christopher Will
// 2/23/16


#include <iostream>
using namespace std;
#include <vector>
#include <cstdio>
#include <ctime>
#include <chrono>



bool check_remainder(unsigned long long int prime, unsigned long long int root_prime) // function to test whether the number generated is prime
{
	for (unsigned long long int i = 2; i <= root_prime; i++) // loop from 2 upto the square root of the number
	{
		if (prime% i == 0) // the number evenly divides into i, so it can't be prime
			return false;
	}
	return true; // the number never evenly divided into i for i from 2 to square root of the number, so it must be prime
}

bool mod_exp(vector<unsigned long long int> exp, unsigned long long int n) //mod exponentiation to test for primality
{
	int base = 3; 
	exp[0] = 0; // subtract 1 from the prime #
	unsigned long long int z = 1;
	for (int i = exp.size() - 1; i >= 0; i--) //use modular exponentiation on the pimre number
	{
		z = (z*z) % n;
		if (exp[i] == 1)
			z = (base*z) % n;
	}
	if (z == 1) // fermat's little theorem holds, so return true
		return true;
	return false;
}



int main()
{
	clock_t start = clock(); // variable to keep track of how long this calculation takes
	srand(time(0)); // seed the RNG
	vector<int> vec_num_primes; //vector to hold the binary number
	int num_primes = 0; // counter for the # of primes found
	int error_count = 0; // counter to see how many times the mod_exp wrongly predicted a # to be prime
	for (int i = 0; i < 100; i++) // make 100 large numbers
	{
		vector<unsigned long long int> vec1; // vector to hold the large binary number
		vec1.push_back(1); // add 1 to the vector (it must be odd to be a large prime)
		for (int j = 0; j < 62; j++) // add a random bit to index i. do this for 126 indices
		{
			int randnum = rand() % 2 + 0;
			vec1.push_back(randnum);
		}
		vec1.push_back(1); // make the most significant digit a 1
		unsigned long long int decimal = 0; // int to hold the decimal value of the large number
		for (unsigned long long int j = 0; j < vec1.size(); j++) // convert from binary to decimal
		{
			unsigned long long int power = pow(2, j);
			decimal += vec1[j] * power;
		}
		unsigned long long int root_decimal = sqrt(decimal);// the square root of the prime #
		bool is_prime = check_remainder(decimal, root_decimal);
		bool mod_exp_prime = mod_exp(vec1, decimal);
		if (!is_prime && mod_exp_prime)
		{
			error_count++; // # is not prime by brute force approach, but it prime by mod_exp algorithm, so increment the error count
		}

		if (is_prime) // number never had an even division, so it must be prime.
		{
			vec_num_primes.push_back(i);
			num_primes++; // increment the counter and print success message to file
		}
	}
	cout << num_primes << " primes found" << endl; //output the # primes found
	cout << "First prime number found after " << vec_num_primes[0] << " iterations" << endl;
	cout << error_count << " instances of Fermat's Little Theorem selecting a non-prime as being prime." << endl;
	double cpu_duration = (clock() - start) / (double)CLOCKS_PER_SEC; // caclulate how long this algorithm took
	cout << "Took " << cpu_duration << " seconds" << endl;
	system("pause");
	return 0;
}
