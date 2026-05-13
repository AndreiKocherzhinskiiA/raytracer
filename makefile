CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS  = -lconfig++

NAME     = raytracer

SRCS     = Raytracer/main.cpp \
           Raytracer/math/MathCalculations.cpp \
           Raytracer/Core/Renderer.cpp \
           Raytracer/Core/Lights.cpp \
           Raytracer/Scene/Scene.cpp \
           Raytracer/Scene/Factory.cpp \
           Raytracer/Lights/Directional.cpp \
           Raytracer/Lights/Point.cpp \
           Raytracer/Primitives/Sphere.cpp  \
           Raytracer/Primitives/Plane.cpp   \
           Raytracer/Primitives/Cylinder.cpp \
           Raytracer/Primitives/Cone.cpp \
           Raytracer/Primitives/Cube.cpp \
           Raytracer/Materials/FlatColor.cpp \
           Raytracer/Materials/Reflection.cpp

OBJS     = $(SRCS:.cpp=.o)

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
