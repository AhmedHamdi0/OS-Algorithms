#include <iostream>
#include<string>

using namespace std;

#define PN 5    //Number of process
#define RN 3	//Number of Resources

int alloc[PN][RN] = {{0,2,0} , {2,0,0} , {3,0,2} , {2,1,1} , {0,0,2}};
int maximum[PN][RN] = {{7,5,3} , {3,2,2} , {9,0,2} , {2,2,2} , {4,3,3}} ;
int available[RN] = {3,2,2} ;
int need[PN][RN] ;
int p , r;

void calculate_need(void)
{
	cout << "The need matrix: \n \t";
	for(r = 0 ; r < RN ; r++)
		cout << "R" << r << "\t";
	cout << "\n";

	for(p = 0 ; p < PN ; p++)
	{
		cout << "P" << p << "\t";
		for(r = 0 ; r < RN ; r++)
		{
			need[p][r] = maximum[p][r] - alloc[p][r];
			cout << need[p][r] << "\t";
		}
		cout << "\n";
	}
}

bool is_safe(void)
{
	int flag ;
	int counter = 0;
	int finish[PN] = { };
	int tempavail[RN] ;
	for(r = 0 ; r < RN ; r++)		
        tempavail[r] = available[r] ;

    do{
		flag = 0 ;
		for(p = 0 ; p < PN ; p++)
		{
			if(finish[p] == 0)
			{
				for(r = 0 ; r < RN ; r++)
					if(need[p][r] > tempavail[r])		
                        break;

				if(r == RN)
				{
					finish[p] = 1 ;
					cout << "\nP" << p << "\t";
					for(r = 0 ; r < RN ; r++)
					{ 
                        tempavail[r] += alloc[p][r];
                        cout << tempavail[r] << "\t"; 
                    }
					flag = 1 ;
					counter++;
				}
			}
		}
	}while(flag == 1);

	if(counter == PN)	
    { 
        cout << "\n System is safe \n";	
        return true; 
    }
	else
    { 
        cout << "\n System is unsafe \n";
    	return false;
    }
}

	
int main(void)
{
	calculate_need();
	is_safe();
    return 0;
}


