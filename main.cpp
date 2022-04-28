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
#include "myHash.h"
#include "myList.h"



// timer
timer timer1;

// U can be any type we want to test. here it's the type of data in the sequence to be sorted; can be changed to any other type for which assignment (=) and less-than comparisons (<) are defined.
typedef int U;

//experiment will involve timing of 3 structures and that the number of "trials" will be 7. By a trial is meant timing of the algorithm for inputs of a single length;
// rather than taking a single such measurement we take seven measurements with different randomly generated inputs and compute their median. (The median computation is done
// in class recorder.) The median is used here rather than the mean because it is less susceptible to fluctuation due to possibly large fluctuations in the individual times.
const int number_of_structures = 4;
const int number_of_trials = 7;

// FACTOR is &&&&&
const int FACTOR = 100;  // <==== this will influence the N (size of the problem)


// self written hash table using dynamic arrays for separate chaining
// quadratic probing hash table created by Gerardo Carranza (gc84@uakron.edu)
//


//output headers
const char* delete_headings[number_of_structures] =
        {"|small Array del ",
         "|  small LL del  ",
         "|  big Array del ",
         "|   big LL del   "};

const char* push_back_headings[number_of_structures] =
        {"|small Array add ",
         "|  small LL add  ",
         "|  big Array add ",
         "|   big LL add   "};

const char* search_headings[number_of_structures] =
        {"|sm Array search ",
         "|  sm LL search  ",
         "|big Array search",
         "|  big LL search "};



int main()
{
    int N0, N1, N2, number;
    N1 = 1;    // smallest sequence
    N2 = 1000;  // largest sequence

    // for our outputting of the results
    std::ofstream ofs("results.txt");

    // this is going to hold the measurements
    std::vector<recorder<timer> > stats(number_of_structures);

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

        cout << std::setw(4) << N0 << std::flush;
        ofs << std::setw(4) << N0;

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
                        // my hash table SMALL
                        arrayHash smallArray(10);
                        for (int f = 0; f < number; ++f) {
                            smallArray.insert(f);
                        }
                        timer1.restart();
                        for (int m = 0; m < number; ++m) {
                            smallArray.remove(m);
                        }
                    }
                    else if (i == 1){
                        // linked list hash (created by Kevin Nguyen) SMALL
                        myHash smallLinkedList(10);
                        for (int f = 0; f < number; ++f) {
                            smallLinkedList.insert(f);
                        }
                        timer1.restart();
                        for (int m = number - 1; m > 0; --m) {
                            smallLinkedList.del(m);
                        }
                    }
                    else if (i == 2) {
                        // my hash table BIG
                        arrayHash bigArray(1000);
                        for (int f = 0; f < number; ++f) {
                            bigArray.insert(f);
                        }
                        timer1.restart();
                        for (int m = 0; m < number; ++m) {
                            bigArray.remove(m);
                        }
                    }
                    else if (i == 3){
                        // linked list hash (created by Kevin Nguyen) BIG
                        myHash bigLinkedList(1000);
                        for (int f = 0; f < number; ++f) {
                            bigLinkedList.insert(f);
                        }
                        timer1.restart();
                        for (int m = number - 1; m > 0; --m) {
                            bigLinkedList.del(m);
                        }
                    }
                    timer1.stop();
                    stats[i].record(timer1);
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

    // testing append
    for (N0 = N1; N0 <= N2; N0 *= 2)
    {

        number = N0 * FACTOR * 10;

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
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        arrayHash hashArray(10);
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashArray.insert(h);
                        }
                    } else if (i == 1) {
                        myHash hashLinkedList(10);
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashLinkedList.insert(h);
                        }
                    }
                    else if (i == 2) {
                        arrayHash hashArray(1000);
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashArray.insert(h);
                        }
                    } else if (i == 3) {
                        myHash hashLinkedList(1000);
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashLinkedList.insert(h);
                        }
                    }
                    timer1.stop();
                    stats[i].record(timer1);
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
                for (int k = 0; k < repetitions; ++k) {
                    if (i == 0) {
                        arrayHash hashArray(10);
                        for (int h = 0; h < number; ++h) {
                            hashArray.insert(h);
                        }
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashArray.search(h);
                        }
                    } else if (i == 1) {
                        myHash hashLinkedList(10);
                        for (int h = 0; h < 0; ++h) {
                            hashLinkedList.insert(h);
                        }
                        timer1.restart();
                        for (int h = 0; h < 0; ++h) {
                            hashLinkedList.isIn(h);
                        }
                    }
                    if (i == 2) {
                        arrayHash hashArray(1000);
                        for (int h = 0; h < number; ++h) {
                            hashArray.insert(h);
                        }
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashArray.search(h);
                        }
                    } else if (i == 3) {
                        myHash hashLinkedList(1000);
                        for (int h = 0; h < number; ++h) {
                            hashLinkedList.insert(h);
                        }
                        timer1.restart();
                        for (int h = 0; h < number; ++h) {
                            hashLinkedList.isIn(h);
                        }
                    }
                    timer1.stop();
                    stats[i].record(timer1);
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

        if (repetitions > 1)
            repetitions /= 2;
    }

    return 0;
}


