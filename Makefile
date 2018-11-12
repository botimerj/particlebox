
CC 		:= g++
INCLUDE := -Iinclude/ -Isrc/
LINK 	:= -Lsrc/ -Llib/ -lglfw3 -lglad -lm -lrt -ldl -lX11 -lpthread
SRC 	:= src/*.cpp

all: pbox 

pbox: 
	$(CC) $(INCLUDE) $(SRC) main.cpp -o main $(LINK) 

physics:
	$(CC) $(INCLUDE) physics.cpp -o physics 

pat:
	$(CC) $(INCLUDE) pat.cpp -o pat 


clean:
	rm main physics pat
.PHONY: all pbox physics pat
