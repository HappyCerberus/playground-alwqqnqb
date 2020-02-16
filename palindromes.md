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
