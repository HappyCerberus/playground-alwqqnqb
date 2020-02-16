# Common Coding Interview Questions: Palindromes

Palindromes are a common topic for interview questions as they lend themselves to algorithmically interesting solutions.

In this article we will go through several interview questions, each building on the previous ones.

## Verifying a palindrome


```C++ runnable
// { autofold
#include <string>
#include <iostream>
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

        cout << boolalpha << "is_palindrome(\"a\") = " << is_palindrome("a") << endl;
        cout << boolalpha << "is_palindrome(\"ab\") = " << is_palindrome("ab") << endl;
        cout << boolalpha << "is_palindrome(\"\") = " << is_palindrome("") << endl;
        cout << boolalpha << "is_palindrome(\"aa\") = " << is_palindrome("aa") << endl;
}
// }
```

