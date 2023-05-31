// #include "stdafx.h"
#include <iostream>
// #include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<random>
#include<fstream>
#include<string>

using namespace std;

#define SIZE 5      // assume number of processes = 5

struct process
{
    int number, arrival, burst, priority;
};

process * sort_process(struct process *, int);
int FCFS(struct process*, int, int*);
int SJF_NP(struct process * , int, int*);
int SJF_P(struct process * , int, int*);
int Priority_NP(struct process * , int, int*);
int Priority_P(struct process * , int, int*);
int RR(struct process * , int , int, int*); 


int main()
{
    struct process list1[SIZE] = {{1,0,1,3},{2,3,8,4},{3,4,5,2},{4,5,2,2},{5,8,4,1}};
    int wait_time[SIZE] = { } , total_wait_time;
	// cout << "\nFCFS\n";
	// FCFS(list1,SIZE, wait_time);
	// cout << "\nSJF_NP\n";
	// SJF_NP(list1,SIZE, wait_time);
	// cout << "\nSJF_P\n";
	// SJF_P(list1,SIZE, wait_time);
	// cout << "\nPriority_NP\n";
	// Priority_NP(list1,SIZE, wait_time);
	// cout << "\nPriority_P\n";
	// Priority_P(list1,SIZE, wait_time);
	// cout << "\n RR\n";
	// RR(list1,SIZE,3, wait_time);
	// getch();
    return 0;
}


class queue 
{
    private:
        int front, rear, counter, size;
        struct process * qu;

    public:
        queue(int s)
        {
            size = s;
            qu = new process[size];
            front = rear = counter = 0;
        }

        void enqueue(process temp)
        {
            qu[rear] = temp;
            rear = (rear + 1) % size;
            counter++;
        }   

        process dequeue(void)
        {
            process temp = qu[front];
            front = (front + 1) % size;
            counter--;
            return temp;
        } 

        bool is_full(void)
        {
            return counter == size ; 
        }

	    bool is_empty(void)
        {
            return counter == 0 ; 
        }
};


process * sort_process(process * prs, int n)
{
    process temp, *list;
    list = new process[n];
    int a, b;

    for(a = 0; a < n; a++)
        list[a] = prs[a];

    for(a = 0; a < n; a++)
    {
        for(b = a+1; b < n; b++)
        {
            if(list[a].arrival > list[b].arrival)
            {
                temp = list[a];
                list[a] = list[b];
                list[b] = temp;
            }
            // cout <<list[a].number <<"\t"<<list[a].arrival <<"\t"<<list[a].burst <<"\t"<<list[a].priority <<"\n";
        }
    }
    return list;
}


int FCFS(process *prs, int n, int *waitingTime)
{
    process *list = sort_process(prs, n);

    int time = 0;
    int totalWaitingTime = 0;
    for(int a = 0; a < n; a++)
    {
        while (list[a].burst > 0)
        {
            if(time >= list[a].arrival)
            {
                cout << time << "~" << time + 1 << "\t\t" << list[a].number << endl;
                list[a].burst--; 
            }
            else 
            {
                cout << time << "~" << time + 1 << "\t\t" << "NULL" << endl;
            }
            time ++;
        }
        waitingTime[a] = time - prs[a].arrival - prs[a].burst;
        totalWaitingTime += waitingTime[a];
    }

    cout << "Waiting Times: " << endl;
    for(int a = 0; a < n; a++)
        cout << "P" << list[a].number << "\t" << waitingTime[a] << endl;
    
    cout << "Total Waiting Time = " << totalWaitingTime << endl;
    return totalWaitingTime;
}


int SJF_NP(struct process * prs, int n, int *waitingTime)
{
    process *list = sort_process(prs, n);

    int time = 0;
    int totalWaitingTime = 0;
    int min_index, min_burst;
    int still = 1;

    while(still)
    {
        min_index = -1;
        min_burst = 1000;

        for(int a = 0; a < n; a++)
        {
            if((time >= list[a].arrival) && (list[a].burst > 0) && (list[a].burst < min_burst))
            {
                min_burst = list[a].burst;
                min_index = a;
            }
        }

        if(min_index != -1)
        {
            while (list[min_index].burst > 0)
            {
                cout << time << "~" << time + 1 << "\t\t" << list[min_index].number << endl;
                list[min_index].burst --;
                time++;
            }

            waitingTime[min_index] = time - prs[min_index].arrival - prs[min_index].burst;
            totalWaitingTime += waitingTime[min_index];
        }
        else
        {
            still = 0;      // it means all processes probably finished
            for(int a = 0; a < n; a++)
            {
                if(list[a].burst > 0)       // To check that any process hasn't finished yet.
                {
                    still = 1;
                    cout << time << "~" << time + 1 << "\t\t" << "NULL" << endl;
                    time ++;
                    break;
                }
            }
        }
    }

    cout << "Waiting Times: " << endl;
    for(int a = 0; a < n; a++)
        cout << "P" << list[a].number << "\t" << waitingTime[a] << endl;
    
    cout << "Total Waiting Time = " << totalWaitingTime << endl;
    return totalWaitingTime;
}


