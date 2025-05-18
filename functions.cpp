#include "functions.hpp"

Vehicle CadastrarVeiculo(vector<Vehicle> &vehicles){
  string plate;
  string model;
  string brand;
  float initialKm;

  cin.ignore();
  while(true){
    cout << "Cadastrar Veiculo" << endl;
    cout << "Digite a placa: ";
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
        cout << "ERRO: Placa já cadastrada! Tente novamente." << endl;
    } else {
        break;
    }
  }
  cout << "Digite o modelo: ";
  getline(cin, model);
  Maiuscula(model);

  cout << "Digite a marca: ";
  getline(cin, brand);
  Maiuscula(brand);
  
  initialKm = RandomKm();

  Vehicle newCar(plate, model, brand, initialKm);
  return newCar;
}
int FindVehicle(vector<Vehicle> &vehicles){
  string busca;
  int opc;
  for(;;){
    DisplaySearchMenu();
    if(!(cin >> opc)){
      cin.clear();
      cin.ignore();
      cout << "Opcao invalida" << endl;
    }
    cin.ignore();
    if(opc == 1){
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
        return -1;
    }
    else{
      cout << "Invalid option" << endl;
      break;
    }
  }
  return -1;
}
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
void ShowVehicle(size_t index, vector<Vehicle> &vehicles){
  cout << "ID..................................: " << index << endl;
  cout << "Plate...............................: " << vehicles[index].GetPlate() << endl;
  cout << "Model...............................: " << vehicles[index].GetModel() << endl;
  cout << "Brand...............................: " << vehicles[index].GetBrand() << endl;
  cout << "Initial Kilometers..................: " << vehicles[index].GetInitialKm() << endl;
  cout << "Final Kilometers....................: " << vehicles[index].GetFinalKm() << endl;
  vehicles[index].GetTrip().size() > 0 
  ? cout << "Viagens.............................: " << endl 
    << vehicles[index].GetAllTrips() << endl 
  : cout << "Sem viagens..........................." << endl;
  cout << "============================================================================================" << endl;
}
bool DeleteVehicle(size_t index, vector<Vehicle> &vehicles){
  if (index >= 0 && index < vehicles.size()){
    cout << "Carro (placa: " << vehicles[index].GetPlate() << ") deletado" << endl;
    vehicles.erase(vehicles.begin() + index);
    return true;
  }
  return false;
}
void Maiuscula(string &str){
  size_t index;

  for(index = 0; index < str.size(); index++){
    for(char &c : str){
      c = toupper(c);
    }
  }
}
float RandomKm(){
  return rand() % 74000;
}
void ImportarDadosCarros(vector<Vehicle> &vehicles, string &filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) { // Lê placa
        string plate = line;
        if (!getline(file, line)) break; // Lê modelo
        string model = line;
        if (!getline(file, line)) break; // Lê marca
        string brand = line;
        if (!getline(file, line)) break; // Lê km inicial
        float initialKm = stof(line);

        vehicles.emplace_back(plate, model, brand, initialKm);
        
        // Lê rotas (se houver)
        while (file.peek() == 'R') { // Verifica se a próxima linha começa com 'R' (de ROUTE)
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
}

void ExportarDadosCarros(vector<Vehicle> &vehicles, string &filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Erro ao criar arquivo " << filename << endl;
        return;
    }

    for (Vehicle &v : vehicles) {
        file << v.GetPlate() << "\n"
             << v.GetModel() << "\n"
             << v.GetBrand() << "\n"
             << v.GetInitialKm() << "\n";
        
        // Exporta rotas
        vector<Route*> trips = v.GetTrip();
        for (Route *r : trips) {
            file << "ROUTE,"
                 << r->GetOrigin() << ","
                 << r->GetDestination() << ","
                 << r->GetDistanceKm() << "\n";
        }
    }
    
    file.close();
    cout << "Dados exportados com sucesso para " << filename << endl;
}

