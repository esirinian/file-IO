//
//  fileIO2.cpp
//  
//
//  Created by Eric Sirinian on 9/20/16.
//
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

const int MAXCOUNTRIES = 229;

struct country
{
    string name;
    double pop1950, pop1970, pop1990, pop2010, pop2015;
    int growthRate[4];
};

struct world
{
    int numCountries;
    country countries[MAXCOUNTRIES];
    int largest[3];
    int largestGrowthRate[4];
    string potentiallyLarge[MAXCOUNTRIES];
};

int main()
{
    ifstream popFile;
    world myWorld;
    int toThree = 0;
    int temp1, temp2, temp3, temp4;
    int quaterOfThird;
    
    double countrySizes[MAXCOUNTRIES];
    
    int count = -1;
    
    popFile.open("population.csv");
    
    // READING DATA IN TO 'myWorld'
    if (popFile)
    {
        cout << "File Opened..." << endl;
        cout << "Reading file..." << endl;
        do
        {
            count++;
            
            popFile >> myWorld.countries[count].pop1950 >>
                myWorld.countries[count].pop1970 >> myWorld.countries[count].pop1990 >>
                myWorld.countries[count].pop2010 >> myWorld.countries[count].pop2015;

            //TASK 1
            if (toThree >=3)
            {
                if(myWorld.countries[count].pop2015 > myWorld.countries[myWorld.largest[2]].pop2015)
                {
                    if(myWorld.countries[count].pop2015 > myWorld.countries[myWorld.largest[1]].pop2015)
                    {
                        if(myWorld.countries[count].pop2015 > myWorld.countries[myWorld.largest[0]].pop2015)
                        {
                            myWorld.largest[0] = count;
                        }
                        else
                        {
                            myWorld.largest[1] = count;
                        }
                    }
                    else
                    {
                        myWorld.largest[2] = count;
                    }
                }
                else
                {
                    //cout << "not big enough..." << endl;
                }
            }
            else
            {
                myWorld.largest[count] = count;
            }
            
            //TASK 2
            
            myWorld.countries[count].growthRate[0] =
                ((myWorld.countries[count].pop2015 - myWorld.countries[count].pop2010) / myWorld.countries[count].pop2010)  * 100;
            
            myWorld.countries[count].growthRate[1] =
                ((myWorld.countries[count].pop2010 - myWorld.countries[count].pop1990) / myWorld.countries[count].pop1990) * 100;
            
            myWorld.countries[count].growthRate[2] =
                ((myWorld.countries[count].pop1990 - myWorld.countries[count].pop1970) / myWorld.countries[count].pop1970) * 100;
            
            myWorld.countries[count].growthRate[3] =
                ((myWorld.countries[count].pop1970 - myWorld.countries[count].pop1950) / myWorld.countries[count].pop1950) * 100;
            
            
            toThree++;
        } while(getline(popFile, myWorld.countries[count].name));
    }
    else
    {
        cout << "Error reading file.";
    }
    popFile.close();
    
    //TASK 2 CONT.
    
    // 2015 - 2010
    temp1 = myWorld.countries[0].growthRate[0];
    for(int i = 0; i < MAXCOUNTRIES;i++)
    {
        if(myWorld.countries[i].growthRate[0] > temp1)
        {
            temp1 = myWorld.countries[i].growthRate[0];
            myWorld.largestGrowthRate[0] = i;
        }
        
    }
    
    // 2010 - 1990
    temp2 = myWorld.countries[0].growthRate[1];
    for(int i = 0; i < MAXCOUNTRIES;i++)
    {
        //cout << myWorld.countries[i].growthRate[1] << " " << myWorld.countries[i].name << endl;
        if(myWorld.countries[i].growthRate[1] > temp2)
        {
            temp2 = myWorld.countries[i].growthRate[1];
            myWorld.largestGrowthRate[1] = i;
        }
    }
    
    // 1990 - 1970
    temp3 = myWorld.countries[0].growthRate[2];
    for(int i = 0; i < MAXCOUNTRIES;i++)
    {
        if(myWorld.countries[i].growthRate[2] > temp3)
        {
            temp3 = myWorld.countries[i].growthRate[2];
            myWorld.largestGrowthRate[2] = i;
        }
    }

    // 1970 - 1950
    temp4 = myWorld.countries[0].growthRate[3];
    for(int i = 0; i < MAXCOUNTRIES;i++)
    {
        if(myWorld.countries[i].growthRate[3] > temp4)
        {
            temp4 = myWorld.countries[i].growthRate[3];
            myWorld.largestGrowthRate[3] = i;
        }
    }
    
    
    // TASK 3
    
    
    
    
    //OUTPUTS
    
    //TASK 1 OUTPUT
    cout << "~~~~~~~~~~~~The Largest Countries~~~~~~~~~~~~" << endl;
    cout << myWorld.countries[myWorld.largest[0]].pop2015 << myWorld.countries[myWorld.largest[0]].name << endl;
    cout << myWorld.countries[myWorld.largest[1]].pop2015 << myWorld.countries[myWorld.largest[1]].name << endl;
    cout << myWorld.countries[myWorld.largest[2]].pop2015 << myWorld.countries[myWorld.largest[2]].name << endl;
    
    
    //TASK 2 OUTPUT
    cout << endl;
    cout << "~~~~~~~~The Fastest Growing Countries~~~~~~~~" << endl;
    cout << "2015 - 2010: " << myWorld.countries[myWorld.largestGrowthRate[0]].name << endl;
    cout << "2010 - 1990: " << myWorld.countries[myWorld.largestGrowthRate[1]].name << endl;
    cout << "1990 - 1970: " << myWorld.countries[myWorld.largestGrowthRate[2]].name << endl;
    cout << "1970 - 1950: " << myWorld.countries[myWorld.largestGrowthRate[3]].name << endl;
    
    
    //TASK 3 AND OUTPUT
    cout << endl;
    cout << "~~~~~~~~~Potentially Large Countries~~~~~~~~~" << endl << endl;
    cout << "Growth Rate of the 3rd largest country: " << myWorld.countries[myWorld.largest[2]].growthRate[3] << endl << endl;
    quaterOfThird = myWorld.countries[myWorld.largest[2]].pop2015 * 0.25;
    for (int i = 0; i < MAXCOUNTRIES; i++)
    {
        if(myWorld.countries[i].pop2015 >= quaterOfThird && myWorld.countries[i].pop2015 < myWorld.countries[myWorld.largest[2]].pop2015)
        {
            if(myWorld.countries[i].growthRate[3] > myWorld.countries[myWorld.largest[2]].growthRate[3])
            {
                cout << myWorld.countries[i].name << endl;
            }
        }
    }
    
    
    return 0;
}
