CC = g++

TARGET = oggplayer

COMPILEFLAGS = -lopenal -lalut -logg -lvorbis -lvorbisfile

$(TARGET): main.o ogg.o
	$(CC) -o $(TARGET) main.o ogg.o $(COMPILEFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp -Wno-deprecated

ogg.o: ogg.h ogg.cpp
	$(CC) -c ogg.cpp -Wno-deprecated

clean:
	rm -f $(TARGET) main.o ogg.o

