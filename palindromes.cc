#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

bool is_palindrome(const string& s) {
	if (s.length() == 0)
		return true;

	auto l = s.begin();
	auto r = s.end()-1;

	while (*l == *r && l < r) {
		l++;
		r--;
	}

	return l >= r;
}

bool is_palindrome_sentence(const string& s) {
	if (s.length() == 0)
		return true;

	auto l = s.begin();
	auto r = s.end()-1;

	while (l < r) {
		if (!isalnum(*l)) {
			l++;
			continue;
		}

		if (!isalnum(*r)) {
			r--;
			continue;
		}

		if (tolower(*l) != tolower(*r))
			return false;

		l++;
		r--;
	}

	return true;
}

bool is_permuted_palindrome(const string& s) {
	unordered_map<char, int> frequency;
	int uneven = 0;

	for (char c : s) {
		frequency[c]++;
		if (frequency[c] % 2 == 0) {
			uneven--;
		} else {
			uneven++;
		}
	}

	return uneven <= 1;
}

string longest_palindrome(const string& s) {
	pair<int,int> result(0,0);
	int max = 0;

	// for each potential center
	for (int i = 0; i < s.length(); i++) {
		auto grow = [&](int l, int r) {
			while (l >= 0 && r < s.length() && s[l] == s[r]) {
				l--;
				r++;
			}

			if (max < r-l-1) {
				result = make_pair(l+1, r);
				max = r-l-1;
			}
		};

		// center is a single letter
		grow(i-1,i+1);

		// two letter center
		if (i+1 >= s.length() || s[i] != s[i+1])
			continue;

		grow(i-1,i+2);
	}

	return s.substr(result.first, result.second-result.first);
}

string manacher(const string& s) {
	int tail = 0;
	int center = 0;
	int max = 0;
	int pos = 0;

	string padded = "#";
	for (auto c : s) {
		padded += c;
		padded += "#";
	}
	vector<int> length(padded.length(),0);

	auto mirror = [](int it, int center) {
		return center - (it - center); 
	};
	auto lborder = [](int center, int length) {
		return center - (length-1)/2;
	};

	while (tail < padded.length()) {
		// grow the palindrome at center
		while (mirror(tail, center) >= 0 && tail < padded.length() && padded[tail] == padded[mirror(tail,center)]) {
			tail++;
		}

		length[center] = (tail - center - 1)*2 + 1;
		int left_border = lborder(center, length[center]);

		if (length[center] > max) {
			max = length[center];
			pos = left_border;
		}

		int i = center+1;
		while (i < tail) {
			int m_i = mirror(i, center);
			// case 1, fully contained
			if (lborder(m_i, length[m_i]) > left_border) {
				length[i] = length[m_i];
			} else
			// case 2, extending past left border
			if (lborder(m_i, length[m_i]) < left_border) {
				length[i] = (tail - i - 1)*2 + 1;
			} else {
			// case 3, proper prefix
				break;
			}
			i++;
		}
		center = i;
	}

	string result;
	for (int i = pos; i < pos+max; i++) {
		if (padded[i] != '#') {
			result += padded[i];
		}
	}
	return result;
}

int main() {

	vector<string> p1{"a", "ab", "", "aa"};
	for (auto p : p1) {
		cout << boolalpha << "is_palindrome(\"" << p << "\") = " << is_palindrome(p) << endl;
	}

	vector<string> p2{"Was it a car or a cat I saw?", "Murder for a jar of red rum!", "This is not a palindrome.", "?!,." };
	for (auto p : p2) {
		cout << boolalpha << "is_palindrome_sentence(\"" << p << "\") = " << is_palindrome_sentence(p) << endl;
	}

	vector<string> p3{"aabb", "aabbc", "abc"};
	for (auto p : p3) {
		cout << boolalpha << "is_permuted_palindrome(\"" << p << "\") = " << is_permuted_palindrome(p) << endl;
	}

	vector<string> p4{"aabb", "aabac", "xaaxy", "xyz", ""};
	for (auto p : p4) {
		cout << boolalpha << "longest_palindrome(\"" << p << "\") = " << longest_palindrome(p) << endl;
	}

	vector<string> p5{"xabaxcxabay", "aabac", "xyz", "", "aaaa"};
	for (auto p : p5) {
		cout << boolalpha << "manacher(\"" << p << "\") = " << manacher(p) << endl;
	}
}
