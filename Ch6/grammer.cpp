#include "std_lib_facilities.h"

int main() {
    string word, prev, current;
    bool is_run = false;

    cin >> word;

    if (word == "fish" || word == "birds" || word == "C++")
        is_run = true, prev = "noun"; // 문장의 시작은 Noun으로 해야 함
    else {
        cout << "올바르지 않음\n";
        keep_window_open();
        return -1;
    }

    while (true) {
        cin >> word;

        // 문장이 "." 하나로 끝나는 경우 → 올바른 문장
        if (word == ".") {
            cout << "올바름\n";
            return 0;
        }

        // 단어 끝이 '.'이면 틀린 문장 처리 (예: "swim.")
        if (!word.empty() && word.back() == '.') {
            cout << "올바르지 않음\n";
            keep_window_open();
            return -1;
        }

        // 단어별 문법 검사
        if (word == "fish" || word == "birds" || word == "C++")
            current = "noun";
        else if (word == "rules" || word == "fly" || word == "swim")
            current = "verb";
        else if (word == "or" || word == "but" || word == "and")
            current = "conjunction";
        else {
            cout << "올바르지 않음\n";
            keep_window_open();
            return -1;
        }

        // 문법 체크 (올바른 순서인지 확인)
        if (!((prev == "noun" && current == "verb") || (prev == "verb" && current == "conjunction") ||
            (prev == "conjunction" && current == "noun"))) {
            cout << "올바르지 않음\n";
            keep_window_open();
            return -1;
        }

        prev = current;
    }
    //다음과 같이 구현시 문제는 . 으로 끝나는 문장에 대해서 해결 불가

    //따라서 getline으로 전체 받은후에 개행문자별로 파싱해서 구분

    return 0;
}
