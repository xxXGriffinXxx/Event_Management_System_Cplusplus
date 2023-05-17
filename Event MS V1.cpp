#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<string>
#include<Windows.h>
#include<algorithm> 
#include<cctype>
#include<locale>
#include<bits/stdc++.h>
using namespace std;





//string trim from left function
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

//string trim from right function
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

//string trim from both ends function
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

//delete a line from file 
void delete_line(const char *file_name, int n)
{
    ifstream is(file_name); 

    ofstream ofs;
    ofs.open("temp.txt", ofstream::out);
  
    char c;
    int line_no = 1;
    while (is.get(c))
    {
        
        if (c == '\n')
        {
            line_no++;
        }
        
        if (line_no != n)
        {
            ofs << c;
        }

        
    }

    ofs.close();
    is.close();
    remove(file_name);
    rename("temp.txt", file_name);
}

//convert string to char array using for loop
void string_to_char(string str, char *ch)
{
    for (int i = 0; i < str.length(); i++)
    {
        ch[i] = str[i];
    }
}


//get current date and time
const time_t now = time(nullptr);
const tm calendar_time = *localtime( addressof(now) );

string cyear = to_string(calendar_time.tm_year + 1900);
string cmonth = to_string(calendar_time.tm_mon + 1);
string cday = to_string(calendar_time.tm_mday);
string chour = to_string(calendar_time.tm_hour);
string cminute = to_string(calendar_time.tm_min);



class Event 
{
    string title;
    string day;
    string month;
    string year;
    string hour;
    string minute;
    string date;        //mm/dd/yyyy
    string time;        //hh:mm

    public:

    Event() 
    {
        title = "";
        date = "";
        time = "";
    }

    Event(string ti, string d, string mo, string y, string h, string mi) 
    {
        title = ti;
        day = d;
        month = mo;
        year = y;
        hour = h;
        minute = mi;
        date = d + "/" + mo + "/" + y;
        time = h + ":" + mi;
    }

    Event(string d, string mo, string y, string h, string mi) 
    {
        day = d;
        month = mo;
        year = y;
        hour = h;
        minute = mi;
        date = d + "/" + mo + "/" + y;
        time = h + ":" + mi;
    }
   
    Event& operator=(const Event& e) 
    {
        title = e.title;
        day = e.day;
        month = e.month;
        year = e.year;
        hour = e.hour;
        minute = e.minute;
        date = e.date;
        time = e.time;
        return *this;
    }

    Event operator+(const Event& e) 
    {
        Event temp;
        temp.title = title + " and " + e.title;
        temp.date = "1. " + date + "2. " + e.date;
        temp.time = "1. " + time + "2. " + e.time;
        return temp;
    } 

    friend ostream& operator<<(ostream& out, const Event& e) 
    {
        out << "Date: " << e.date << endl;
        out << "Time: " << e.time << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Event& e) 
    {
        cout << "Enter Title: ";
        getline(in, e.title);
        cout << "Enter Date (mm/dd/yyyy): ";
        getline(in, e.date);
        cout << "Enter Time (hh:mm): ";
        getline(in, e.time);
        return in;
    }

    bool operator==(const Event& e) 
    {
        if (title == e.title && date == e.date && time == e.time) 
        {
            return true;
        }
        return false;
    }
};

void add();
void view();
void del();



int main () 
{
    system("cls");


    ifstream event;                          //check if file is working or exists 
    event.open("event.txt");
    if (!event) 
    {
        cout<<"Error in opening file, Fixing...";
        Sleep(1000);
        ofstream ofile;
        ofile.open("event.txt");
        ofile.close();
        ifstream ifile;
        ifile.open("event.txt");
        if (!ifile) 
        {
            cout<<"Error in fixing file, Exiting...";
            Sleep(1000);
            exit(1);
        }
        cout<<"File Fixed, Restarting...";
        Sleep(1000);
    }
    event.close();



    if(cmonth.length() == 1)          //check if month is single digit
    {
        cmonth = "0" + cmonth;
    }

    char a;



    system("cls");
    
    cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";


    cout<<"1. Add Event \n"
          "2. View Event \n"
          "3. Delete Event \n"
          "0. Exit \n\n"
          "Please Enter the number of your choice: ";
    cin>>a;

    switch (a)
    {
    case '0':
        cout<<"Exiting...";
        Sleep(2000);
        exit(0);
        break;

    case '1':
        system("cls");
        cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
        cout<<"ADD NEW EVENT\n\n";
        add();
        break;

    case '2':
        system("cls");
        cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
        cout<<"VIEW EVENT";
        view();
        break;

    case '3':
        system("cls");
        cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
        cout<<"DELETE EVENT";
        del();
        break;
    
    default:
        cout<<"Invalid Input";
    }


return 0;
}

