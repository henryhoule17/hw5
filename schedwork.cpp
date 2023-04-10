#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(DailySchedule& sched, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, unsigned int row, unsigned int col, std::vector<unsigned int>& worker_shifts);
bool notAlreadyScheduled(const DailySchedule& sched, Worker_T id, unsigned int row, unsigned int col);
void populateworker_shifts(vector<unsigned int>& worker_shifts, unsigned int numworkers);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //initializes sched with the proper dimensions 
    //and is populated with INVALID_ID
    vector<Worker_T> day_sched;
	for(size_t i =0; i < avail.size(); i++)
    {
        sched.push_back(day_sched);
        for(size_t j = 0; j < dailyNeed; j++)
            sched[i].push_back(INVALID_ID);
    }

    //initializes vector to track how many shifts 
    //each worker has
    vector<unsigned int> worker_shifts;
    populateworker_shifts(worker_shifts, avail[0].size());

    return scheduleHelper(sched, avail, dailyNeed, maxShifts, 0, 0, worker_shifts);
}

bool scheduleHelper(DailySchedule& sched, 
                    const AvailabilityMatrix& avail, 
                    const size_t d, 
                    const size_t m, 
                    unsigned int row, 
                    unsigned int col, 
                    std::vector<unsigned int>& worker_shifts)
{
    //if schedule is complete
    if (row == sched.size() - 1 && col == d)
      return true; 
    
    //if at end of column
    if (col == d)
    {
      row++;
      col = 0;
    } 

    //if shift empty, find first worker that can fill int
    for(size_t i=0; i<avail[row].size(); i++)
    {
        //cout << "Row: " << row << "  Col: " << col << endl;
        if(avail[row][i] == 1 && notAlreadyScheduled(sched, i, row, 0) && worker_shifts[i] < m)
        {
            //cout << "Adding " << i << endl;
            worker_shifts[i]++;
            sched[row][col] = i;
            bool nextSlot = scheduleHelper(sched, avail, d, m, row, col + 1, worker_shifts);
            if(nextSlot) 
                return true;
            sched[row][col] = INVALID_ID;
            worker_shifts[i]--;
            //cout << "Unadding " << i << endl;
        }
    }

	return false;
}

bool notAlreadyScheduled(const DailySchedule& sched, Worker_T id, unsigned int row, unsigned int col)
{
    if(col == sched[row].size())
        return true;

    if(sched[row][col] == id)
        return false;

    return notAlreadyScheduled(sched, id, row, col+1);
}

void populateworker_shifts(vector<unsigned int>& worker_shifts, unsigned int numworkers)
{
    if(worker_shifts.size() == numworkers)
        return;
    
    worker_shifts.push_back(0);
    populateworker_shifts(worker_shifts, numworkers);
}