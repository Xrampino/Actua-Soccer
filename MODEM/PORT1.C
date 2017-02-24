	serials=(_bios_equiplist()>>9) & 7;
	if (serials<2) serials=2;				//force at least 2 serial ports!

	if (serials<serial_port) serial_port=2;
	check16550(serial_port);

