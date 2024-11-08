void Customer::updateCustomerInfor(const string &inputUserName, const string & inputPassword, const vector<Customer> &customers){
    bool customerFound = false;

    // Find the customer and update the information
     for (const auto &customer : customers)
      {
         if (createUsername(customer.getFullName()) == inputUserName && customer.getPhone() == inputPassword) {  // assuming fullName as unique identifier
            customerFound = true;
            
            int choice;
            cout << "Select the information you want to update:\n";
            cout << "1. Change phone number\n";
            cout << "2. Change address\n";
            cout << "3. Change Date of Birth (DOB)\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();  // To consume the newline after reading choice

            if (choice == 1) {
                string newPhone;
                cout << "Enter the new phone number: ";
                getline(cin, newPhone);
                customer.setPhone(newPhone);
                cout << "Phone number updated successfully.\n";
            } else if (choice == 2) {
                string newAddress;
                cout << "Enter the new address: ";
                getline(cin, newAddress);
                customer.setAddress(newAddress);
                cout << "Address updated successfully.\n";
            } else if (choice == 3) {
                string newDOB;
                cout << "Enter the new Date of Birth (DD/MM/YYYY): ";
                getline(cin, newDOB);
                customer.setDOB(newDOB);
                cout << "Date of Birth updated successfully.\n";
            } else {
                cout << "Invalid choice!\n";
                return;  // Return early in case of invalid choice
            }
            
            // Save the updated customer list back to file
            saveCustomerToFile( customers,"Customer.txt");
            break;
        }
    }

    if (!customerFound) {
        cout << "Customer not found.\n";
    }
}