#include "Functii.h"

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
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	Matrice A, B;
	Operatii _A(&A.values, &B.values), _B(&B.values, &A.values);
	
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
		for (int i = 0; i < erori.size(); i++) {
			if (!erori[i].running) {
				std::swap(erori[i], erori[rezultate.size() - 1]);
				erori.pop_back();
			}
			else {
				erori[i].CreateWindow();
			}
		}

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