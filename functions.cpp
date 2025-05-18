#include "functions.hpp"

// FUNÇÕES MENU
void DisplayMenu(){
  cout << "============================================================================================" << endl;
  cout << "Logistics Services Company" << endl;
  cout << "[1] - Register Vehicle" << endl;
  cout << "[2] - Remove Vehicle" << endl;
  cout << "[3] - Add Route to a Vehicle" << endl;
  cout << "[4] - Remove Route from a Vehicle" << endl;
  cout << "[5] - Vehicle Report" << endl;
  cout << "[6] - General Report" << endl;
  cout << "[7] - Search by Substring" << endl;
  cout << "[0] - Exit" << endl;
  cout << ">> ";
}

void DisplaySearchMenu(){
  cout << "Chose: " << endl;
  cout << "[1] - Search by license plate." << endl;
  cout << "[2] - Search by index." << endl;
  cout << "[0] - Exit" << endl;
  cout << ">> ";
}

// EXECUTAR FUNÇÕES
void ExecuteRemoveVehicle(vector<Vehicle> &vehicles){
  int index = FindVehicle(vehicles);
  if(index >= 0){
    ShowVehicle(index, vehicles);
    if(ConfirmAction("Do you want to delete this vehicle")){
      if(!DeleteVehicle(index, vehicles)){
        cout << "Index (" << index << ") is out of range" << endl;
      }
    }
  }
}

void ExecuteAddRoute(vector<Vehicle> &vehicles){
  cout << "Set route for vehicle" << endl;
  int index = FindVehicle(vehicles);
  if(index >= 0){
    ShowVehicle(index, vehicles);
    if(ConfirmAction("Do you want to add a route to this car")){
      if(!AdicionarRota(index, vehicles)){
        cout << "ERROR: Origin city is the same as destination city! Please try again." << endl;
      }else{
        cout << "Route implemented!" << endl;
      }
    }
  }
}

void ExecuteRemoveRoute(vector<Vehicle> &vehicles){
  int index = FindVehicle(vehicles);
  if(index >= 0){
    size_t i;
    ShowVehicle(index, vehicles);
    cout << "Enter the trip index to delete......:";
    if(!(cin >> i)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number." << endl;
      return;
    }
    if(i < vehicles[index].GetTrip().size()){
      if(ConfirmAction("Do you want to delete this route")){
        if(vehicles[index].DeleteRoute(i)){
          cout << "Route deleted!" << endl;
        } else{
          cout << "ERROR: Could not delete the route!" << endl;
        }
      }
    }
    else{
      cout << "Index (" << i << ") is out of range" << endl;
    }
  }
}

void ExecuteSearchBySubstring(vector<Vehicle> &vehicles){
  string town;
  cin.ignore();
  cout << "Find Trip" << endl;
  cout << "City name (origin/destination)......: ";
  getline(cin, town);
  Maiuscula(town);

  bool found = false;
  vector<size_t> indexVehicles;

  cout << "SEARCH RESULTS:" << endl << "==============================================" << endl;

  for(size_t i = 0; i < vehicles.size(); i++){
    string result = vehicles[i].SearchTripBySubstring(town);
    if(!result.empty()){
      if(!found){
        found = true;
      }
      cout << result;
      indexVehicles.push_back(i);
    }
  }
  if (!found) {
    cout << "No trips found for city: " << town << endl;
  }
  if (found) {
    cout << "VEHICLES WITH THESE ROUTES: " << endl << "==============================================" << endl;
    for (size_t i : indexVehicles) {
        ShowVehicle(i, vehicles);
      }
  }
}

bool ConfirmAction(const string &message){
  int answer;
  while(true){
    cout << message << endl << "[1] - Yes" << endl << "[2] - No" << endl;
    if(!(cin >> answer)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number." << endl;
      continue;
    }
    cin.ignore();
    if(answer == 1) return true;
    if(answer == 2){
      cout << "Exiting..........................................." << endl;
      return false;
    }
    cout << "Invalid option! Please try again" << endl;
  }
}

// CADASTRAR VEICULO
Vehicle CadastrarVeiculo(vector<Vehicle> &vehicles){
  string plate;
  string model;
  string brand;
  float initialKm;

  cin.ignore();
  while(true){
    cout << "Register a Vehicle" << endl;
    cout << "Enter the license plate.............: ";
    getline(cin, plate);
    Maiuscula(plate);

    bool placaRepetida = false;
        
    for(Vehicle &veiculo : vehicles) {
        if(veiculo.GetPlate() == plate) {
            placaRepetida = true;
            break;
        }
    }
    if(placaRepetida) {
        cout << "ERROR: License plate already registered! Please try again." << endl;
    } else {
        break;
    }
  }
  cout << "Enter the model.....................: ";
  getline(cin, model);
  Maiuscula(model);

  cout << "Enter the brand.....................: ";
  getline(cin, brand);
  Maiuscula(brand);
  
  initialKm = RandomKm();

  Vehicle newCar(plate, model, brand, initialKm);
  return newCar;
}

