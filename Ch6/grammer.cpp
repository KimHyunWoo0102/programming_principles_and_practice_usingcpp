#include "std_lib_facilities.h"

int main() {
    string word, prev, current;
    bool is_run = false;

    cin >> word;

    if (word == "fish" || word == "birds" || word == "C++")
        is_run = true, prev = "noun"; // ������ ������ Noun���� �ؾ� ��
    else {
        cout << "�ùٸ��� ����\n";
        keep_window_open();
        return -1;
    }

    while (true) {
        cin >> word;

        // ������ "." �ϳ��� ������ ��� �� �ùٸ� ����
        if (word == ".") {
            cout << "�ùٸ�\n";
            return 0;
        }

        // �ܾ� ���� '.'�̸� Ʋ�� ���� ó�� (��: "swim.")
        if (!word.empty() && word.back() == '.') {
            cout << "�ùٸ��� ����\n";
            keep_window_open();
            return -1;
        }

        // �ܾ ���� �˻�
        if (word == "fish" || word == "birds" || word == "C++")
            current = "noun";
        else if (word == "rules" || word == "fly" || word == "swim")
            current = "verb";
        else if (word == "or" || word == "but" || word == "and")
            current = "conjunction";
        else {
            cout << "�ùٸ��� ����\n";
            keep_window_open();
            return -1;
        }

        // ���� üũ (�ùٸ� �������� Ȯ��)
        if (!((prev == "noun" && current == "verb") || (prev == "verb" && current == "conjunction") ||
            (prev == "conjunction" && current == "noun"))) {
            cout << "�ùٸ��� ����\n";
            keep_window_open();
            return -1;
        }

        prev = current;
    }
    //������ ���� ������ ������ . ���� ������ ���忡 ���ؼ� �ذ� �Ұ�

    //���� getline���� ��ü �����Ŀ� ���๮�ں��� �Ľ��ؼ� ����

    return 0;
}
