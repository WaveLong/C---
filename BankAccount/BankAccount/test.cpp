#include <iostream>
#include<string>
#include "Date.h"
#include "Accumulator.h"
#include "Account.h"
#include "Controller.h"

using namespace std;

int main() {
	Date init_date(2020, 8, 1);
	Controller con(init_date);
	string cmd;
	while (!con.isEnd()) {
		cout << "Comand: " << "[N]ew account\t[D]eposite\t[W]ithdraw\t[S]how\t[Q]uery\t[C]hange day\t[M]onth\t[q]uit" << endl;
		getline(cin, cmd);
		con.runCommand(cmd);
	}
	return 0;
}

