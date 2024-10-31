#include "Staff.cpp"
#include "Date.cpp"
#include "Person.cpp"

int main ()
{
     Date date(10,10,2006);
     Staff staff("Ngan Nguyen", "047389251238", "0384698955", "Quang Tri", "Female", date, "L05", "Laundry", "4.000.000/month");
     //staff.addNewStaff(staff);
     vector<Staff> staffs = {staff};
     staff.updateStaffFile(staffs, "Staff.txt");
     //staff.removeStaffByCCCD("048300002425");
}