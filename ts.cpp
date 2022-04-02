// FORMATER : On Windows Shift + Alt + F.
#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define NDEBUG 0

std::vector<int> sectors;

struct rocket
{
  int distance = 0;
  int speed = 3;
  int startPoint = 0;
  int spreadRate = 0;
  int spreadLeft = 0;
  int spreadRight = 0;
};

class CRocket
{       // The class
public: // Access specifier
  int m_distance = 0;
  int m_speed = 3;
  int m_impactPoint = 0;
  int m_spreadRate = 0;
  int m_spreadLeft = 0;
  int m_spreadRight = 0;

  CRocket(int distance, int speed, int impactPoint, int spreadRate)
  {
    m_distance = distance;
    m_speed = speed;
    m_impactPoint = impactPoint;
    m_spreadRate = spreadRate;
    m_spreadLeft = -1;
    m_spreadRight = -1;
  }
  void display()
  {
    cout << "m_distance: " << m_distance;
    cout << " m_speed: " << m_speed;
    cout << " m_impactPoint: " << m_impactPoint;
    cout << " m_spreadRate: " << m_spreadRate;
    cout << " m_spreadLeft: " << m_spreadLeft;
    cout << " m_spreadRight: " << m_spreadRight;

    cout << "\n";
  }
};

int isPanetFulltInfected()
{
  for (int n : sectors)
  {
    if (n == 0)
      return 0;
  }
  return 1;
}

void showPlanet()
{
  for (int n : sectors)
  {
    std::cout << n << ", ";
  }
  cout << " -- full infected: " << isPanetFulltInfected() << "\n";
}

void initializeSector(int number)
{
  for (int i = 0; i < number; i++)
  {
    sectors.push_back(0);
  }
}

int main(int argc, char **argv)
{
 

  initializeSector(10000);
  CRocket r1(0, 1, 500, 1);
  CRocket r2(1, 1, 3000, 2);
  CRocket r3(4, 1, 6000, 4);
  // r1.display();

  std::vector<CRocket> rockets;
  rockets.push_back(r1);
  rockets.push_back(r2);
  rockets.push_back(r3);

// Just display all rockets
#ifndef NDEBUG
  for (int y = 0; y < rockets.size(); y++)
  {
    cout << "rocket " << y << ": ";
    rockets.at(y).display();
  }
#endif

  // Max infection time is specified by the min spread time by 1 and the amount of sectors
  for (long unsigned int x = 0; x < sectors.size(); x++)
  {

// Iterrate over all rockes and mark the infected sectors
#ifndef NDEBUG
    cout << "Itteration " << x << "\n";
#endif
    for (long unsigned int y = 0; y < rockets.size(); y++)
    {
      if (rockets.at(y).m_distance > 0)
      {
        rockets.at(y).m_distance = rockets.at(y).m_distance - rockets.at(y).m_speed;
      }
      #ifndef NDEBUG
      if (rockets.at(y).m_distance == 0)
      {
        cout << "impact rocket " << y << "\n";
        rockets.at(y).m_distance = -1;
      }
      #endif

      if (rockets.at(y).m_distance <= 0)
      {
        // Ausbreitung nach links
        if (rockets.at(y).m_spreadLeft == -1)
        {
          rockets.at(y).m_spreadLeft = rockets.at(y).m_impactPoint;
          sectors.at(rockets.at(y).m_spreadLeft) = 1;
        }
        else
        {
          for (int z = 0; z < rockets.at(y).m_spreadRate; z++)
          {
            rockets.at(y).m_spreadLeft--;
            if (rockets.at(y).m_spreadLeft < 0)
              rockets.at(y).m_spreadLeft = sectors.size() - 1;
            sectors.at(rockets.at(y).m_spreadLeft) = 1;
          }
        }

        // Ausbreitung nach rechts
        if (rockets.at(y).m_spreadRight == -1)
        {
          rockets.at(y).m_spreadRight = rockets.at(y).m_impactPoint;
          sectors.at(rockets.at(y).m_spreadRight) = 1;
        }
        else
        {
          for (int z = 0; z < rockets.at(y).m_spreadRate; z++)
          {
            rockets.at(y).m_spreadRight++;
            if (rockets.at(y).m_spreadRight >= int(sectors.size()))
              rockets.at(y).m_spreadRight = 0;
            sectors.at(rockets.at(y).m_spreadRight) = 1;
          }
        }
      }
    }
#ifndef NDEBUG
    cout << "  ";
    showPlanet();
#endif
    if (isPanetFulltInfected() == 1)
    {
      cout << "full infected after " << x << " itterations\n";
      return 0;
    }
  }
  cout << endl;
}