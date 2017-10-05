# ft2stdio
# ft2stdio [![Build Status](https://travis-ci.org/RandomReaper/ft2tcp.svg?branch=master)](https://travis-ci.org/RandomReaper/ft2tcp)
Read ft[2]232h in ft245 synchronous mode and write to stdout

C code for [ft245_sync_if.vhd](https://github.com/RandomReaper/pim-vhdl/blob/master/hdl/rtl/ft245_sync_if/ft245_sync_if.vhd).

# Compiling

```bash
git clone https://github.com/RandomReaper/ft2stdio.git
cd ft2stdio && mkdir build && cd build
cmake ..
make
```

## Windows drivers
By default windows will install the FTDI drivers, but the WinUSB drivers are necessary for libusb,
the driver used can be changed using [zadig](http://zadig.akeo.ie/). 