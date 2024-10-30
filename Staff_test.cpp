#include "Staff.cpp"
#include "Date.cpp"
#include "Person.cpp"

int main ()
{
     Date date(10,10,2006);
     Staff staff("Ngan Nguyen", "047389251238", "0384698955", "Quang Tri", "Nu", date, "L05", "Laundry", "4.000.000/month");
     staff.saveStafftoStaffFile(staff, "Staff.txt");
}