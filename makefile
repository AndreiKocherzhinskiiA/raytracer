CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -fPIC
LDFLAGS  = -lconfig++ -ldl

NAME     = raytracer

# Core sources — compiled directly into the binary
CORE_SRCS = Raytracer/main.cpp \
            Raytracer/math/MathCalculations.cpp \
            Raytracer/Core/Renderer.cpp \
            Raytracer/Core/Lights.cpp \
            Raytracer/Scene/Scene.cpp 
            # Raytracer/Scene/Factory.cpp

CORE_OBJS = $(CORE_SRCS:.cpp=.o)

# Plugin shared libraries
PLUGINS = plugins/directional.so \
          plugins/point.so \
          plugins/sphere.so \
          plugins/plane.so \
          plugins/cylinder.so \
          plugins/cone.so \
          plugins/cube.so \
          plugins/flatcolor.so \
          plugins/reflection.so

all: plugins_dir $(NAME) $(PLUGINS)

plugins_dir:
	mkdir -p plugins

$(NAME): $(CORE_OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(CORE_OBJS) $(LDFLAGS)

# Lights
plugins/directional.so: Raytracer/Lights/Directional.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

plugins/point.so: Raytracer/Lights/Point.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

# Primitives
plugins/sphere.so: Raytracer/Primitives/Sphere.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

plugins/plane.so: Raytracer/Primitives/Plane.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

plugins/cylinder.so: Raytracer/Primitives/Cylinder.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

plugins/cone.so: Raytracer/Primitives/Cone.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

plugins/cube.so: Raytracer/Primitives/Cube.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

# Materials
plugins/flatcolor.so: Raytracer/Materials/FlatColor.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

plugins/reflection.so: Raytracer/Materials/Reflection.cpp
	$(CXX) $(CXXFLAGS) -shared -o $@ $<

# Pattern rule for core .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(CORE_OBJS)
	rm -f $(PLUGINS)

fclean: clean
	rm -f $(NAME)
	rm -rf plugins

re: fclean all

.PHONY: all clean fclean re plugins_dir