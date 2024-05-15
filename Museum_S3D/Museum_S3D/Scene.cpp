#include "Scene.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Model.h"
#include <map>
#include <string>

Renderer* renderer;
Renderer* renderPodium;

map<std::string, Model>* models;
//AABB BOXES


Scene::Scene(GLuint width, GLuint height) :
	Width(width), Height(height)
{

}

Scene::~Scene()
{
	delete renderer;
}

void Scene::Init()
{
	//Shaders
	ResourceManager::LoadShader("Floor.vs", "Floor.fs", "shaderFloor");

	//Textures
	ResourceManager::LoadTexture("../../Textures/floor.jpg", "floorTexture");
	ResourceManager::LoadTexture("../../Textures/wall.jpg", "wallTexture");
	ResourceManager::LoadTexture("../../Textures/Ceiling.png", "ceilingTexture");
	ResourceManager::LoadTexture("../../Textures/grassTexture.jpg", "grassTexture");
	ResourceManager::LoadTexture("../../Textures/muzeu.jpg", "museumTexture");
	ResourceManager::LoadTexture("../../Textures/door.jpg", "doorTexture");
	//ResourceManager::LoadTexture("../../Textures/butterflies.jpg", "butterflies");
	ResourceManager::LoadTexture("../../Textures/bugs.jpg", "bugs");
	ResourceManager::LoadTexture("../../Textures/dragonfly.jpg", "dragonfly");
	ResourceManager::LoadTexture("../../Textures/Spiders.jpg", "spiders");


	//Info about animals
	ResourceManager::LoadTexture("../../Textures/bearinfo.png", "bearinfo");
	ResourceManager::LoadTexture("../../Textures/wolfinfo.png", "wolfinfo");
	ResourceManager::LoadTexture("../../Textures/spinosaurusInfo.png", "spinosaurusInfo");
	ResourceManager::LoadTexture("../../Textures/barosaurusInfo.png", "barosaurusInfo");
	ResourceManager::LoadTexture("../../Textures/dilophosaurusInfo.png", "dilophosaurusInfo");
	ResourceManager::LoadTexture("../../Textures/quetzalcoatlusInfo.png", "quetzalcoatlusInfo");
		
	models = new map<std::string, Model>();
	//MODELS

	//Mountain/forest zone
	models->insert({ "Wolf",Model("../../3DObjects/Wolf/wolf.obj") });
	models->insert({ "Tree",Model("../../3DObjects/Tree/Tree.obj") });
	models->insert({ "Spinosaurus", Model("../../3DObjects/Spinosaurus/13217_Spinosaurus_V1_NEW.obj") });
	models->insert({ "Quetzalcoatlus", Model("../../3DObjects/Quetzalcoatlus/13623_Quetzalcoatlus_v1_L2.obj") });
	models->insert({ "Wire", Model("../../3DObjects/Wire/wire.obj") });
	models->insert({ "Dilophosaurus", Model("../../3DObjects/Dilophosaurus/dilophosaurus.obj") });
	models->insert({ "Barosaurus", Model("../../3DObjects/Barosaurus/21534_Barosaurus_v1.obj") });
	models->insert({ "Bear", Model("../../3DObjects/Bear/Bear.obj") });
	models->insert({ "Cearadactylus", Model("../../3DObjects/Cearadactylus/13627_Cearadactylus_v2_l3.obj") });
	models->insert({ "Vultur", Model("../../3DObjects/Vultur/Vultur.obj") });
	models->insert({ "Grass",Model("../../3DObjects/Grass/Grass.obj") });
	models->insert({ "Podium",Model("../../3DObjects/Podium/podium.obj") });
	models->insert({ "Oak Tree",Model("../../3DObjects/Oak Tree/10445_Oak_Tree_v1_max2010_iteration-1.obj") });
	//models->insert({ "Plant1",Model("../../3DObjects/Plants/Plant1/flower 04.obj") });

	//Renderers
	renderer = new Renderer(ResourceManager::GetShader("shaderFloor"));
	renderPodium = new Renderer(ResourceManager::GetShader("shaderFloor"), true);
}

void Scene::SetCamera(Camera* camera)
{
	pCamera = camera;
}

float rotationAngle = 0.0f;

