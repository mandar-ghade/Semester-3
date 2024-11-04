#pragma once
#include <iostream>
#include <fstream>

struct Header {
	char id_length;
	char color_map_type; // if color map present
	char image_type; // type of image (grayscale, compressed, etc.)
	short color_map_origin; // starting index of color map (0 usually)
	short color_map_length; // (0 usually)
	char color_map_depth; // bit depth of map (0 usually)
	short x_origin;
	short y_origin;
	short width;
	short height;
	char pixel_depth; // bits of each pixel
	char image_descriptor; // additional details about the image.
	Header& operator=(const Header& rhs);
	Header(
		char id_length, 
		char color_map_type,
		char image_type,
		short color_map_origin,
		short color_map_length,
		char color_map_depth,
		short x_origin,
		short y_origin,
		short width,
		short height,
		char pixel_depth,
		char image_descriptor
	): id_length(id_length), color_map_type(color_map_type), image_type(image_type), color_map_origin(color_map_origin), color_map_length(color_map_length), color_map_depth(color_map_depth), x_origin(x_origin), y_origin(y_origin), width(width), height(height), pixel_depth(pixel_depth), image_descriptor(image_descriptor) {};
	Header(const Header& rhs): id_length(rhs.id_length), color_map_type(rhs.color_map_type), image_type(rhs.image_type), color_map_origin(rhs.color_map_origin), color_map_length(rhs.color_map_length), color_map_depth(rhs.color_map_depth), x_origin(rhs.x_origin), y_origin(rhs.y_origin), width(rhs.width), height(rhs.height), pixel_depth(rhs.pixel_depth), image_descriptor(rhs.image_descriptor) {};
	void write_to_path(std::fstream& stream);
};

void print_header(Header& h);
Header from_path(std::string& str);
Header retrieve_header(std::fstream& stream);

