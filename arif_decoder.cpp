#include <iostream>
#include <fstream>
#include <cstddef>
#include <map>
#include <iomanip>
using namespace std;

int main()
{
	ifstream fin("output.txt");
	ofstream fout("text_input.txt");

	unsigned long long count;
	short int size_of_chars;
	int freq_size;
	fin >> count >> size_of_chars >> freq_size;

	map <unsigned char, double long*> frequency;
	double long a = 0, b = 0;
	while (freq_size--)
	{
		unsigned char c;
		int freq;
		c = fin.get();
		fin >> freq;
		frequency[c] = new double long[3];
		frequency[c][0] = double long(freq) / double long(count);
		b = a + frequency[c][0];
		frequency[c][1] = a;
		frequency[c][2] = b;
		a = b;
		c = fin.get();
	}

	double long num;
	int temp = size_of_chars;
	while (fin>>num)
	{
		while ((temp--) && (count--))
		{
			for (auto s : frequency)
			{
				if (frequency[s.first][2] > num && frequency[s.first][1] <= num)
				{
					fout << s.first;
					num = (num - s.second[1]) / (s.second[2] - s.second[1]);
					break;
				}
			}
		}
		temp = size_of_chars;
	}

	return 0;
}
