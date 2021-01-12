//
// Created by Don on 1/9/2021.
//
#include "ListDisplay.h"
#include <iostream>
#include <list>
#include <string>
#include <direct.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>

const std::vector <std::string> currentAssets = {"Cash","Cash Equivalent (Bank Accounts)", "Short Term Investments","Net Receivables",
                                           "Inventory", "Other Current Assets"};
const std::vector <std::string> nonCurrentAssets = {"Property, Plant and Equipment", "Accumulated Depreciation", "Equity and Other Investments",
                                              "Goodwill", "Intangible Assets", "Other Long Term Assets"};
const std::vector <std::string> currentLiabilities = {"Short Term Debt", "Current Portion of Long Term Debt", "Accounts Payable", "Taxes Payable",
                                                "Accrued Liabilities", "Deferred Revenues", "Other Current Liabilities"};
const std::vector <std::string> nonCurrentLiabilities = {"Long Term Debt", "Deferred Taxes Liabilities", "Deferred Revenues",
                                                   "Other Long Term Liabilities"};
const std::vector <std::string> equity = {"Common Stock", "Retained Earnings", "Accumulated Other Comprehensive Income"};


std::string displayList(std::vector<std::string> listToDisplay, bool addExit) {
    int num = 1;
    for (const auto &item : listToDisplay) {
        std::cout << std::to_string(num) + ") " + item << std::endl;
        num += 1;
    }
    if (addExit) {
        std::cout << std::to_string(num) + ") Exit" << std::endl;
        num += 1;
    }
    int userChoice;
    std::cin >> userChoice;
    if (std::to_string(userChoice) == std::to_string(num)) {
        std::exit(0);
    }
    return listToDisplay.at(userChoice - 1);

}

void setUpFolders(){
    _mkdir("Personal Finance Data");
    _chdir("Personal Finance Data");

    std::vector<std::string> csvFiles = {"Balance Sheet Data.csv", "Categories.csv", "Income and Expense.csv"};

    for (const auto &item : csvFiles) {
        std::ifstream checkCSV(item);
        if (checkCSV){
            std::cout << item << " has been found. Proceeding." << std::endl;
            continue;
        }
        else{
            std::cout << item << " was not found, creating one now.";
            std::ofstream createCSV (item);

            if(item == "Balance Sheet Data.csv") {
                createCSV << "Description" << ',' << "Amount" << ',' << "Account Type" << ','<< "URL" << std::endl;
            }
            else if(item == "Income and Expense.csv"){
                createCSV << "Description" << ',' << "Amount" << ',' << "Category" << ',' << "Transaction Type" << std::endl;
            }
            else{
                std::cout << "This item was not found: " << item << std::endl;
            }
        }
    }

    _chdir("..");
}

void addATransaction(){
    std::string accountType, description, amount, category, transactionType;
    _chdir("Personal Finance Data");

    //Get Information from user.
    std::cout << "Adding a new transaction." << std::endl;
    accountType = getAccountType();

    //If the item is in the currentAsset vector, it is a current asset and be on the balance sheet
    if(std::find(currentAssets.begin(), currentAssets.end(), accountType) != currentAssets.end()){
        std::cout << "What is a description for the transaction?" << std::endl;
        std::cin >> description;
        std::cout << "What is a amount for the transaction?" << std::endl << '$';
        std::cin >> amount;
        std::cout << std::endl << "What is a category for the transaction?" << std::endl;

        std::vector <std::string> categories;
        _chdir("Personal Finance Data");
        std::ifstream categoryList("Categories.csv");
        std::string input;
        while (getline(categoryList, input)){
            categories.push_back(input);
        }
        category = displayList(categories, false);

        _chdir("Personal Finance Data");
        std::ofstream file;
        file.open("Balance Sheet Data.csv", std::ios_base::app);
        file << description << ',' << amount << ',' << category << ',' << accountType << std::endl;
        file.close();
        _chdir("..");

        std::cout << "The transaction has been recorded." << std::endl;

    }

    std::cout << "What is a description for the transaction?" << std::endl;
    std::cin >> description;
    std::cout << "What is a amount for the transaction?" << std::endl << '$';
    std::cin >> amount;
    std::cout << std::endl << "What is a category for the transaction?" << std::endl;

    //Get Data from "Categories.csv"
    std::vector <std::string> categories;
    _chdir("Personal Finance Data");
    std::ifstream categoryList("Categories.csv");
    std::string input;
    while (getline(categoryList, input)){
        categories.push_back(input);
    }
    category = displayList(categories, false);


    std::cout << "What type of transaction is this?" << std::endl;
    transactionType = displayList({"Asset", "Liability","Income","Expense"}, false);


    //Input the data
    _chdir("Personal Finance Data");
    std::ofstream file;
    file.open("Data.csv", std::ios_base::app);
    file << description << ',' << amount << ',' << category << ',' << transactionType << std::endl;
    file.close();
    _chdir("..");

    std::cout << "The transaction has been recorded." << std::endl;
}



