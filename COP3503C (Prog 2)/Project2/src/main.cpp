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

void test_1() {
	std::string fp_1 = "input/layer1.tga";
	std::string fp_2 = "input/pattern1.tga";
	std::string output_path = "output/part1.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = f1.multiply(f2);
	f3.write_to_path(output_path);
}

void test_2() {
	std::string fp_1 = "input/car.tga";
	std::string fp_2 = "input/layer2.tga";
	std::string output_path = "output/part2.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = f1.subtract(f2);
	f3.write_to_path(output_path);
}

void test_3() {
	std::string fp_1 = "input/layer1.tga";
	std::string fp_2 = "input/pattern2.tga";	
	std::string fp_4 = "input/text.tga";
	std::string output_path = "output/part3.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = f1.multiply(f2);
	TGAFile f4 = TGAFile::from_path(fp_4);
	TGAFile f5 = f3.screen(f4);
	f5.write_to_path(output_path);
}

void test_4() {
	std::string fp_1 = "input/layer2.tga";
	std::string fp_2 = "input/circles.tga";	
	std::string fp_4 = "input/pattern2.tga";
	std::string output_path = "output/part4.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = f1.multiply(f2);
	TGAFile f4 = TGAFile::from_path(fp_4);
	TGAFile f5 = f3.subtract(f4);
	f5.write_to_path(output_path);
}

void test_5() {
	std::string fp_1 = "input/layer1.tga";
	std::string fp_2 = "input/pattern1.tga";
	std::string output_path = "output/part5.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = f1.overlay(f2);
	f3.write_to_path(output_path);
}


void test_6() {
	std::string fp_1 = "input/car.tga";
	std::string output_path = "output/part6.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = f1.add(0, 200, 0);
	f2.write_to_path(output_path);
}

void test_7() {
	std::string fp_1 = "input/car.tga";
	std::string output_path = "output/part7.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = f1.scale_red(4);
	TGAFile f3 = f2.scale_blue(0);
	f3.write_to_path(output_path);
}

void test_8() {
	std::string fp_1 = "input/car.tga";
	std::string red_output_path = "output/part8_r.tga";
	std::string green_output_path = "output/part8_g.tga";
	std::string blue_output_path = "output/part8_b.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	f1.write_red_to_path(red_output_path);
	f1.write_green_to_path(green_output_path);
	f1.write_blue_to_path(blue_output_path);
}

void test_9() {
	std::string fp_1 = "input/layer_red.tga";
	std::string fp_2 = "input/layer_green.tga";
	std::string fp_3 = "input/layer_blue.tga";
	std::string output_path = "output/part9.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	TGAFile f2 = TGAFile::from_path(fp_2);
	TGAFile f3 = TGAFile::from_path(fp_3);
	TGAFile combined = TGAFile::from_files(f1, f2, f3);
	combined.write_to_path(output_path);
}


void test_10() {
	std::string fp_1 = "input/text2.tga";
	std::string output_path = "output/part10.tga";
	TGAFile f1 = TGAFile::from_path(fp_1);
	f1.write_to_path_upside_down(output_path);
}

int main(int argc, char* argv[]) {
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
	test_7();
	test_8();
	test_9();
	test_10();
	return 0;
}

