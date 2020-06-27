#include <iostream>
#include "diophantine.h"

using namespace std;

void main() {
	int array[16];
	CDiophantine dp(1,1,1,1,1,40);

	int ans;
	ans = dp.Solve();
	if (ans == -1) {
		cout << "No solution found." << endl;
		system("pause");
	}
	else {
		gene gn = dp.GetGene(ans);

		cout << "The solution set to (u*w*x^2*y) + (y) + (w^2*x*z) + (u*w*x*z) + (u*w*x*z) = 40:\n";
		cout << "u = " << gn.alleles[0] << "." << endl;
		cout << "w = " << gn.alleles[1] << "." << endl;
		cout << "x = " << gn.alleles[2] << "." << endl;
		cout << "y = " << gn.alleles[3] << "." << endl;
		cout << "z = " << gn.alleles[4] << "." << endl;
		system("pause");
	}
}