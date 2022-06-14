#pragma once

#ifndef FUNCTII
#define FUNCTII

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>
#include <list>
#include <string>

typedef std::vector<std::vector<float>> Matrix;

class NewWindow {
protected:
	const char* windowTitle;
	virtual void WindowCode();
public:
	NewWindow(const char* _windowTitle);
	void Run();
};

class Matrice : public NewWindow {
public:
	Matrix values;
	std::string nume;
	Matrice(std::string _nume, const char* _windowTitle);
	void WindowCode() override;
};

class MatriceRezultat {
private:
	std::string title;
public:
	static int contor;
	bool running = true;
	Matrix matrix;
	MatriceRezultat(Matrix X);
	void CreateWindow();
};

class Operatii : public NewWindow {
private:
	float constanta = 1;
	std::vector<std::string> buttonTexts;
public:
	Matrix* thisMatrix;
	Matrix* otherMatrix;
	Operatii(Matrice* X, Matrice* Y, const char* _windowTitle);
	void InmultireConstanta();
	void Adunare();
	void Scadere();
	void WindowCode() override;
};

class Eroare {
private:
	std::string message;
public:
	bool running = false;
	void UpdateMessage(std::string _message);
	void CreateWindow();
};

#endif