int Priority_NP(struct process *prs , int n, int *waitingTime)
{
    process *list = sort_process(prs, n);

    int time = 0;
    int min_index, min_priority;
    int still = 1;
    int totalWaitingTime = 0;

    while (still)
    {
        min_index = -1;
        min_priority = 1000;

        for(int a = 0; a < n; a++)
        {
            if((time >= list[a].arrival) && (list[a].burst > 0) && (list[a].priority < min_priority))
            {
                min_priority = list[a].priority;
                min_index = a;
            }
        }

        if(min_index != -1)
        {
            while (list[min_index].burst > 0)
            {
                cout << time << "~" << time + 1 << "\t\t" << list[min_index].number << endl;
                list[min_index].burst--;
                time++;
            }

            waitingTime[min_index] = time - prs[min_index].arrival - prs[min_index].burst;
            totalWaitingTime += waitingTime[min_index];
        }
        else
        {
            still = 0;
            for(int a = 0; a < n; a++)
            {
                if(list[a].burst > 0)
                {
                    still = 1;
                    cout<< time << "~" << time + 1 << "\t\t" << "NULL" << endl;
                    time++;
                    break;
                }
            }
        }
    }

    cout << "Waiting Times: " << endl;
    for(int a = 0; a < n; a++)
        cout << "P" << list[a].number << "\t" << waitingTime[a] << endl;
    
    cout << "Total Waiting Time = " << totalWaitingTime << endl;
    return totalWaitingTime;
}


int SJF_P(struct process *prs, int n, int *waitingTime)
{
    process *list = sort_process(prs, n);

    int time = 0;
    int min_index, min_burst;
    int still = 1;
    int totalWaitingTime = 0;

    while(still)
    {
        min_index = -1;
        min_burst = 1000;

        for(int a = 0; a < n; a++)
        {
            if((time >= list[a].arrival) && (list[a].burst > 0) && (list[a].burst < min_burst))
            {
                min_burst = list[a].burst;
                min_index = a;
            }
        }

        if(min_index != -1)
        {
            cout << time << "~" << time + 1 << "\t\t" << list[min_index].number << endl;
            list[min_index].burst --;
            time++;

            if(list[min_index].burst == 0)
            {
                waitingTime[min_index] = time - prs[min_index].arrival - prs[min_index].burst;
                totalWaitingTime += waitingTime[min_index];
            }
        }
        else
        {
            still = 0;      // it means all processes probably finished
            for(int a = 0; a < n; a++)
            {
                if(list[a].burst > 0)       // To check that any process hasn't finished yet.
                {
                    still = 1;
                    cout << time << "~" << time + 1 << "\t\t" << "NULL" << endl;
                    time ++;
                    break;
                }
            }
        }
    }

    cout << "Waiting Times: " << endl;
    for(int a = 0; a < n; a++)
        cout << "P" << list[a].number << "\t" << waitingTime[a] << endl;
    
    cout << "Total Waiting Time = " << totalWaitingTime << endl;
    return totalWaitingTime;
}


int Priority_P(struct process *prs , int n, int *waitingTime)
{
    process *list = sort_process(prs, n);

    int time = 0;
    int min_index, min_priority;
    int still = 1;
    int totalWaitingTime = 0; 

    while (still)
    {
        min_index = -1;
        min_priority = 1000;

        for(int a = 0; a < n; a++)
        {
            if((time >= list[a].arrival) && (list[a].burst > 0) && (list[a].priority < min_priority))
            {
                min_priority = list[a].priority;
                min_index = a;
            }
        }

        if(min_index != -1)
        {
            cout << time << "~" << time + 1 << "\t\t" << list[min_index].number << endl;
            list[min_index].burst--;
            time++;

            if(list[min_index].burst == 0)
            {
                waitingTime[min_index] = time - prs[min_index].arrival - prs[min_index].burst;
                totalWaitingTime += waitingTime[min_index];
            }
        }
        else
        {
            still = 0;
            for(int a = 0; a < n; a++)
            {
                if(list[a].burst > 0)
                {
                    still = 1;
                    cout<< time << "~" << time + 1 << "\t\t" << "NULL" << endl;
                    time++;
                    break;
                }
            }
        }
    }

    cout << "Waiting Times: " << endl;
    for(int a = 0; a < n; a++)
        cout << "P" << list[a].number << "\t" << waitingTime[a] << endl;
    
    cout << "Total Waiting Time = " << totalWaitingTime << endl;
    return totalWaitingTime;
}


int RR(process *prs , int n , int quantum, int *waitingTime)
{
	struct process temp , *list ;
	list = sort_process(prs,n);
	
	queue myque(n);
	int time = 0 , still = 1 , index = 0, totalWaitingTime;
	process current;

	for(int k = index ; k < n ; k++)
    {
        if(list[k].arrival == 0)	
        { 
            myque.enqueue(list[k]);  
            index++; 
        }
    }

	while((index < n) || (myque.is_empty() == false))
	{
		if(myque.is_empty() == true)			
		{
			cout << time << " ~ " << time+1 << "\t\t" << "IDLE \n";
			time++ ;
		}
		else
		{
			current = myque.dequeue();
			for(int k = 1 ; k <= quantum ; k++)
			{
				if(current.burst > 0)
                {
					cout << time << " ~ " << time+1 << "\t\t" << current.number << "\n";
					time++ ;
					current.burst--;
				}
                else
                {
                    waitingTime[current.number] = time - prs[current.number].arrival - prs[current.number].burst;
                }
			}
		}

		for(int k = index ; k < n ; k++)
        {   
            if(list[k].arrival <= time)		
                { 
                    myque.enqueue(list[k]);  
                    index++; 
                }
        }
			
		if(current.burst > 0)
        {
            myque.enqueue(current);
        }			
	}

    cout << "Waiting Times: " << endl;
    for(int a = 0; a < n; a++)
        cout << "P" << list[a].number << "\t" << waitingTime[a] << endl;
    
    cout << "Total Waiting Time = " << totalWaitingTime << endl;
    return totalWaitingTime;
}
