C = C++
FLAGS = -Wextra -Wall -Werror -std=c++98
NAME = ft_containers
SRCS = main.cpp
OBJS = ${SRCS:.cpp=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(C) $(FLAGS) $(SRCS) -o ft
	$(C) $(FLAGS) $(SRCS) -D USING_STD -o std

%.o: %.cpp 
	${C} ${FLAGS} -c $< -o $@

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -rf ft std

re: fclean all