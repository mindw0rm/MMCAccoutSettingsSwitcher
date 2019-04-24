CC = g++
TARGET = MMCAccoutSettingsSwitcher
SRC = $(TARGET)/$(TARGET).cpp
HDR = $(TARGET)/json.hpp
CFLAGS = -Wall
DEBUGFLAGS = -D_DEBUG -g
LDFLAGS = 

release: Release/$(TARGET).o
	$(CC) $(CFLAGS) -o Release/$(TARGET) Release/$(TARGET).o $(LFLAGS) 

debug: Debug/$(TARGET).o
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o Debug/$(TARGET) Debug/$(TARGET).o $(LFLAGS)

Release/$(TARGET).o: $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c -o Release/$(TARGET).o $<

Debug/$(TARGET).o: $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c -o Debug/$(TARGET).o $<

.PHONY: clean
clean: 
	rm -rf Release/*
	rm -rf Debug/*

