objects := openal-example.o Wav.o
libs := -lopenal

all: openal-example

openal-example: $(objects)
	g++ -o $@ $^ $(libs)

%.o: %.cpp
	g++ -c -MMD -o $@ $<

-include $(objects:.o=.d)

clean:
	rm -f *.o *.d openal-example
