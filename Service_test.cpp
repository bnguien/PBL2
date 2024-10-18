#include "Service.cpp"

int main ()
{
     string fileSer = "Service.txt";
     vector<Service> services = readFileService (fileSer);

     displayService (services);
     return 0;
}