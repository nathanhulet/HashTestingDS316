/*
   ACADEMIC INTEGRITY PLEDGE

   - I have not used source code obtained from another
     student nor any other unauthorized source, either
     modified or unmodified. Any source code used for
     testing that is another student's has been
     appropriately documented

   - All source code and documentation used in my program
     is either my original work or was derived by me from
     the source code published in the textbook for this
     course or presented in class. Other sources are acknowledged
     without transcribing code verbatim

   - I have not discussed coding details about this project
     with anyone other than my instructor, TA, and my immediate
     project team. I understand that I may discuss the concepts
     of this program with other students and that another student
     may help me debug my program so long as neither of us writes
     anything during the discussion or modifies any computer file
     during the discussion.

   - I have violated neither the spirit nor letter of these
     restrictions.

   Signed: Nathan Hulet Date: 04/20/2022

   COPYRIGHT (C) 2022 Nathan Hulet. All rights reserved.
   DS316 Project 3
   Author.  Nathan Hulet, nmh91
   Version. 1.00 04.20.2022.
   Files: main.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp
          arrayHash.h
          arrayHash.cpp
          chainingArray.h
          chainingArray.cpp

Acknowledgments and special thanks to Dr. David Musser, retired Professor of Computer Science
His wisdom includes a 37-year career combining academic, industry, and research-institute positions, including almost 20 years at Rensselaer.
Coding modifications included the original work with permission: copyright (c) 1997 Rensselaer Polytechnic Institute

 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <limits>
#include <fstream>
#include <iterator>
#include <random>

#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"
#include "arrayHash.h"
#include "chainingArray.h"

// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

//experiment will involve timing of 3 structures and that the number of "trials" will be 7. By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median. (The median computation is done
// in class recorder.) The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.
const int number_of_structures = 2;
const int number_of_trials = 7;

// FACTOR is &&&&&
const int FACTOR = 10000;  // <==== this will influence the N (size of the problem)


// self written hash table using dynamic arrays for separate chaining
// quadratic probing hash table created by Gerardo Carranza (gc84@uakron.edu)
//


//output headers
const char* delete_headings[number_of_structures] =
        {"| Array Hash del ",
         "| Quad Hash del  "};

const char* push_back_headings[number_of_structures] =
        {"| Array Hash add ",
         "| Quad Hash add  "};

const char* search_headings[number_of_structures] =
        {"|Array Hash search",
         "| Quad Hash search"};

const char* insert_headings[number_of_structures] =
        {"|array Hash B-size",
         "| Quad Hash B-size"};



int main()
{
    int N0, N1, N2, number;
    N1 = 1;    // smallest sequence
    N2 = 1000;  // largest sequence

    // for our outputting of the results
    std::ofstream ofs("results.txt");

    // this is going to hold the measurements
    std::vector<recorder<timer> > stats(number_of_structures);

    // declaration of testing structures and support sturctures
    std::vector<U> testValues;
    // my hash table
    arrayHash myArrayHash(100);
    // quadratic probing hash table
    // quadHash quadHashTable(100);

    // The times are taken for short computations by repeating those computations a number of times
    // (controlled by the variable repetitions), so that they take long enough to register nonzero times.
    // In our example where N1 = 1(meaning a sequence of length 1,000 (or, more generally, 1 * factor),
    // then the time will be computed for executing the algorithm 32 times
    int repetitions = std::max(32/N1, 1);

    cout << "____";
    for (auto & delete_heading : delete_headings)
        cout << delete_heading;
    cout << std::endl;

    cout << "Size";
    for (int i = 0; i < number_of_structures; ++i)
        cout << "|       Time     ";
    cout << std::endl;

    // testing erase speed
    for (N0 = N1; N0 <= N2; N0 *= 2) {

        number = N0 * FACTOR;

        // load them up
        for (int i = 0; i < number; ++i)
            testVector.push_back(i);

        for (int i = 0; i < number; ++i)
        {
            mySTList.push_back(i);
        }
        for (int i = 0; i < number; ++i)
        {
            myList.addBack(i);
        }
        cout << std::setw(4) << N0 << std::flush;
        ofs << std::setw(4) << N0;

        replaceVector = testVector;
        otSTList = mySTList;

        for (int i = 0; i < number_of_structures; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            // Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
            // (The repetitions factor is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_structures; ++i)
            {
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        timer1.restart();
                        myList.erase();
                    } else if (i == 1) {
                        timer1.restart();
                        otSTList.erase(otSTList.begin(), otSTList.end());
                    } else {
                        timer1.restart();
                        testVector.erase(testVector.begin(), testVector.end());
                    }

                    timer1.stop();
                    stats[i].record(timer1);
                    //
                    // Notice here we restore because the operation we are testing removes everything
                    // ------------------------------------------------------------------------------
                    if (i == 0) {
                        // our LL
                        for (int z = 0; z < number; ++z) {
                            myList.addBack(z);
                        }
                    } else if (i == 1) {
                        otSTList = mySTList;  // list
                    } else {
                        testVector = replaceVector;  // vectors
                    }
                    // ------------------------------------------------------------------------------
                }
            }
        } // end of trials loop

        for (int i = 0; i < number_of_structures; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << std::endl;
        ofs << std::endl;

        x.clear();

        if (repetitions > 1)
            repetitions /= 2;
    }

    cout << "\n\n____";
    for (auto & delete_heading : push_back_headings)
        cout << delete_heading;
    cout << std::endl;

    cout << "Size";
    for (int i = 0; i < number_of_structures; ++i)
        cout << "|       Time     ";
    cout << std::endl;

    // testing push_back
    for (N0 = N1; N0 <= N2; N0 *= 2)
    {

        number = N0 * FACTOR;

        // ensure lists are clear
        myList.erase();
        testVector.erase(testVector.begin(), testVector.end());
        otSTList.erase(otSTList.begin(), otSTList.end());

        cout << std::setw(4) << N0 << std::flush;
        ofs << std::setw(4) << N0;

        y = x;
        otSTList = mySTList;

        for (int i = 0; i < number_of_structures; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            // Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
            // (The repetitions FACTOR is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_structures; ++i)
            {
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            myList.addBack(h);
                        }
                    } else if (i == 1) {
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            otSTList.push_back(h);
                        }
                    } else {
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            testVector.push_back(h);
                        }
                    }

                    timer1.stop();
                    stats[i].record(timer1);
                    //
                    // Notice here we erase because the operation we are testing adds everything
                    // ------------------------------------------------------------------------------
                    if (i == 0) {
                        myList.erase(); // my list
                    } else if (i == 1) {
                        otSTList.erase(otSTList.begin(), otSTList.end());  // lists
                    } else {
                        testVector.erase(testVector.begin(), testVector.end());  //vectors
                    }
                    // ------------------------------------------------------------------------------
                }
            }
        } // end of trials loop

        for (int i = 0; i < number_of_structures; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << std::endl;
        ofs << std::endl;

        x.clear();

        if (repetitions > 1)
            repetitions /= 2;
    }

    cout << "\n\n____";
    for (auto & delete_heading : search_headings)
        cout << delete_heading;
    cout << std::endl;

    cout << "Size";
    for (int i = 0; i < number_of_structures; ++i)
        cout << "|       Time     ";
    cout << std::endl;

    // testing search
    for (N0 = N1; N0 <= N2; N0 *= 2) {

        number = N0 * FACTOR;

        // load them up with the same list of numbers
        for (int i = 0; i <= number; ++i) {
            testVector.push_back(i);
        }
        for (int i = 0; i <= number; ++i)
        {
            otSTList.push_back(i);
        }
        for (int i = 0; i <= number; ++i)
        {
            myList.addBack(i);
        }

        cout << std::setw(4) << N0 << std::flush;
        ofs << std::setw(4) << N0;

        for (int i = 0; i < number_of_structures; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            // Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
            // (The repetitions FACTOR is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_structures; ++i)
            {
                // the number to search for is right before the end of the list
                int searchFor = number - 1;
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        timer1.restart();
                        auto useless = myList.search(searchFor);
                    } else if (i == 1) {
                        timer1.restart();
                        auto useless = std::count(otSTList.begin(), otSTList.end(), searchFor);

                    } else {
                        timer1.restart();
                        auto useless = std::count(testVector.begin(), testVector.end(), searchFor);
                    }

                    timer1.stop();
                    stats[i].record(timer1);
                }
            }
        } // end of trials loop

        // lists are erased so that a new number of elements can be added
        myList.erase(); // my list
        otSTList.erase(otSTList.begin(), otSTList.end());
        testVector.erase(testVector.begin(), testVector.end());

        for (int i = 0; i < number_of_structures; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << std::endl;
        ofs << std::endl;

        x.clear();

        if (repetitions > 1)
            repetitions /= 2;
    }

    // testing sorted search
    for (N0 = N1; N0 <= N2; N0 *= 2) {

        number = N0 * FACTOR;

        // load them up with the same list of numbers
        for (int i = 0; i <= number; ++i) {
            testVector.push_back(i);
        }
        for (int i = 0; i <= number; ++i)
        {
            otSTList.push_back(i);
        }
        for (int i = 0; i <= number; ++i)
        {
            myList.addBack(i);
        }

        cout << std::setw(4) << N0 << std::flush;
        ofs << std::setw(4) << N0;

        for (int i = 0; i < number_of_structures; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            // Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
            // (The repetitions FACTOR is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_structures; ++i)
            {
                // the number to search for is right before the end of the list
                int searchFor = number - 1;
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        timer1.restart();
                        auto useless = myList.sortedSearch(searchFor);
                    } else if (i == 1) {
                        timer1.restart();
                        auto useless = std::count(otSTList.begin(), otSTList.end(), searchFor);

                    } else {
                        timer1.restart();
                        auto useless = std::count(testVector.begin(), testVector.end(), searchFor);
                    }

                    timer1.stop();
                    stats[i].record(timer1);
                }
            }
        } // end of trials loop
        // structures are erases to add new elements for a new search
        myList.erase(); // my list
        otSTList.erase(otSTList.begin(), otSTList.end()); // stl list
        testVector.erase(testVector.begin(), testVector.end()); // vector

        for (int i = 0; i < number_of_structures; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << std::endl;
        ofs << std::endl;

        x.clear();

        if (repetitions > 1)
            repetitions /= 2;
    }


    cout << "\n\n____";
    for (auto & delete_heading : insert_headings)
        cout << delete_heading;
    cout << std::endl;

    cout << "Size";
    for (int i = 0; i < number_of_structures; ++i)
        cout << "|       Time     ";
    cout << std::endl;



    // testing insert right before mid
    for (N0 = N1; N0 <= N2; N0 *= 2) {

        number = N0 * FACTOR;

        //inserts are fast, so I multiplied the factor by 10 to achieve clearer results
        number *= 10;

        // load them up with the same list of numbers
        for (int i = 0; i <= number; ++i) {
            testVector.push_back(i);
        }
        for (int i = 0; i <= number; ++i)
        {
            otSTList.push_back(i);
        }
        for (int i = 0; i <= number; ++i)
        {
            myList.addBack(i);
        }

        cout << std::setw(4) << N0 << std::flush;
        ofs << std::setw(4) << N0;

        for (int i = 0; i < number_of_structures; ++i)
            stats[i].reset();

        for (int j = 0; j < number_of_trials; ++j)
        {

            // Notice here we repeat the computation repetitions # of times, not for each one, and we record the total time.
            // (The repetitions FACTOR is divided out when the time is later reported on the output stream.)
            for (int i = 0; i < number_of_structures; ++i)
            {
                int searchFor =  (number / 2) - 2;
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        timer1.restart();
                        auto node = myList.sortedSearch(searchFor);
                        myList.insertNode(node, searchFor);
                    } else if (i == 1) {
                        timer1.restart();
                        auto itPos = otSTList.begin();
                        std::advance(itPos, searchFor);
                        otSTList.insert(itPos, searchFor);

                    } else {
                        timer1.restart();
                        auto itPos = testVector.begin();
                        std::advance(itPos, searchFor);
                        testVector.insert(itPos, searchFor);
                    }

                    timer1.stop();
                    stats[i].record(timer1);
                }
            }
        } // end of trials loop
        myList.erase(); // my list
        otSTList.erase(otSTList.begin(), otSTList.end());
        testVector.erase(testVector.begin(), testVector.end());

        for (int i = 0; i < number_of_structures; ++i)
        {
            stats[i].report(cout, repetitions);
            stats[i].report(ofs, repetitions);
        }

        cout << std::endl;
        ofs << std::endl;

        x.clear();

        if (repetitions > 1)
            repetitions /= 2;
    }

    return 0;

}
