//
// Created by Don on 1/9/2021.
//

#ifndef PERSONALFINANCECPP_LISTDISPLAY_H
#define PERSONALFINANCECPP_LISTDISPLAY_H
#include <iostream>
#include <vector>
#include <string>

std::string displayList(std::vector<std::string> listToDisplay, bool addExit);
std::string getAccountType();



void setUpFolders();
void addATransaction();
void addACategory();
void removeALineItem(const char *const);
void viewCategories();
void viewIncomeStatement();



#endif //PERSONALFINANCECPP_LISTDISPLAY_H