void add() {
    
    int a;
    
    cout<<"\n\n";
    cout<<"1. Add New Event \n"
          "2. Add Event Based on Existing Event \n\n"
          "Please Enter the number of your choice: ";
    cin>>a;
    cout<<"\n\n";

    if (a==1) 
    {
        string T;
        char d[2];
        char mo[2];
        char y[4];
        char h[2];
        char m[2];

        string td1;
        string tmo1;
        string ty1;
        string th1;
        string tm1;

        a:
        system("cls");
        cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
        cout<<"ADD NEW EVENT\n\n\n\n";

        cout<<"Enter the title of the event: ";
        getline(cin >> ws, T);
        trim(T);
        cout<<"\nEnter the date of the event(days dd): ";
        cin>>d[0]>>d[1];

        cout<<"\nEnter the month of the event(mm): ";
        cin>>mo[0]>>mo[1];

        if(mo[0] > '1' && mo[1] > '2' || mo[0] == '0' && mo[1] == '0')
        {
            cout<<"Invalid Month";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '2' && d[0] > '2' && d[1] > '8')
        {
            cout<<"Invalid Feburary Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '3' && d[0] > '3' && d[1] > '1')
        {
            cout<<"Invalid March Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '4' && d[0] > '3' && d[1] > '0')
        {
            cout<<"Invalid April Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '5' && d[0] > '3' && d[1] > '1')
        {
            cout<<"Invalid May Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '6' && d[0] > '3' && d[1] > '0')
        {
            cout<<"Invalid June Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '7' && d[0] > '3' && d[1] > '1')
        {
            cout<<"Invalid July Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '8' && d[0] > '3' && d[1] > '1')
        {
            cout<<"Invalid August Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '0' && mo[1] == '9' && d[0] > '3' && d[1] > '0')
        {
            cout<<"Invalid September Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '1' && mo[1] == '0' && d[0] > '3' && d[1] > '1')
        {
            cout<<"Invalid October Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '1' && mo[1] == '1' && d[0] > '3' && d[1] > '0')
        {
            cout<<"Invalid November Date";
            Sleep(1000);
            goto a;
        }

        if(mo[0] == '1' && mo[1] == '2' && d[0] > '3' && d[1] > '1')
        {
            cout<<"Invalid December Date";
            Sleep(1000);
            goto a;
        }

        if(d[0] <= '0' && d[1] <= '0')
        {
            cout<<"Invalid Date";
            Sleep(1000);
            goto a;
        }

        
        cout<<"\nEnter the year of the event(yyyy): ";
        cin>>y[0]>>y[1]>>y[2]>>y[3];
        


        for(int i = 0; i < sizeof(d); ++i) 
        {
            td1 += d[i];
        }

        for(int i = 0; i < sizeof(mo); ++i) 
        {
            tmo1 += mo[i];
        }

        for(int i = 0; i < sizeof(y); ++i) 
        {
            ty1 += y[i];
        }

        int nd = stoi(td1);
        int nmo = stoi(tmo1);
        int ny = stoi(ty1);

        int ncd = stoi(cday);
        int ncmo = stoi(cmonth);
        int ncy = stoi(cyear);

        if(ny < ncy)
        {
            cout<<"You can add only future events!! Resuming...";
            Sleep(2000);
            goto a;
        }

        if(ny == ncy && nmo < ncmo)
        {
            cout<<"You can add only future events!! Resuming...";
            Sleep(2000);
            goto a;
        }
        
        if (ny == ncy &&nmo == ncmo && nd < ncd)
        {
            cout<<"You can add only future events!! Resuming...";
            Sleep(2000);
            goto a;
        }
        
        
        
        cout<<"\nEnter the time in hours (hh, 00-24): ";
        cin>>h[0]>>h[1];
        if( (h[0] > '2' && h[1] > '4') || (h[0] < '0' && h[1] < '0') )
        {
            cout<<"Invalid Hour";


            Sleep(1000);
            goto a;
        }

        cout<<"\nEnter the time in minutes (00-60): ";
        cin>>m[0]>>m[1];


        for(int i = 0; i < sizeof(h); ++i) 
        {
            th1 += h[i];
        }

        for(int i = 0; i < sizeof(m); ++i) 
        {
            tm1 += m[i];
        }

        int nh = stoi(th1);
        int nm = stoi(tm1);
        int nch = stoi(chour);
        int ncm = stoi(cminute);

        if( (m[0] > '6' && m[1]) || (m[0] < '0' && m[1] < '0') )
        {
            cout<<"Invalid Minute";
            Sleep(1000);
            goto a;
        }

        if ( (ny == ncy) && (nmo == ncmo) && (nd == ncd) )
        {
            if ( (nh < nch) || (nh == nch && nm < ncm) )
            {
                cout<<"You can add only future events!! Resuming...";
                Sleep(2000);
                goto a;
            }
        }
        


        cout<<"\n\n";

        cout<<"Title: "<<T<<"\n"
              "Date: "<<d[0]<<d[1]<<"-"<<mo[0]<<mo[1]<<"-"<<y[0]<<y[1]<<y[2]<<y[3]<<"\n"
              "Time: "<<h[0]<<h[1]<<":"<<m[0]<<m[1]<<"\n\n";

        string td;
        string tmo;
        string ty;
        string th;
        string tm;

        for (int i = 0; i < 2; i++)             //char to string
        {
            td += d[i];
            tmo += mo[i];
            th += h[i];
            tm += m[i];
        }
        for (int i = 0; i < 4; i++)             //char to string
        {
            ty += y[i];
        }
        

        ofstream outfile(T + ".txt" , ios::trunc);
        outfile << T << endl << td << endl << tmo << endl << ty << endl << th << endl << tm << endl;
        outfile.close();  

        fstream add("event.txt", ios::app);
        add << T << endl;
        add.close();

        cout<<"(1) Repeat            \n"
              "(2) Return to Home    \n"
              "(0) Exit              \n"
              "Please Enter the desired operation number: ";
        int opt;
        cin>>opt;

        if(opt == 1) {
            cout<<"Processing... \n";
            Sleep(1000);
            goto a;
        }

        else if(opt == 2) {
            cout<<"Processing... \n";
            Sleep(1000);
            main();
        }

        else if(opt == 0) {
            cout<<"Exiting... \n";
            Sleep(1000);
            exit(0);
        }

        
        
    }

    else if (a==2) 
    {
        string T;
        string tdate;
        string tmonth;
        string tyear;
        string thour;
        string tminute;

        b:

        system("cls");
        cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
        cout<<"ADD EVENT BASED ON EXISTING EVENT \n\n\n";

        cout<<"Following are the events in your calendar: \n";

        ifstream inaddview("event.txt");
        string L;
        while (getline(inaddview, L))
        {
            cout<<L<<"\n";
        }
        inaddview.close();

        cout<<"\n\n\nEnter the title of the event (Enter 0 if none): ";
        getline(cin >> ws, T);
        trim(T);

        if (T == "0") {
            cout<<"Returning to Home... \n";
            Sleep(1000);
            main();
        }

        ifstream inaddget(T + ".txt");
        if(!inaddget) {
            cout<<"Event not found!! Resuming... \n";
            Sleep(2000);
            goto b;
        }
        getline(inaddget, tdate);
        getline(inaddget, tmonth);
        getline(inaddget, tyear);
        getline(inaddget, thour);
        getline(inaddget, tminute);
        inaddget.close();

        Event curr(cday, cmonth, cyear, chour, cminute);
        Event exist(tdate, tmonth, tyear, thour, tminute);

        if (curr == exist) {
            cout<<"Existing Event has passed, you can add only future Events!! Resuming...";
            Sleep(2000);
            goto b;
        }

        Event newevent = exist;
        cout<<"Event Created from selected Event: \n";
        cout<<"Title: "<<T<<"\n";
        cout<<newevent;

        cout<<"\n\nEnter Title for the new event: ";
        getline(cin >> ws, T);
        trim(T);

        cout<<"\n\nDo you want to edit the date and time of the event? (Y/N): ";
        char ch;
        cin>>ch;



        if (ch == 'Y' || ch == 'y') {

            char d[2];
            char mo[2];
            char y[4];
            char h[2];
            char m[2];


            cout<<"\nEnter the day: ";
            cin>>d[0]>>d[1];
            cout<<"Enter the month: ";
            cin>>mo[0]>>mo[1];
            cout<<"Enter the year: ";
            cin>>y[0]>>y[1]>>y[2]>>y[3];
            cout<<"Enter the hour: ";
            cin>>h[0]>>h[1];
            cout<<"Enter the minute: ";
            cin>>m[0]>>m[1];

            for (int i = 0; i < 2; i++)             //char to string
            {
                tdate += d[i];
                tmonth += mo[i];
                thour += h[i];
                tminute += m[i];
            }

            for (int i = 0; i < 4; i++)             //char to string
            {
                tyear += y[i];
            }

            cout<<"\n\nEvent Created: \n";
            cout<<"Title: "<<T<<"\n"
                  "Date: "<<tdate<<"-"<<tmonth<<"-"<<tyear<<"\n"
                  "Time: "<<thour<<":"<<tminute<<"\n\n";


            ofstream inaddmake(T + ".txt" , ios::trunc);
            inaddmake << T << endl;
            inaddmake << tdate << endl;
            inaddmake << tmonth << endl;
            inaddmake << tyear << endl;
            inaddmake << thour << endl;
            inaddmake << tminute << endl;
            inaddmake.close();

            ofstream inadd("event.txt", ios::app);
            inadd << T << endl;
            inadd.close();


        }

        else {
            
            ofstream inaddmake(T + ".txt" , ios::trunc);
            inaddmake << T << endl;
            inaddmake << tdate << endl;
            inaddmake << tmonth << endl;
            inaddmake << tyear << endl;
            inaddmake << thour << endl;
            inaddmake << tminute << endl;
            inaddmake.close();

            ofstream inadd("event.txt", ios::app);
            inadd << T << endl;
            inadd.close();


            cout<<"\nDate and Time of the event will be same as the existing event. \n\n";
            cout<<"(1)Repeat     \n"
                  "(2)Return to home    \n"
                  "(0)Exit       \n"
                  "Please Enter the desired operation number: ";
            int opt;
            cin>>opt;
            
            if(opt == 1) {
                cout<<"Processing... \n";
                Sleep(1000);
                goto b;
            }

            else if(opt == 2) {
                cout<<"Processing... \n";
                Sleep(1000);
                main();
            }

            else if(opt == 0) {
                cout<<"Exiting... \n";
                Sleep(1000);
                exit(0);
            }
        }
      

    }

    else 
    {
        cout<<"Invalid Input!! Resuming... \n";
        Sleep(2000);
        main();
    }

}

void view() {

        system("cls");
        cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
        cout<<"VIEW EVENT\n";

        string T;
        string title;
        string tdate;
        string tmonth;
        string tyear;
        string thour;
        string tminute;

        cout<<"\n\n\nFollowing are the events in your calendar: \n";
        fstream viewall("event.txt");
        string L;
        while (getline(viewall, L))
        {
            cout<<L<<"\n";
        }
        viewall.close();

        cout<<"\n\n\nEnter the title of the event (Enter 0 if none): ";
        getline(cin >> ws, T);
        trim(T);


        if (T == "0") {
            cout<<"Bypassing...";
            Sleep(1000);
            main();
        }


        ifstream infile2(T + ".txt");
        getline(infile2, title);
        getline(infile2, tdate);
        getline(infile2, tmonth);
        getline(infile2, tyear);
        getline(infile2, thour);
        getline(infile2, tminute);
        infile2.close();

        cout<<"Title: "<<title<<"\n"
              "Date:  "<<tdate<<"/"<<tmonth<<"/"<<tyear<<"\n"
              "Time:  "<<thour<<":"<<tminute<<"\n\n\n";


        //find the difference between the current time and the event time
        int tdate1, tmonth1, tyear1, thour1, tminute1;
        int cdate1, cmonth1, cyear1, chour1, cminute1;

        tdate1 = stoi(tdate);
        tmonth1 = stoi(tmonth);
        tyear1 = stoi(tyear);
        thour1 = stoi(thour);
        tminute1 = stoi(tminute);

        cdate1 = stoi(cday);
        cmonth1 = stoi(cmonth);
        cyear1 = stoi(cyear);
        chour1 = stoi(chour);
        cminute1 = stoi(cminute);

        int rdate, rmonth, ryear, rhour, rminute;
        rdate = tdate1 - cdate1;
        rmonth = tmonth1 - cmonth1;
        ryear = tyear1 - cyear1;
        rhour = thour1 - chour1;
        rminute = tminute1 - cminute1;

        if (rminute < 0) {
            rminute = rminute + 60;
            rhour = rhour - 1;
        }

        if (rhour < 0) {
            rhour = rhour + 24;
            rdate = rdate - 1;
        }

        if (rdate < 0) {
            rdate = rdate + 30;
            rmonth = rmonth - 1;
        }

        if (rmonth < 0) {
            rmonth = rmonth + 12;
            ryear = ryear - 1;
        }

        cout<<"Time remaining: \n"
              "Years: "<<ryear<<"\n"
              "Months: "<<rmonth<<"\n"
              "Days: "<<rdate<<"\n"
              "Hours: "<<rhour<<"\n"
              "Minutes: "<<rminute<<"\n\n\n";





        cout<<"Repeat           (1) \n"
              "Return to Home   (2) \n"
              "Exit             (0) \n"
              "Please Enter the desired operation number: ";
        int opt;
        cin>>opt;

        if(opt == 1) {
            cout<<"Processing... \n";
            Sleep(1000);
            view();
        }

        else if(opt == 2) {
            cout<<"Processing... \n";
            Sleep(1000);
            main();
        }

        else if(opt == 0) {
            cout<<"Exiting... \n";
            Sleep(1000);
            exit(0);
        }

}

void del() {
    system("cls");
    cout<<"\t\t\t\tW E L C O M E  T O  E V E N T  M A N A G E R \n\n\n";
    cout<<"DELETE EVENT";

    string tempT;

    cout<<"\n\n\nFollowing are the events in your calendar: \n";
    fstream view("event.txt");
    string line;
    int i=1;
        while (getline(view, line))
        {

            cout << i <<". "<< line << endl;
            ++i;
        }
    view.close();

    char lineno[1];

    cout<<"\n\nEnter the TITLE of the event you want to delete(Enter 0 if none): ";
    getline(cin >> ws, tempT);
    trim(tempT);
    if(tempT == "0"){
        cout<<"Bypassing...";
        Sleep(1000);
        main();
    }
    cout<<"Enter the Line Number of the event you want to delete: ";
    cin>>lineno[0];

    fstream test(tempT + ".txt");
    if (!test)
    {
        cout<<"Event does not exist, or you have entered wrong Title!! \n\n";
        cout<<"Restarting!!!\n";
        Sleep(2000);
        del();
    }
    test.close();


    string tlineno;
    tlineno = lineno[0];
    int n = stoi(tlineno);

    delete_line("event.txt", n);

    cout<<"\nEvent Deleted: "<<tempT<<" \n\n";
    remove((tempT + ".txt").c_str());

    cout<<"Remaining events in your calendar: \n";
    fstream view2("event.txt");
    string line2;
        while (getline(view2, line2))
        {
            cout << line2 << endl;
        }
    view2.close();

    cout<<"\n\n\n";

    cout<<"Repeat           (1) \n"
          "Return to Home   (2) \n"
          "Exit             (0) \n"
          "Please Enter the desired operation number: ";
    int opt;
    cin>>opt;

        if(opt == 1) {
            cout<<"Processing... \n";
            Sleep(1000);
            del();
        }

        else if(opt == 2) {
            cout<<"Processing... \n";
            Sleep(1000);
            main();
        }

        else if(opt == 0) {
            cout<<"Exiting... \n";
            Sleep(1000);
            exit(0);
        }


}
