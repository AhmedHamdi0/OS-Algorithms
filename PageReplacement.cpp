#include <iostream>
#include<string>

using namespace std;

#define LENGTH 13      //number of pages = 13
#define MAX_PAGE_NUMBER 7
#define FRAME_NUMBER 3
int pages[LENGTH] = {1 , 2 , 3 , 1 , 4 , 5 , 2 , 1 , 2 , 6 , 7 , 3 , 2 };
int frames[FRAME_NUMBER];

void FIFO(void);
void optimal(void);
void LRU(void);
void LFU(void);

int main()
{
    FIFO();
    optimal();
    LRU();
    LFU();
    return 0;
}

void FIFO(void)
{
    cout<< "\nFIFO" << endl;
    int k, c, current_page, page_faults = 0;

    for(k = 0; k < FRAME_NUMBER; k++)
    {
        frames[k] = -1;
    }

    int victim = 0;
    for(int page_number = 0; page_number < LENGTH; page_number++)
    {
        int done = 0, exist = 0;
        current_page = pages[page_number];

        // To check if the page already exits in the 3 frames
        for(k = 0; k < FRAME_NUMBER; k++)
        {
            if(frames[k] == current_page)
            {
                exist = 1;
                cout << "\n" << page_number << "\t" << current_page ;
                break;
            }
        }

        // page doesn't exist in the 3 frames but there is an empty place
        if(exist == 0)
        {
            for(k = 0; k < FRAME_NUMBER; k++)
            {
                if(frames[k] == -1)
                {
                    done = 1;   // it means the page dosen't exist in the 3 frames but there is an empty place
                    frames[k] = current_page;
                    cout << "\n" << page_number << "\t" << current_page ;
                    // Just to print the 3 frames content
                    for(c = 0; c < FRAME_NUMBER; c++)
                    {
                        cout << frames[c] << "\t";
                    }
                    page_faults++;
                    break;
                }
            }
        }

        // page replce
        if((exist == 0) && (done == 0))
        {
            frames[victim] = current_page;
            victim = (victim + 1) % FRAME_NUMBER;
            cout << "\n" << page_number << "\t" << current_page ;
            for(c = 0; c < FRAME_NUMBER; c++)
            {
                cout << frames[c] << "\t";
            }
            page_faults++;
        }
    }
    cout << "\nNumber of page faults = " << page_faults << "\n";
}


void optimal(void)
{
    cout<< "\nOptimal\n";
    int k, c, current_page, page_faults = 0;

    for(k = 0; k < FRAME_NUMBER; k++)
    {
        frames[k] = -1;
    }

    for(int page_number = 0; page_number < LENGTH; page_number++)
    {
        int done = 0, exist = 0;
        current_page = pages[page_number];

        for(k = 0; k < FRAME_NUMBER; k++)
        {
            if(frames[k] == current_page)
            {
                exist = 1;
                cout << "\n" << page_number << "\t" << current_page ;
                break;
            }
        }

        if(exist == 0)
        {
            for(k = 0; k < FRAME_NUMBER; k++)
            {
                if(frames[k] == -1)
                {
                    done = 1;
                    frames[k] = current_page;
                    cout << "\n" << page_number << "\t" << current_page ;
                    for(c = 0; c < FRAME_NUMBER; c++)
                    {
                        cout << frames[k] << "\t";
                    }
                    page_faults++;
                    break;
                }
            }
        }

        if((exist == 0) && (done == 0))
        {
            int next_use[FRAME_NUMBER];
            for(k = 0; k < FRAME_NUMBER; k++)
            {
                next_use[k] = LENGTH + 1;
            }

            for(k = 0; k < FRAME_NUMBER; k++)
            {
                for(c = page_number; c < LENGTH; c++)
                {
                    if(frames[k] == pages[c])
                    {
                        next_use[k] = c;
                        break;
                    }
                }
            }

            int victim = 0;
            for(k = 1; k < FRAME_NUMBER; k++)
            {
                if(next_use[k] > next_use[victim])
                {
                    victim = k;
                }
            }

            frames[victim] = current_page;
            cout << "\n" << page_number << "\t" << current_page ;
            for(c = 0; c < FRAME_NUMBER; c++)
            {
                cout << frames[k] << "\t";
            }
            page_faults++;
        }
    }
    cout << "\nNumber of page faults = " << page_faults << "\n";
}


