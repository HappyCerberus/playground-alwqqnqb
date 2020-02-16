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
}