void Scene::Render()
{
	// FIRST ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(-50.0f, 0.f, 0.f), glm::vec3(), 0.f, glm::vec3(), NULL);

	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-50.f, 4.5f + resize, -4.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-50.f, 4.5f + resize, 5.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-95.5f + resize, 4.5f + resize, 0.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(-50.f, 30.f + resize, 0.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-45.209f + resize, 9.55f, 0.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-50.f, 9.55f, 4.79f + resize), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);

	// SECOND ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(), glm::vec3(), 0.f, glm::vec3(), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(0.f, 4.5f + resize, -4.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(0.f, 4.5f + resize, 5.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(4.5f + resize, 4.5f + resize, 0.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-5.5f - resize, 4.5f + resize, 0.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(0.f, 30.f + resize, 0.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);

	renderer->Draw(ResourceManager::GetTexture("museumTexture"), pCamera, glm::vec3(0.f, 11.5f + resize, -3.4f - resize), glm::vec3(0.6f, 0.8f, 0.4f), glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(4.77f + resize, 9.55f, 0.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-5.185f - resize, 9.55f, 0.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-0.5f, 9.55f, 4.79f + resize), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderPodium->Draw(ResourceManager::GetTexture("grassTexture"), pCamera, glm::vec3(0.f, 0.f, -20.f), glm::vec3(23.5f, 1.f, 10.f), 0.0f, glm::vec3(), NULL);
	renderer->Draw(ResourceManager::GetTexture("wolfinfo"), pCamera, glm::vec3(15.f , 13.f, -45.f + resize), glm::vec3(0.2f, 0.3f, 0.25f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("bearinfo"), pCamera, glm::vec3(-5.f, 13.f, -45.f + resize), glm::vec3(0.2f, 0.3f, 0.25f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	// THIRD ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(50.0f, 0.f, 0.f), glm::vec3(), 0.f, glm::vec3(), NULL);

	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(50.f, 4.5f + resize, -4.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(50.f, 4.5f + resize, 5.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(54.5f + resize, 4.5f + resize, 0.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);

	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(50.f, 30.f + resize, 0.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);
	
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(44.87f - resize, 9.55f, 0.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(48.f, 9.55f, 4.7f + resize), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);

	renderer->Draw(ResourceManager::GetTexture("quetzalcoatlusInfo"), pCamera, glm::vec3(35.f, 13.f, -45.f + resize), glm::vec3(0.2f, 0.3f, 0.25f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("spinosaurusInfo"), pCamera, glm::vec3(50.f, 18.f, -45.f + resize), glm::vec3(0.2f, 0.3f, 0.25f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("dilophosaurusInfo"), pCamera, glm::vec3(65.f, 13.f, -45.f + resize), glm::vec3(0.2f, 0.3f, 0.25f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);

	// SIXTH ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(-50.0f, 0.f, 50.f), glm::vec3(), 0.f, glm::vec3(), NULL);

	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-50.f, 4.5f + resize, 45.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-50.f, 4.5f + resize, 55.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-95.5f + resize, 4.5f + resize, 50.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(-50.f, 30.f + resize, 50.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(5.271f + resize, 9.55f, 50.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(270.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(48.f, 9.55f, 4.812f + resize), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);

	// FIFTH ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(0.0f, 0.f, 50.f), glm::vec3(), 0.f, glm::vec3(), NULL);

	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(0.f, 4.5f + resize, 45.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(0.f, 4.5f + resize, 55.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(-45.5f + resize, 4.5f + resize, 50.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(0.f, 30.f + resize, 50.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(4.73f + resize, 9.55f, 50.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-45.1f + resize, 9.55f, 50.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-0.2f, 9.55f, 4.815f + resize), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(3.f, 9.55f, 4.815f + resize), glm::vec3(0.2f, 0.3f, 0.2f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);

	// FOURTH ROOM
	renderer->Draw(ResourceManager::GetTexture("floorTexture"), pCamera, glm::vec3(50.0f, 0.f, 50.f), glm::vec3(), 0.f, glm::vec3(), NULL);

	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(50.f, 4.5f + resize, 45.5f - resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(50.f, 4.5f + resize, 55.5f + resize), glm::vec3(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(4.5f + resize, 4.5f + resize, 50.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("wallTexture"), pCamera, glm::vec3(54.5f + resize, 4.5f + resize, 50.f), glm::vec3(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("ceilingTexture"), pCamera, glm::vec3(50.f, 30.f + resize, 50.f), glm::vec3(), 0.f, glm::vec3(0.f, 0.f, 1.f), NULL);
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-45.25f + resize, 9.55f, 50.f), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f), 'z');
	renderer->Draw(ResourceManager::GetTexture("doorTexture"), pCamera, glm::vec3(-50.f, 9.55f, 4.81f + resize), glm::vec3(0.3f, 0.4f, 0.4f), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f), NULL);

}

void Scene::RenderModels()
{
	ModelShader modelShader("modelLoading.vs", "modelLoading.fs");

	modelShader.use();
	glm::mat4 projectionM = pCamera->GetProjectionMatrix();
	glm::mat4 viewM = pCamera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionM));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(viewM));

	// First Room - ?

	// Second Room - Cristina
	
	glm::mat4 modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(8.0f, 0.5f, -20.0f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(270.0f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(315.0f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Wolf").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-1.0f, 0.5f, -20.0f)); 
	modelM = glm::scale(modelM, glm::vec3(0.22f, 0.22f, 0.22f));
	modelM = glm::rotate(modelM, glm::radians(270.0f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(-350.0f), glm::vec3(0.f, 0.f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Bear").Draw(modelShader);

	// Third Room - Andrei

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(50.f, -0.4f, -15.f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.1f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Spinosaurus").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(37.f, 15.f, -15.f));
	modelM = glm::scale(modelM, glm::vec3(0.04f, 0.04f, 0.04f));
	modelM = glm::rotate(modelM, glm::radians(270.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(0.f, 0.f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Quetzalcoatlus").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(33.f, 35.f, -10.f));
	modelM = glm::scale(modelM, glm::vec3(1.f, 7.2f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Wire").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(41.f, 35.f, -18.f));
	modelM = glm::scale(modelM, glm::vec3(1.f, 7.2f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Wire").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(39.2f, 32.9f, -12.f));
	modelM = glm::scale(modelM, glm::vec3(1.f, 8.2f, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Wire").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(68.7f, 7.3f, -13.f));
	modelM = glm::scale(modelM, glm::vec3(8.f, 7.f, 5.f));
	modelM = glm::rotate(modelM, glm::radians(20.f), glm::vec3(0.f, -0.3f, 0.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Dilophosaurus").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(35.f, -0.3f, 15.f));
	modelM = glm::scale(modelM, glm::vec3(2.f, 3.3f, 1.5f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(315.f), glm::vec3(0.f, 0.f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Barosaurus").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(67.f, -0.35f, 14.f));
	modelM = glm::scale(modelM, glm::vec3(0.08f, 0.1f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f));
	modelM = glm::rotate(modelM, glm::radians(180.f), glm::vec3(0.f, 0.f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Cearadactylus").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(67.3f, -0.4f, 14.f));
	modelM = glm::scale(modelM, glm::vec3(3.f, 3.f, 3.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Podium").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(66.3f, -0.4f, -9.8f));
	modelM = glm::scale(modelM, glm::vec3(4.f, 4.f, 4.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Podium").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(50.f, -0.4f, -16.5f));
	modelM = glm::scale(modelM, glm::vec3(4.f, 4.f, 4.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Podium").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(34.5f, -0.4f, 16.5f));
	modelM = glm::scale(modelM, glm::vec3(4.f, 4.f, 4.f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Podium").Draw(modelShader);

	// Sixth Room - Andrei

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(50.f, -0.5f, 50.f));
	modelM = glm::scale(modelM, glm::vec3(0.07f, 0.07f, 0.07f));
	modelM = glm::rotate(modelM, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Grass").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(50.f, -0.1f, 50.f));
	modelM = glm::scale(modelM, glm::vec3(0.04f, 0.04f, 0.04f));
	modelM = glm::rotate(modelM, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelM = glm::rotate(modelM, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Oak Tree").Draw(modelShader);

	// Fifth Room - Cristina

	rotationAngle += 0.25f;

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-1.5f, 0.f, 50.f));
	modelM = glm::scale(modelM, glm::vec3(0.1f, 0.1f, 0.1f));
	modelM = glm::rotate(modelM, glm::radians(235.f), glm::vec3(1.0f, 1.0f, 1.0f));
	modelM = glm::rotate(modelM, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Vultur").Draw(modelShader);

	modelM = glm::mat4();
	modelM = glm::translate(modelM, glm::vec3(-1.5f, -0.5f, 50.f));
	modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
	modelM = glm::rotate(modelM, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelM));
	models->at("Grass").Draw(modelShader);

	// Fourth Room - ?
}