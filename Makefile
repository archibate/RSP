OBJS=main.o MeshNode.o Mesh.o MeshLoader.o Texture.o Light.o Shader.o Camera.o stb_image.o
PKGS+=glfw3 x11 glew
LDFLAGS+=`pkg-config --libs $(PKGS)`
CXXFLAGS+=`pkg-config --cflags $(PKGS)`

run: target.app
	./target.app

target.app: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
