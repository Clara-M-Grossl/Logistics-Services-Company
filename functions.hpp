#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "vehicle.hpp"
#include "route.hpp"


using namespace std;

class Vehicle;

Vehicle CadastrarVeiculo(vector<Vehicle> &vehicles);
int FindVehicle(vector<Vehicle> &vehicles);
void ShowVehicle(size_t index, vector<Vehicle> &vehicles);
bool DeleteVehicle(size_t index, vector<Vehicle> &vehicles);

void Maiuscula(string &str);
float RandomKm();
int FindIndexByPlate(string &plate, vector<Vehicle> &vehicles);

void ImportarDadosCarros(vector<Vehicle> &vehicles, string &filename);
void ExportarDadosCarros(vector<Vehicle> &vehicles, string &filename);
bool AdicionarRota(int i, vector<Vehicle> &vehicles);

void DisplayMenu();
bool ConfirmAction(const string &message);
void ExecuteRemoveVehicle(vector<Vehicle> &vehicles);
void ExecuteAddRoute(vector<Vehicle> &vehicles);
void ExecuteRemoveRoute(vector<Vehicle> &vehicles);
void ExecuteSearchBySubstring(vector<Vehicle> &vehicles);

void DisplaySearchMenu();
int SearchByPlate(vector<Vehicle> &vehicles);
int SearchByIndex(vector<Vehicle> &vehicles);
#endif 