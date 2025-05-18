#include "vehicle.hpp"

//CONSTRUTORES E DESTRUTORES
Vehicle::Vehicle(string plate, string model, string brand, float initialKm){
  m_plate = plate;
  m_model = model;
  m_brand = brand;
  m_initialKm = initialKm;
  m_finalKm = initialKm;
}

Vehicle::~Vehicle(){
  for (Route* route : m_trips) {
      delete route;
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

//FUNÇÕES GET
string Vehicle::GetAllTrips(){
  stringstream stream;
  for(size_t i = 0; i < m_trips.size(); i++){
    stream << "ID..................................: " << i 
           << "\nOrigin..............................: " << m_trips[i]->GetOrigin() 
           << "\nDestination.........................: " << m_trips[i]->GetDestination() 
           << "\nDistance............................: " << m_trips[i]->GetDistanceKm() 
           << "\n------------------------------------------------------------------\n";
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

vector<Route*> Vehicle::GetTrip(){
  return m_trips;
}

//FUNÇÕES SET
void Vehicle::SetKm(float km) {
    m_finalKm = km;
}

// RELACIONADAS A ROUTE

void Vehicle::IncludeTrip(string &origin, string &destination, float distance){
  m_trips.push_back(new Route(origin, destination, distance));
  m_finalKm += distance;
}

bool Vehicle::DeleteRoute(size_t index){
  if (index >= m_trips.size()) {
      return false;
  }
  delete m_trips[index];
  m_trips.erase(m_trips.begin() + index);
  return true;
}

string Vehicle::SearchTripBySubstring(string wordToSearch){
  stringstream stream;
  size_t i = 0;
  for(Route* trip : m_trips){
    if (trip->GetOrigin() == wordToSearch || trip->GetDestination() == wordToSearch) {    
          stream << "ID..................................: " << i << "\n"
                 << "Origin..............................: " << trip->GetOrigin() << "\n"
                 << "Destination.........................: " << trip->GetDestination() << "\n"
                 << "Distance............................: " << trip->GetDistanceKm() << "\n"
                 << "==============================================\n";
    }
    i++;
  }
  return stream.str();
}