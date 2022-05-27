#pragma once

#ifndef FUNCTII
#define FUNCTII

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<std::vector<float>> Matrix;

class NewWindow {
protected:
	char* title; // to be fixed
	virtual void WindowCode();
public:
	//NewWindow(const char* _title); // same as above
	void CreateWindow(const char* _title);
};

class Matrice : public NewWindow {
public:
	Matrix values;
	Matrice();
	void WindowCode() override;
};

class MatriceRezultat {
private:
	char* title;
public:
	static int contor;
	bool running = true;
	Matrix matrix;
	MatriceRezultat(Matrix X);
	char* GenerateID();
	void CreateWindow();
};

class Operatii : public NewWindow {
private:
	float constanta = 1;
public:
	Matrix* thisMatrix;
	Matrix* otherMatrix;
	Operatii(Matrix* X, Matrix* Y);
	void InmultireConstanta();
	void Adunare();
	void Scadere();
	void WindowCode() override;
};

class Eroare {
private:
	std::string message;
public:
	void UpdateMessage(std::string _message);
	bool running = false;
	void CreateWindow();
};

#endif