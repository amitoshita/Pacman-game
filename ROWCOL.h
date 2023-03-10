#ifndef _ROWANDCOL_H_
#define _ROWANDCOL_H_

class logicalROWCOL {
private:
	int ROW, COL;
public:
	int getlogicR() {
		return ROW;
	}
	int getlogicC() {
		return COL;
	}
	void setlogicR(int R) {
		ROW = R;
	}
	void setlogicC(int C) {
		COL = C;
	}
};

#endif