// FUNÇÕES RELACIONADAS AO VEICULO
int FindVehicle(vector<Vehicle> &vehicles){
  string busca;
  int opc;
  for(;;){
    DisplaySearchMenu();
    if(!(cin >> opc)){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input! Please enter a number." << endl;
      break;
    }
    if(opc == 1){
      cin.ignore();
      if(int index = SearchByPlate(vehicles); index != -1){
        return index;
      }
      break;
    }
    else if(opc == 2){
      if(int index = SearchByIndex(vehicles); index != -1){
        return index;
      }
    }
    else if(opc == 0){
        cout << "Goodbye.............................................................." << endl;
        break;
    }
    else{
      cout << "Invalid option! Please try again" << endl;
      break;
    }
  }
  return -1;
}

void ShowVehicle(size_t index, vector<Vehicle> &vehicles){
  cout << "ID..................................: " << index << endl;
  cout << "Plate...............................: " << vehicles[index].GetPlate() << endl;
  cout << "Model...............................: " << vehicles[index].GetModel() << endl;
  cout << "Brand...............................: " << vehicles[index].GetBrand() << endl;
  cout << "Initial Kilometers..................: " << vehicles[index].GetInitialKm() << endl;
  cout << "Final Kilometers....................: " << vehicles[index].GetFinalKm() << endl;
  vehicles[index].GetTrip().size() > 0 
  ? cout << "Trips...............................: \n------------------------------------------------------------------" << endl 
    << vehicles[index].GetAllTrips() << endl 
  : cout << "No trips............................." << endl;
  cout << "============================================================================================" << endl;
}

bool DeleteVehicle(size_t index, vector<Vehicle> &vehicles){
  if (index >= 0 && index < vehicles.size()){
    cout << "Vehicle (license plate: " << vehicles[index].GetPlate() << ") deleted" << endl;
    vehicles.erase(vehicles.begin() + index);
    return true;
  }
  return false;
}

bool AdicionarRota(int i, vector<Vehicle> &vehicles){
  string origin;
  string destination;
  bool origemDest = false;
  while(true){
    cout << "Enter origin: ";
    getline(cin, origin);
    Maiuscula(origin);

    cout << "Enter destination: ";
    getline(cin, destination);
    Maiuscula(destination);

    if(origin == destination){
      origemDest = true;
      break;
    }
    break;
  }
  if(origemDest) {
      return false;
  }
  
  float distance = GetValidDistance();
  vehicles[i].IncludeTrip(origin, destination, distance);
  return true;
}

// FUNÇÕES DE BUSCA
int FindIndexByPlate(string &plate, vector<Vehicle> &vehicles){
  size_t index = 0;
  for(Vehicle &v : vehicles){
    if(v.GetPlate() == plate){
      return index;
    }
    index ++;
  }
  return -1;
}

int SearchByPlate(vector<Vehicle> &vehicles){
  cout << "Enter the license plate.............: ";
  string plate;
  getline(cin, plate);
  Maiuscula(plate);

  int index = FindIndexByPlate(plate, vehicles);
  if(index == -1){
    cout << "License plate (" << plate << ") not found!" << endl;
  }
  return index;
}

int SearchByIndex(vector<Vehicle> &vehicles){
  cout << "Enter the index.....................: ";
  size_t index;

  if(!(cin >> index)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid option! Please try again." << endl;
    return -1;
  }
  if (index >= vehicles.size()){
    cout << "Index (" << index << ") is out of range" << endl;
    return -1;
  }
  return static_cast<int>(index);
}

// FUNÇÕES DE FORMATAÇÃO/CHECAGEM
void Maiuscula(string &str){
  size_t index;

  for(index = 0; index < str.size(); index++){
    for(char &c : str){
      c = toupper(c);
    }
  }
}

float GetValidDistance() {
    float distance;
    while (true) {
        cout << "Enter distance: ";
        if (cin >> distance) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return distance;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number." << endl;
        }
    }
}

float RandomKm(){
  return rand() % 25000;
}

//FUNÇÕES DE ARQUIVO
void ImportarDadosCarros(vector<Vehicle> &vehicles, string &filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string plate = line;
        if (!getline(file, line)) break;
        string model = line;
        if (!getline(file, line)) break;
        string brand = line;
        if (!getline(file, line)) break;
        float initialKm = stof(line);

        vehicles.emplace_back(plate, model, brand, initialKm);
        
        while (file.peek() == 'R') {
            getline(file, line);
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            
            string origin = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string dest = line.substr(pos2 + 1, pos3 - pos2 - 1);
            float distance = stof(line.substr(pos3 + 1));
            
            vehicles.back().IncludeTrip(origin, dest, distance);
        }
    }
    
    file.close();
    cout << "Data successfully imported from " << filename << endl;
}

void ExportarDadosCarros(vector<Vehicle> &vehicles, string &filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error creating file " << filename << endl;
        return;
    }

    for (Vehicle &v : vehicles) {
        file << v.GetPlate() << "\n"
             << v.GetModel() << "\n"
             << v.GetBrand() << "\n"
             << v.GetInitialKm() << "\n";
        
        vector<Route*> trips = v.GetTrip();
        for (Route *r : trips) {
            file << "ROUTE,"
                 << r->GetOrigin() << ","
                 << r->GetDestination() << ","
                 << r->GetDistanceKm() << "\n";
        }
    }
    
    file.close();
    cout << "Data successfully exported to " << filename << endl;
}
