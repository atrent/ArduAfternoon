#!/bin/bash

# Arduino Builder Autopilot rev 0.1b by Matt Huntin', C.Spuckler Inc.
#
# arduprocess <sketch.ino>
#
## preprocess a sketch.ino file and generate a sketch.cpp AVR-G++ compatible
## for the sudar-Makefile toolchain

SKETCH=$1
MY_HOME=$HOME
MY_WKDIR=${MY_HOME}/Arduino

ARDUINO_DIR=${MY_WKDIR}/arduino-1.8.5
MY_ARDULIBS=${ARDUINO_DIR}/libraries
# fully qualified board name: ##
BOARD=arduino:avr:uno
################################
BUILD_DIR=$(basename $1 .ino)_build
OUT_FILE=$(basename $1 .ino).cpp
PROMPT="ArduBuilder>";


#### DEBUG !!! ####
printf %b "

######## ARDUINO BUILDER AUTOPILOT 0.1b ########
## a Matt H. - C.Spuckler Inc frugal software ##
################################################

SKETCH=$SKETCH
MY_HOME=$MY_HOME
ARDUINO_DIR=$ARDUINO_DIR
MY_ARDULIBS=$MY_ARDULIBS
BOARD=$BOARD
BUILD_DIR=$BUILD_DIR
OUT_FILE=$OUT_FILE
\n";
#### END DEBUG ####

beep -l10 -f400;
sleep 0.5;

# if SKETCH not terminate with .ino..
if [ ! $SKETCH = *.ino ]; then
  printf %b "$PROMPT ERROR: input file: \"${SKETCH}\" not .ino\n";
  beep -l600 -f200 -r1 -d25 ;
  exit 1;
fi

# if OUTFILE symlink exists..
if [ -h ./${OUT_FILE} ]; then
  rm ./${OUT_FILE};
fi

# if BUILD_DIR exists..
if [ ! -d ./${BUILD_DIR} ]; then
  mkdir ./${BUILD_DIR};
else
  printf %b "$PROMPT BUILD_DIR already exist..\n";
fi

## DEBUG ##
printf %b "
${PROMPT} running:

${ARDUINO_DIR}/arduino-builder
-preprocess
-hardware       ${ARDUINO_DIR}/hardware
-tools          ${ARDUINO_DIR}/hardware/tools/avr
-tools          ${ARDUINO_DIR}/tools-builder
-libraries      ${ARDUINO_DIR}/libraries
-libraries      ${MY_ARDULIBS}
-fqbn           ${BOARD}
-build-path     ./${BUILD_DIR}
-warnings       default
${SKETCH}
\n";
## END DEBUG ##

#RUN arduino-builder
printf %b "$PROMPT arduino-builder: \n"
${ARDUINO_DIR}/arduino-builder  \
-preprocess  \
-hardware       ${ARDUINO_DIR}/hardware  \
-tools          ${ARDUINO_DIR}/hardware/tools/avr  \
-tools          ${ARDUINO_DIR}/tools-builder  \
-libraries      ${ARDUINO_DIR}/libraries  \
-libraries      ${MY_ARDULIBS}  \
-fqbn           ${BOARD}  \
-build-path     ./${BUILD_DIR}  \
-warnings       default  \
$1 > /dev/null;
ardBuildOk=$?;

# if arduino-builder exit...
if [ ! -v $ardBuildOk ]; then
  printf %b "$PROMPT arduino-builder: exit $?.. \n";
else
  beep -l600 -f200 -r1 -d25 ;
  printf %b "$PROMPT WARNING: arduino-builder, exit: $? \n";
  exit 1;
fi

# move processed .cpp file in pwd if exist
if [ -e ./${BUILD_DIR}/sketch/${SKETCH}.cpp ]; then
  mv ./${BUILD_DIR}/sketch/${SKETCH}.cpp ./${OUT_FILE};
  mvOk=$?;
fi

# remove build dir if exists
if [ -d ./${BUILD_DIR} ] && [ ! -v $mvOk ]; then
  rm -r ./${BUILD_DIR};
  printf %b "$PROMPT Done\n";
  beep -l30 -f600 -r4 -d25 ;
else
  printf %b "$PROMPT ERROR! BUILD_DIR not created!\n";
  beep -l600 -f200 -r1 -d25 ;
fi




