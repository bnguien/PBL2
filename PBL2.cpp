#pragma once
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

class Person {
private:
     string name;
     string CCCD;
     string add;
     string phone;
     int age;
public:
     Person (string name, string CCCD, string add, string phone, int age) : name (name), CCCD(CCCD), add(add), phone(phone), age(age) {}
     string getName () {
          return name;
     }
     void setName (string name) {
          this->name = name;
     }

     string getCCCD () {
          return CCCD;
     }
     void setCCCD (string CCCD) {
          this->CCCD = CCCD;
     }

     string getAdd () {
          return add;
     }
     void setAdd (string add) {
          this->add = add;
     }

     string getPhone () {
          return phone;
     }
     void setPhone (string phone) {
          this->phone = phone;
     }

     int getAge () {
          return age;
     }
     void setAge (int age) {
          this->age = age;
     }

     void splitName (const string& fullName, string& Name)//dùng trong sắp xếp ds tên khách hàng 
{
     //Tìm vị trí khoảng trắng cuối cùng trong chuỗi họ và tên
     size_t viTriKhoangTrangCuoi = fullName.find_last_of(' ');
     if(viTriKhoangTrangCuoi != string::npos){
          Name=fullName.substr(viTriKhoangTrangCuoi+1);
     } 
     else{
          Name=fullName;
     }
}
void toLowerCase(string& str)//dùng trong tìm kiếm theo tên, không pb chữ hoa chữ thường
{        
     int i=0;
     while(str[i] != '\0'){
          str[i]=tolower(str[i]);
          i++;
     }
}
void standardizeName() {
        string res = "";
        stringstream ss(name);
        string token;
        while (ss >> token) {
            res += toupper(token[0]);
            for (size_t i = 1; i < token.length(); i++) {
                res += tolower(token[i]);
            }
            res += " ";
        }
        res.erase(res.length() - 1);
        name = res;
     }/*Vd: nhap ten nguyen vAn a thi se chuan hoa thanh Nguyen Van A, dung trong in danh sach*/
};

class Room {
private:
     string ID;
     string type; //single, double, suite, deluxe, standard
     string price;
     string view;//sea, city, garden
public:
     Room(string ID, string type, string price, string view): ID(ID), type(type), price(price), view(view){}
     string getID(){
          return ID;
     }
     void setID(string ID){
          this->ID=ID;
     }
     string gettype(){
          return type;
     }
     void settype(string type){
          this->type=type;
     }
     string getprice(){
          return price;
     }
     void setprice(string type){
          this->type=type;
     }
     string getview(){
          return view;
     }
     void setview(){
          this->view=view;
     }
};