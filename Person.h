#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include "Vector.h" // Kiểm tra xem Vector.h có cần thiết hay không

// Tránh việc sử dụng 'using namespace std;' trong header files
// Sử dụng std::string, std::vector trực tiếp trong mã

class Person {
private:
    std::string fullName;
    std::string CCCD;
    std::string phone;
    std::string add;
    std::string gender;
    Date DOB; // Sử dụng Date ở đây

public:
    Person() {}
    Person(const Person &P) : fullName(P.fullName), CCCD(P.CCCD), phone(P.phone), add(P.add), gender(P.gender), DOB(P.DOB) {}
    
    Person(std::string fullName, std::string CCCD, std::string phone, std::string add, std::string gender, Date DOB) {
        this->fullName = fullName;
        this->CCCD = CCCD;
        this->phone = phone;
        this->add = add;
        this->gender = gender;
        this->DOB = DOB;
    }

    bool setFullName(const std::string& fullName);
    std::string getFullName() const;
    bool setCCCD(const std::string& CCCD);
    std::string getCCCD() const;
    bool setPhone(const std::string& phone);
    std::string getPhone() const;
    void setAdd(const std::string& add);
    std::string getAdd() const;
    void setGender(const std::string& gender);
    std::string getGender() const;
    bool setDOB(const Date& DOB);
    Date getDOB() const;

    void splitName(const std::string &fullName, std::string &name);
    void toLowerCase(std::string &str);
    std::string standardizeString(const std::string& input);
    static vector<Person> readFilePerson(const std::string& fileName);
    static void displayPerson(const vector<Person>& people);
    ~Person() {}
};

#endif
