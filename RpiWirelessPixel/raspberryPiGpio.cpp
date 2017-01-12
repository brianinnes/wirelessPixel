/*
 * RaspberryPiGpio.cpp
 *
 *  Created on: 27 Oct 2016
 *      Author: brian
 */
#include "raspberryPiGpio.h"
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_MAX 3
#define DIRECTION_MAX 35
#define VALUE_MAX 30

using namespace std;

RaspberryPiGpio::RaspberryPiGpio() {
	this->pin = -1;
}

RaspberryPiGpio::~RaspberryPiGpio() {
	// disable CE pin
	close(this->pin_fd);

	char buffer[BUFFER_MAX];
		ssize_t bytes_written;
		int fd;

		fd = open("/sys/class/gpio/unexport", O_WRONLY);
		if (-1 == fd) {
			fprintf(stderr, "Failed to open unexport for writing!\n");
		}

		bytes_written = snprintf(buffer, BUFFER_MAX, "%d", this->pin);
		write(fd, buffer, bytes_written);
		close(fd);

}


void RaspberryPiGpio::setPin(uint8_t p) {
	this->pin = p;
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", this->pin);
	write(fd, buffer, bytes_written);
	close(fd);

	// wait for export to complete
	usleep(100000);

	char path[DIRECTION_MAX];

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", this->pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
	}

	if (-1 == write(fd, "out", 3)) {
		fprintf(stderr, "Failed to set direction!\n");
	}

	close(fd);

	char d_path[VALUE_MAX];
	snprintf(d_path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", this->pin);
	this->pin_fd = open(d_path, O_WRONLY);
	if (-1 == pin_fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
	}
}

uint8_t RaspberryPiGpio::setPinState(uint8_t value) {
	static const char s_values_str[] = "01";

	//char path[VALUE_MAX];
	if (1 != write(this->pin_fd, &s_values_str[0 == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}
	return 0;
}
