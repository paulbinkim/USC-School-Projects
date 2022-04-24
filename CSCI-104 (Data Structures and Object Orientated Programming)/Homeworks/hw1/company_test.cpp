// Paul Kim, pbkim@usc.edu
// company_test.cpp

// Test code graded on quality and thoroughness of your tests**

#include "company.hpp"
#include <iostream>

int main() {
    std::cout << "Creating an array of 12 companies" << std::endl;
    CompanyTracker CT = CompanyTracker(12);

    std::cout << "Merging Company 0 and Company 1" << std::endl;
    CT.merge(0, 1);
    std::cout << "Is Company 0 in the same Company as Company 1?" << std::endl;
    std::cout << std::boolalpha << CT.inSameCompany(0, 1) << std::endl;  // Should print true.

    std::cout << "Attempting to merge the same Company" << std::endl;
    CT.merge(0, 1);                                                      // Edge Case (merging same company)
    std::cout << std::boolalpha << CT.inSameCompany(0, 1) << std::endl;  // Should print true. (Nothing should change)

    CT.merge(1, 2);

    std::cout << "Attempting to merge the two companies that are already merged" << std::endl;
    CT.merge(0, 2);  // Edge Case (merging two companies that already merged)
    std::cout << std::boolalpha << CT.inSameCompany(0, 2) << std::endl;  // Should print true.

    CT.merge(3, 4);
    CT.merge(5, 6);
    CT.merge(3, 6);

    // Mid-Merge Checks to see if function is wrking
    std::cout << "Mid-Merge Checks" << std::endl;  // Should print true.
    CT.merge(0, 5);
    std::cout << std::boolalpha << CT.inSameCompany(0, 5) << std::endl;  // Should print true.
    CT.merge(7, 9);
    std::cout << std::boolalpha << CT.inSameCompany(7, 9) << std::endl;  // Should print true.
    CT.merge(7, 8);
    std::cout << std::boolalpha << CT.inSameCompany(7, 8) << std::endl;  // Should print true.

    std::cout << "Error Checking (Check if Company 0 shares the same company at Company 7)" << std::endl;
    std::cout << std::boolalpha << CT.inSameCompany(0, 7) << std::endl;  // Should print false.

    CT.merge(10, 11);
    CT.merge(2, 11);
    CT.merge(9, 13);  // Merge Edge Cases (out of bounds)
    CT.merge(-1, 5);  // Merge Edge Cases (out of bounds)

    std::cout << "Error Checking (Check if Company 0 shares with Company 11)" << std::endl;
    std::cout << std::boolalpha << CT.inSameCompany(0, 11) << std::endl;  // Should print true.

    CT.split(2);
    CT.split(2);
    CT.split(2);

    CT.split(2);  // Edge Case (splitting a single company)
    std::cout << "Error Checking (Use Split for Company 2 to remove from all parents)" << std::endl;
    std::cout << "Is Company 2 still in the same Company as Company 0" << std::endl;
    std::cout << std::boolalpha << CT.inSameCompany(0, 2)
              << std::endl;  // Should print false. (2 is splitted all the way to the base)

    CT.split(5);
    CT.split(5);
    CT.split(1);
    CT.split(8);
    CT.split(9);
    CT.split(11);
    CT.split(-1);  // Edge Case (out of bounds)
    CT.split(15);  // Edge Case (out of bounds)

    std::cout << std::boolalpha << CT.inSameCompany(0, 1)
              << std::endl;  // Should print false. (Companies 0 and 1 are not connected)
    std::cout << std::boolalpha << CT.inSameCompany(3, 4)
              << std::endl;  // Should print true. (Companies 3 and 4 are still connected)
    std::cout << std::boolalpha << CT.inSameCompany(7, 8)
              << std::endl;  // Should print false. (Companies 7 and 8 splitted)
    std::cout << std::boolalpha << CT.inSameCompany(0, 13)
              << std::endl;  // Should print false. (Company 13 is out of bounds) (Edge Case)

    return 0;
}

// Push to Github and Submit by 2:30