#include <cmath>
#include <cstring>
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

void multiply();

void run_cli() {
	std::string option;
}

void print_help() {
	std::cout << "Project 2: Image Processing, Fall 2024\n\n";
	std::cout << "Usage:" << "\n";
	std::cout << "\t./project2 [output] [firstImage] [method] [...]\n";
}

bool valid_file_input(char* output_file) {
	size_t period_index = 0;
	bool contains_period = false;
	std::string output_file_str(output_file, strlen(output_file));
	for (size_t i = 0; i < strlen(output_file); i++) {
		if (output_file[i] == '\n') {
			continue;
		} else if (output_file[i] == '.' && !contains_period) {
			contains_period = true;
			period_index = i;
		} else if (output_file[i] == '.' && contains_period) {
			return false;
		} else if (contains_period) {
			if (i != period_index + 1) {
				return false;
			} else if (i + 3 != strlen(output_file)) {
				return false;
			} else {
				std::string extension = output_file_str.substr(strlen(output_file) - 3, 3);
				if (extension == "tga") {
					return true;
				} else {
					return false;
				}
			}
		}
	}
	return contains_period;

	//std::string extension = output_file.substr(strlen(output_path) - 3, 3);
	//std::cout << extension << '\n';
	return true;
}

bool get_if_file_exists(std::string &name) {
	std::fstream stream(name, std::ios_base::in | std::ios_base::binary);
	return stream.is_open();
}
void parse_cli(int argc, char* argv[]) {
	if (argc == 1) {
		return;
	}
	if (argc == 2) {
		print_help();
		return;
	}
	if (argc == 3) {
		std::cout << "Invalid method name" << '\n';
		return;
	}
	if (!valid_file_input(argv[1]) || !valid_file_input(argv[2])) {
		std::cout << "Invalid file name." << '\n';
		return;
	}
	std::string output_file_name(argv[1], strlen(argv[1]));
	std::string tracking_image_name(argv[2], strlen(argv[2]));
	if (!std::strcmp(argv[1], "--help")) {
		print_help();
	}
	TGAFile tracking_image = TGAFile::from_path(tracking_image_name);
	tracking_image = TGAFile::from_path(tracking_image_name);
	for (int i = 3; i < argc; i++) {
		if (!strcmp(argv[i], "multiply")) {
			if (i + 1 >= argc) {
				std::cout << "Missing argument.\n";
				return;
			} else if (!valid_file_input(argv[i + 1])) {
				std::cout << "Invalid argument, invalid file name.\n";
				return;
			}
			std::string target_file = argv[i + 1];
			if (!get_if_file_exists(target_file)) {
				std::cout << "Invalid argument, file does not exist.\n";
				return;
			} else {
				tracking_image = 
			}
		}
	}
}

int main(int argc, char* argv[]) {
	parse_cli(argc, argv);
//	test_1();
//	test_2();
//	test_3();
//	test_4();
//	test_5();
//	test_6();
//	test_7();
//	test_8();
//	test_9();
//	test_10();
	return 0;
}

