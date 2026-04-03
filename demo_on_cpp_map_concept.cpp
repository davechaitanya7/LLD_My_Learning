#include<bits/stdc++.h>
#include<map>
#include<string>


void Displaymap(std::map<int,std::string> map1){
    for (auto &pair : map1)
    {
        std::cout << "Employee ID   : " << pair.first << std::endl;
        std::cout << "Employee Name : " << pair.second << std::endl;
        std::cout << "----------------------------" << std::endl;
    }
}

int main()
{
    std::map<int,std::string> key_val;

    int emp_id = 1;
    std::string emp_name = "Chaitanya Dave";
    key_val.insert({emp_id,emp_name});

    std::cout<<"Already Employee Data : "<<std::endl;
    Displaymap(key_val);


    int n=0;
    std::cout << "Enter Employee ID and Name (EOF to stop):" << std::endl;
    while (std::cin >> emp_id) {
        std::cin.ignore();                  // ignore newline after ID
        getline(std::cin, emp_name);        // read full name (handles spaces)
        key_val.emplace(emp_id, emp_name);
    }

    std::cout<<"Total the Employee Records : "<<std::endl;
    Displaymap(key_val);

        return 0;
}