bool AdicionarRota(int i, vector<Vehicle> &vehicles){
  string origin;
  string destination;
  float distance;
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
  cout << "Enter distance: ";
  cin >> distance;
  cin.ignore();

  vehicles[i].IncludeTrip(origin, destination, distance);
  return true;
}

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
bool ConfirmAction(const string &message){
  int answer;
  while(true){
    cout << message << endl << "[1] - Sim" << endl << "[2] - Nao" << endl;
    cin >> answer;
    cin.ignore();
    if(answer == 1) return true;
    if(answer == 2){
      cout << "Saindo..........................................." << endl;
      return false;
    }
    cout << "Opcao invalida" << endl;
  }
}
void ExecuteRemoveVehicle(vector<Vehicle> &vehicles){
  int index = FindVehicle(vehicles);
  if(index >= 0){
    ShowVehicle(index, vehicles);
    if(ConfirmAction("Voce deseja excluir esse carro?")){
      if(!DeleteVehicle(index, vehicles)){
        cout << "Indice (" << index << ") nao pertence ao intervalo" << endl;
      }
    }
  }
}
void ExecuteAddRoute(vector<Vehicle> &vehicles){
  cout << "Definir rota para veiculo" << endl;
  int index = FindVehicle(vehicles);
  if(index >= 0){
    ShowVehicle(index, vehicles);
    if(ConfirmAction("Voce deseja adicionar uma rota a esse carro?")){
      if(!AdicionarRota(index, vehicles)){
        cout << "ERRO: Cidade de origem igual a de destino! Tente novamente." << endl;
      }else{
        cout << "Rota implementada" << endl;
      }
    }
  }
}
void ExecuteRemoveRoute(vector<Vehicle> &vehicles){
  int index = FindVehicle(vehicles);
  if(index >= 0){
    size_t i;
    ShowVehicle(index, vehicles);
    cout << "Digite o indice da viagem para excluir: ";
    cin >> i;
    if(i < vehicles[index].GetTrip().size()){
      if(ConfirmAction("Voce deseja excluir essa rota?")){
        if(vehicles[index].DeleteRoute(i)){
          cout << "Rota excluida" << endl;
        } else{
          cout << "Nao foi possivel excluir a rota" << endl;
        }
      }
    }
    else{
      cout << "Indice (" << i << ") nao pertence ao intervalo" << endl;
    }
  }
}
void ExecuteSearchBySubstring(vector<Vehicle> &vehicles){
  string town;
  cin.ignore();
  cout << "Find Trip" << endl;
  cout << "Nome da cidade (origem/destino)......................: ";
  getline(cin, town);
  Maiuscula(town);

  for(size_t i = 0; i < vehicles.size(); i++){
    string result = vehicles[i].SearchTripBySubstring(town);
    if(!result.empty()){
      cout << result;
      ShowVehicle(i, vehicles);
    }
  }
}

void DisplaySearchMenu(){
  cout << "Escolha: " << endl;
  cout << "[1] - Busca por placa." << endl;
  cout << "[2] - Busca por indice." << endl;
  cout << "[0] - Sair" << endl;
  cout << ">> ";
}
int SearchByPlate(vector<Vehicle> &vehicles){
  cout << "Digite a placa........................: ";
  string plate;
  getline(cin, plate);
  Maiuscula(plate);

  int index = FindIndexByPlate(plate, vehicles);
  if(index == -1){
    cout << "Placa (" << plate << ") nao encontrada!" << endl;
  }
  return index;
}
int SearchByIndex(vector<Vehicle> &vehicles){
  cout << "Digite o indice........................: ";
  size_t index;

  if(!(cin >> index)){
    cin.ignore();
    cout << "Entrada invalida" << endl;
    return -1;
  }
  if (index >= vehicles.size()){
    cout << "Indice (" << index << ") nao pertence ao intervalo" << endl;
    return -1;
  }
  return static_cast<int>(index);
}