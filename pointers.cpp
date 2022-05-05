#include <iostream>

struct s {
	unsigned int x;
};

int main() {
	// Create a variable almond
	unsigned int almond = 17;
	// Create a pointer to almond
	unsigned int *almondPointer = &almond;
	// Note that:
	// unsigned int* almondPointer = &almond;
	// is the same thing (position of * )
	
	// Now print the pointer
	std::cout << "almondPointer points to " << almondPointer
	<< ", which has a value of " << *almondPointer
	<< "." << std::endl << std::endl;
	
	
	// Now create a struct instance
	s myStruct;							// Create a struct
	myStruct.x = 12;					// Set a value of x in the struct
	s *myStructPointer = &myStruct;		// Create a pointer to the struct
	
	// To get the value of x using the pointer use:
	std::cout << (*myStructPointer).x << std::endl;
	// Or preferably 
	std::cout << myStructPointer->x << std::endl; // It's the arrow operator!
}
