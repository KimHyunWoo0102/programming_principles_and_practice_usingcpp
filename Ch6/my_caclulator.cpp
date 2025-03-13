#include"../std_lib_facilities.h"

class Token {
public:
	char kind;
	double value;
};

class Token_stream {
public:
	Token get();//Token 가져오기
	void putback(Token t);//Token 되돌려놓기
private:
	bool full{ false };
	Token buffer;
};

void Token_stream::putback(Token t) {
	if (full)error("가득 찬 버퍼에 putback() 시도");
	buffer = t;
	full = true;
}
Token Token_stream::get() {
	if (full) {//이미 가득차 있다면 
		full = false;//버퍼에 토큰 전달
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch)
	{
	case ';'://출력
	case 'q'://종료
	case '!'://팩토리얼 연산
	case '(':case ')':case '+':case '-':case '*':case '/':
		return Token{ ch };//문자 그대로 사용
	case '.':
	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9': {
		cin.putback(ch); //문자를 다시 되돌리고
		double val;
		cin >> val;//val에 double형으로 집어넣음
		return Token{ '8',val };
	}
	default:
		error("잘못된 토큰");
		break;
	}
}

Token_stream ts;
double expression();

double primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')error(")로 끝나야함");
		return d;
	}
	case '8': {
		int x = t.value;
		double tmp = 1;
		t = ts.get();
		if (t.kind == '!')
		{
			for (int i = 1; i <=x; i++) {
				tmp *= i;
			}

			return tmp;
		}
		else {
			ts.putback(t);
			return x;
		}
	}
	default:
		error("primary가 나와야함");
	}
}
double term() {
	double left = primary();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();

			if (d == 0)error("0으로 나누기");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}
double expression() {
	/*term
	expression + term
	expression - term 처리후 반환*/

	double left = term();//expression 읽고 처리
	Token t = ts.get();//다음 토큰 가져오기

	while (true) {
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int main()
try {
	double val = 0;
	while (cin) {
		Token t = ts.get();

		if (t.kind == 'q')break;
		if (t.kind == ';')cout << "=" << val << '\n';
		else {
			ts.putback(t);
			val = expression();
		}
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

