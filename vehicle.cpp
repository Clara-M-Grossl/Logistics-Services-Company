#include "vehicle.hpp"

Vehicle::Vehicle(){
  
}
Vehicle::Vehicle(string plate, string model, string brand, float initialKm){
  m_plate = plate;
  m_model = model;
  m_brand = brand;
  m_initialKm = initialKm;
  m_finalKm = initialKm;
}
Vehicle::~Vehicle(){
  for (Route* route : m_trips) {
      delete route;  // Manually free each Route
  }
}
Vehicle::Vehicle(const Vehicle& other) 
    : m_plate(other.m_plate),
      m_model(other.m_model),
      m_brand(other.m_brand),
      m_initialKm(other.m_initialKm),
      m_finalKm(other.m_finalKm) 
{
    for (const Route* route : other.m_trips) {
        m_trips.push_back(new Route(*route));
    }
}
Vehicle& Vehicle::operator=(const Vehicle& other) {
  if (this != &other) {
      for (Route* route : m_trips) {
          delete route;
      }
      m_trips.clear();

      m_plate = other.m_plate;
      m_model = other.m_model;
      m_brand = other.m_brand;
      m_initialKm = other.m_initialKm;
      m_finalKm = other.m_finalKm;

      for (const Route* route : other.m_trips) {
          m_trips.push_back(new Route(*route));
      }
  }
  return *this;
}

string Vehicle::SearchTripBySubstring(string wordToSearch){
  stringstream stream;
  for(size_t i = 0; i < m_trips.size(); i++){
    if(m_trips[i]->GetOrigin().find(wordToSearch) != string::npos ||m_trips[i]->GetDestination().find(wordToSearch) != string::npos){
      stream << "Origem...........................: " << m_trips[i]->GetOrigin() << "\nDestino...........................: " << 
      m_trips[i]->GetDestination() << "\nDistancia...........................: " << m_trips[i]->GetDistanceKm() << "\n------------------------------------------------------------------\n";
    }
  }
  return stream.str();
}
string Vehicle::GetAllTrips(){
  stringstream stream;
  
  for(size_t i = 0; i < m_trips.size(); i++){
    stream << "Origem.............................: " << m_trips[i]->GetOrigin() << "\nDestino.............................: " << 
    m_trips[i]->GetDestination() << "\nDistancia............................: " << m_trips[i]->GetDistanceKm() << "\n------------------------------------------------------------------\n";
  }
  return stream.str();
}
string Vehicle::GetPlate(){
  return m_plate;
}
string Vehicle::GetModel(){
  return m_model;
}
string Vehicle::GetBrand(){
  return m_brand;
}
float Vehicle:: GetInitialKm(){
  return m_initialKm;
}
float Vehicle::GetFinalKm(){
  return m_finalKm;
}
void Vehicle::IncludeTrip(string &origin, string &destination, float distance){
  m_trips.push_back(new Route(origin, destination, distance));
  m_finalKm += distance;
}
vector<Route*> Vehicle::GetTrip(){
  return m_trips;
}
bool Vehicle::DeleteRoute(size_t index){
  if (index >= m_trips.size()) {
      return false;
  }
  delete m_trips[index];
  m_trips.erase(m_trips.begin() + index);
  return true;
}
void Vehicle::showRoute(size_t index){
  cout << "Route ID..............................: " << index << endl;
  cout << "Origin................................: " << m_trips[index]->GetOrigin() << endl;
  cout << "Destination...........................: " << m_trips[index]->GetDestination() << endl;
  cout << "Distance..............................: " << m_trips[index]->GetDistanceKm() << endl;
}
void Vehicle::SetKm(float km) {
    m_finalKm = km;
}


