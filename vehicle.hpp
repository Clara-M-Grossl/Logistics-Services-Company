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
    //CONSTRUTORES E DESTRUTORES
    Vehicle(string plate, string model, string brand, float m_initialKm);
    ~Vehicle();
    Vehicle(const Vehicle& other);
    Vehicle& operator = (const Vehicle& other);
    
    //FUNÇÕES GET
    string GetAllTrips();
    string GetPlate();
    string GetModel();
    string GetBrand();
    float GetInitialKm();
    float GetFinalKm();
    vector<Route*> GetTrip();
    
    //FUNÇÕES SET
    void SetKm(float km);
    
    //RELACIONADAS A ROUTE
    void IncludeTrip(string &origin, string &destination, float distance);
    bool DeleteRoute(size_t index);
    string SearchTripBySubstring(string wordToSearch);


    


};

#endif