void LRU(void)
{
    cout<< "\nLRU\n";
    int k, c, current_page, page_faults = 0;

    for(k = 0; k < FRAME_NUMBER; k++)
    {
        frames[k] = -1;
    }

    for(int page_number = 0; page_number < LENGTH; page_number++)
    {
        int done = 0, exist = 0;
        current_page = pages[page_number];

        for(k = 0; k < FRAME_NUMBER; k++)
        {
            if(frames[k] == current_page)
            {
                exist = 1;
                cout << "\n" << page_number << "\t" << current_page ;
                break;
            }
        }

        if(exist == 0)
        {
            for(k = 0; k < FRAME_NUMBER; k++)
            {
                if(frames[k] == -1)
                {
                    done = 1;
                    frames[k] = current_page;
                    cout << "\n" << page_number << "\t" << current_page ;
                    for(c = 0; c < FRAME_NUMBER; c++)
                    {
                        cout << frames[k] << "\t";
                    }
                    page_faults++;
                    break;
                }
            }
        }

        if((exist == 0) && (done == 0))
        {
            int prev_use[FRAME_NUMBER];
            for(k = 0; k < FRAME_NUMBER; k++)
            {
                prev_use[k] = -1;
            }

            for(k = 0; k < FRAME_NUMBER; k++)
            {
                for(c = page_number; c >= 0; c--)
                {
                    if(frames[k] == pages[c])
                    {
                        prev_use[k] = c;
                        break;
                    }
                }
            }

            int victim = 0;
            for(k = 1; k < FRAME_NUMBER; k++)
            {
                if(prev_use[k] < prev_use[victim])
                {
                    victim = k;
                }
            }

            frames[victim] = current_page;
            cout << "\n" << page_number << "\t" << current_page ;
            for(c = 0; c < FRAME_NUMBER; c++)
            {
                cout << frames[k] << "\t";
            }
            page_faults++;
        }
    }
    cout << "\nNumber of page faults = " << page_faults << "\n";
}


void LFU(void)
{
    cout<< "\nLRU\n";
    int k, c, current_page, page_faults = 0;

    for(k = 0; k < FRAME_NUMBER; k++)
    {
        frames[k] = -1;
    }

    int number_of_use[MAX_PAGE_NUMBER+1];
    for(k = 0; k <= MAX_PAGE_NUMBER; k++)
    {
        number_of_use[k] = 0;
    }

    for(int page_number = 0; page_number < LENGTH; page_number++)
    {
        int done = 0, exist = 0;
        current_page = pages[page_number];

        for(k = 0; k < FRAME_NUMBER; k++)
        {
            if(frames[k] == current_page)
            {
                exist = 1;
                cout << "\n" << page_number << "\t" << current_page ;
                break;
            }
        }

        if(exist == 0)
        {
            for(k = 0; k < FRAME_NUMBER; k++)
            {
                if(frames[k] == -1)
                {
                    done = 1;
                    frames[k] = current_page;
                    cout << "\n" << page_number << "\t" << current_page ;
                    for(c = 0; c < FRAME_NUMBER; c++)
                    {
                        cout << frames[k] << "\t";
                    }
                    page_faults++;
                    break;
                }
            }
        }

        if((exist == 0) && (done == 0))
        {
            int victim = 0;
            for(k = 1; k < FRAME_NUMBER; k++)
            {
                if(number_of_use[frames[k]] < number_of_use[frames[victim]])
                {
                    victim = k;
                }
            }

            frames[victim] = current_page;
            cout << "\n" << page_number << "\t" << current_page << number_of_use[current_page] << endl;
            for(c = 0; c < FRAME_NUMBER; c++)
            {
                cout << frames[k] << "\t";
            }
            page_faults++;
        }
        number_of_use[current_page]++;
    }
    cout << "\nNumber of page faults = " << page_faults << "\n";   
}
