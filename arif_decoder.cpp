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
		cout << c << " ";
		cout.width(10);
		cout << frequency[c][0] << " ";
		cout.width(10);
		cout << frequency[c][1] << " ";
		cout.width(10);
		cout << frequency[c][2] << endl;
		a = b;
		c = fin.get();
	}

	double long num;
	int temp = size_of_chars;
	while (fin>>num)
	{
		double long _h,
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
	}

	return 0;
}
