#include "Globals.h"

void NewWindow::WindowCode() {

}
     NewWindow::NewWindow(const char* _windowTitle) {
		 windowTitle = _windowTitle;
	 }
void NewWindow::Run() {
	ImGui::Begin(windowTitle, NULL, ImGuiWindowFlags_AlwaysAutoResize);
	// eventual de adaugat parametrii

	WindowCode();

	ImGui::End();
}

     Matrice::Matrice(std::string _nume, const char* _windowTitle)
		 : NewWindow(_windowTitle)
	 {
	values.resize(1, std::vector<float>(1, 0.0f));
	nume = _nume;
}
void Matrice::WindowCode() {
	using namespace ImGui;

	int matrixSize = values.size();
	if (Button("Increase") && matrixSize < 10) {
		values.push_back(std::vector<float>(matrixSize, 0));
		matrixSize++;
		for (int i = 0; i < matrixSize; i++) {
			values[i].push_back(0);
		}
	}
	SameLine();
	if (Button("Decrease") && matrixSize > 1) {
		values.pop_back();
		matrixSize--;
		for (int i = 0; i < matrixSize; i++) {
			values[i].pop_back();
		}
	}

	int inputWidth = 40;
	PushItemWidth(inputWidth);
	// resize not working properly 
	for (int n = 0; n < matrixSize * matrixSize; n++)
	{
		PushID(n);
		InputFloat(" ", &values[n / matrixSize][n % matrixSize], 0, 0, "%.2f", ImGuiInputTextFlags_AutoSelectAll);
		if ((n + 1) % matrixSize != 0) {
			SameLine();
		}
		PopID();
	}
}

     Operatii::Operatii(Matrice* X, Matrice* Y, const char* _windowTitle)
		 : NewWindow(_windowTitle) {
	thisMatrix = &(X->values);
	otherMatrix = &(Y->values);
	buttonTexts.push_back(std::string("x " + X->nume));
	buttonTexts.push_back(std::string(X->nume + " + " + Y->nume));
	buttonTexts.push_back(std::string(X->nume + " - " + Y->nume));
}
void Operatii::InmultireConstanta() {
	Matrix matrix = *thisMatrix;

	using namespace ImGui;

	PushItemWidth(80);
	InputFloat(" ", &constanta, 0, 0, "%.2f", ImGuiInputTextFlags_AutoSelectAll);
	SameLine();
	if (Button(buttonTexts[0].c_str())) {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				matrix[i][j] *= constanta;
			}
		}
		rezultate.push_back(MatriceRezultat(matrix));
	}
}
void Operatii::Adunare() {
	Matrix A = *thisMatrix, B = *otherMatrix;

	using namespace ImGui;
	if (Button(buttonTexts[1].c_str())) {
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			eroare.UpdateMessage("Dimensiunile matricilor trebuie sa fie identice");
			return;
		}

		Matrix C;
		C.resize(A.size(), std::vector<float>(A[0].size()));
		for (int i = 0; i < C.size(); i++) {
			for (int j = 0; j < C[0].size(); j++) {
				C[i][j] = A[i][j] + B[i][j];
			}
		}
		rezultate.push_back(MatriceRezultat(C));
	}
}
void Operatii::Scadere() {
	Matrix A = *thisMatrix, B = *otherMatrix;

	using namespace ImGui;

	if (Button(buttonTexts[2].c_str())) {
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			eroare.UpdateMessage("Dimensiunile matricilor trebuie sa fie identice");
			return;
		}

		Matrix C;
		C.resize(A.size(), std::vector<float>(A[0].size()));
		for (int i = 0; i < C.size(); i++) {
			for (int j = 0; j < C[0].size(); j++) {
				C[i][j] = A[i][j] - B[i][j];
			}
		}
		rezultate.push_back(MatriceRezultat(C));
	}
}
void Operatii::WindowCode() {
	using namespace ImGui;

	InmultireConstanta();
	Adunare();
	Scadere();
}

int  MatriceRezultat::contor = 0;
     MatriceRezultat::MatriceRezultat(Matrix X) {
	matrix = X;
	contor++;
	title = "Rezultat " + std::to_string(contor);
}
void MatriceRezultat::CreateWindow() {
	using namespace ImGui;

	ImGui::Begin(title.c_str(), &running, ImGuiWindowFlags_AlwaysAutoResize);

	int inputWidth = 40;
	PushItemWidth(inputWidth);
	// resize not working properly 
	for (int n = 0; n < matrix.size() * matrix.size(); n++)
	{
		PushID(n);
		InputFloat(" ", &matrix[n / matrix.size()][n % matrix.size()], 0, 0, "%.2f", ImGuiInputTextFlags_ReadOnly);
		if ((n + 1) % matrix.size() != 0) {
			SameLine();
		}
		PopID();
	}

	ImGui::End();
}

void Eroare::UpdateMessage(std::string _message) {
	message = _message;
	running = true;
}
void Eroare::CreateWindow() {
	using namespace ImGui;
	if (!running) {
		return;
	}
	else {
		OpenPopup("Eroare");
	}

	SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f),
		ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("Eroare", &running, 
		ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {

		Text((const char*)message.c_str());
		ImGui::EndPopup();
	}
}