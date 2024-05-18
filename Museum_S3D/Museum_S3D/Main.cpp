#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h> 
#include <vector>
#include<thread>

#include <GL/glew.h>

#define GLM_FORCE_CTOR_INIT 
#include <GLM.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Scene.h"
#include "Camera.h"
#include "ResourceManager.h"


#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 960;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

Camera* pCamera = nullptr;

void Cleanup()
{
	delete pCamera;
}

// timing
double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;

float specularStrength = 0.5f;
float ambientStrength = 0.1f;
float diffuseStrength = 0.5f;
int specularExponent = 32;

Scene Museum(SCR_WIDTH, SCR_HEIGHT);

int main(int argc, char** argv)
{
	std::string strFullExeFileName = argv[0];
	std::string strExePath;
	const size_t last_slash_idx = strFullExeFileName.rfind('\\');
	if (std::string::npos != last_slash_idx) {
		strExePath = strFullExeFileName.substr(0, last_slash_idx);
	}

	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Museum", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();

	glEnable(GL_DEPTH_TEST);

	// Create camera
	pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0, 0.0, 3.0));

	glm::vec3 lightPos(0.0f, 0.0f, 2.0f);

	ResourceManager::LoadShader("Lamp.vs", "Lamp.fs", "shaderLamp");
	ResourceManager::LoadShader("PhongLight.vs", "PhongLight.fs", "shaderLight");
	Shader lampShader = ResourceManager::GetShader("shaderLamp");
	Shader lightingShader = ResourceManager::GetShader("shaderLight");

	Museum.SetCamera(pCamera);
	Museum.Init();

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// input
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.Use();
		lightingShader.SetVec3("objectColor", 0.5f, 1.0f, 0.31f);
		lightingShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);

		glm::vec3 lightPos2 = lightPos + glm::vec3(cos(float(glfwGetTime())), sin(float(glfwGetTime())), 0.0f);
		lightingShader.SetVec3("lightPos", lightPos2);
		lightingShader.SetVec3("viewPos", pCamera->GetPosition());

		lightingShader.SetMat4("projection", pCamera->GetProjectionMatrix());
		lightingShader.SetMat4("view", pCamera->GetViewMatrix());

		glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(3.0f));
		lightingShader.SetMat4("model", model);
		lightingShader.SetFloat("ambientStrength", ambientStrength);
		lightingShader.SetFloat("diffuseStrength", diffuseStrength);
		lightingShader.SetFloat("specularStrength", specularStrength);
		lightingShader.SetInt("specularExponent", specularExponent);

		Museum.Render();
		Museum.RenderModels();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
	}

	Cleanup();
	ResourceManager::Clear();

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		pCamera->ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		pCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		pCamera->ProcessKeyboard(UP, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		pCamera->ProcessKeyboard(DOWN, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		ambientStrength = std::min(1.0f, ambientStrength + 0.1f);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		ambientStrength = std::max(0.0f, ambientStrength - 0.1f);
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		pCamera->SetPosition(-50.0f, 3.0f, 3.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		pCamera->SetPosition(0.0f, 3.0f, 3.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		pCamera->SetPosition(50.0f, 3.0f, 3.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		pCamera->SetPosition(-30.0f, 3.0f, 43.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		pCamera->SetPosition(-8.0f, 3.0f, 36.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		pCamera->SetPosition(30.0f, 3.0f, 40.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		pCamera->Reset(width, height);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	pCamera->Reshape(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	pCamera->MouseControl((float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
	pCamera->ProcessMouseScroll((float)yOffset);
}
