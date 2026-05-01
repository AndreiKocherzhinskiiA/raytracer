CXX       = g++
CXXFLAGS  = -std=c++17 -Wall -Wextra -I. -lconfig++
LDFLAGS   = -lconfig++

NAME      = raytracer

SRCS      = Raytracer/main.cpp \
            Raytracer/math/MathCalculations.cpp \
            Raytracer/Core/Renderer.cpp \
            Raytracer/Scene/Scene.cpp \
			Raytracer/Scene/ObjectFactory.cpp
OBJS      = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
