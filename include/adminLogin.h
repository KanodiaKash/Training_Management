#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

bool checkdate(int d, int m, int y)
{
    if (y < 1000)
    {
        return false;
    }
    if (y > 2030)
    {
        return false;
    }
    if (!(1 <= m && m <= 12))
        return false;
    if (!(1 <= d && d <= 31))
        return false;
    if ((d == 31) && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
        return false;
    if ((d == 30) && (m == 2))
        return false;
    if ((m == 2) && (d == 29) && (y % 4 != 0))
        return false;
    if ((m == 2) && (d == 29) && (y % 400 == 0))
        return true;
    if ((m == 2) && (d == 29) && (y % 100 == 0))
        return false;
    if ((m == 2) && (d == 29) && (y % 4 == 0))
        return true;

    return true;
}

 
const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 

int countLeapYears(int d[]) 
{ 
	int years = d[2]; 
	if (d[1] <= 2) 
		years--; 

	return (years / 4 - years / 100 + years / 400); 
} 


int countNoOfDays(int dt1[], int dt2[]) 
{ 
	
	long int n1 = dt1[2] * 365 ; 
    n1 += countLeapYears(dt1);
	for (int i = 0; i < dt1[1] - 1; i++) 
		n1 = n1+ monthDays[i]; 
	n1=n1+dt1[0];

	long int n2 = dt2[2] * 365 ; 
    n2 += countLeapYears(dt2);
	for (int i = 0; i < dt2[1] - 1; i++) 
		n2 = n2+ monthDays[i]; 
	n2=n2+dt2[0];

	return (n2 - n1); 
} 



bool validateString(string str) {
    bool result = true;
    for (int i=0; i<str.length(); i++) {
        if (isalpha(str[i])==false) {            
            cout<<"\n Please enter a string value only."<<endl;
            result = false;
            break;
        }
    }
    return result;
}

int batchID, nod, nop;
string technology, startDate, endDate, venueDetail, month, facultyName;

class admin
{
public:
    void createSchedule()       
    {
        cout << "\n\nBelow are the mandatory details for creating new schedule" << endl;
        cout << "\n1. Batch Id                        2. Technology Name" << endl;
        cout << "3. Start Date                      4. End Date" << endl;
        cout << "5. Total Number of Days            6. Venue Details" << endl;
        cout << "7. No. of Participants             8. Month" << endl;

        cout << "\nNow please enter the details below carefully." << endl;

        cout << "Enter the batch id : ";
        cin >> batchID;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cin.ignore();

        cout << "Enter the technology name : ";
        getline(cin, technology);          
        
        if (!validateString(technology)) {
            createSchedule();
        }

        cout << "Enter the start date of traning (Use Format {DD-MM-YYYY}) : ";
        getline(cin, startDate);

        string T;
        int arr[3];
        int i = 0, result;

        stringstream X(startDate);
        while (getline(X, T, '-'))
        {
            int r = stoi(T);
            arr[i] = r;
            i++;
        }

        result = checkdate(arr[0], arr[1], arr[2]);
        int date1[] = {arr[0], arr[1], arr[2]};
        i = 0;

        if (result == 0)
        {
            cout << "\nOops! you have entered wrong date/format." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the end date of training (Use Format {DD-MM-YYYY}) : ";
        getline(cin, endDate);

        stringstream Y(endDate);
        while (getline(Y, T, '-'))
        {
            int r = stoi(T);
            arr[i] = r;
            i++;
        }
        result = checkdate(arr[0], arr[1], arr[2]);
        int date2[] = {arr[0], arr[1], arr[2]};
        i = 0;

        if (result == 0)
        {
            cout << "\nOops! you have entered wrong date/format." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

       int diff = countNoOfDays(date1, date2);
       int nod=diff;
       cout << "\nYour number of training days are : " << diff << " days" << endl;

        cout << "Enter the venue : ";
        getline(cin, venueDetail);

        if (!validateString(venueDetail)) {
            createSchedule();
        }

        cout << "Enter the total number of participants : ";
        cin >> nop;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the month of training to be schedule : ";
        cin >> month;

        if (!validateString(month)) {
            createSchedule();
        }

        fstream f1;
        f1.open("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/schedule.csv", ios::app);
        if(!f1){
            cout<<"No such file found"<<endl;
        }
        else{
            f1 <<"\n"<< batchID << " " << technology << " " << startDate << " " << endDate << " " << nod << " " << venueDetail << " " << nop << " " << month;
            f1.close();
            cout << "\n New Schedule Has Been Created.\n" << endl;
        }

        string opt;

        cout << "\nDo you want to create another schdedule (yes/no) : ";
        cin >> opt;

        if (opt == "yes" || opt == "y" || opt == "YES" || opt == "Y" || opt=="Yes")
        {
            createSchedule();
        }
        else
        {
            adminModules();
        }
    }

    void updateSchedule()       
    {
        fstream file;      

        file.open("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/schedule.csv", ios::in);
        int count = 0;
        vector<string> v;

        string details, line, word;

        while (getline(file, line)) 
        {
            count++;
        }
        file.close();

        file.open("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/schedule.csv", ios::in);
        for (int i = 0; i < count; i++)
        {
            getline(file, details);
            stringstream s(details);
            while (getline(s, word, ' '))
            {
                v.push_back(word);
            }
        }
        file.close();

        string id;
        cout << "\nEnter batch id for updating the schedule : ";
        cin >> id;

        int i = 0;
        int flag = 0;
        string tech, sdate, edate, nd, venue, np, mos;

        while (i < v.size())
        {
            if (v[i] == id)
            {
                flag = 1;
                cout << "Enter technology : ";
                cin >> tech;
                v[i + 1] = tech;

                cout << "Enter start date  : ";
                cin >> sdate;

                v[i + 2] = sdate;

                cout << "Enter end date : ";
                cin >> edate;

                v[i + 3] = edate;

                cout << "Enter number of days : ";
                cin >> nd;

                v[i + 4] = nd;

                cout << "Enter venue : ";
                cin >> venue;
                
                v[i + 5] = venue;

                cout << "Enter number of participants : ";
                cin >> nop;

                v[i + 6] = to_string(nop);

                cout << "Enter month of start : ";
                cin >> mos;
                v[i + 7] = mos;
            }
            i = i + 8;
        }

        if (flag == 0)
        {
            cout << "\nNo Such Record Found for batch_id...!! \nTaking you back to Dashboard" << endl;
            adminModules();
        }

        file.open("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/schedule.csv", ios::out | ios::trunc);    //mean
        int z = 0;
        while (z < v.size())       
        {
            file << v[z] << " " << v[z + 1] << " " << v[z + 2] << " " << v[z + 3] << " " << v[z + 4] << " " << v[z + 5] << " " << v[z + 6] << " " << v[z + 7] << endl;
            z = z + 8;
        }

        file.close();

        cout << "\nYour schedule has been updated." << endl;

        string option;
        cout << "\nDo you want to update a schedule again type(yes/no) : " << endl;
        cin >> option;

        if (option == "yes" || option == "Y" || option == "YES" || option == "y")
        {
            updateSchedule();
        }
        else
        {
            cout << "Taking you back to dashboard" << endl;
            adminModules();
        }
    }

    void allotTrainer()         
    {
        string techName;
        int flag = 0;
        cout << "\n Please enter a faculty name : ";
        cin >> facultyName;

        if (!validateString(facultyName)) {
            cout<<"Error!!! \nPlease enter a valid faculty name"<<endl;
            allotTrainer();
        }

        cout << "\n Please enter the technology name for which you want to assign trainer : ";
        cin >> techName;

        if (!validateString(techName)) {
            cout<<"Error!!! \nPlease enter a valid technology name"<<endl;
            allotTrainer();
        }

        ifstream f2("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/schedule.csv");  //no ios app or ios on
        while (f2 >> batchID >> technology >> startDate >> endDate >> nod >> venueDetail >> nop >> month)
        {
            transform(technology.begin(), technology.end(), technology.begin(), ::tolower);
            transform(techName.begin(), techName.end(), techName.begin(), ::tolower);

            ofstream f3("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/trainerallotment.csv", ios::app);
            if (technology == techName)
            {
                flag = 1;
                f3 << batchID << " " << technology << " " << startDate << " " << endDate << " " << nod << " " << venueDetail << " " << nop << " " << month << " " << facultyName << endl;
            }
        }

        if (flag == 0)
        {
            cout << "\nTechnology is not found" << endl;
        }

        string opt;
        cout << "\nDo you want to continue with allotment trainer (yes/no) : ";
        cin >> opt;

        if (opt == "yes" || opt == "Y" || opt == "YES")
        {
            allotTrainer();
        }
        else
        {
            cout << "\nTaking you on your dashboard..." << endl;
            adminModules();
        }
    }

    void generateReport()           
    {
        string mon, tname;
        int count = 1;
        cout << "\nPlease enter a month for which you want to generate report : ";
        cin >> mon;

        if (!validateString(mon)) {
            generateReport();
        }

        cout << "\nPlease enter a technology name : ";
        cin >> tname;

        if (!validateString(tname)) {
            generateReport();
        }

        ifstream f3("C:/Users/ASUS/Desktop/iitg_docs_kash/Training-Schedule-Management-main/Project_Flies/data/schedule.csv");
        while (f3 >> batchID >> technology >> startDate >> endDate >> nod >> venueDetail >> nop >> month)
        {
            transform(month.begin(), month.end(), month.begin(), ::tolower);
            transform(mon.begin(), mon.end(), mon.begin(), ::tolower);
            transform(tname.begin(), tname.end(), tname.begin(), ::tolower);
            transform(technology.begin(), technology.end(), technology.begin(), ::tolower);

            if (month == mon && technology == tname)
            {
                cout << "\n\nSchedule --> " << count << endl;
                cout << "Batch Id                :            " << batchID 
                    << "\nTechnology              :            " << technology 
                    << "\nStart Date              :            " << startDate 
                    << "\nEnd Date                :            " << endDate 
                    << "\nNumber of Days          :            " << nod 
                    << "\nVenue Details           :            " << venueDetail 
                    << "\nNumber of Participants  :            " << nop << "\nMonth                   :            " << month << endl;
                count++;
            }
        }

        if (count == 1)
        {
            cout << "\nYou haven't created a schedule for this month. \nPlease create schedule for this month and try to generate report." << endl;
        }
        string opt;
        cout << "Do you want to continue with the session (yes/no) : ";
        cin >> opt;

        if (opt == "yes" || opt == "y" || opt == "YES" || opt == "Y")
        {
            adminModules();
        }
        else
        {
            cout << "See you again." << endl;
            exit(0);
        }
    }

    void adminModules()
    {
        cout << "\nHere's your Dashboard \nPlease enter your choice to perform particular tasks" << endl;
        cout << "\n\n--------------------------------------------------------" << endl;
        cout << "\tEnter 1 -> To Create New Schedule" << endl;
        cout << "\tEnter 2 -> To Update Existing Schedule" << endl;
        cout << "\tEnter 3 -> To Allot A Trainer" << endl;
        cout << "\tEnter 4 -> To Generate Report" << endl;
        cout << "\tEnter 5 -> To Quit From This Session" << endl;
        cout << "--------------------------------------------------------" << endl;

        int choice;
        cout << "\n\nPlease enter your choice : ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nPlease enter a number!!" << endl;
            adminModules();
        }
        else
        {
            switch (choice)
            {
            case 1:
                createSchedule();
                break;
            case 2:
                updateSchedule();
                break;
            case 3:
                allotTrainer();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                int n;
                cout << "\nWhere you want to move \nPlease choose from below options" << endl;
                cout << "\nChoose 1 -> Go Back To Dashboard \nChoose 2 -> Exit From The System" << endl;

                cout << "\n\nPlease enter your choice here : ",
                    cin >> n;

                if (n == 1)
                {
                    adminModules();
                }
                else if (n == 2)
                {
                    cout << "See you again" << endl;
                    exit(0);
                }
                else
                {
                    cout << "Please choose correct option" << endl;
                    adminModules();
                }
                break;

            default:
                cout << "Please choose valid Option" << endl;
                adminModules();
                break;
            }
        }
    }
};
