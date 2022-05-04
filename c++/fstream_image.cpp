#include <fstream>

int main() {

	const int width = 255;
	const int height = 255;

	std::ofstream img ("picture.ppm");
	img << "P3" << std::endl;
	img << height << " " << width << std::endl;
	img << "255" << std::endl;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int r = x % 256;
			int g = y % 256;
			int b = (x * y) % 256;
			img << r << " " << g << " " << b << std::endl;
		}
	}

	return 0;
}
