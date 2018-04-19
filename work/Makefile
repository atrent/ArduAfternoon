	## Makefile Arduino AVR ##
	##########################

## read Arduino.mk for more config options


MY_HOME			= /mnt/mael_home/elio


### For ATTinyCore
#**grep attinyx5 ~/Arduino/hardware/ATTinyCore/avr/boards.txt**

ARDUINO_DIR		= ${MY_HOME}/bin/arduino-1.8.5
#ARDUINO_CORE_PATH	= ${ARDUINO_DIR}/hardware/ATTinyCore/avr/cores/tiny
#BOARDS_TXT	        = ${ARDUINO_DIR}/hardware/ATTinyCore/avr/boards.txt

#ALTERNATE_CORE          = ATTinyCore
#ALTERNATE_CORE_PATH     = ${MY_HOME}/arduino_afternoon/arduino/cores/ATTinyCore/avr
USER_LIB_PATH		= ${MY_HOME}/arduino_afternoon/arduino/libraries

#ARDUINO_VAR_PATH	= ${ARDUINO_DIR}/hardware/ ..
#ARDUINO_PLATFORM_LIB_PATH = ${ARDUINO_DIR}/hardware/ ..
#ARDUINO_LIB_PATH	= ${ARDUINO_DIR}/hardware/ATTinyCore/avr/libraries

#BOARD_TAG               = attinyx5
#BOARD_SUB               = 85
#F_CPU                   = 128000L

ARDMK_DIR		= ${MY_HOME}/arduino_afternoon/arduino/Arduino-Makefile_sudar
include                 ${ARDMK_DIR}/Arduino.mk
AVR_TOOLS_DIR		= ${ARDUINO_DIR}/hardware/tools/avr

#BOARDS_TXT		= ${ARDUINO_DIR}/hardware/arduino/avr/boards.txt
#ARDUINO_LIB_PATH	= ${MY_HOME}/arduino_afternoon/arduino/libraries
#ARDUINO_PLATFORM_LIB_PATH = ${ARDUINO_DIR}/hardware/arduino/avr/libraries
#ARDUINO_SKETCHBOOK	= ${MY_HOME}/arduino_afternoon/arduino

#OBJDIR			=



# ISP..

ISP_PROG                = avrisp
ISP_PORT                = /dev/ttyACM0
AVRDUDE_ISP_BAUDRATE    = 19200

#ISP_LOCK_FUSE_PRE      = 0x3f
#ISP_LOCK_FUSE_POST     = 0xcf
#ISP_HIGH_FUSE          = 0xdf
#ISP_LOW_FUSE           = 0xff
#ISP_EXT_FUSE           = 0x01
#ISP_EEPROM             = 0


# --- UNO the beautifulll!!
BOARD_TAG		= uno
BOARD_SUB		= atmega328p
MCU			= atmega328p
F_CPU			= 16000000L
DEVICE_PATH             = /dev/ttyACM0



# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile


### CFLAGS_STD
### Set the C standard to be used during compilation. Documentation \ (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cflags_std)
#CFLAGS_STD        = -std=gnu11

### CXXFLAGS_STD
### Set the C++ standard to be used during compilation. Documentation \ (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cxxflags_std)
#CXXFLAGS_STD      = -std=gnu++11

### CXXFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
#CXXFLAGS         += -pedantic -Wall -Wextra




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
#MONITOR_PORT = /dev/ttyACM0
#include /usr/share/arduino/Arduino.mk

# --- nano ide 1.6
#BOARD_TAG   = nano
#BOARD_SUB   = atmega328
#ARDUINO_DIR = /where/you/installed/arduino-1.6.5
#include /usr/share/arduino/Arduino.mk

# --- pro mini
#BOARD_TAG    = pro5v328
#MONITOR_PORT = /dev/ttyACM0
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


# ALTERNATIVE CORES
#
# To use alternative cores for platforms such as ATtiny, you need to
# specify a few more variables, depending on the core in use.
#
# The HLT (attiny-master) core can be used just by specifying
# ALTERNATE_CORE, assuming your core is in your ~/sketchbook/hardware
# directory. For example:
#
# ISP_PORT          = /dev/ttyACM0
# BOARD_TAG         = attiny85
# ALTERNATE_CORE    = attiny-master
#
# To use the more complex arduino-tiny and TinyCore2 cores, you must
# also set ARDUINO_CORE_PATH and ARDUINO_VAR_PATH to the core
# directory, as these cores essentially replace the main Arduino core.
# For example:
#
# ISP_PORT          = /dev/ttyACM0
# BOARD_TAG         = attiny85at8
# ALTERNATE_CORE    = arduino-tiny
# ARDUINO_VAR_PATH  = ~/sketchbook/hardware/arduino-tiny/cores/tiny
# ARDUINO_CORE_PATH = ~/sketchbook/hardware/arduino-tiny/cores/tiny
#
# or....
#
# ISP_PORT          = /dev/ttyACM0
# BOARD_TAG         = attiny861at8
# ALTERNATE_CORE    = tiny2
# ARDUINO_VAR_PATH  = ~/sketchbook/hardware/tiny2/cores/tiny
# ARDUINO_CORE_PATH = ~/sketchbook/hardware/tiny2/cores/tiny
