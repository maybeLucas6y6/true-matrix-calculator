#include "Functii.h"  // can be left out??
#include "Globals.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Matrix Calculator", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//eroare.UpdateMessage("Test foarte foarte foarte lung");
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// --------------------------------------

		A.CreateWindow("Matrice A");
		B.CreateWindow("Matrice B");
		_A.CreateWindow("Operatii A");
		_B.CreateWindow("Operatii B");
		for (int i = 0; i < rezultate.size(); i++) {
			if (!rezultate[i].running) {
				std::swap(rezultate[i], rezultate[rezultate.size() - 1]);
				rezultate[i].contor--;
				rezultate.pop_back();
			}
			else {
				rezultate[i].CreateWindow();
			}
		}

		eroare.CreateWindow();

		// --------------------------------------

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}