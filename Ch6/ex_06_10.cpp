#include "../std_lib_facilities.h"


signed long long permut(int a,int b) {
	if(a<b)
		error("a must be greater than or equal to b.");
	//input a,b and return permutation(a,b)
	signed long long ret = 1;
	for (signed long long i = b + 1; i <= a; i++)
		ret *= i;

	return ret;
}

signed long long combi(int a, int b) {
	if (b < 0)
		error("b must be greater than or equal to 0.");
	signed long long ret = 1;
	ret *= permut(a, b);

	b = (a - b) > b ? b : (a - b);
	//nCr = nC(n-r)
	for (int i = 1; i <= b; i++)
		ret /= i;
	return ret;
}


void start() {
	cout << "Enter 'p' for permutation, 'c' for combination, or 'q' to quit.\n";

	char op;
	int a, b;

	while (true) {
		cout << ">";
		cin >> op;
		if (op == 'q')
			break;

		if (!(cin >> a >> b))error("Invalid input. Enter digit number");
	
		if (op == 'p') cout << permut(a, b) << '\n';
		else if (op == 'c')cout << combi(a, b) << '\n';
		else error("Invalid selection. Please choose a valid option.");
	}
}

int main() 
try {
	start();
	keep_window_open("0");
	return 0;
}
catch (exception& e) {
	cerr << e.what() << '\n';
	keep_window_open("~1");
	return 1;
}
catch (...) {
	cerr << "exception \n";
	keep_window_open("~2");
	return 2;
}