#include "../std_lib_facilities.h"

int main() {
    string str;
    vector<string> nums = { " thousand "," hundred ", " ten ", "" };  // 영어 단위
    int ret = 0;

    cin >> str;

     문자열을 정수로 변환
    for (int i = 0; i < str.size(); i++) {
        int tmp = str[i] - '0';
        int p = 1;
        for (int j = 0; j < str.size() - i - 1; j++) {
            p *= 10;
        }
        ret += (tmp * p);
    }

    cout << ret << " is ";

     자리수에 맞게 영어 숫자 출력
    int flag = 4 - str.size();
    for (int i = 0; i < str.size(); i++, ++flag) {
        cout << str[i] - '0' << nums[flag];
    }

    return 0;
}



 Chapter 06, exercise 09: read digits from input and compose them into
 integers. Handle number with one to four digits.
// Hint: '5'-'0' == 5 (get integer value of character)

#include "../lib_files/std_lib_facilities.h"

vector<string> num_words;

// initialise vector with words
void init()
{
    num_words.push_back("thousand");
    num_words.push_back("hundred");
    num_words.push_back("ten");
    num_words.push_back("one");
}

// calculates integer from vector of characters
int char_to_int(vector<int> v)
{
    if (v.size() == 0)
        error("empty vector handed to char_to_int()");
    if (v.size() > 4)
        error("char_to_int can handle only up to four digits");
    int num = 0;
    for (int i = 0; i < v.size(); ++i)
        num = 10 * num + v[i];
    return num;
}

// handle the plural s: print an 's' if input is bigger than 1 or exactly 0
void plural_s(int n)
{
    if (n == 0 || n > 1)
        cout << 's';
    if (n == 1)
        return;
    if (n < 0)
        error("plural_s can handle only non-negative numbers");
}

// prints number as text
void print_number(vector<int> v, int num)
{
    if (num > 9999 || v.size() > 4)
        error("print_number can only handle numbers with four digits");
    if (v.size() == 0)
        error("print_number was handed an empty vector");
    cout << num << " is ";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ' << num_words[i + 4 - v.size()];
        plural_s(v[i]);
        if (i < v.size() - 1)
            cout << " and ";
    }
    cout << endl;
}
다른 사람이 짠거
int main()
try {
    init();

    cout << "Enter number with up to four digits, followed by a ';' and a newline.\n";
    cout << "Enter 'q' to quit.\n";
    while (true) {
        // get input from cin, put into vector of characters
        vector<int> ch_vec;
        char ch;
        while (cin >> ch) {
            if (ch == 'q')
                return 0;
            if (ch < '0' || ch>'9') {
                cin.ignore(10000, '\n'); // we're not interested after a non-digit input
                break;
            }
            ch_vec.push_back(ch - '0');
        }

        // calculate integer from input
        int as_int = char_to_int(ch_vec);

        // produce output
        print_number(ch_vec, as_int);

        cout << "Try again:\n";
    }
    return 0;
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}