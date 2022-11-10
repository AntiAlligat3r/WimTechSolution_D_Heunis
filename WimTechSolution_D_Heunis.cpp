//Donovan Heunis 9903175266085 09/11/2022

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<algorithm>

using namespace std;

struct CellTowers
{
    string sCellID;
    double dEasting,dNorthing,dLongitude,dLatitude;    
};
struct CellTowerDistances
{
    string sCellID1,sCellID2;
    double dDistance;
};
struct CellTowerFrequencyAssignment
{
    string sCellID1,sCellID2;
    double dDistance;
    int iFrequency;
};
bool CellTowerSorting(CellTowerDistances CellDistance1,CellTowerDistances CellDistance2)
{
 //Compares all distances and sorts them from largest to smallest
    if(CellDistance1.dDistance > CellDistance2.dDistance)
    {
        return true;
    }
    return false;
}

void FurthestCellTowersCalc(CellTowers cell1,CellTowers cell2,CellTowerDistances CellDistance)
{
    //Struct just needs to be divided into 2 to get all the unique tower pairs
    for(int i = 0;i< size(cell1.sCellID);i++)
    {
        for(int z = 0; z < size(cell1.sCellID);z++)//double for loop to run entire list with all possibilities
        {
            CellDistance.sCellID1 = cell1.sCellID[i];//creating a tower pair
            CellDistance.sCellID2 = cell2.sCellID[z];
            CellDistance.dDistance = LongLatDistance(cell1.dLongitude,cell2.dLongitude,cell1.dLatitude,cell2.dLatitude); //Calls LongLatDistance to calculate the distance between 2 towers
        }
    }
}
double LongLatDistance(double _dLongitude1,double _dLongitude2,double _dLatitude1,double _dLatitude2)
{
    double _distance = 0.0,_haversineLatitude = 0.0,_harversineLongitude = 0.0;
    const double RADIUS = 6371;// Earths avg Radius in km

    _haversineLatitude = pow(sin(0.5 * (_dLatitude2 - _dLatitude1)),2); //sin²((θ₂ - θ₁)/2) -> sin²(0.5*(θ₂ - θ₁))
    _harversineLongitude = cos(_dLatitude1) * cos(_dLatitude2) * pow(sin(0.5 * (_dLongitude2 - _dLongitude1)),2); //cosθ₁⋅cosθ₂⋅sin²(0.5*(φ₂ - φ₁))
    _distance = 2*RADIUS*asin(sqrt(_haversineLatitude + _harversineLongitude)); //2R⋅sin⁻¹(√[sin²((θ₂ - θ₁)/2) + cosθ₁⋅cosθ₂⋅sin²((φ₂ - φ₁)/2)]) - haversine formula , calculation can be 0.5% incorrect due to spheroid shape of earth

    
    return _distance;
}

