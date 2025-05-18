#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "functions.hpp"
#include "route.hpp"


class Vehicle{
  private:
    string m_plate;
    string m_model;
    string m_brand;
    float m_initialKm;
    float m_finalKm;
    vector<Route*> m_trips;

  public:
    Vehicle();
    ~Vehicle();
    Vehicle(string plate, string model, string brand, float m_initialKm);
    void IncludeTrip(string &origin, string &destination, float distance);
    string SearchTripBySubstring(string wordToSearch);

    Vehicle(const Vehicle& other); //copia
    Vehicle& operator = (const Vehicle& other); //atribuiçao

    string GetAllTrips();
    string GetPlate();
    string GetModel();
    string GetBrand();
    vector<Route*> GetTrip();
    float GetInitialKm();
    float GetFinalKm();
    void showRoute(size_t index);
    bool DeleteRoute(size_t index);
    

    void SetKm(float km);

};

#endif