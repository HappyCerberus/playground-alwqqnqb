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
}
