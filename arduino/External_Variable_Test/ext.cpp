#include "ext.hpp"

// a is referenced in the cpp file and not in the hpp file.
// Therefore you need to include ext2.h in the cpp file
#include "ext2.h"

int Apple::foo() {
  return a;
}
