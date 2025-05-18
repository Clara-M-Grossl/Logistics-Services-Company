#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <limits>

#include "vehicle.hpp"
#include "route.hpp"


using namespace std;

class Vehicle;

// FUNÇÕES MENU
void DisplayMenu();
void DisplaySearchMenu();

// EXECUTAR FUNÇÕES
void ExecuteRemoveVehicle(vector<Vehicle> &vehicles);
void ExecuteAddRoute(vector<Vehicle> &vehicles);
void ExecuteRemoveRoute(vector<Vehicle> &vehicles);
void ExecuteSearchBySubstring(vector<Vehicle> &vehicles);
bool ConfirmAction(const string &message);

// CADASTRAR VEICULO
Vehicle CadastrarVeiculo(vector<Vehicle> &vehicles);

// FUNÇÕES RELACIONADAS AO VEICULO
int FindVehicle(vector<Vehicle> &vehicles);
void ShowVehicle(size_t index, vector<Vehicle> &vehicles);
bool DeleteVehicle(size_t index, vector<Vehicle> &vehicles);
bool AdicionarRota(int i, vector<Vehicle> &vehicles);

// FUNÇÕES DE BUSCA
int FindIndexByPlate(string &plate, vector<Vehicle> &vehicles);
int SearchByPlate(vector<Vehicle> &vehicles);
int SearchByIndex(vector<Vehicle> &vehicles);

// FUNÇÕES DE FORMATAÇÃO/CHECAGEM
void Maiuscula(string &str);
float GetValidDistance();
float RandomKm();

//FUNÇÕES DE ARQUIVO
void ImportarDadosCarros(vector<Vehicle> &vehicles, string &filename);
void ExportarDadosCarros(vector<Vehicle> &vehicles, string &filename);

#endif 