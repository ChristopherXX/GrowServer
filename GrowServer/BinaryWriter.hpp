#pragma once
#ifndef BINARYWRITER_HPP
#define BINARYWRITER_HPP

#include <cstdint>
#include <string>

class BinaryWriter {
public:
	uint8_t* data;
	int mempos;
	int len;

	void write(short value) {
		memcpy(data + mempos, &value, sizeof(short));
		mempos += sizeof(short);
	}
	void write(int value) {
		memcpy(data + mempos, &value, sizeof(int));
		mempos += sizeof(int);
	}
	void write(uint8_t* value, int length) {
		memcpy(data + mempos, value, length);
		mempos += length;
	}
	void write(std::string value) {
		memcpy(data + mempos, value.c_str(), value.length());
		mempos += (int)value.length();
	}

	BinaryWriter(int len) {
		this->mempos = 0;
		this->len = len;
		data = new uint8_t[len];
		memset(data, 0, len);
	}
	~BinaryWriter() {
		delete[] data;
	}
};
#endif