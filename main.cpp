#include <iostream>
#include "route.hpp"
#include "functions.hpp"
#include "vehicle.hpp"

using namespace std;

int main(){
  int opc;

  vector<Vehicle> vehicles;
  vector<Route> routes;

  srand(time(0));

  string filename = "vehicles_data.txt";
    
  ImportarDadosCarros(vehicles, filename);
  
  for(;;){
    DisplayMenu();
    cin >> opc;
    
    if(opc == 1){
      vehicles.push_back(CadastrarVeiculo(vehicles));
      continue;
    }
    if(opc == 2){
      ExecuteRemoveVehicle(vehicles);
      continue;
    }
    if(opc == 3){
      ExecuteAddRoute(vehicles);
    }
    if(opc == 4){
      ExecuteRemoveRoute(vehicles);
      continue;
    }
    if(opc == 5){
      ShowVehicle(FindVehicle(vehicles), vehicles);
      continue;
    }
    if(opc == 6){
      for(size_t i = 0; i < vehicles.size(); i++){
        ShowVehicle(i, vehicles);
      }
      continue;
    }
    if(opc == 7){
      ExecuteSearchBySubstring(vehicles);
      continue;
    }
    if(opc == 0){
      ExportarDadosCarros(vehicles, filename); 
      cout << "==========================================================================================================" << endl;
      cout << "Goodbye.............................................................." << endl;
      break;
    }
    else{
      cout << "==========================================================================================================" << endl;
      cout << "Invalid option......................................................" << endl;
      continue;
    }
  }
  return 0;
}
