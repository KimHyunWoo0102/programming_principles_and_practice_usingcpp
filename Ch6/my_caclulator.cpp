#include"../std_lib_facilities.h"

class Token {
public:
	char kind;
	double value;
};

class Token_stream {
public:
	Token get();//Token ��������
	void putback(Token t);//Token �ǵ�������
private:
	bool full{ false };
	Token buffer;
};

void Token_stream::putback(Token t) {
	if (full)error("���� �� ���ۿ� putback() �õ�");
	buffer = t;
	full = true;
}
Token Token_stream::get() {
	if (full) {//�̹� ������ �ִٸ� 
		full = false;//���ۿ� ��ū ����
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch)
	{
	case ';'://���
	case 'q'://����
	case '!'://���丮�� ����
	case '(':case ')':case '+':case '-':case '*':case '/':
		return Token{ ch };//���� �״�� ���
	case '.':
	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9': {
		cin.putback(ch); //���ڸ� �ٽ� �ǵ�����
		double val;
		cin >> val;//val�� double������ �������
		return Token{ '8',val };
	}
	default:
		error("�߸��� ��ū");
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
		if (t.kind != ')')error(")�� ��������");
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
		error("primary�� ���;���");
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

			if (d == 0)error("0���� ������");
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
	expression - term ó���� ��ȯ*/

	double left = term();//expression �а� ó��
	Token t = ts.get();//���� ��ū ��������

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

