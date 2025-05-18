#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <iostream>
#include <string>

using namespace std;

class Route{
  private:
    string *m_origin;
    string *m_destination;
    float *m_distanceKm;

  public:
    // CONSTRUTORES E DESTRUTORES
    Route(string &ori, string &dest, float km);
    ~Route();
    Route(const Route& other);
    Route& operator=(const Route& other);

    // FUNÇÕES GET
    string GetOrigin();
    string GetDestination();
    float GetDistanceKm();

    // FUNÇÕES SET
    void SetOrigin(string origin);
    void SetDest(string destination);
    void SetKm(float kilometers);
};

#endif