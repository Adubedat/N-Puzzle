.SILENT:

NAME = n-puzzle

SRC_PATH = $(ROOT)/src
ROOT = .
OBJ_FOLDER = obj
INC_PATH = $(ROOT)/includes

OBJ_PATH = $(OBJ_FOLDER)
DST_PATH = $(ROOT)
LFT_PATH =

CC = clang++ -g
CFLAGS = -std=c++11 -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = -fsanitize=address
LDLIBS =

SRC_NAME =	main.cpp \
			Grid.cpp \
			GenerateGrid.cpp \
			Hamming.cpp \
			Manhattan.cpp \
			ManhattanLinearConflict.cpp \
			Solver.cpp \
			Options.cpp


OBJ_NAME = $(SRC_NAME:.cpp=.o)

INC_NAME = 	Grid.hpp \
			GenerateGrid.hpp \
			IHeuristic.hpp \
			Hamming.hpp \
			Manhattan.hpp \
			ManhattanLinearConflict.hpp \
			Solver.hpp \
			Options.hpp

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
INC = $(addprefix $(INC_PATH)/,$(INC_NAME))
DST = $(addprefix $(DST_PATH)/,$(NAME))
TEST = $(addprefix $(DST),_TEST)

all: $(DST)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	printf "\e[32m[✔]\e[36m $@"
	printf "\033[0m\n"

$(DST): $(OBJ) $(INC)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(DST)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

$(TEST): $(filter-out $(OBJ_PATH)/main.o, $(OBJ)) $(OBJ_PATH)/test.o $(INC)
	$(CC) $(filter-out $(OBJ_PATH)/main.o, $(OBJ)) $(OBJ_PATH)/test.o $(LDFLAGS) $(LDLIBS) -o $(TEST)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

clean:
	printf "\e[36m"
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	printf "\e[36m"
	@rm -fv $(DST)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

ac: all clean

test: $(TEST)
	@./$(TEST) puzzles/diego


.PHONY: all clean fclean re
