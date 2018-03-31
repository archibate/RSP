#include <GL/glew.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <glad/glad.h>
#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "VertexObjects.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "MeshNode.h"
#include "ssthrow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::auto_ptr;

void terminate(int status);

static bool loadShader(Shader *shaderProgram,
		const char *vertexShaderSource,
		const char *fragmentShaderSource)
{
	const char *infoLog;

	ShaderCode vertexShader(GL_VERTEX_SHADER);
	vertexShader.source(vertexShaderSource);
	if (infoLog = vertexShader.compileGetError()) {
		string infoLogStr = infoLog;
		delete infoLog;
		SSTHROW("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
			<< infoLogStr);
	}

	ShaderCode fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.source(fragmentShaderSource);
	if (infoLog = fragmentShader.compileGetError()) {
		string infoLogStr = infoLog;
		delete infoLog;
		SSTHROW("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
			<< infoLogStr);
	}

	shaderProgram->attach(vertexShader);
	shaderProgram->attach(fragmentShader);
	if (infoLog = shaderProgram->linkGetError()) {
		string infoLogStr = infoLog;
		delete infoLog;
		SSTHROW("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
			<< infoLogStr);
	}
	return true;
}

Shader *lightingShader, *lampShader, *skyboxShader;
MeshNode *rootNode;
Texture *skyboxTexture;
MeshNode *skyboxNode;

static string file_get_contents(const char *filename) {
	ifstream f(filename);
	stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

static void initGL()
{
	// enable some tests

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// load shaders

	if (!loadShader(lightingShader = new Shader,
		file_get_contents("lighting.vert").c_str(),
		file_get_contents("lighting.frag").c_str())
	   ) terminate(-1);

	if (!loadShader(lampShader = new Shader,
		file_get_contents("lamp.vert").c_str(),
		file_get_contents("lamp.frag").c_str())
	   ) terminate(-1);

	/*if (!loadShader(skyboxShader = new Shader,
		file_get_contents("skybox.vert").c_str(),
		file_get_contents("skybox.frag").c_str())
	   ) terminate(-1);*/

	// load models

	rootNode = new MeshNode("cubes.node");
	rootNode->setup();

	/*glm::mat4 skyboxModel;
	skyboxModel = glm::scale(skyboxModel, glm::vec3(5.0f, 5.0f, 5.0f));
	skyboxNode = new MeshNode(cube, skyboxModel);

	skyboxTexture = new Texture;
	skyboxTexture->loadCubeMap("images/skybox/", ".jpg");*/
}

Camera camera
	( glm::vec3(0.0f,  0.1f,  3.0f)
	, glm::vec3(0.0f,  0.0f, -1.0f)
	, glm::vec3(0.0f,  1.0f,  0.0f)
	);

struct Projection {
	glm::mat4 m;

	void resize(float ratio) {
		m = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
	}

	glm::mat4 getProjview(const Camera &camera) const {
		return m * camera.getViewMatrix();
	}
} projection;

static void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float lastFrame = 0.0f;
	float currFrame = glfwGetTime();
	float deltaTime = currFrame - lastFrame;
	lastFrame = currFrame;
	camera.updateByInput(2.5f * deltaTime);

	auto projview = projection.getProjview(camera);

	Light light
		( camera.pos
		, glm::vec3(1.0f, 1.0f, 1.0f)
		, camera.front
		, glm::cos(glm::radians(12.5f))
		, glm::cos(glm::radians(17.5f))
		);

	DirLight sunlight
		( glm::vec3(0.0f, 1.0f, 0.0f)
		, glm::vec3(1.0f, 0.9f, 0.8f) * 2.0f
		);

	glm::mat4 rootModel;

/*using std::cout;
using std::endl;*/

	/*skyboxShader->use();
	skyboxTexture->activeBind(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);
	skyboxShader->uniform("skybox", 0);
	camera.unify(*skyboxShader);
	skyboxShader->uniformMatrix4("projview", glm::value_ptr(projview));
	skyboxNode->draw(*skyboxShader, rootModel);*/

	auto &shader = *lightingShader;
	shader.use();
	sunlight.unifyEnable(shader);
	light.unifyEnable(shader, 0);
	camera.unify(shader);
	shader.uniformMatrix4("projview", glm::value_ptr(projview));
	rootNode->draw(shader, rootModel);
}

static void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	camera.input.left = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	camera.input.right = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

	camera.input.forward = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	camera.input.backward = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);

	camera.input.up = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
	camera.input.down = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS);
}

static void resizeCallback(GLFWwindow *window, int width, int height)
{
	projection.resize((float) width / (float) height);

	glViewport(0, 0, width, height);
}

void terminate(int status)
{
	glfwTerminate();
	std::exit(status);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	int width = 800, height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
	if (!window) {
		SSTHROW("ERROR::GLFW::WINDOW::CREATE_FAILED\nFailed to create GLFW window");
	}
	glfwMakeContextCurrent(window);
	resizeCallback(window, width, height);
	glfwSetFramebufferSizeCallback(window, resizeCallback);

#ifdef _WIN32
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		SSTHROW("ERROR::GLAD::GLLOADER::INIT_FAILED\nFailed to initialize GLAD");
	}
#endif

	glewInit();

	initGL();

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
