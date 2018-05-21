# Variables
COMPILER = g++
LIBS     = -lglut -lSOIL -lGLU -lGL -lm -lsfml-graphics
CFLAGS   = -g
NAME     = main


all:
	$(COMPILER) -c $(NAME).cpp $(LIBS) $(CFLAGS)
	$(COMPILER) -o $(NAME) $(NAME).o $(CLASSES) $(LIBS)

