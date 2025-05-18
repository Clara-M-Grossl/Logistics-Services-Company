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
    Route(string &ori, string &dest, float km);
    ~Route();

    Route(const Route& other);

    // Operador de atribuição (evita double-free)
    Route& operator=(const Route& other);

    string GetOrigin();
    string GetDestination();
    float GetDistanceKm();

    void SetOrigin(string origin);
    void SetDest(string destination);
    void SetKm(float kilometers);
};

#endif