	## Makefile Arduino AVR ##
	##########################

## Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile
## read Arduino.mk for more config options

## PLEASE NOTE

## UNCOMMENT "Arduino.mk" line 861 "Determine ARDUINO_LIBS automatically"
## to enable automatic user lib finding. Each user library dir should be
## named exactly as the "#include .h" file and should be placed in the
## ARDUINO_DIR/libraries or in the USER_LIB_PATH

## Put a copy of this Makefile in the working dir, and issue "make help".
## The command make compiles, build and link,
## the command make upload flash the MCU too.


MY_HOME			= ${HOME}

ARDMK_DIR		= ${MY_HOME}/Arduino/Arduino-Makefile_sudar
ARDUINO_DIR		= ${MY_HOME}/bin/arduino-1.8.5
AVR_TOOLS_DIR		= ${ARDUINO_DIR}/hardware/tools/avr
BOARDS_TXT		= ${ARDUINO_DIR}/hardware/arduino/avr/boards.txt
USER_LIB_PATH		= ${HOME}/Arduino/libraries
ARDUINO_LIB_PATH	= ${HOME}/Arduino/libraries
ARDUINO_PLATFORM_LIB_PATH = ${ARDUINO_DIR}/hardware/arduino/avr/libraries
ARDUINO_SKETCHBOOK	= ${MY_HOME}/Arduino/sketchbook
# Master Makefile from sudar repo
include                 ${ARDMK_DIR}/Arduino.mk


# --- UNO the beautifullll!! -----------
# --p.s.--keep-it-simple-stupid!!-------
BOARD_TAG		= uno
BOARD_SUB		= atmega328p
MCU			= atmega328p
F_CPU			= 16000000L
# --------------------------------------



# --- leonardo (or pro micro w/leo bootloader)
#BOARD_TAG    = leonardo
#MONITOR_PORT = /dev/ttyACM0
#include /usr/share/arduino/Arduino.mk

# --- mega2560 ide 1.0
#BOARD_TAG    = mega2560
#ARDUINO_PORT = /dev/ttyACM0
#include /usr/share/arduino/Arduino.mk

# --- mega2560 ide 1.6
#BOARD_TAG    = mega
#BOARD_SUB    = atmega2560
#MONITOR_PORT = /dev/ttyACM0
#ARDUINO_DIR  = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- nano ide 1.0
#BOARD_TAG    = nano328
#MONITOR_PORT = /dev/ttyUSB0
#include /usr/share/arduino/Arduino.mk

# --- nano ide 1.6
#BOARD_TAG   = nano
#BOARD_SUB   = atmega328
#ARDUINO_DIR = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- pro mini
#BOARD_TAG    = pro5v328
#MONITOR_PORT = /dev/ttyUSB0
#include /usr/share/arduino/Arduino.mk

# --- sparkfun pro micro
#BOARD_TAG         = promicro16
#ALTERNATE_CORE    = promicro
#BOARDS_TXT        = $(HOME)/arduino/hardware/promicro/boards.txt
#BOOTLOADER_PARENT = $(HOME)/arduino/hardware/promicro/bootloaders
#BOOTLOADER_PATH   = caterina
#BOOTLOADER_FILE   = Caterina-promicro16.hex
#ISP_PROG          = usbasp
#AVRDUDE_OPTS      = -v
#include /usr/share/arduino/Arduino.mk

# --- chipkit
#BOARD_TAG = mega_pic32
#MPIDE_DIR = /where/you/installed/mpide-0023-linux64-20130817-test
#include /usr/share/arduino/chipKIT.mk

# --- pinoccio
#BOARD_TAG         = pinoccio256
#ALTERNATE_CORE    = pinoccio
#BOOTLOADER_PARENT = $(HOME)/arduino/hardware/pinoccio/bootloaders
#BOOTLOADER_PATH   = STK500RFR2/release_0.51
#BOOTLOADER_FILE   = boot_pinoccio.hex
#CFLAGS_STD        = -std=gnu99
#CXXFLAGS_STD      = -std=gnu++11
#include /usr/share/arduino/Arduino.mk

# --- fio
#BOARD_TAG = fio
#include /usr/share/arduino/Arduino.mk

# --- atmega-ng ide 1.6
#BOARD_TAG    = atmegang
#BOARD_SUB    = atmega168
#MONITOR_PORT = /dev/ttyACM0
#ARDUINO_DIR  = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- teensy3
#BOARD_TAG   = teensy31
#ARDUINO_DIR = /where/you/installed/the/patched/teensy/arduino-1.0.6
#include /usr/share/arduino/Teensy.mk

# --- mighty 1284p
#BOARD_TAG         = mighty_opt
#BOARDS_TXT        = $(HOME)/arduino/hardware/mighty-1284p/boards.txt
#BOOTLOADER_PARENT = $(HOME)/arduino/hardware/mighty-1284p/bootloaders
#BOOTLOADER_PATH   = optiboot
#BOOTLOADER_FILE   = optiboot_atmega1284p.hex
#ISP_PROG          = usbasp
#AVRDUDE_OPTS      = -v
#include /usr/share/arduino/Arduino.mk

# --- mightycore
#ALTERNATE_CORE = MightyCore
#BOARD_TAG = 1284
#MCU = atmega1284p
#BOARD_TAG = 644
#MCU = atmega644p
#VARIANT = standard
#F_CPU = 16000000L
#include /usr/share/arduino/Arduino.mk

# ---  megacore
#BOARD_TAG      = 128
#ALTERNATE_CORE = megacore
#F_CPU          = 16000000L
#include /usr/share/arduino/Arduino.mk

# --- sanguino 644p
#BOARD_TAG      = atmega644p
#ALTERNATE_CORE = sanguino
#ISP_PROG       = usbasp
#AVRDUDE_OPTS   = -v
#include /usr/share/arduino/Arduino.mk

# --- atmega328p on breadboard
#BOARD_TAG    = atmega328bb
#ISP_PROG     = usbasp
#AVRDUDE_OPTS = -v
#BOARDS_TXT   = $(HOME)/arduino/hardware/breadboard/boards.txt
#include /usr/share/arduino/Arduino.mk
