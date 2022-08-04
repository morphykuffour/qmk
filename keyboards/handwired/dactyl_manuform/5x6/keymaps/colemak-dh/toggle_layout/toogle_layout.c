#include <stdio.h> // printf
#include <wchar.h> // wprintf

#include <hidapi.h>
// #include "hidapi/hidapi/hidapi.h"

#define MAX_STR 255

int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[65];
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;

	// Initialize the hidapi library
	res = hid_init();

    //  Dactyl Manuform
    // idVendor           0x444d 
    // idProduct          0x3536 
	handle = hid_open(0x444d, 0x3536, NULL);

	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	wprintf(L"Manufacturer String: %s\n", wstr);

	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	wprintf(L"Product String: %s\n", wstr);

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	wprintf(L"Serial Number String: (%d) %s\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	wprintf(L"Indexed String 1: %s\n", wstr);

	// // Toggle LED (cmd 0x80). The first byte is the report number (0x0).
	// buf[0] = 0x0;
	// buf[1] = 0x80;
	// res = hid_write(handle, buf, 65);

	// Close the device
	hid_close(handle);

	// Finalize the hidapi library
	res = hid_exit();

	return 0;
}
