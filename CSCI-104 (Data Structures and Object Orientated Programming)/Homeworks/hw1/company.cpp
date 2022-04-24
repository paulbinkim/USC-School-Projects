// Paul Kim, pbkim@usc.edu
// company.cpp

#include "company.hpp"

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];  // An array of pointers to all the 1-person companies (does not contain
                                             // merged)
    for (int i = 0; i < numCompanies; ++i) {
        companies[i] = new Company();  // Calls the Company() constructor
    }
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    for (int j = 0; j < numCompanies; j++) {       // Deallocates the rest of the parent nodes using split function.
        while (companies[j]->parent != nullptr) {  // TA said this is fine (runtime)
            split(j);
        }
    }
    for (int i = 0; i < numCompanies; i++) {  // Deallocates companies
        delete companies[i];
    }
    delete[] companies;  // Deallocates the array that held the companies
}

/** Merges the largest companies containing students i and j.
 * Generates a new Company object which will become the parent company of
 * the largest companies currently containing students i and j.
 */
void CompanyTracker::merge(int i, int j) {
    bool Result = inSameCompany(i, j);
    if (i < 0 || i > numCompanies || j < 0 || j > numCompanies) {  // Checks if i or j are out of range
        return;
    } else if (Result == true) {
        return;
    } else {
        Company* tempcomp1 = largestCompany(i);
        Company* tempcomp2 = largestCompany(j);
        Company* temp = new Company(tempcomp1, tempcomp2);  
        tempcomp1->parent = temp;
        tempcomp2->parent = temp;
    }
}

/** Splits the largest company that student i belongs to.
 * Deletes that Company object, and makes sure that the two subcompanies
 * have no parent afterwards.
 */
void CompanyTracker::split(int i) {
    if (i < 0 || i > numCompanies) {  // Checks if i is out of range
        return;
    } else if (companies[i]->parent == nullptr) {
        return;
    } else {
        Company* temp
                = largestCompany(i);  // Deletes parent node, and reinitializes parent node of merge 1 and merge 2.
        temp->merge1->parent = nullptr;
        temp->merge2->parent = nullptr;
        delete temp;
    }
}

/** Returns whether students i and j are currently in the same company.
 * Returns true if i == j. Returns false if i or j (or both) is out of range.
 */
bool CompanyTracker::inSameCompany(int i, int j) {
    if (i < 0 || i > numCompanies || j < 0 || j > numCompanies) {  // Checks if i or j are out of range
        return false;
    } else if (companies[i]->parent == nullptr || companies[j]->parent == nullptr) {
        return false;  // False because if one or the other are not merged yet, they are not in same company
    } else if (companies[i]->parent == companies[j]->parent) {
        return true;  // True if they share the same parent company in the 1st level
    } else {
        Company* temp1 = largestCompany(i);
        Company* temp2 = largestCompany(j);
        if (temp1
            == temp2) {  // If both i and j share the largest company, then, logically, they are in the same company
            return true;
        } else {
            return false;  // If both students do not share the same company, they are not in the same company.
        }
    }
}

/**
 Function to find the largest company that a student i is part of.
 */
Company* CompanyTracker::largestCompany(int i) {
    if (companies[i]->parent == nullptr) {
        return companies[i];
    } else {
        Company* temp = companies[i];
        while (temp->parent != nullptr) {  // Iterates until parent is the higest node.
            temp = temp->parent;
        }
        return temp;
    }
}