void txtStringSplit(string _sInput,string _sDelimiter, string *ptrInput)
{
    int stringStart = 0;
    int stringEnd = _sInput.find(_sDelimiter); // finds the position of the given delimiter in the string _sInput

    int i = 0;
    while(stringEnd != -1)
    {
        //create array to capture each line in txt file that is broken up into the next "Relevant values", then use Pointers to read the data from the array before it is overwritten by next cycle
        *(ptrInput + i) = _sInput.substr(stringStart, stringEnd - stringStart);// Assigns part of a string to input array via pointers. looks for the delimiter and copies the string from start to the delimiter, exluding delimiter
        stringStart = stringEnd + _sDelimiter.size(); //moving the starting point to the previous end point +1 to exlude delimiter
        stringEnd = _sInput.find(_sDelimiter,stringStart);//moving the end point to the next delimiter
        i++;
    }
    i++;
    *(ptrInput + i) = _sInput.substr(stringStart, stringEnd - stringStart);
}
void FrequencyAssignment(CellTowerDistances CellDistance[],CellTowerFrequencyAssignment CellFrequency[])
{
    //this needs work, need to rethink the frequency assignment so that even though tower A and B are far away and C and D are far away, A and B cannot have the same frequency as tower C is next to tower A (for example)
    int numCellTowers = ((sizeof(CellDistance)/sizeof(CellDistance[0].sCellID1))/2); //half of the list is repeated
    int frequency = 110,iCount = 1;
    double towersPerFrequency = numCellTowers / 6; //6 Frequencies to work with
    towersPerFrequency = (int)round(towersPerFrequency);
    for(int i = 0;i < numCellTowers;i++)
    {
        if(iCount == towersPerFrequency)
        {
            frequency++;//increments the frequency once max calculated frequency users are reached
        }
        CellFrequency[i].sCellID1 = CellDistance[i].sCellID1;
        CellFrequency[i].sCellID2 = CellDistance[i].sCellID2;
        CellFrequency[i].dDistance = CellDistance[i].dDistance;
        CellFrequency[i].iFrequency = frequency;
        cout << "Frequency " << frequency << " has been assigned to towers "<<CellFrequency[i].sCellID1 <<" and "<< CellFrequency[i].sCellID2 <<" with a distance of "<< CellFrequency[i].dDistance <<" between them" << endl;
        iCount++;
    }
}
void FrequencyAssignmentNew(CellTowerDistances CellDistance[],CellTowerFrequencyAssignment CellFrequency[])
{
    //This is a new approach I tried, not sure it works to eliminate the problem
    int numCellTowers = ((sizeof(CellDistance)/sizeof(CellDistance[0].sCellID1))/2); //half of the list is repeated
    int frequency = 110,iCount = 1;
    double towersPerFrequency = numCellTowers / 6; //6 Frequencies to work with
    towersPerFrequency = (int)round(towersPerFrequency);
    for(int i = 0;i < numCellTowers;i++)
    {
        if(iCount == towersPerFrequency)
        {
            frequency++;//increments the frequency once max calculated frequency users are reached
        }
        for(int z = 0;z < numCellTowers;z++)
        {
            if((CellDistance[z].sCellID2 == CellDistance[i].sCellID1) && (CellDistance[z].dDistance < 100)  &&(CellDistance[z].dDistance > 0))
            {
                //if the distance is between 0m and 100m , a new frequency that is not used by the other close friends must be used 
                if(frequency != 116)
                    CellFrequency[i].iFrequency = frequency+1;
                else
                    CellFrequency[i].iFrequency = frequency-1;
                break;
            }
        }
        CellFrequency[i].sCellID1 = CellDistance[i].sCellID1;
        CellFrequency[i].sCellID2 = CellDistance[i].sCellID2;
        CellFrequency[i].dDistance = CellDistance[i].dDistance;

        if(CellFrequency[i].iFrequency == NULL)
            CellFrequency[i].iFrequency = frequency;

        cout << "Frequency " << frequency << " has been assigned to towers "<<CellFrequency[i].sCellID1 <<" and "<< CellFrequency[i].sCellID2 <<" with a distance of "<< CellFrequency[i].dDistance <<endl;
        iCount++;
    }
}
int main()
{
    //Declare Variables used by main
    char cInputMethod = 'q',cInputFlag = 'a';
    bool bValid = false, bLoop = true, bValidYesNo = false;
    int iCount = 0;
    string arrProperties[5];
    string *ptr_arr;

    ptr_arr = arrProperties;
    //Declare Struct CellTowers with size 100
    struct CellTowers CellTowerList[100];
    struct CellTowerDistances CellDistance[100];
    struct CellTowerFrequencyAssignment CellFrequency[100];

    cout << "Welcome to Cell Tower Frequency Assigner" <<endl;

    //Choose file read or manual entry
    cout << "Please choose Input Method: (M) Manual, (T) Text File" <<endl;

    //Input Validation
    while(!bValid)
    {
        cin >> cInputMethod;

        //If M is Entered, then all fields must manually be completed
        if(cInputMethod == 'M')
        {
            bValid = true;
            do
            {
                cout << "Please enter the Cell Towers ID :";
                cin >> CellTowerList[iCount].sCellID;

                cout <<"Please enter the Cell Towers Easting :";
                cin >> CellTowerList[iCount].dEasting;

                cout << "Please enter the Cell Towers Northing :";
                cin >> CellTowerList[iCount].dNorthing;

                cout << "Please enter the Cell Towers Longitude :";
                cin >> CellTowerList[iCount].dLongitude;

                cout << "Please enter the Cell Towers Latitude :";
                cin >> CellTowerList[iCount].dLatitude;
                cout << endl;

                do
                {
                    cout << "Do you want to Add another Cell Tower?/n(Y) Yes/(N) No: ";
                    cin >> cInputFlag;

                    if(toupper(cInputFlag) == 'N')
                    {
                        bLoop = false;
                        bValidYesNo = true;
                    }
                    else if(toupper(cInputFlag) == 'Y')
                        bValidYesNo = true;
                    else
                        cout << "Please enter a valid Answer";

                } while (!bValidYesNo); //Checks if Answer entered is Y or N
                
            }while(bLoop);
            
        }
        else if(cInputMethod == 'T')
        {
            bValid = true;
            ifstream inputText;
            string stextLine;
            
            try
            {
                inputText.open("Test.txt");
                while(!inputText.eof())
                {
                    getline(inputText,stextLine);
                    txtStringSplit(stextLine,",",ptr_arr); //Populate Pointer array

                    CellTowerList[iCount].sCellID = *(ptr_arr + 0); //assigns sCellID a Value from the Pointer Array
                    CellTowerList[iCount].dEasting = stold(*(ptr_arr + 1));
                    CellTowerList[iCount].dNorthing = stold(*(ptr_arr + 2));
                    CellTowerList[iCount].dLongitude = stold(*(ptr_arr + 3));
                    CellTowerList[iCount].dLatitude = stold(*(ptr_arr + 4));
                }
                inputText.close();
               // throw exception;   
            }
            catch(...)
            {
                cout << "Error Encountered Opening Input File" << endl;//ususally the File does not exist
            }
            
        }
        else
        {
            cout << "Invalid Input Received, Please Enter a Valid Input Method: (M) Manual, (T) Text File" <<endl;
        }
    }

    FurthestCellTowersCalc(CellTowerList[100],CellTowerList[100],CellDistance[100]);

    int i = sizeof(CellDistance)/sizeof(CellDistance[0].dDistance);
    sort(CellDistance,CellDistance + i,CellTowerSorting);//with help of Cell Tower Sorting , will sort according to farthest Distances

    FrequencyAssignment(CellDistance,CellFrequency);
    
    return 0;
};








