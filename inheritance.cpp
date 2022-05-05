#include <stdio.h>

// Base class
class Fruit {
	public:
		Fruit() {
			this->publicVar = 10;
			this->privateVar = 40;
		}
		void eat() {
			printf("You ate the fruit!");
		}
		int publicVar;
	private:
		void chuck() {
			printf("You chucked the fruit!");
		}
		int privateVar;
};

// Derived class
class Apple: public Fruit {
	public:
		int pips;
};

/*
What does the access spcifier in the class inheritance mean?
class DerivedClass: access-specifier BaseClass {};
The access-specifier can be public, protected or private

If you use public inheritance:
	All public members of the base class will become public
	members of the derived class.
	---   Base Class  -->  Derived Class  ---
		   public --> public
		protected --> protected
		  private --> private

If you use protected inheritance:
	---   Base Class  -->  Derived Class  ---
		   public --> protected
		protected --> protected
		  private --> private

If you use private inheritance
	---   Base Class  -->  Derived Class  ---
		   public --> private
		protected --> private
		  private --> private

*/

int main(void) {

	Apple obj;

	return 0;
}
