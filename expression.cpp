
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>

typedef long long ll;

struct Token {
    int type;   // 1: number, 2: operator, 3: parenthesis
    ll value;
};

bool isDigit (char c) {
    return c >= '0' && c <= '9';
}

Token getNextToken (const std::string& s, unsigned int& index) {
    // Skip spaces first.
    while (s[index] == ' ') index++;

    if (isDigit(s[index])) {
        ll num = 0;
        while (isDigit(s[index])) {
            num = num * 10 + s[index] - '0';
            index++;
        }
        return Token{1, num};
    }
    else if (s[index] == '(' || s[index] == ')') {
        return Token{3, s[index++]};
    }
    else {
        return Token{2, s[index++]};
    }
}

ll eval (ll a, ll b, ll op) {
    if (op == '+') return a + b;
    else if (op == '-') return a - b;
    else if (op == '*') return a * b;
    else if (op == '/') return a / b;
    else if (op == '^') return std::pow(a, b);
    return 0;
}

void calcOneOperator (std::vector<ll>& nums, std::vector<ll>& ops) {
    ll a, b, c;
    b = nums.back(); nums.pop_back();
    a = nums.back(); nums.pop_back();
    c = ops.back(); ops.pop_back();
    ll d = eval(a, b, c);
    nums.push_back(d);
}

int main (void) {
    std::map<ll, ll> precedence;
    precedence['+'] = 0;
    precedence['-'] = 0;
    precedence['*'] = 5;
    precedence['/'] = 5;
    precedence['^'] = 10;
//    precedence['('] = 15;
//    precedence[')'] = 15;

    std::vector<ll> nums;
    std::vector<ll> ops;

    std::string s;
//    std::cin >> s;
    std::getline(std::cin, s);

    unsigned int index = 0;
    while (index < s.size()) {
        Token token = getNextToken(s, index);
        if (token.type == 1) {
            nums.push_back(token.value);
        }
        else if (token.type == 2) {
            while (!ops.empty() && ops.back() != '(' && precedence[token.value] <= precedence[ops.back()]) {
                calcOneOperator(nums, ops);
            }
            ops.push_back(token.value);
        }
        else if (token.type == 3) {
            if (token.value == '(') {
                ops.push_back(token.value);
            }
            else {
                while (!ops.empty() && ops.back() != '(') {
                    calcOneOperator(nums, ops);
                }
                // Pop '(' out of the stack.
                ops.pop_back();
            }
        }
    }

    while (!ops.empty()) {
        calcOneOperator(nums, ops);
    }

    std::cout << nums.back() << '\n';
}
