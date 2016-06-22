#include <iostream>
using namespace std;
#include <vector>
#include <fstream>

vector <int> subtract(vector<int> vec1, vector<int> vec2)
{
	vector<int> difference; // vector to hold the difference between the two numbers
	difference.push_back(0);
	int carry = 0; // set the carry to 0
	for (int i = 0; i < vec1.size(); i++)
	{
		difference.push_back(0);// add space to the vector
		if ((carry + vec1[i] + vec2[i]) % 2 == 1) // check to see if these sums are odd
		{
			difference[i] = 1; // set the ith index to 1
		}

		else
		{
			difference[i] = 0; // set the ith index to 0 if the sum was even
		}


		if ((carry + vec2[i] + difference[i]) >= 2) // update the carry if this sum is more than 1
			carry = 1;
		else // sum was 1 or 0, set the carry to 0.
			carry = 0;
	}
	return difference;
}

bool compare(vector<int> vec1, vector<int> vec2)
{
	if (vec1.size() > vec2.size()) // vec1 is longer than vec2, so it must be a higher number
		return true;
	if (vec2.size() > vec1.size())
		return false;

	int same = 0; // counter to be used to check if the two vectors are the same
	for (int i = 0; i < vec1.size(); i++) // vector must be the same size, so see if they are different
	{
		if (vec1[i] > vec2[i])
			return true;
		if (vec2[i] > vec1[i])
			return false;
		else
			same++;
	}
	if (same == vec1.size()) // numbers were the same, so return true
		return true;
}

void add_zeros(vector<int>& vec1, vector<int>& vec2)
{
	// numbers may not have been same length, so add leading 0's to the shorter number if this is the case
	if (vec1.size() != vec2.size())
	{
		if (vec1.size() > vec2.size())
		{
			int difference = vec1.size() - vec2.size();
			for (int i = 0; i < difference; i++)
			{
				vec2.push_back(0);
			}
		}
		else
		{
			int difference = vec2.size() - vec1.size();
			for (int i = 0; i < difference; i++)
			{
				vec1.push_back(0);
			}
		}
	}
}

vector<int> find_sum(vector<int> vec1, vector<int> vec2) // finds the sum of 2 vectors
{
	vector<int> sum_vec; // vector to hold the sum
	int sum;
	int carry = 0; // carry is initially 0
	int added_sum; // this will be the sum that actual gets display from each addition

				   // add the numbers
	for (int i = 0; i < vec1.size(); i++)
	{
		sum = (vec1[i] + carry) + vec2[i];
		if (sum > 1) // check to see if the sum was higher than the base minus 1
		{
			added_sum = sum % 2; // find the actual sum and then find the carry from the addition
			carry = (sum / 2) % 2; // find the carry 
			sum_vec.push_back(added_sum); // add the actual sun to the vector containing these sums
		}
		else
		{
			sum_vec.push_back(sum); // sum wasn't large, so can just add it to the vector directly and reset the carry to 0
			carry = 0;

		}
		if (i == vec1.size() - 1) // if at the last iteration and have a carry > 0, then have to add this carry to the vector
		{
			sum_vec.push_back(carry);
		}
	}
	return sum_vec;
}

void remove_zeros(vector<int>& vec) // remove extraneous zeros from the front of the vector
{
	int i = vec.size() - 1;
	while (vec[i] == 0 && i != 0) // remove until we reach a 1 or the vector has only 1 element left
	{
		vec.pop_back();
		i--;
	}
}


vector<int> rdivide(vector<int> vec1, vector<int> vec2)
{
	vector<int> quotient; // create quotient and remainder vectors and add the 0 element to them 
	vector<int> remainder;
	quotient.push_back(0);
	remainder.push_back(0);

	for (int i = vec1.size() - 1; i >= 0; i--) // double the quotient and remainder by adding 0 to the 0th index
	{
		quotient.push_back(0);
		for (int j = quotient.size() - 1; j > 0; j--)
			quotient[j] = quotient[j - 1];
		quotient[0] = 0;

		remainder.push_back(0);
		for (int k = remainder.size() - 1; k > 0; k--)
			remainder[k] = remainder[k - 1];
		remainder[0] = 0;

		if (vec1[i] == 1) // add 1 to the remainder if the ith index is 1
		{
			vector<int> num_one;
			num_one.push_back(1);
			add_zeros(remainder, num_one);
			remainder = find_sum(remainder, num_one); // adds 1 to the remainder
		}

		remove_zeros(remainder); // remove extraneous zeros from these vectors so the comparison is corrext
		remove_zeros(vec2);

		if ((compare(remainder, vec2)) == true)// subtract the divisor from the remainder and add 1 to the quotient
		{
			add_zeros(remainder, vec2);
			remainder = subtract(remainder, vec2);
			vector<int> num_one;
			num_one.push_back(1);
			add_zeros(quotient, num_one);
			quotient = find_sum(quotient, num_one);
			remove_zeros(quotient);
		}
	}
	return remainder;
}


