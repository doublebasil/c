#include <stdint.h>
#include <stdio.h>

class apple {
	public:
		void test(void) {
			printf("it worked!\n");
		}
};

void foo(apple i) {
	i.test();
}

void ptrfoo(apple* obj_ptr) {
	obj_ptr->test();
}

int main(void) {
	apple obj;

	foo(obj);
	ptrfoo(&obj);

	return 0;
}
