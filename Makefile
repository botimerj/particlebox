
CC 		:= g++
INCLUDE := -Iinclude/ -Isrc/
LINK 	:= -Lsrc/ -Llib/ -lglfw3 -lglad -lm -lrt -ldl -lX11 -lpthread
SRC 	:= src/*.cpp

all: pbox 

pbox: 
	$(CC) $(INCLUDE) $(SRC) main.cpp -o main $(LINK) 

clean:
	rm main 
.PHONY: all pbox 
