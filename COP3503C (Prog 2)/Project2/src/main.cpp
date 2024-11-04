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
	std::cout << "\t./project2.out [output] [firstImage] [method] [...]\n";
}

bool valid_file_input(char* output_file) {
	size_t period_index = 0;
	bool contains_period = false;
	std::string output_file_str(output_file, strlen(output_file));
	for (size_t i = 0; i < strlen(output_file); i++) {
		if (output_file[i] == '.' && !contains_period) {
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

bool is_valid_combined_arguments(int i, int argc, char* argv[]) {
	if (i + 2 >= argc) {
		std::cout << "Missing argument.\n";
		return false;
	}
	if (!valid_file_input(argv[i + 1]) || !valid_file_input(argv[i + 2])) {
		std::cout << "Invalid argument, invalid file name.\n";
		return false;
	}
	std::string target_file_1 = argv[i + 1];
	std::string target_file_2 = argv[i + 2];
	if (!get_if_file_exists(target_file_1) || !get_if_file_exists(target_file_2)) {
		std::cout << "Invalid argument, file does not exist.\n";
		return false;
	} else {
		return true;
	}
}

bool is_valid_argument(int i, int argc, char* argv[], bool expects_file) {
	if (i + 1 >= argc) {
		std::cout << "Missing argument.\n";
		return false;
	} else if (expects_file) {
		if (!valid_file_input(argv[i + 1])) {
			std::cout << "Invalid argument, invalid file name.\n";
			return false;
		}
		std::string target_file = argv[i + 1];
		if (!get_if_file_exists(target_file)) {
			std::cout << "Invalid argument, file does not exist.\n";
			return false;
		} else {
			return true;
		}
	} else if (!expects_file) {
		try {
			int _ = std::stoi(argv[i + 1]);
			return true;
		} catch (std::invalid_argument) {
			std::cout << "Invalid argument, expected number.\n";
			return false;
		}
	}
	return true;
}

void parse_cli(int argc, char* argv[]) {
	if (argc <= 1) {
		print_help();
	}
	if (argc == 2) {
		if (!strcmp(argv[1], "--help")) {
			print_help();
		} else if (!valid_file_input(argv[1])) {
			std::cout << "Invalid file name." << '\n';
		} else {
			print_help();
		}
		return;
	}
	//if (argc == 3) {
	//	if (!valid_file_input(argv[2])) {
	//		std::cout << "Invalid file name." << '\n';
	//		return;
	//	} else {
	//		//std::cout << "Invalid method name" << '\n';
	//		//print_help();
	//	}
	//	return;
	//}
	if (!valid_file_input(argv[1]) || !valid_file_input(argv[2])) {
		std::cout << "Invalid file name." << '\n';
		return;
	}
	std::string output_file_name(argv[1], strlen(argv[1]));
	std::string tracking_image_name(argv[2], strlen(argv[2]));
	if (!strcmp(argv[1], "--help")) {
		print_help();
	}
	if (!get_if_file_exists(tracking_image_name)) {
		std::cout << "File does not exist.\n";
		return;
	}
	TGAFile tracking_image = TGAFile::from_path(tracking_image_name);
	bool has_operation = false;
	for (int i = 3; i < argc; i++) {
		if (!strcmp(argv[i], "multiply")) {
			if (!is_valid_argument(i, argc, argv, true)) return;
			std::string target_file = argv[i + 1];
			TGAFile target = TGAFile::from_path(target_file);
			tracking_image = tracking_image.multiply(target);
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "subtract")) {
			if (!is_valid_argument(i, argc, argv, true)) return;
			std::string target_file = argv[i + 1];
			TGAFile target = TGAFile::from_path(target_file);
			tracking_image = tracking_image.subtract(target);
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "overlay")) {
			if (!is_valid_argument(i, argc, argv, true)) return;
			std::string target_file = argv[i + 1];
			TGAFile target = TGAFile::from_path(target_file);
			tracking_image = tracking_image.overlay(target);
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "screen")) {
			if (!is_valid_argument(i, argc, argv, true)) return;
			std::string target_file = argv[i + 1];
			TGAFile target = TGAFile::from_path(target_file);
			tracking_image = tracking_image.screen(target);
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "combine")) {
			if (!is_valid_combined_arguments(i, argc, argv)) return;
			std::string target_file_1 = argv[i + 1];
			std::string target_file_2 = argv[i + 2];
			TGAFile target_1 = TGAFile::from_path(target_file_1);
			TGAFile target_2 = TGAFile::from_path(target_file_2);
			tracking_image = TGAFile::from_files(tracking_image, target_1, target_2);
			if (!has_operation) has_operation = true;
			i += 2;
		} else if (!strcmp(argv[i], "flip")) {
			tracking_image = tracking_image.flip();
			if (!has_operation) has_operation = true;
		} else if (!strcmp(argv[i], "onlyred")) {
			tracking_image = tracking_image.onlyred();
			if (!has_operation) has_operation = true;
		} else if (!strcmp(argv[i], "onlygreen")) {
			tracking_image = tracking_image.onlygreen();
			if (!has_operation) has_operation = true;
		} else if (!strcmp(argv[i], "onlyblue")) {
			tracking_image = tracking_image.onlyblue();
			if (!has_operation) has_operation = true;
		} else if (!strcmp(argv[i], "addred")) {
			if (!is_valid_argument(i, argc, argv, false)) return;
			int n = std::stoi(argv[i + 1]);
			u8 amount = static_cast<u8>(std::abs(n));
			if (n < 0) {
				tracking_image = tracking_image.subtract(0, 0, amount);
			} else {
				tracking_image = tracking_image.add(0, 0, amount);
			}
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "addgreen")) {
			if (!is_valid_argument(i, argc, argv, false)) return;
			int n = std::stoi(argv[i + 1]);
			u8 amount = static_cast<u8>(std::abs(n));
			if (n < 0) {
				tracking_image = tracking_image.subtract(0, amount, 0);
			} else {
				tracking_image = tracking_image.add(0, amount, 0);
			}
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "addblue")) {
			if (!is_valid_argument(i, argc, argv, false)) return;
			int n = std::stoi(argv[i + 1]);
			u8 amount = static_cast<u8>(std::abs(n));
			if (n < 0) {
				tracking_image = tracking_image.subtract(amount, 0, 0);
			} else {
				tracking_image = tracking_image.add(amount, 0, 0);
			}
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "scalered")) {
			if (!is_valid_argument(i, argc, argv, false)) return;
			int n = std::stoi(argv[i + 1]);
			u8 amount = static_cast<u8>(n);
			tracking_image = tracking_image.scale_red(amount);
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "scalegreen")) {
			if (!is_valid_argument(i, argc, argv, false)) return;
			int n = std::stoi(argv[i + 1]);
			u8 amount = static_cast<u8>(n);
			tracking_image = tracking_image.scale_green(amount);
			if (!has_operation) has_operation = true;
			i += 1;
		} else if (!strcmp(argv[i], "scaleblue")) {
			if (!is_valid_argument(i, argc, argv, false)) return;
			int n = std::stoi(argv[i + 1]);
			u8 amount = static_cast<u8>(n);
			tracking_image = tracking_image.scale_blue(amount);
			if (!has_operation) has_operation = true;
			i += 1;
		} else {
			break;
		}
	}
	if (has_operation) {
		tracking_image.write_to_path(output_file_name);
	} else {
		std::cout << "Invalid method name." << '\n';
	}
}

int main(int argc, char* argv[]) {
	if (argc > 1) parse_cli(argc, argv);
	else print_help();
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

