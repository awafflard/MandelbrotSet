NAME = MandelbrotSet

CXX = g++

CXXFLAGS = -Wall -Werror -Wextra -o3 -std=c++17 -pthread

INC = -I inc

LIB = -lsfml-graphics -lsfml-window -lsfml-system

SRC = 	src/main.cpp\
		src/ComplexNumber.cpp\
	  	src/Context.cpp\
		src/FpsCounter.cpp\
		src/Mandelbrot.cpp

OBJ = $(SRC:src/%.cpp=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INC) -o build/$(NAME) $^ $(LIB)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf build

re: fclean all

.PHONY: all clean fclean re