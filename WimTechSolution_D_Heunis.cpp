//Donovan Heunis 9903175266085 09/11/2022

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct CellTowers
{
    char cCellID; //Might need to change to String to accomodate more than 24 Towers
    double dEasting,dNorthing,dLongitude,dLatitude;    
};

void CellTowerSorting(CellTowers cells)
{

}
int main()
{
    //Declare Variables used by main
    char cInputMethod = 'q';
    bool bValid = false;

    //Declare Struct CellTowers
    struct CellTowers CellTowerList;

    cout << "Welcome to Cell Tower Frequency Assigner" <<endl;

    //Choose file read or manual entry
    cout << "Please choose Input Method: (M) Manual, (T) Text File" <<endl;

    //Input Validation
    while(bValid == false)
    {
        cin >> cInputMethod;

        //If M is Entered, then all fields must manually be completed
        if(cInputMethod == 'M')
        {
            bValid = true;
            cout << "Please enter the Cell Towers ID";
            cin >> CellTowerList.cCellID;

            cout <<"Please enter the Cell Towers Easting";
            cin >> CellTowerList.dEasting;

            cout << "Please enter the Cell Towers Northing";
            cin >> CellTowerList.dNorthing;

            cout << "Please enter the Cell Towers Longitude";
            cin >> CellTowerList.dLongitude;

            cout << "Please enter the Cell Towers Latitude";
            cin >> CellTowerList.dLatitude;
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
                    cout << stextLine << endl;
                }
                inputText.close();
               // throw exception;   
            }
            catch(...)
            {

            }
            
        }
        else
        {
            cout << "Invalid Input Received, Please Enter a Valid Input Method: (M) Manual, (T) Text File" <<endl;
        }
    }
    

    
    

    
    
    

    
    
    

    
};