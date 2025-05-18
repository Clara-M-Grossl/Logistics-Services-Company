#include "route.hpp"

Route::Route(string &ori, string &dest, float km){
  m_origin = new string(ori);
  m_destination =  new string(dest);
  m_distanceKm =  new float(km);
}
Route::~Route(){
  delete m_origin;
  delete m_destination;
  delete m_distanceKm;
}

Route::Route(const Route& other) {
    m_origin = new std::string(*other.m_origin);
    m_destination = new std::string(*other.m_destination);
    m_distanceKm = new float(*other.m_distanceKm);
}

Route& Route::operator=(const Route& other) {
    if (this != &other) { 
        *m_origin = *other.m_origin;
        *m_destination = *other.m_destination;
        *m_distanceKm = *other.m_distanceKm;
    }
    return *this;
}

string Route::GetOrigin(){
  return *m_origin;
}
string Route::GetDestination(){
  return *m_destination;
}
float Route::GetDistanceKm(){
  return *m_distanceKm;
}

void Route::SetOrigin(string origin){
  *m_origin = origin;
}
void Route::SetDest(string destination){
  *m_destination = destination;
}
void Route::SetKm(float kilometers){
  *m_distanceKm = kilometers;
}