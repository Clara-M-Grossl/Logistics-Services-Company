#include "vehicle.hpp"
#include "functions.hpp"
#include "route.hpp"

int main(){
  int opc;
  vector<Vehicle> vehicles;
  vector<Route> routes;
  string filename = "vehicles_data.txt";

  srand(time(0));
  
  ImportarDadosCarros(vehicles, filename);
  
  for(;;){
    DisplayMenu();
    if(!(cin >> opc)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number." << endl;
      continue;
    }
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
      continue;
    }
    if(opc == 4){
      ExecuteRemoveRoute(vehicles);
      continue;
    }
    if(opc == 5){
      int i = FindVehicle(vehicles);
      if(i >= 0){
        ShowVehicle(i, vehicles);
      }
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
      cout << "Invalid option! Please try again." << endl;
      continue;
    }
  }
  return 0;
}