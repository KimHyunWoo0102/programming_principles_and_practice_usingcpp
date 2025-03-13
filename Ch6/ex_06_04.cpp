#include"../std_lib_facilities.h"
// Chapter 06, exercise 06: implement given grammar, check if sentence follows
// the grammar

/*
	Implements this grammar:

	Sentence:
		Subject Verb
		Sentence Conjunction Sentence

		Subject:
			Noun
			"the" Noun

		Conjunction:
			"and"
			"or"
			"but"

		Noun:
			"birds"
			"fish"
			"C++"

		Verb:
			"rules"
			"fly"
			"swim"

	and checks if an entered sentence is correct according to it or not.
*/

class Token_stream {
public:
	string get();//Token 가져오기
	void putback(string s);//Token 되돌려놓기
private:
	bool full{ false };
	string buffer;
};

void Token_stream::putback(string s) {
	if (full)error("가득 찬 버퍼에 putback() 시도");
	buffer = s;
	full = true;
}

string Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}

	string word = "";
	cin >> word;

	return word;
}


Token_stream ts;

bool sentence();
bool subject();
bool noun();
bool verb();
bool conjunc();

int main()
try {
	bool is_run = true;
	while (true) {

		string tmp = ts.get();
		if (tmp == "q")
			break;
		else {
			ts.putback(tmp);
		}

		is_run = sentence();

		if (!is_run)
			cout << "문법 오류!\n";
		else
			cout << "올바른 문법!\n";

	}
	keep_window_open("~0");
}
catch (exception& e) {
	cerr << e.what() << endl;
	keep_window_open("~1");
	return 1;
}
catch (...) {
	cerr << "exception \n";
	keep_window_open("~2");
	return 2;
}

bool sentence() {
	return subject();
}
bool subject() {
	string word = ts.get();

	if (word == "the")
		return noun();
	else {
		ts.putback(word);
		return noun();
	}
}

bool noun(){
	string word = ts.get();

	if (word == "birds" || word == "fish" || word == "C++")
		return verb();
	else
		return false;
}
bool verb() {
	string word = ts.get();

	if (word == "rules" || word == "fly" || word == "swim")
		return conjunc();
	else
		return false;
}

bool conjunc() {
	string word = ts.get();

	if (word == ".")
		return true;

	if (word == "and" || word == "or" || word == "but")
		return sentence();

	return false;
}