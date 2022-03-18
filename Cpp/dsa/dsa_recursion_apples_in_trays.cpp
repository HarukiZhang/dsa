#include <iostream>
using namespace std;

/*Put Apples in Trays*/
// Count how many arrangements for putting apples in trays,
// where apples and trays are regarded as the same;
// That is to say, do not count combination, rather, arrangement;

int appleTray(int appleN, int trayN){
	/* Boundaries:
		1) if there is only one apple, no matter how many trays,
			there's only one arrangement;
		2) the same as above for the condition that there's only one tray;
		3) if there's no apple, the only one arrangement is to put "no apple" in trays;	*/
	if (appleN == 1 || trayN == 1 || appleN == 0)
		return 1;
	/* The first category: when the number of trays is greater than that of apples;
		We can consider that even if we put one apple on each tray, there still are
			trays left empty; So, those empty trays are not our concern at all;
		So, the scale of the problem "put k apples in m trays" 
			is diminished by us to "put k apples in k trays"; */
	if (trayN > appleN)
		return appleTray(appleN, appleN);
	/* The second: when the number of trays is lesser than or equal to that of apples;
	We can split the problem into two parts:
		1) the arrangements when we let at least one tray to be empty;
			in this situation, the scale could be shrank eventually to only one tray;
		2) the arrangements when we put at least one apple on each tray;
			in this situation, we diminished the apple's number;
	*/
	else return /*(1)*/ appleTray(        appleN, trayN - 1)
			  + /*(2)*/ appleTray(appleN - trayN, trayN    );
}

int main() {
	int aN, tN;
	cin >> aN >> tN;
	cout << appleTray(aN, tN);
}