//Income and expenses will be added by the user and stored in a file.
//Every time the user adds a new income/expense,


std::string getAccountType(){
    std::string primaryAccountType, genericAccountType, specificAccountType;
    std::cout << "What is the primary account type?" << std::endl;
    primaryAccountType = displayList({"Asset", "Liability","Equity","Income","Expense"}, false);

    if(primaryAccountType == "Asset" || primaryAccountType == "Liability"){
        std::cout << "What is the term of the " << primaryAccountType << '?' << std::endl;
        genericAccountType = displayList({"Current "+primaryAccountType, "NonCurrent "+primaryAccountType}, false);


        std::cout << "What is the specific type of " << genericAccountType << '?' << std::endl;
        if(genericAccountType == "Current Asset"){
            specificAccountType = displayList(currentAssets, false);
            return specificAccountType;
        }
        else{
            specificAccountType = displayList(nonCurrentAssets, false);
            return specificAccountType;
        }

    }
    else{
        if(primaryAccountType == "Income"){
            return "Income";
        }
        else{
            return "Expense";
        }
    }

}

void addACategory(){
    std::string newCategory;
    _chdir("Personal Finance Data");
    std::cout << "What is a description of the new category you would like to add?" << std::endl;
    std::cin >> newCategory;

    std::ofstream file;
    file.open("Categories.csv", std::ios_base::app);
    file << newCategory << std::endl;
    file.close();
    _chdir("..");

    std::cout << "The category has been added." << std::endl;
}

void removeALineItem(const char *const fileName){
    std::string line, find, transaction;

    //Get Data from "Data.csv"
    std::vector <std::string> data;
    _chdir("Personal Finance Data");
    std::ifstream dataList(fileName);
    std::string input;
    while (getline(dataList, input)){
        data.push_back(input);
    }
    dataList.close();

    std::cout << "What line item would you like to remove?" << std::endl;
    transaction = displayList(data, false);


    std::ifstream myFile; //for reading records
    myFile.open(fileName);

    std::ofstream temp;
    temp.open("temp.csv");
    while (getline(myFile, line))
    {
        if (line != transaction)
            temp << line << std::endl;
    }
    myFile.close();
    temp.close();
    std::remove(fileName);
    std::rename("temp.csv", fileName);

    std::cout <<"The line item has been removed." << std::endl;


}

void viewCategories(){
    std::vector <std::string> data;
    _chdir("Personal Finance Data");
    std::ifstream dataList("Categories.csv");
    std::string input;
    while (getline(dataList, input)){
        data.push_back(input);
    }
    dataList.close();

    std::cout << "These are the current categories you have set up." << std::endl;
    for (const auto &item : data) {
        std::cout << item << std::endl;

    }

}

void viewIncomeStatement(){
    std::string line, find, transaction;

    float netExpenses = 0;
    float netIncome = 0;

    std::string description, amount, category, transactionType;

    //Get Data from "Data.csv"
    std::vector <std::string> data;
    _chdir("Personal Finance Data");
    std::ifstream dataList("Data.csv");

    std::cout << "Here are all of the expenses." << std::endl;

    while(getline(dataList, line)){
        std::stringstream ss(line);
        getline(ss, description, ',');
        getline(ss, amount, ',');
        getline(ss, category, ',');
        getline(ss, transactionType, ',');


        if (transactionType == "Income"){
            std::cout << description << " is income." << std::endl;
            netIncome += ::atof(amount.c_str());
        }
        else{
            std::cout << description << " is an expense." << std::endl;
            netExpenses += ::atof(amount.c_str());
        }

    }

    std::cout << "The sum of the income is: " << netIncome << std::endl;
    std::cout << "The sum of the expenses is: " << netExpenses << std::endl;
    std::cout << "The net income is: $" << netIncome-netExpenses << std::endl;


}
