#include <iostream>
#include <fstream>
#include <map>
#include <cstddef>
constexpr short int SIZEOF_NUM = 7;
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

	double num=0;
	int temp = size_of_chars;
	while (count)
	{
		double _h,
			_l,
			h = 1,
			l = 0;
		for (int j = 0; j < SIZEOF_NUM; j++)
		{
			unsigned char buf;
			fin.read((char*)&buf, sizeof(buf));
			for (int i = 0; i < 8; i++)
			{
				if ((1<<i)&buf)
				{
					num += double(1) / pow(2, j * 8 + i + 1);
				}
			}
		}

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
		num = 0;
	}

	return 0;
}
