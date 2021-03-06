# Common Coding Interview Questions: Palindromes

Palindromes are a common topic for interview questions as they lend themselves to algorithmically interesting solutions.

In this article we will go through several interview questions related to palindromes.

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

We can extend the code to return all palindromes by simply emmiting each palindrome when its encountered in the `grow` lambda.

#### Complexity analysis

Our search `grow` lambda is $`O(n)`$ time complexity, since we invoke it for each position in the string (potentially twice) we end up with $`O(n^2)`$ time complexity.
Space complexity is $`O(1)`$ since the only thing we are storing are the maximum palindrome length and its boundaries.

### The $`O(n)`$ solution - Manacher's algorithm

Let's look at our brute force solution: What is the extra work that we are doing? Well, we keep re-checking the same characters multiple times, since we start the growth of the palindrome from each potential center. Can we exploit the properties of palindromes in some way?

Let's consider a string `yabacabax`. If we just determined that the palindrome with the center `c` is length `7`, can we use this information for the following potential centers? Indeed, for this particular case, we can simply re-use the information from the mirrored section, since the palindromes with centers in `a`, `b`, and `a` are all fully contained within the bigger palindrome at center `c`.

In actuality there are 3 situations we can run into:

1. the palindrome at the mirrored position is fully contained within the bigger palindrome
2. the palindrome at the mirrored position extendeds past the left border of the bigger palindrome
3. the palindrome at the mirrored position is a prefix of the bigger palindrome (ends at the left border of the bigger palindrome)

For case 1, we can simply copy the information, since the palindrome is fully contained, its mirror will be also fully contained.

For case 2, let's consider an example. `xabaxcxabay`, the palindrome at center `c` is `abaxcxaba`. What can we say about the palindrome at center `b`? Well, it's mirrored palindrome extends beyond the left side of the bigger palindrome. Is it possible that it extends past the right side of the palindrome? It isn't possible. If the palindrome at center `b` extended past the right side of the palindrome, the entire string would have to be `xabaxcxabax`. But that is in conflict with palindrome at center `c` being `abaxcxaba`.

For case 3, this is the only case where we can't determine the length of the palindrome from the mirrored section. We at least know that the part fully contianed within the greater palindrome is already a palindrome, so we can continue checking just after the greater palindrome.

We still need to deal with one small problem. This algorithm relies on having a center of a palindrome be a single character. Fortnuatelly we can simply pad the string with special characters, in which case if the center of the string is inbetween two characters, it will now be on the special character.

```C++ runnable
// { autofold
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// }
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
// { autofold
int main() {
	vector<string> p5{"xabaxcxabay", "aabac", "aaaa", "xyz", ""};
	for (auto p : p5) {
		cout << boolalpha << "manacher(\"" << p << "\") = " << manacher(p) << endl;
	}
}
// }
```

Since we calculate maximum palindrome at each center this way, the algorithm can be used as basis for solutions that require more than just the maximum palindrome. 

#### Complexity analysis

All the iterators in our solution are monotonically increasing, leading to $`O(n)`$ time complexity.
Since we store the lengths of iterators at each center, this solution has $`O(n)`$ space complexity.

## Generating palindromes

Interview questions regarding generating palindromes are quite diverse, however most of them boil down to some form of edits.

For example: "Given a string, determine the minimum number of inserts to turn the string into a palindrome."

### Dynamic programming solution $`O(n^2)`$

Let's consider when we need to make an insertion. If we start from the outside of the string, we only need to insert new character when we find a mismatch. However, then we need to be careful, the minimal number of insertions can be reached by inserting on either side of the string.

We can express this as a recursive relationship. Given a substring, spanning from index $`i`$ to index $`j`$ we can have two situations:

1. the characters at indexes $`i`$ and $`j`$ match, the number of required inserts is the same as for the substring spanning from $`i+1`$ to $`j-1`$.
2. the characters at indexes $`i`$ and $`j`$ do not match, we need to make an edit. The number of required inserts is therefore $`1 + min(inserts(i+1, j), inserts(i, j-1))`$.

We can build this recursion bottom up, using dynamic programming. Single characters are palindromes, so they require zero edits. Two character sequences either require 0 (if the characters match), or 1 edit. Building up from there, we simply iterate over all the lengths of substrings and every starting position, using our recursive formula to determine the minimum number of edits.

```C++ runnable
// { autofold
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// }
int min_inserts(const string& s) {
	if (s == "")
		return 0;

    vector<vector<int>> dp(s.length(), vector<int>(s.length(), 0));
        
    // Two character size palindromes.
    for (int j = 0; j < s.length()-1; j++) {
        if (s[j] == s[j+1]) {
            dp[j][j+1] = 0;    
        } else {
            dp[j][j+1] = 1;
        }
    }
        
    // every length
    for (int i = 2; i < s.length(); i++) {
        // every position
        for (int j = s.length()-i-1; j >= 0; j--) {
            if (s[j] == s[j+i]) {
                dp[j][j+i] = dp[j+1][j+i-1];
            } else {
                dp[j][j+i] = 1 + min(dp[j+1][j + i], dp[j][j + i - 1]);
                    
            }
        }
    }
    
    return dp[0][s.length()-1];   
}
// { autofold
int main() {
	vector<string> p6{"", "aabac", "xyz", "aaaa", "xabaxcxabay"};
	for (auto p : p6) {
		cout << "min_inserts(\"" << p << "\") = " << min_inserts(p) << endl;
	}
}
// }
```

#### Complexity analysis

The two main loops are in the order of N each, leading to $`O(n^2)`$ time complexity. This particular implementation also has $`O(n^2)`$ (this can be optimized down to $`O(n)`$).

***

Previous:  [$`O(1)`$ data structure](https://tech.io/playgrounds/52828/common-coding-interview-questions-o1-data-structure)

***

[![CC-BY-SA](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-sa/4.0/)

This work is licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
Šimon Tóth 2020 (kontakt@simontoth.cz)
