#include <iostream>
#include <fstream>
#include "header.h"

Header from_path(std::string& str) {
	std::fstream stream(str, std::ios_base::in | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("File could not be found.");
	}
	Header h = retrieve_header(stream);
	return h;
}

Header retrieve_header(std::fstream& stream) {
	if (!stream.is_open()) {
		throw std::runtime_error("File could not be found.");
	}
	char id_length = 0;
	char color_map_type = 0; // if color map present
	char image_type = 0; // type of image (grayscale, compressed, etc.)
	short color_map_origin = 0; // starting index of color map (0 usually)
	short color_map_length = 0; // (0 usually)
	char color_map_depth = 0; // bit depth of map (0 usually)
	short x_origin = 0;
	short y_origin = 0;
	short width = 0;
	short height = 0;
	char pixel_depth = 0; // bits of each pixel
	char image_descriptor = 0; // additional details about the image.
	stream.read(&id_length, 1);
	stream.read(&color_map_type, 1);
	stream.read(&image_type, 1);
	stream.read(reinterpret_cast<char*>(&color_map_origin), 2);
	stream.read(reinterpret_cast<char*>(&color_map_length), 2);
	stream.read(&color_map_depth, 1);
	stream.read(reinterpret_cast<char*>(&x_origin), 2);
	stream.read(reinterpret_cast<char*>(&y_origin), 2);
	stream.read(reinterpret_cast<char*>(&width), 2);
	stream.read(reinterpret_cast<char*>(&height), 2);
	stream.read(&pixel_depth, 1);
	stream.read(&image_descriptor, 1);
	Header h(id_length, color_map_type, image_type, color_map_origin, color_map_length, color_map_depth, x_origin, y_origin, width, height, pixel_depth, image_descriptor);
	return h;
}

void print_header(Header& h) {
	std::cout << "id_length: " << static_cast<int>(h.id_length) << '\n';
	std::cout << "color_map_type: " << static_cast<int>(h.color_map_type) << '\n';
	std::cout << "image_type: " << static_cast<int>(h.image_type) << '\n';
	std::cout << "color_map_origin: " << h.color_map_origin << '\n';
	std::cout << "color_map_length: " << h.color_map_length << '\n';
	std::cout << "color_map_depth: " << static_cast<int>(h.color_map_depth) << '\n';
	std::cout << "x_origin: " << h.x_origin << '\n';
	std::cout << "y_origin: " << h.y_origin << '\n';
	std::cout << "width: " << h.width << '\n';
	std::cout << "height: " << h.height << '\n';
	std::cout << "pixel_depth: " << static_cast<int>(h.pixel_depth) << '\n';
	std::cout << "image_descriptor: " << static_cast<int>(h.image_descriptor) << '\n';
}

void Header::write_to_path(std::fstream& stream) {
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found (Header).");
	}
	stream.write(&id_length, 1);
	stream.write(&color_map_type, 1);
	stream.write(&image_type, 1);
	stream.write(reinterpret_cast<char*>(&color_map_origin), 2);
	stream.write(reinterpret_cast<char*>(&color_map_length), 2);
	stream.write(&color_map_depth, 1);
	stream.write(reinterpret_cast<char*>(&x_origin), 2);
	stream.write(reinterpret_cast<char*>(&y_origin), 2);
	stream.write(reinterpret_cast<char*>(&width), 2);
	stream.write(reinterpret_cast<char*>(&height), 2);
	stream.write(&pixel_depth, 1);
	stream.write(&image_descriptor, 1);
}

