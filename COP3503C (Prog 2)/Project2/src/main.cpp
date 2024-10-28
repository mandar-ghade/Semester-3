#include <cmath>
#include <iostream>
#include <fstream>
#include "header.h"
#include "reader.h"

Header test_header() {
	std::string p = "input/car.tga";
	Header h = from_path(p);
	print_header(h);
	return h;
}

unsigned char a[3];

int main(int argc, char* argv[]) {
	std::string fp_1 = "input/layer2.tga";
	std::string fp_2 = "input/circles.tga";
	std::string fp_4 = "input/pattern2.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = f1.multiply(f2);
	TGAFile f4 = TGAFile::from_path(fp_4);
	TGAFile f5 = f3.subtract(f4);
	std::string fp_3 = "input/test_out.tga";
	f5.write_to_path(fp_3);
	//Header h = test_header();
	//std::string p = "input/car.tga";
	//std::string o = "input/car2.tga";
	//f.write_to_path(o);
	return 0;
}

