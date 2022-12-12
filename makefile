EXECDIR = Debug
INC_PATH = inc
SRC_PATH = src
CMD_DEL = rm
SRC := $(wildcard $(SRC_DIR)/*.c)

ifeq ($(OS),Windows_NT)
	DETECTED_OS := Windows
	CMD_DEL := del
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
    endif
endif

all:
	$(MAKE) build
	$(MAKE) runWindows

build:
	avr-gcc -mmcu=atmega328p -o $(EXECDIR)/main.bin main.c $(SRC_PATH)/usart.c -I $(INC_PATH) 

compile:
	$(MAKE) build
	avr-objcopy -j .text -j .data -O ihex $(EXECDIR)/main.bin main.hex
	avr-size -C --mcu=atmega328p $(EXECDIR)/main.bin

run:
	sudo avrdude -p m328p -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:$(EXECDIR)/main.hex

runWindows:
	avrdude -p m328p -c arduino -P com8 -b 115200 -U flash:w:main.hex

clean:
	$(CMD_DEL) $(EXECDIR)
#	$(CMD_DEL) $(EXECDIR)/main.bin main.hex main.o $(EXECDIR)

#ifeq ($(OS),Windows_NT)
#    CCFLAGS += -D WIN32
#else
#    UNAME_S := $(shell uname -s)
#    ifeq ($(UNAME_S),Linux)
#        CCFLAGS += -D LINUX
#    endif
#endif

$(shell mkdir $(EXECDIR))