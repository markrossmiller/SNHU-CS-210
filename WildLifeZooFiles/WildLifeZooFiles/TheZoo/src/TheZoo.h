#include <iostream>
#include <jni.h>
#include "Animal.h"
using namespace std;

void GenerateData();
void AddAnimal(vector <Animal *> animal_v);
void RemoveAnimal(vector <Animal *> animal_v, string track);
vector <Animal *> LoadDataFromFile();
void SaveDataToFile(vector <Animal *> animal_v);
void DisplayMenu(vector <Animal *> animal_v);
void DisplayAnimalData(vector <Animal *> animal_v);
