#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct Car {
  enum {MAX_CHAR_LEN=100};
  char Name[MAX_CHAR_LEN];
  double MPG;
  int Cylinders;
  double Displacement;
  double Horsepower;
  double Weight;
  double Acceleration;
  int Model;
  char Origin[MAX_CHAR_LEN];
  bool isValid;
  Car();
};

Car::Car(){
    for (int index = 0; index < MAX_CHAR_LEN; index++) {
        Name[index] = '\0';
    }
    for (int index = 0; index < MAX_CHAR_LEN; index++) {
        Origin[index] = '\0';
    }
    MPG = 0;
    Cylinders = 0;
    Displacement = 0;
    Horsepower = 0;
    Weight = 0;
    Acceleration = 0;
    Model = 0;
    isValid = false;
}


const int MAX_CARS=500;
Car readCar(ifstream &inFile){
    Car car; 
    inFile.get(car.Name, Car::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> car.MPG;
    inFile.ignore(100,';');
    inFile >> car.Cylinders;
    inFile.ignore(100,';');
    inFile >> car.Displacement;
    inFile.ignore(100,';');
    inFile >> car.Horsepower;
    inFile.ignore(100,';');
    inFile >> car.Weight;
    inFile.ignore(100,';');
    inFile >> car.Acceleration;
    inFile.ignore(100,';');
    inFile >> car.Model;
    inFile.ignore(100,';');
    inFile >> car.Origin;
    inFile.ignore(100,'\n');
    // If we reached the end of the file while reading, then the entry is not valid
    car.isValid = !inFile.eof();
    return car;
}

int readCars(Car cars[]) {
    ifstream carFile("cars.txt");
    int numCars = 0;
    while(carFile.peek() != EOF && numCars < MAX_CARS) {
        cars[numCars] = readCar(carFile);
        numCars++;
    }
    return numCars;
}

int printCars(Car cars[], int indexCars) {
  if(cars[indexCars].isValid == false){
    return 0;
  }
  cout << "Index " << indexCars << ": ";
  int temp = 0;
  while(cars[indexCars].Name[temp] != '\0') {
    cout << cars[indexCars].Name[temp];
    temp++;
  }
  cout << ";" << cars[indexCars].MPG << ";" << cars[indexCars].Cylinders << ";" << cars[indexCars].Displacement << ";" << cars[indexCars].Horsepower << ";" << cars[indexCars].Weight << ";" << cars[indexCars].Acceleration << ";" << cars[indexCars].Model << ";" << cars[indexCars].MPG << ";";
  temp = 0;
  while(cars[indexCars].Origin[temp] != '\0') {
    cout << cars[indexCars].Origin[temp];
    temp++;
  }
  cout << endl;
  return 0;
}

int printCarsByOrigin(Car cars[], char temp[]) {
  for(int index = 0; index < MAX_CARS; index++){
    if(cars[index].isValid && strcmp(cars[index].Origin, temp) == 0){
      printCars(cars, index);
    }
  }
  return 0;
}

int removeCar(Car cars[], int tempIndex){
  if(cars[tempIndex].isValid == true){
    cars[tempIndex].isValid = false;
  }
  return 0;
}

int addCar(Car cars[], char nName[], double nMPG, int nCylanders, double nDisplacement, double nHorsepower, double nWeight, double nAcceleration, int nModel, char nOrigin[]){
  for(int index = 0; index < MAX_CARS; index++){
    if(cars[index].isValid == false){
      strcpy(cars[index].Name, nName);
      cars[index].MPG = nMPG;
      cars[index].Cylinders = nCylanders;
      cars[index].Displacement = nDisplacement;
      cars[index].Horsepower = nHorsepower;
      cars[index].Weight = nWeight;
      cars[index].Acceleration = nAcceleration;
      cars[index].Model = nModel;
      strcpy(cars[index].Origin, nOrigin);
      cars[index].isValid = true;
      return 0;
    }
  }
  return 0;
}


int setCharArray(char temp[]){
  for (int index = 0; index < MAX_CARS; index++) {
        temp[index] = '\0';
    }
    return 0;
}


int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
      cin.clear();
      cin.ignore(1000,'\n');
      cout << "Invalid Data!" << endl;
      cout << prompt;
      cin >> temp;
    }
    return temp;
}

double readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

int readCharArray(const char prompt[], char Name[]){
  char temp[100];
  int index = 0;
  do{
    cout << prompt;
    cin >> temp;
    while(temp[index] != '\0'){
      index++;
    }
  }
  while(index > 100);
  strcpy(Name, temp);
  return 0;
}


int main(){
Car cars[MAX_CARS]; 
readCars(cars);
int input;
int temp;


while (true){
  input = readInt("1.Display the car list\n2.Remove a car from the list\n3.Add a car to the list\n4.Display cars by origin\n5.Quit\n\nEnter a Number: ");

  if(input == 1){
    for(int index = 0; index < MAX_CARS; index++){
      printCars(cars, index);
    }
    cout << endl;
  }
  if(input == 2){
    temp = readInt("\nEnter Index to delete: ");
    removeCar(cars, temp);
    cout << endl;
  }
  if(input == 3){
    cout << endl;
    char tempName[100];
    setCharArray(tempName);
    char tempOrigin[100];
    setCharArray(tempOrigin);
    double MPG;
    int Cylinders;
    double Displacement;
    double Horsepower;
    double Weight;
    double Acceleration;
    int Model;
    
    readCharArray("Enter Name: ", tempName);
    MPG = readDouble("Enter MPG: ");
    Cylinders = readInt("Enter Cylanders: ");
    Displacement = readDouble("Enter Displacement: ");
    Horsepower = readDouble("Enter Horsepower: ");
    Weight = readDouble("Enter Weight: ");
    Acceleration = readDouble("Enter Acceleration: ");
    Model = readInt("Enter Model: ");
    readCharArray("Enter Origin: ", tempOrigin);
    addCar(cars, tempName, MPG, Cylinders, Displacement, Horsepower, Weight, Acceleration, Model, tempOrigin);
    cout << endl;
  }
  if(input == 4){
    cout << ""
    printCarsByOrigin(cars, temp);
  }
  if(input == 5){
    return 0;
  }
}

return 0;
}