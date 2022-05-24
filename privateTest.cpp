#include <stdio.h>

class Cashew {
	private:
		int pr() {
			return v;
		}
		int v;
	public:
		int pu() {
			return pr();
		}
		Cashew() {
			v = 29;
		}
};

int main(void) {
	Cashew obj;
	printf("%d\n", obj.pu());

	return 0;
}
