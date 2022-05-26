#include "Functii.h"

std::vector<MatriceRezultat> rezultate;

// #define GET_VARIABLE_NAME(Variable) (#Variable)
// test

void NewWindow::WindowCode() {

}
void NewWindow::CreateWindow(const char* _title) {
	ImGui::Begin(_title, NULL, ImGuiWindowFlags_AlwaysAutoResize);

	WindowCode();

	ImGui::End();
}

     Matrice::Matrice() {
	values.resize(1, std::vector<float>(1, 0.0f));
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

     Operatii::Operatii(Matrix* X, Matrix* Y) {
	thisMatrix = X;
	otherMatrix = Y;
}
void Operatii::InmultireConstanta() {
	Matrix matrix = *thisMatrix;

	using namespace ImGui;

	PushItemWidth(80);
	InputFloat(" ", &constanta, 0, 0, "%.2f", ImGuiInputTextFlags_AutoSelectAll);
	SameLine();
	if (Button("Inmulteste cu constanta")) {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				matrix[i][j] *= constanta;
			}
		}
		MatriceRezultat tmp(matrix);
		rezultate.push_back(tmp);
	}
}
void Operatii::Adunare() {
	Matrix A = *thisMatrix, B = *otherMatrix;

	using namespace ImGui;

	if (Button("Aduna cu ")) { // de completat " "
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			// popup
			return;
		}

		Matrix C;
		C.resize(A.size(), std::vector<float>(A[0].size()));
		for (int i = 0; i < C.size(); i++) {
			for (int j = 0; j < C[0].size(); j++) {
				C[i][j] = A[i][j] + B[i][j];
			}
		}
		MatriceRezultat tmp(C);
		rezultate.push_back(tmp);
	}
}
void Operatii::Scadere() {
	Matrix A = *thisMatrix, B = *otherMatrix;

	using namespace ImGui;

	if (Button("Scade ")) { // de completat " "
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			// popup
			return;
		}

		Matrix C;
		C.resize(A.size(), std::vector<float>(A[0].size()));
		for (int i = 0; i < C.size(); i++) {
			for (int j = 0; j < C[0].size(); j++) {
				C[i][j] = A[i][j] - B[i][j];
			}
		}
		MatriceRezultat tmp(C);
		rezultate.push_back(tmp);
	}
}
void Operatii::WindowCode() {
	using namespace ImGui;

	InmultireConstanta();
	Adunare();
	Scadere();
}

int   MatriceRezultat::contor = 0;
      MatriceRezultat::MatriceRezultat(Matrix X) {
	matrix = X;
	contor++;
	char* newTitle;
	char* id = GenerateID();
	newTitle = new char[50];
	strcpy_s(newTitle, 50, "Rezultat ");
	strcat_s(newTitle, 50, id);
	title = newTitle;
}
char* MatriceRezultat::GenerateID() {
	std::string tmp1 = std::to_string(contor);
	const char* tmp2 = tmp1.c_str();
	char* newID = _strdup(tmp2);
	return newID;
}
void  MatriceRezultat::CreateWindow() {
	using namespace ImGui;

	ImGui::Begin(title, &running, ImGuiWindowFlags_AlwaysAutoResize);

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