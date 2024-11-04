#pragma once
#include "header.h"
#include <iostream>
#include <vector>
#include <memory>

typedef unsigned char u8;

u8 clamp(float n);
u8 clamp_norm(float n);

struct Pixel {
public:
	u8 B;
	u8 G;
	u8 R;
	Pixel(u8 B, u8 G, u8 R): B(B), G(G), R(R) {};
	void print() {
		std::cout << "Pixel(" << static_cast<int>(B) << ", " << static_cast<int>(G) << ", " << static_cast<int>(R) << ")\n";
	}
	std::tuple<float, float, float> normalize(); 
	//std::tuple<float, float, float> denormalize(); 
	std::tuple<u8, u8, u8> multiply(Pixel& rhs);
	std::tuple<u8, u8, u8> screen(Pixel& rhs);
	std::tuple<u8, u8, u8> subtract(Pixel& rhs);
	std::tuple<u8, u8, u8> addition(Pixel& rhs);
	std::tuple<u8, u8, u8> overlay(Pixel& rhs);
	std::tuple<u8, u8, u8> as_tuple();
	Pixel& operator=(const Pixel& rhs);
};

class TGAFile {
private:
	static TGAFile from_stream(std::fstream& stream);
public:
	Header header;
	std::vector<std::unique_ptr<Pixel>> pixels;
	TGAFile(const TGAFile& file);
	TGAFile(Header& header, std::vector<std::unique_ptr<Pixel>>& pixels): header(header), pixels(std::move(pixels)) {};
	static TGAFile from_path(std::string& name);
	static TGAFile from_files(TGAFile& red, TGAFile& green, TGAFile& blue);
	void write_to_path(std::string& path);
	void write_to_path_upside_down(std::string& path);
	void write_blue_to_path(std::string& path);
	void write_green_to_path(std::string& path);
	void write_red_to_path(std::string& path);
	TGAFile flip();
	TGAFile onlyred();
	TGAFile onlygreen();
	TGAFile onlyblue();
	TGAFile multiply(TGAFile& rhs);
	TGAFile screen(TGAFile& rhs);
	TGAFile subtract(TGAFile& rhs);
	TGAFile addition(TGAFile& rhs);
	TGAFile overlay(TGAFile& rhs);
	TGAFile add(u8 B_ = 0, u8 G_ = 0, u8 R_ = 0);
	TGAFile subtract(u8 B_ = 0, u8 G_ = 0, u8 R_ = 0);
	TGAFile scale_blue(u8 B_ = 0);
	TGAFile scale_green(u8 G_ = 0);
	TGAFile scale_red(u8 R_ = 0);
	TGAFile& operator=(const TGAFile& file);
};

Pixel* next_pixel(std::fstream& stream);

