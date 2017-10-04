project(ft2stdio)
add_executable(ft2stdio main.c ../ft2tcp/ft245_duplex.c)
include_directories(../ft2tcp)
target_link_libraries(ft2stdio usb-1.0 ftdi1)
