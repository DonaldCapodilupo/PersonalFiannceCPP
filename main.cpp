//
// Created by Don on 1/9/2021.
//
#include <vector>

#include "ListDisplay.h"


//std::vector <std::string> currentAssets = {"Cash","Cash Equivalent (Bank Accounts)", "Short Term Investments","Net Receivables",
//                                           "Inventory", "Other Current Assets"};
//std::vector <std::string> nonCurrentAssets = {"Property, Plant and Equipment", "Accumulated Depreciation", "Equity and Other Investments",
//                                              "Goodwill", "Intangible Assets", "Other Long Term Assets"};
//std::vector <std::string> currentLiabilities = {"Short Term Debt", "Current Portion of Long Term Debt", "Accounts Payable", "Taxes Payable",
//                                                "Accrued Liabilities", "Deferred Revenues", "Other Current Liabilities"};
//std::vector <std::string> nonCurrentLiabilities = {"Long Term Debt", "Deferred Taxes Liabilities", "Deferred Revenues",
//                                                   "Other Long Term Liabilities"};
//std::vector <std::string> equity = {"Common Stock", "Retained Earnings", "Accumulated Other Comprehensive Income"};

//Income and expenses will be added by the user and stored in a file.
//Every time the user adds a new income/expense, 



int main() {
    getAccountType();
    setUpFolders();

    std::string userChoice;
    std::vector <std::string> mainMenuOptions = {"Add A Transaction", "Remove A Transaction",
                                            "Add A Category", "Remove A Category", "View Categories",
                                            "View Income Statement"};
    std::cout << "What option would you like to choose?" << std::endl;

    do {
        userChoice = displayList(mainMenuOptions, true);
        if (userChoice == "Add A Transaction") {
            addATransaction();
        } else if (userChoice == "Remove A Transaction") {
            removeALineItem("Data.csv");
        } else if (userChoice == "Add A Category") {
            addACategory();
        }

        if (userChoice == "Remove A Category") {
            removeALineItem("Categories.csv");
        } else if (userChoice == "View Categories") {
            viewCategories();
        } else if (userChoice == "View Income Statement") {
            viewIncomeStatement();
        }
    }while( userChoice != "Exit");

        std::cout << "User chose " + userChoice;


    return 0;
}