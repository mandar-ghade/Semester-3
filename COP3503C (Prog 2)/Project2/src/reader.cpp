#include "reader.h"
#include "header.h"
#include <fstream>

TGAFile TGAFile::from_path(std::string& name) {
	std::fstream stream(name, std::ios_base::in | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("File could not be found.");
	}
	TGAFile f = from_stream(stream);
	return f;
}

Pixel* next_pixel(std::fstream& stream) {
	unsigned char B = 0;
	unsigned char G = 0;
	unsigned char R = 0;
	stream.read(reinterpret_cast<char*>(&B), 1);
	stream.read(reinterpret_cast<char*>(&G), 1);
	stream.read(reinterpret_cast<char*>(&R), 1);
	Pixel* new_pixel = new Pixel(B, G, R);
	return new_pixel;
}

TGAFile TGAFile::from_stream(std::fstream& stream) {
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found.");
	}
	Header h = retrieve_header(stream);
	std::vector<std::unique_ptr<Pixel>> pixels;
	unsigned int pixel_count = static_cast<unsigned int>(h.height) * static_cast<unsigned int>(h.width);
	for (unsigned int i = 0; i < pixel_count; i++) {
		Pixel* next = next_pixel(stream);
		std::unique_ptr<Pixel> next_ptr(next);
		pixels.push_back(std::move(next_ptr));
	}
	TGAFile f(h, pixels);
	return f;
}

void TGAFile::write_to_path(std::string& path) {
	std::fstream stream(path, std::ios_base::out | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found.");
	}
	header.write_to_path(stream);
	for (unsigned long i = 0; i < pixels.size(); i++) {
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->B), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->G), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->R), 1);
	}
}

u8 clamp(float n) {
	if (n < 0) {
		return 0;
	} else if (n > 255) {
		return 255;
	} else {
		return static_cast<u8>(n + 0.5f);
	}
}

u8 clamp_norm(float n) {
	if (n < 0) {
		return 0;
	} else if (n > 255) {
		return 255;
	}
	return static_cast<u8>(n*255 + 0.5f);
}

u8 norm(float n) {
	return static_cast<u8>(n / 255);
}

std::tuple<float, float, float> Pixel::normalize() {
	float B_ = static_cast<float>(this->B) / 255;
	float G_ = static_cast<float>(this->G) / 255;
	float R_ = static_cast<float>(this->R) / 255;
	return {B_, G_, R_};
}

//std::tuple<float, float, float> Pixel::denormalize() {
//	std::tuple<float, float, float> n_pixel = this->normalize();
//	float new_B = (B + 0.5f) * std::get<0>(n_pixel);
//	float new_G = (G + 0.5f) * std::get<1>(n_pixel);
//	float new_R = (R + 0.5f) * std::get<2>(n_pixel);
//	return { new_B, new_G, new_R };
//}

std::tuple<u8, u8, u8> Pixel::multiply(Pixel& rhs) {
	auto np1 = normalize();
	auto np2 = rhs.normalize();
	float new_B = std::get<0>(np1) * std::get<0>(np2);
	float new_G = std::get<1>(np1) * std::get<1>(np2);
	float new_R = std::get<2>(np1) * std::get<2>(np2);
	return { clamp_norm(new_B), clamp_norm(new_G), clamp_norm(new_R) };
}

std::tuple<u8, u8, u8> Pixel::screen(Pixel& rhs) {
	auto np1 = normalize();
	auto np2 = rhs.normalize();
	float B_ = 1 - ((1 - std::get<0>(np1)) * (1 - std::get<0>(np2)));
	float G_ = 1 - ((1 - std::get<1>(np1)) * (1 - std::get<1>(np2)));
	float R_ = 1 - ((1 - std::get<2>(np1)) * (1 - std::get<2>(np2)));
	return { clamp_norm(B_), clamp_norm(G_), clamp_norm(R_) };
}

std::tuple<u8, u8, u8> Pixel::subtract(Pixel& rhs) {
	auto p1 = as_tuple();
	auto p2 = rhs.as_tuple();
	float B_ = std::get<0>(p1) - std::get<0>(p2);
	float G_ = std::get<1>(p1) - std::get<1>(p2);
	float R_ = std::get<2>(p1) - std::get<2>(p2);
	return { clamp(B_), clamp(G_), clamp(R_) };
}

