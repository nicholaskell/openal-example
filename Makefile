
SRC_DIR=src/

OBJDIR=$(SRC_DIR)_nv_obj/

EXECUTABLE_NAME=application
PROJECT_NAME=OpenAL_Example

COMPILE_VERSION_MAJOR = 0
COMPILE_VERSION_MINOR = 0
COMPILE_VERSION_REVISION = "0"

OPEN_GL_LIBRARIES = -lglut -lGLU 
OPEN_AL_LIBRARIES = -lopenal
OPEN_CV_LIBRARIES = 

SDL2_LIBRARIES = -lSDL2
SDL_LIBRARIES = -lSDL_image -lSDL_mixer -lSDL -lSDL_ttf
SFML_LIBRARIES = -lsfml-system -lsfml-window -lsfml-network -lsfml-graphics -lsfml-audio
MEDIA_LIBRARIES = $(OPEN_AL_LIBRARIES)
PRINTING_LIBRARIES = -lcups
COMMUNICATION_LIBRARIES = -lserial
VIDEO_LIBRARIES = -lavutil -lavformat -lavcodec -lavdevice -lavfilter -lswscale
COMPRESSION_LIBRARIES = -lz -lbz2
OTHER_LIBRARIES = -ldl -lm
LIBRARIES = $(OTHER_LIBRARIES) $(COMPRESSION_LIBRARIES) $(MEDIA_LIBRARIES)






MKDIR_P=mkdir -p
UNAME:=$(shell uname -s)

CPP_SOURCES:=$(shell find $(SRC_DIR) -type f -name '*.cpp')
CPP_OBJECTS=$(CPP_SOURCES:%.cpp=$(OBJDIR)%.o) 
OBJECTS=$(CPP_OBJECTS)

CPP_ONLY_WARNING_FLAGS:=  -Wsign-compare
WARNING_FLAGS_NO_WARNINGS:= -w
WARNING_FLAGS_ALL_WARNINGS:= -Wall

WARNING_FLAGS := $(CPP_ONLY_WARNING_FLAGS) -Wunreachable-code

# -O0 is the default Optimization flag
OPTIMIZE_FLAGS:= -O3

CC = g++
CPP_LINK_FLAGS =  -o
CPP_FLAGS = 

SDL_CONFIG_DIR = 
SDL_CONFIG = sdl-config --cflags
SDL_CONFIG_COMMAND = $(SDL_CONFIG_DIR)$(SDL_CONFIG)






LINKER_EXTRAS =
COMPILER_EXTRAS = -I/home/robd/libs/include/
#LIBRARIES =  -lSDL_image -lSDL_mixer -lSDL -lSDL_ttf -lcups -lserial -ldl -lm



#  Include Project specific Makefile include after the vars are set, bet before the rules are.
#  This way, any variable can be overriden, and a custom rule will be declared first - thus, 
#  will be executed, while the default will be ignored.

#include $(SRC_DIR)project.mk

VERSION=$(COMPILE_VERSION_MAJOR)_$(COMPILE_VERSION_MINOR)_$(COMPILE_VERSION_REVISION)
UPDATE_NAME=$(PROJECT_NAME)_$(VERSION)

VERSION_DEFINES:= -D VERSION_MAJOR=$(COMPILE_VERSION_MAJOR) -D VERSION_MINOR=$(COMPILE_VERSION_MINOR) -D VERSION_REVISION=$(COMPILE_VERSION_REVISION)


COMPILE_DATE:= `date +'%y.%m.%d'`
COMPILE_TIME:= `date +'%H:%M:%S'`
COMPILE_DATE_TIME_DEFINES:= -D COMPILE_DATE=\"$(COMPILE_DATE)\" -D COMPILE_TIME=\"$(COMPILE_TIME)\"

EXECUTABLE?= $(EXECUTABLE_NAME)_$(VERSION)
DEFINES := $(VERSION_DEFINES) $(COMPILE_DATE_TIME_DEFINES)
COMPILER_FLAGS = -c $(OPTIMIZE_FLAGS)

all: start game done 

auto: all
	./$(EXECUTABLE)
	
game: version checkos $(OBJECTS)
	@echo -n 'Start executable linking.....'
	@if $(CC) $(OPENGL_FLAGS) $(CPP_LINK_FLAGS) $(EXECUTABLE) $(DEFINES) $(OBJECTS) $(LINKER_EXTRAS) $(LIBRARIES) ;\
	then printf "SUCCESS!!\t\t\t";echo '';echo '-- Produced: '$(EXECUTABLE); rm  $(EXECUTABLE_NAME); ln -s $(EXECUTABLE) $(EXECUTABLE_NAME)  ;echo '';\
	else echo ''; echo "FAIL"; echo ''; exit 1;\
	fi


$(OBJDIR)%.o : %.cpp
	@$(MKDIR_P) $(@D)
	@printf '%s' 'Compiling $*.cpp....'
	@if $(CC) -Wno-deprecated  $(DEFINES) $(COMPILER_FLAGS) $(COMPILER_EXTRAS) -I ./$(SRC_DIR) $< -o $@;\
	then echo "Success";\
	else echo "FAIL"; echo ''; exit 1;\
	fi


version:
	echo $(VERSION) > version
	echo $(PROJECT_NAME) > project
	echo $(PROJECT_NAME)$(VERSION)

.PHONY: 	clean done start nick v_colonFile checkosx scrub game camera update version
.IGNORE: 	clean

clean:
	@echo '';echo '';echo '';
	@echo  "Starting the clean."
	-rm  $(OBJECTS) $(EXECUTABLE_NAME)
	@echo "cleaned up."
	@echo '';echo '';echo 'Files left behind:';
	ls -R $(OBJDIR) | grep "\.o"
	
checkos:
ifeq ($(UNAME),Darwin)
	@echo "Compiling on OS X"
	$(eval export OPENGL_FLAGS= -framework Carbon -framework OpenGL -framework GLUT)
#	$(eval export SDL_CONFIG_DIR = /usr/local/bin/)
#	$(eval export LINKER_EXTRAS+= $(SRC_DIR)/SDLMain.m `$(SDL_CONFIG_COMMAND) --libs`)
#	$(eval export COMPILER_EXTRAS+= -j8)
endif


done:
	@echo '';echo '';echo '';
	
start:
	clear;
	@echo '';echo '';echo '';
	@echo 'Start.'; 

scrub: start clean game done

echo_vars:
	@echo "sdl-config: " $(SDL_CONFIG_COMMAND)

buildArchive: all
	./buildArchive.sh

update: buildArchive
	rsync -tv --progress ./update/$(UPDATE_NAME).tar.gz /media/baytekupdate/
	rsync -tv --progress ./update/$(UPDATE_NAME).sum /media/baytekupdate/
	rsync -tv --progress ./update/current /media/baytekupdate/
	rsync -tv --progress ./update/install.sh /media/baytekupdate/

release:
	$(eval export COMPILER_EXTRAS+= -O3)
	$(eval export EXECUTABLE = $(EXECUTABLE_NAME))
	make all

canidate:
	$(eval export COMPILE_VERSION_REVISION+= 'rc')
	$(eval export EXECUTABLE=EXECUTABLE+'rc')
	make release
	




	
	
	
	
	
	
	
	
	
	
	
	
	
	
