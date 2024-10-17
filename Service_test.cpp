//ngựa ngựa test thêm mà file không chạy được =)))))

#include "Service.h"

int main ()
{
     string fileSer = "Service.txt";
     vector<Service> services = readFileService (fileSer);

     displayService (services);
     return 0;
}