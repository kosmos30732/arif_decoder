#include <iostream>
#include <fstream>
#include <map>
#include <cstddef>
using namespace std;

int main()
{
	ifstream fin("output.txt", ios::binary);
	ofstream fout("text_input.txt");

	unsigned long long count;
	unsigned int freq_size;
	short int size_of_chars;

	fin.read((char*)&count, sizeof(count));
	fin.read((char*)&size_of_chars, sizeof(size_of_chars));
	fin.read((char*)&freq_size, sizeof(freq_size));

	map <unsigned char, double*> frequency;
	double a = 0, b = 0;
	while (freq_size--)
	{
		unsigned char c;
		unsigned int freq;
		fin.read((char*)&c, sizeof(c));
		fin.read((char*)&freq, sizeof(freq));

		frequency[c] = new double[3];
		frequency[c][0] = double(freq) / double(count);
		b = a + frequency[c][0];
		frequency[c][1] = a;
		frequency[c][2] = b;
		a = b;
	}

	double num;
	int temp = size_of_chars;
	while (fin.read(reinterpret_cast<char*>(&num), sizeof(num)))
	{
		double _h,
			_l,
			h = 1,
			l = 0;
		while ((temp--) && (count--))
		{
			for (auto s : frequency)
			{
				_l = l + frequency[s.first][1] * (h - l);
				_h = l + frequency[s.first][2] * (h - l);
				if (_l <= num && num < _h)
				{
					l = _l;
					h = _h;
					fout << s.first;
					break;
				}
			}
		}
		temp = size_of_chars;
		if (fin.peek() == EOF)
		{
			break;
		}
	}

	return 0;
}
