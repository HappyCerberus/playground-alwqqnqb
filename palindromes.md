# Common Coding Interview Questions: Palindromes

Palindromes are a common topic for interview questions as they lend themselves to algorithmically interesting solutions.

In this article we will go through several interview questions, each building on the previous ones.

## Verifying a palindrome

A string of letters is a palindrome if it is identical to it's reversion. However we don't need to reverse the string to verify this is true.

Using two iterators, we can simply walk over the string from the start and end, verifying each pair of corresponding letters. Keep in mind that both "aba" and "aa" are palindromes (which is a corner case we don't have to deal when using iterators).

```C++ runnable
// { autofold
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// }
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
// { autofold
int main() {
        vector<string> p1{"a", "ab", "", "aa"};
        for (auto p : p1) {
                cout << boolalpha << "is_palindrome(\"" << p << "\") = " << is_palindrome(p) << endl;
        }
}
// }
```

For palindromic sentences we need to include aditional checks. For example: "Was it a car or a cat I saw?" is a palindromic sentence, but our `is_palindrome` function will return false, since the string does not exactly match its reversion.

```C++ runnable
// { autofold
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// }
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
// { autofold
int main() {
        vector<string> p2{"Was it a car or a cat I saw?", "Murder for a jar of red rum!", "This is not a palindrome.", "?!,." };
        for (auto p : p2) {
                cout << boolalpha << "is_palindrome_sentence(\"" << p << "\") = " << is_palindrome_sentence(p) << endl;
        }
}
// }
```

### Complexity analysis

In either case, we visit each character in the string once, leading to $`O(n)`$ time complexity. We only store two iterators, leading to $`O(1)`$ time complexity.

## Searching for palindromes

Most palindrome related interview questions involve searching for palindromes within a given string. This can be finding the longest palindrome, splitting a string into palindromes, or simply returning all the palindromes contained within a string.

### Brute force $`O(n^2)`$ solution

To find all the palindromes within a string we can use the same process we used for verifying a palindrome, but instead of starting from the outside we start from the center. Again, we need to keep in mind that a center of palindrome can be either one or two characters.

```C++ runnable
// { autofold
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// }
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
// { autofold
int main() {
	vector<string> p4{"aabb", "aabac", "xaaxy", "xyz", ""};
	for (auto p : p4) {
		cout << boolalpha << "longest_palindrome(\"" << p << "\") = " << longest_palindrome(p) << endl;
	}
}
// }
```
