#include "PreImports.h"
#include "util/model/RenderUtil.h"
#include "util/GenericUtil.h"
#include "util/Logger.h"
#include "util/GameConstants.h"
#include "util/model/Shader.h"
#include "objects/GameObject.h"
#include "objects/type/Player.h"
#include "misc/Keybind.h"
#include "util/Keybinds.h"
#include "util/Profiler.h"
#include "world/World.h"

#include <stb_image.h>
#include <CGAL/basic.h>
#include <CGAL/Polygon_mesh_processing/intersection.h>

#include "ui/WorldEditorGui.h"
#include "world/CollisionLoader.h"

#include "misc/Config.h"

//the bin folder contents needs to be copied!

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void renderQuad();

unsigned int postFBO = 0;
unsigned int colorBuffer = 0;
unsigned int rboDepth = 0;

int stride = 8;
std::map<std::string, std::string> args;
std::chrono::high_resolution_clock::time_point lastFrameTime;

struct Light {
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

std::vector<Light> lights;

int main(int argc, char *argv[]) {
	Logger logger;
	cout << "[INFO] [Main] Game loading..." << endl;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg.starts_with("--")) {
			std::string key = arg.substr(2);
			if (i + 1 < argc && std::string(argv[i + 1]).starts_with("--") == false) {
				args[key] = argv[++i];
			} else {
				args[key] = "true";
			}
		}
	}

	GameConstants::debug = args.contains("debug");

	Config::load();

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow *window = glfwCreateWindow(GameConstants::window_width, GameConstants::window_height, "Dungeon Game (Loading...)",
	                                      NULL, NULL);
	GameConstants::window = window;
	if (!window) {
		std::cerr << "[ERROR] [Main] Couldn't create the window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glEnable(GL_DEPTH_TEST);

	if (const GLenum err = glewInit(); err != GLEW_OK) {
		std::cerr << "[ERROR] [Main] GLEW init failed: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void) io;

	// Setup ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	GLFWimage *icon = RenderUtil::getImageData("src/resources/textures/ui/icon");
	glfwSetWindowIcon(window, 1, icon);
	stbi_image_free(icon->pixels);
	delete icon;

	GameConstants::foregroundShader = Shader("foreground");
	GameConstants::backgroundShader = Shader("background");
	GameConstants::simpleShader = Shader("simple");
	GameConstants::objectShader = Shader("object");
	GameConstants::textShader = Shader("text");
	GameConstants::uiShader = Shader("ui");
	GameConstants::postProcessor = Shader("post");
	GameConstants::postProcessor.use();
	GameConstants::postProcessor.setInt("hdrBuffer", 0);

	RenderUtil::genOrLoadAtlas(true);

	CollisionLoader::loadCollisionMaps();

	glm::vec3 lightPos(1.5f, 1.0f, -2.3f);

	cout << "[INFO] [Game] Game loaded!" << endl;
	cout << "[INFO] [Game] Game took " << glfwGetTime() << " seconds to start!" << endl;

	GameConstants::world = World();
	GameConstants::player = std::make_shared<Player>(glm::vec3(0, 0, 0));;
	GameConstants::world.addObject(std::static_pointer_cast<GameObject>(GameConstants::player));

	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
		lastFrameTime = now;

		auto oldProfilerResults = Profiler::getResults();

		Profiler::fpsHistory[Profiler::fpsIndex % 100] = 1.0f / std::max(deltaTime, 0.0001f);
		Profiler::fpsIndex++;

		Profiler::beginFrame();

		Profiler::beginSection("ImGui");
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Inventory");
		ImGui::Text("You have %d apples", 5);
		ImGui::End();

		ImGui::Begin("Debug options");
		ImGui::SeparatorText("Game");
		ImGui::Checkbox("Wireframe", &GameConstants::wireframe);
		ImGui::Checkbox("Show AABB's", &GameConstants::debugCollision);
		ImGui::Checkbox("Post-Processing", &GameConstants::postProcessingEnabled);
		const char* debugRenderModes[] = {"Default", "Simple", "Normal", "Metal", "Rough", "Emissive", "TexCoords"};
		ImGui::ListBox("Debug render mode", &GameConstants::debugRenderMode, debugRenderModes, IM_ARRAYSIZE(debugRenderModes));
		ImGui::InputInt("FPS", &GameConstants::targetFPS);

		ImGui::SeparatorText("Player");
		if (ImGui::Button("Launch"))
			for (const auto &object: GameConstants::world.getObjects()) {
				object->velocity = glm::vec3(5, 5, 5);
			};
		ImGui::End();

		ImGui::Begin("Profiler");
		ImGui::PlotLines("FPS", Profiler::fpsHistory, 100, 0, nullptr, 0.0f, 120, ImVec2(0, 80));

		for (const auto &[name, res]: oldProfilerResults) {
			ImGui::Text("%s: %.3f s (%.3f ms avg, %d calls)", name.c_str(),
			            res.totalTime / 1000.0f,
			            res.totalTime / res.callCount,
			            res.callCount);
		}
		ImGui::End();
		Profiler::endSection("ImGui");

		static WorldGameObjectsEditor gameObjectsEditor;
		gameObjectsEditor.draw();

		logger.render();

		if (GameConstants::wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		Profiler::beginSection("Input");
		for (auto &k: GameConstants::keybindsManager.keybinds) k->update(window);
		glfwSetInputMode(window, GLFW_CURSOR,
		                 !GameConstants::keybindsManager.TOGGLE_CURSOR->isPressed() && !GameConstants::debugging
			                 ? GLFW_CURSOR_DISABLED
			                 : GLFW_CURSOR_NORMAL);
		Profiler::endSection("Input");

		Profiler::beginSection("World Tick");
		GameConstants::world.tick(deltaTime);
		Profiler::endSection("World Tick");

		auto model = glm::mat4(1.0f);
		auto view = glm::mat4(1.0f);

		glm::mat4 projection;
		//dont divide by 0
		int fbWidth, fbHeight;
		glfwGetFramebufferSize(GameConstants::window, &fbWidth, &fbHeight);
		float aspect = (fbHeight > 0) ? (float) fbWidth / fbHeight : 4.0f / 3.0f;

		projection = glm::ortho(0.0f, (float)fbWidth, 0.0f, (float)fbHeight, -1.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		Profiler::beginSection("Main");
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Profiler::beginSection("Render");
		GameConstants::world.drawWorld(projection);
		Profiler::endSection("Render");

		//disables gamma correction, so colours aren't washed out
		if (GameConstants::debugging) {
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}


		Profiler::endSection("Main");

		ImGui::EndFrame();

		Profiler::beginSection("GLFW Render");
		glfwSwapBuffers(window);
		glfwPollEvents();
		Profiler::endSection("GLFW Render");

		string title = ("Dungeon Game!!!");
		glfwSetWindowTitle(window, title.c_str());

		Profiler::beginSection("Sleep");
		float targetFrameTime = 1.0f / GameConstants::targetFPS;
		auto sleepDuration = targetFrameTime - deltaTime;
		if (sleepDuration > 0.002f) {
			std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::duration<float>(sleepDuration)
			));
		}
		Profiler::endSection("Sleep");

		Profiler::endFrame();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	glfwSetWindowSize(window, width, height);
	GameConstants::window_width = width;
	GameConstants::window_height = height;

	glBindTexture(GL_TEXTURE_2D, colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	if (!GameConstants::keybindsManager.TOGGLE_CURSOR->isPressed() && !GameConstants::debugging) {
		int windowX;
		int windowY;
		float maxSensitivity = 50.0f;
		float sensitivity = 50.0f;
		glfwGetWindowPos(window, &windowX, &windowY);

		// //we dont wan NaN from /0
		// GameConstants::player->yaw -= (xpos - (windowX + GameConstants::window_width / 2)) / max(
		// 			maxSensitivity - sensitivity, 1.0f) /
		// 		20;
		// GameConstants::player->pitch -= (ypos - (windowY + GameConstants::window_height / 2)) / max(
		// 			maxSensitivity - sensitivity, 1.0f)
		// 		/ 20;
		//
		// GameConstants::player->yaw = glm::mod(GameConstants::player->yaw, 360.0f);
		// GameConstants::player->pitch = glm::clamp(GameConstants::player->pitch, -89.0f, 89.0f);

		glfwSetCursorPos(window, windowX + GameConstants::window_width / 2, windowY + GameConstants::window_height / 2);
	}
}