std::tuple<u8, u8, u8> Pixel::addition(Pixel& rhs) {
	auto p1 = as_tuple();
	auto p2 = rhs.as_tuple();
	float B_ = std::get<0>(p1) + std::get<0>(p2);
	float G_ = std::get<1>(p1) + std::get<1>(p2);
	float R_ = std::get<2>(p1) + std::get<2>(p2);
	return { clamp(B_), clamp(G_), clamp(R_) };
}

std::tuple<u8, u8, u8> Pixel::overlay(Pixel& rhs) {
	auto np1 = normalize();
	auto np2 = rhs.normalize();
	u8 B_ = 0;
	u8 G_ = 0;
	u8 R_ = 0;

	if (std::get<0>(np2) <= 0.5) {
		B_ = clamp_norm(2 * std::get<0>(np1) * std::get<0>(np2));
	} else {
		B_ = clamp_norm(1 - (2 * (1 - std::get<0>(np1)) * (1 - std::get<0>(np2))));
	}

	if (std::get<1>(np2) <= 0.5) {
		G_ = clamp_norm(2 * std::get<1>(np1) * std::get<1>(np2));
	} else {
		G_ = clamp_norm(1 - (2 * (1 - std::get<1>(np1)) * (1 - std::get<1>(np2))));
	}

	if (std::get<2>(np2) <= 0.5) {
		R_ = clamp_norm(2 * std::get<2>(np1) * std::get<2>(np2));
	} else {
		R_ = clamp_norm(1 - (2 * (1 - std::get<2>(np1)) * (1 - std::get<2>(np2))));
	}

	return { B_, G_, R_ };
}

std::tuple<u8, u8, u8> Pixel::as_tuple() {
	return {this->B, this->G, this->R};
}

