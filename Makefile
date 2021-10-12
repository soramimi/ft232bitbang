
all:
	gcc -I /usr/local/include/libftdi1 wpins.cpp -L /usr/local/lib -l ftdi1 -o wpins
	gcc -I /usr/local/include/libftdi1 rpins.cpp -L /usr/local/lib -l ftdi1 -o rpins

# Q. How do I make libusb work as non-root?
# A. https://askubuntu.com/questions/978552/how-do-i-make-libusb-work-as-non-root
