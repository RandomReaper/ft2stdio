/************************************************************************//**
 * \file	ft2stdio/main.c
 *
 * \brief	Read ft[2]232h in ft245 synchronous mode and write to stdout
 *
 * \author	marc at pignat.org
 *
 * \TODO	duplex, error handling.
 *
 * This file is based on ft2tcp (also authored by myself) and is intended to
 * be less CPU hungry.
 *
 *************************************************************************//*
 *
 * Copyright 2015,2016 Marc Pignat
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "ft245_duplex.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define ARRAY_SIZE(__X__)(sizeof(__X__)/sizeof(__X__[0]))

static void fatal(const char *msg, const char *f, int n)
{
	printf("fatal:'%s' at %s:%d\n", msg, f, n);
}

static int read_callback(uint8_t *buffer, int length, void *userdata)
{
	if (length)
	{
		write(STDOUT_FILENO, buffer, length);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	uint16_t supported_pid[] = {0x6010, 0x6014};
	uint16_t found_pid = 0;
	struct ftdi_version_info info;
	struct ftdi_context *ftdi;
	struct ftdi_duplex_context *duplex;

	int i;
	int type;

	info = ftdi_get_library_version();
	ftdi = ftdi_new();

	if (!ftdi)
	{
		fatal("ftdi_new failed", __FILE__, __LINE__ );
		return -1;
	}

	if (ftdi_set_interface(ftdi, INTERFACE_A))
	{
		fatal("ftdi_set_interface failed", __FILE__, __LINE__ );
		return -1;
	}

	for (i = 0 ; i < ARRAY_SIZE(supported_pid); i++)
	{
		if (ftdi_usb_open(ftdi, 0x0403, supported_pid[i]) == 0)
		{
			found_pid = supported_pid[i];
			break;
		}
	}

	if (!found_pid)
	{
		fatal("no devices found", __FILE__, __LINE__ );

		printf("Searched for vid:pid : ");
		for (i = 0 ; i < ARRAY_SIZE(supported_pid); i++)
		{
			printf("0403:%04x, ", supported_pid[i]);
		}
		printf("\n");
		return -1;
	}

	duplex = ftdi_duplex_start(ftdi, read_callback, NULL, 8, 8);

	if (!duplex)
	{
		fatal("ftdi_duplex_start failed", __FILE__, __LINE__ );
		return -1;
	}

	printf("%s: started\n", argv[0]);

	for (;;)
	{
		int ret = ftdi_duplex_poll(duplex);
		if (ret)
		{
			fatal("ftdi_duplex_poll failed", __FILE__, __LINE__ );
			return -1;
		}
	}

	return 0;
}