TGAFile TGAFile::multiply(TGAFile& rhs) {
	if (
		(this->header.height * this->header.width) != 
		(rhs.header.height * rhs.header.width)
	) {
		throw std::runtime_error("Incorrect file size 1");
	}
	Header h = header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* lhs_pixel = this->pixels.at(i).get();
		Pixel* rhs_pixel = rhs.pixels.at(i).get();
		auto new_tuple = lhs_pixel->multiply(*rhs_pixel);
		Pixel* next_ptr = new Pixel(
			std::get<0>(new_tuple), 
			std::get<1>(new_tuple),
			std::get<2>(new_tuple)
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::screen(TGAFile& rhs) {
	if (
		(this->header.height * this->header.width) != 
		(rhs.header.height * rhs.header.width)
	) {
		throw std::runtime_error("Incorrect file size 2");
	}
	Header h = header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* lhs_pixel = this->pixels.at(i).get();
		Pixel* rhs_pixel = rhs.pixels.at(i).get();
		auto new_tuple = lhs_pixel->screen(*rhs_pixel);
		Pixel* next_ptr = new Pixel(
			std::get<0>(new_tuple), 
			std::get<1>(new_tuple),
			std::get<2>(new_tuple)
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::subtract(TGAFile& rhs) {
	if (
		(this->header.height * this->header.width) != 
		(rhs.header.height * rhs.header.width)
	) {
		throw std::runtime_error("Incorrect file size 3");
	}
	Header h = header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* lhs_pixel = this->pixels.at(i).get();
		Pixel* rhs_pixel = rhs.pixels.at(i).get();
		auto new_tuple = lhs_pixel->subtract(*rhs_pixel);
		Pixel* next_ptr = new Pixel(
			std::get<0>(new_tuple), 
			std::get<1>(new_tuple),
			std::get<2>(new_tuple)
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::addition(TGAFile& rhs) {
	if (
		(this->header.height * this->header.width) != 
		(rhs.header.height * rhs.header.width)
	) {
		throw std::runtime_error("Incorrect file size 4");
	}
	Header h = header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* lhs_pixel = this->pixels.at(i).get();
		Pixel* rhs_pixel = rhs.pixels.at(i).get();
		auto new_tuple = lhs_pixel->addition(*rhs_pixel);
		Pixel* next_ptr = new Pixel(
			std::get<0>(new_tuple), 
			std::get<1>(new_tuple),
			std::get<2>(new_tuple)
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::overlay(TGAFile& rhs) {
	if (
		(this->header.height * this->header.width) != 
		(rhs.header.height * rhs.header.width)
	) {
		throw std::runtime_error("Incorrect file size 5");
	}
	Header h = header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* lhs_pixel = this->pixels.at(i).get();
		Pixel* rhs_pixel = rhs.pixels.at(i).get();
		auto new_tuple = lhs_pixel->overlay(*rhs_pixel);
		Pixel* next_ptr = new Pixel(
			std::get<0>(new_tuple), 
			std::get<1>(new_tuple),
			std::get<2>(new_tuple)
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::from_files(TGAFile& red, TGAFile& green, TGAFile& blue) {
	if (
		(red.header.height * red.header.width) != 
		(green.header.height * green.header.width)
	||
		(red.header.height * red.header.width) !=
		(blue.header.height * blue.header.width)
	) {
		std::cout << (int)red.header.height << '\n';
		std::cout << (int)red.header.width << '\n';
		std::cout << (int)green.header.height << '\n';
		std::cout << (int)green.header.width << '\n';
		std::cout << (int)blue.header.height << '\n';
		std::cout << (int)blue.header.width << '\n';
		throw std::runtime_error("Incorrect file size 6");
	}
	Header h = red.header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < red.pixels.size(); i++) {
		unsigned char red_pixel = red.pixels.at(i).get()->R;
		unsigned char green_pixel = green.pixels.at(i).get()->G;
		unsigned char blue_pixel = blue.pixels.at(i).get()->B;
		Pixel* next_ptr = new Pixel(
			blue_pixel, 
			green_pixel,
			red_pixel
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

void TGAFile::write_to_path_upside_down(std::string& path) {
	std::fstream stream(path, std::ios_base::out | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found.");
	}
	header.write_to_path(stream);
	for (unsigned long i = 1; i < this->pixels.size() + 1; i++) {
		stream.write(reinterpret_cast<char*>(&pixels.at(pixels.size() - i).get()->B), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(pixels.size() - i).get()->G), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(pixels.size() - i).get()->R), 1);
	}
}

void TGAFile::write_blue_to_path(std::string& path) {
	std::fstream stream(path, std::ios_base::out | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found.");
	}
	header.write_to_path(stream);
	for (unsigned long i = 0; i < pixels.size(); i++) {
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->B), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->B), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->B), 1);
	}
}

void TGAFile::write_green_to_path(std::string& path) {
	std::fstream stream(path, std::ios_base::out | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found.");
	}
	header.write_to_path(stream);
	for (unsigned long i = 0; i < pixels.size(); i++) {
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->G), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->G), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->G), 1);
	}
}

void TGAFile::write_red_to_path(std::string& path) {
	std::fstream stream(path, std::ios_base::out | std::ios_base::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("Output path not found.");
	}
	header.write_to_path(stream);
	for (unsigned long i = 0; i < pixels.size(); i++) {
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->R), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->R), 1);
		stream.write(reinterpret_cast<char*>(&pixels.at(i)->R), 1);
	}
}

TGAFile TGAFile::add(u8 B_, u8 G_, u8 R_) {
	Header h = this->header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		u8 new_B = clamp(static_cast<float>(this->pixels.at(i).get()->B) + static_cast<float>(B_));
		u8 new_G = clamp(static_cast<float>(this->pixels.at(i).get()->G) + static_cast<float>(G_));
		u8 new_R = clamp(static_cast<float>(this->pixels.at(i).get()->R) + static_cast<float>(R_));
		Pixel* next_ptr = new Pixel(
			new_B, 
			new_G,
			new_R
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::scale_blue(u8 B_) {
	Header h = this->header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* pix = this->pixels.at(i).get();
		Pixel* next_ptr = new Pixel(
			clamp(pix->B * B_),
			pix->G,
			pix->R
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::scale_green(u8 G_) {
	Header h = this->header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* pix = this->pixels.at(i).get();
		Pixel* next_ptr = new Pixel(
			pix->B,
			clamp(pix->G * G_),
			pix->R
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}

TGAFile TGAFile::scale_red(u8 R_) {
	Header h = this->header;
	std::vector<std::unique_ptr<Pixel>> vec;
	for (unsigned int i = 0; i < this->pixels.size(); i++) {
		Pixel* pix = this->pixels.at(i).get();
		Pixel* next_ptr = new Pixel(
			pix->B,
			pix->G,
			clamp(pix->R* R_)
		);
		std::unique_ptr<Pixel> next_unique_ptr(next_ptr);
		vec.push_back(std::move(next_unique_ptr));
	}
	TGAFile f(h, vec);
	return f;
}
