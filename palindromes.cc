#include <string>
#include <iostream>
#include <unordered_map>
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

	cout << boolalpha << "is_palindrome(\"a\") = " << is_palindrome("a") << endl;
	cout << boolalpha << "is_palindrome(\"ab\") = " << is_palindrome("ab") << endl;
	cout << boolalpha << "is_palindrome(\"\") = " << is_palindrome("") << endl;
	cout << boolalpha << "is_palindrome(\"aa\") = " << is_palindrome("aa") << endl;


	cout << boolalpha << "is_permuted_palindrome(\"aabb\") = " << is_permuted_palindrome("aabb") << endl;
	cout << boolalpha << "is_permuted_palindrome(\"aabbc\") = " << is_permuted_palindrome("aabbc") << endl;
	cout << boolalpha << "is_permuted_palindrome(\"abc\") = " << is_permuted_palindrome("abc") << endl;

}
