#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
class seat{
public:
  string name;
  long long int phno;
  long passport;
  string seat_no;
  int flight_no;
  int cost;
  seat(){}
  seat(string n,long long int p, long ps, string seat,int f,int c){
    name = n;
    phno=p;
    passport=ps;
    seat_no=seat;
    flight_no=f;
    cost=c;
  }
  void seat_details(){
    cout<<"Name: "<<name<<endl<<"Phone No. : "<<phno<<endl<<"Passport No. : "<<passport<<endl<<"Seat No. : "<<seat_no<<endl<<"Flight No. : "<<flight_no<<endl<<"Cost: "<<cost<<endl;
  }
};

class flight:public seat {
public:
  seat* arr[6][29]={0};
  int flight_no;
  string destination;
  string from;
  int departure_time;//HHMM hrs
  int arrival_time;//HHMM hrs
  int v_seats=144;
  flight(int f, string fro, string dest, int dept_t, int arr_t){
     flight_no=f;
     destination = dest;
     from = fro;
     departure_time=dept_t;
     arrival_time=arr_t;
     for(int i=0;i<3;i++){
       arr[1][i]=NULL;
       arr[4][i]=NULL;
     }
     for(int i=0;i<6;i++){
       for(int j=3;j<7;j++){
         arr[i][j]=NULL;
       }
     }
  }
  void print(){
      cout<<"Flight number="<<flight_no<<"\nFrom="<<from<<"\nDestination="<<destination<<"\nDeparture time="<<departure_time<<"\nArrival time="<<arrival_time<<endl;
  }
};

seat* makeSeat(string seat_no,int flight_no,int cost){
  string name;
  long long int phno;
  long passport;
  cout<<"Enter name, phone no, passport no: ";
  cin>>name>>phno>>passport;
  seat *s=new seat(name,phno,passport,seat_no,flight_no,cost);
  cout<<"seat alloted "<<seat_no<<endl;
  return s;
}

void ReserveSeat(flight* flights[],int a){
    int flt_no;
    cout<<"Enter Flight number: ";
    cin>>flt_no;
    int i;
    for(i=0;i<a;i++){
      if(flights[i]->flight_no==flt_no){
        break;
      }
    }
    if(i==a){
      cout<<"Flight not found"<<endl;
      return;
    }
    int n;
    cout<<"Enter number of seats required: ";
    cin>>n;
    int num=n;
    if(n>(flights[i]->v_seats)){
      cout<<"Not enough seats"<<endl;
      return;
    }
    int v=0;
    for(int j=0;j<6;j++){
      for(int k=0;k<3;k++)
        if((flights[i]->arr[j][k])!=NULL) v++;
    }
    v=12-v;
    int x;
    cout<<"Enter 1 for First class or 2 for Economy: ";
    cin>>x;
    string seatno="";
    economy:
    if(x==1){
     if(n>v){
      cout<<"Not enough seats in first class, would you like to reserve in Economy?(y/n)"<<endl;
      char t;
      cin>>t;
      if(t=='y') {
        x=2;
        //cout<<"Goto called";
        goto economy;
      }
      else return;
    }
    int w;
    cout<<"Enter 1 for Window seat or 2 for Aisle(First Class): ";
    cin>>w;
    if(w==1){
      int k;
      for( k=0;k<3;k++){
        if(flights[i]->arr[0][k]==NULL){
          seatno="";
          seatno+="A"+to_string(k+1);
          n--;
          flights[i]->arr[0][k]=makeSeat(seatno,flt_no,10000);
          break;
        }
        else if(flights[i]->arr[5][k]==NULL){
          seatno="";
          seatno+="F"+to_string(k+1);
          n--;
          flights[i]->arr[5][k]=makeSeat(seatno,flt_no,10000);
          break;
        }
      }
      if(flights[i]->arr[2][k]==NULL && n) {
        seatno="";
        seatno+="C"+to_string(k+1);
        n--;
        flights[i]->arr[2][k]=makeSeat(seatno,flt_no,10000);
      }
      if(flights[i]->arr[3][k]==NULL && n>0) {
        seatno="";
        seatno+="D"+to_string(k+1);
        n--;
        flights[i]->arr[3][k]=makeSeat(seatno,flt_no,10000);
      }
      if(flights[i]->arr[5][k]==NULL && n) {
        seatno="";
        seatno+="F"+to_string(k+1);
        n--;
        flights[i]->arr[5][k]=makeSeat(seatno,flt_no,10000);
      }
        for(int j=0;j<6;j++){
          for(int k=0;k<3;k++) {
            if(flights[i]->arr[j][k]==NULL && k!=2 && k!=4 && n) {
              seatno="";
              seatno.push_back(char(int('A')+j));
              seatno+=to_string(k+1);
              n--;
              flights[i]->arr[j][k]=makeSeat(seatno,flt_no,10000);
            }
         }
       }
  }
  else {
    int k;
      for( k=0;k<3;k++){
        if(flights[i]->arr[2][k]==NULL){
          seatno="";
          seatno+="C"+to_string(k+1);
          n--;
          flights[i]->arr[2][k]=makeSeat(seatno,flt_no,10000);
             break;
          }
          else if(flights[i]->arr[3][k]==NULL){
            seatno="";
            seatno+="D"+to_string(k+1);
            n--;
            flights[i]->arr[3][k]=makeSeat(seatno,flt_no,10000);
            break;
          }
        }
        if(flights[i]->arr[0][k]==NULL && n) {
          seatno="";
          seatno+="A"+to_string(k+1);
          n--;
          flights[i]->arr[0][k]=makeSeat(seatno,flt_no,10000);
        }
        if(flights[i]->arr[3][k]==NULL && n>0) {
          seatno="";
          seatno+="D"+to_string(k+1);
          n--;
          flights[i]->arr[3][k]=makeSeat(seatno,flt_no,10000);
        }
        if(flights[i]->arr[5][k]==NULL && n) {
          seatno="";
          seatno+="F"+to_string(k+1);
          n--;
          flights[i]->arr[5][k]=makeSeat(seatno,flt_no,10000);
        }
          for(int j=0;j<6;j++){
            for(int k=0;k<3;k++){
              if(flights[i]->arr[j][k]==NULL && k!=2 && k!=4 && n) {
                seatno="";
                seatno.push_back(char(int('A')+j));
                seatno+=to_string(k+1);
                n--;
                flights[i]->arr[j][k]=makeSeat(seatno,flt_no,10000);
              }
          }
        }
     }
    flights[i]->v_seats-=num;
   }
    if(n==0) return;
    if(x==2){
         v=flights[i]->v_seats-v;
         if(n>v){
            return;
          }
          int w;
          cout<<"Enter 1 for Window seat or 2 for Aisle(Economy): ";
          cin>>w;
          if(w==1){ int k;
              for( k=7;k<28;k++)
              {
                if(flights[i]->arr[0][k]==NULL){
                  seatno="";
                  seatno+="A"+to_string(k+1);
                  n--;
                  flights[i]->arr[0][k]=makeSeat(seatno,flt_no,5000);
                  break;
                }
                else if(flights[i]->arr[5][k]==NULL){
                  seatno="";
                  seatno+="F"+to_string(k+1);
                  n--;
                  flights[i]->arr[5][k]=makeSeat(seatno,flt_no,5000);
                  break;
                }
              }
              for(int j=0;j<6;j++){
                  if(flights[i]->arr[j][k]==NULL && n) {
                    seatno="";
                    seatno.push_back(char(int('A')+j));
                    seatno+=to_string(k+1);
                    n--;
                    flights[i]->arr[j][k]=makeSeat(seatno,flt_no,5000);
                  }
              }
               for(int j=0;j<6;j++){
                 for(int k=7;k<28;k++){
                   if(flights[i]->arr[j][k]==NULL && n) {
                     seatno="";
                     seatno.push_back(char(int('A')+j));
                     seatno+=to_string(k+1);
                     n--;
                     flights[i]->arr[j][k]=makeSeat(seatno,flt_no,5000);
                   }
               }
             }
          }
          else {
            int k;
               for( k=7;k<28;k++)
               {
                 if(flights[i]->arr[2][k]==NULL && n){
                   seatno="";
                   seatno+="C"+to_string(k+1);
                   n--;
                   flights[i]->arr[2][k]=makeSeat(seatno,flt_no,5000);
                   break;
                 }
                 else if(flights[i]->arr[3][k]==NULL && n){
                   seatno="";
                   seatno+="D"+to_string(k+1);
                   n--;
                   flights[i]->arr[3][k]=makeSeat(seatno,flt_no,5000);
                   break;
                 }
               }
               for(int j=0;j<6;j++){
                   if(flights[i]->arr[j][k]==NULL && n) {
                     seatno="";
                     seatno.push_back(char(int('A')+j));
                     seatno+=to_string(k+1);
                     n--;
                     flights[i]->arr[j][k]=makeSeat(seatno,flt_no,5000);
                   }
               }
                for(int j=0;j<6;j++){
                  for(int k=7;k<28;k++){
                    if(flights[i]->arr[j][k]==NULL && n) {
                      seatno="";
                      seatno.push_back(char(int('A')+j));
                      seatno+=to_string(k+1);
                      n--;
                      flights[i]->arr[j][k]=makeSeat(seatno,flt_no,5000);
                    }
                }
              }
     }
     flights[i]->v_seats-=num;
}
    else{
      cout<<"Invalid input x n"<<x<<n<<endl;
    }

}
void UserTicket(flight* flights[],int a){
  int flt_no;
  cout<<"Enter Flight number: ";
  cin>>flt_no;
  int i;
  for(i=0;i<a;i++){
    if(flights[i]->flight_no==flt_no){
      break;
    }
  }
  if(i==a){
    cout<<"Flight not found"<<endl;
    return;
  }
    int ppt;
    cout<<"Enter passport no. ";
    cin>>ppt;
    int j,k;
    for(j=0;j<6;j++){
      for(k=0;k<29;k++){
        if(flights[i]->arr[j][k]!=NULL){
          if(flights[i]->arr[j][k]->passport==ppt){
            flights[i]->arr[j][k]->seat_details();
             return;}
        }
      }
    }
    cout<<"No passenger found"<<endl;
    return;
}
bool myCompare(flight* flt1,flight* flt2){
  if(flt1->departure_time<flt2->departure_time)
    return true;
  else if(flt1->departure_time==flt2->departure_time)
    return flt1->arrival_time<flt2->arrival_time;
  return false;
}
void sortFlights(flight* flights[],int a){
  sort(flights,flights+a,myCompare);
}
void FlightSchedule(flight* flights[],int a){
  cout<<"FlightNumber  DepartureTime  ArrivalTime"<<endl;
  for(int i=0;i<a;i++){
    flight* flt=flights[i];
    cout<<"    "<<flt->flight_no<<"         "<<flt->departure_time<<"          "<<flt->arrival_time<<"\n";
  }
}
void FlightDetails(flight* flights[],int a){
  int flt_no;
  cout<<"Enter Flight number: ";
  cin>>flt_no;
  int i;
  for(i=0;i<a;i++){
    if(flights[i]->flight_no==flt_no){
      break;
    }
  }
  if(i==a){
    cout<<"Flight not found"<<endl;
    return;
  }
  flights[i]->print();
}
void DisplayPassenger(flight* flights[],int a){
  int flt_no;
  cout<<"Enter Flight number: ";
  cin>>flt_no;
  int i;
  for(i=0;i<a;i++){
    if(flights[i]->flight_no==flt_no){
      break;
    }
  }
  if(i==a){
    cout<<"Flight not found"<<endl;
    return;
  }
  int j,k;
  cout<<"Name \t Seat No."<<endl;
  for(j=0;j<6;j++){
    for(k=0;k<29;k++){
      if(flights[i]->arr[j][k]!=NULL){
            cout<<flights[i]->arr[j][k]->name<<"\t"<<flights[i]->arr[j][k]->seat_no<<endl;
      }
    }
  }
}
void Add(flight* flights[],int &a){
  if(a==100){
    cout<<"Airlines Full";
    return;
  }
  int flight_no;
  string destination;
  string from;
  int departure_time;
  int arrival_time;
  cout<<"Enter Flight number, Origin, Destination, Departure time(HHMM), Arrival time(HHMM)\n ";
  cin>>flight_no>>destination>>from>>departure_time>>arrival_time;
  flights[a++]=new flight(flight_no,destination,from,departure_time,arrival_time);
  sortFlights(flights,a);
}
void Edit(flight* flights[],int &a){
  int flt_no;
  cout<<"Enter Flight number: ";
  cin>>flt_no;
  int i;
  for(i=0;i<a;i++){
    if(flights[i]->flight_no==flt_no){
      break;
    }
  }
  if(i==a){
    cout<<"Flight not found"<<endl;
    return;
  }
  int flight_no;
  string destination;
  string from;
  int departure_time;
  int arrival_time;
  cout<<"Enter new Flight number, Origin, Destination, Departure time(HHMM), Arrival time(HHMM)\n ";
  cin>>flight_no>>destination>>from>>departure_time>>arrival_time;
  flights[i]=new flight(flight_no,destination,from,departure_time,arrival_time);
  sortFlights(flights,a);
}
void Delete(flight* flights[],int &a){
  int flt_no;
  cout<<"Enter Flight number: ";
  cin>>flt_no;
  int i;
  for(i=0;i<a;i++){
    if(flights[i]->flight_no==flt_no){
      break;
    }
  }
  if(i==a){
    cout<<"Flight not found"<<endl;
    return;
  }
  for(;i<a;i++){
    flights[i]=flights[i+1];
  }
  flights[--a]=0;
}
void AdminOptions(flight* flights[],int &a){
  int pwd;
  cout<<"Enter password:"<<endl;
  cin>>pwd;
  if(pwd!=354555){
    cout<<"incorrect password"<<endl;
    return;
  }
  else{
    cout<<"Welcome!!\n";
  }
  int z;
  m:
  cout << "Admin options" << endl;
  cout << "1. Add New Flight" << endl;
  cout << "2. Edit a Flight" << endl;
  cout << "3. Delete a Flight" << endl;
  cout << "4. Exit Admin Menu." << endl;
  cout << "Choose One: ";
  cin>>z;
  switch(z){
    case 1: Add(flights,a);
        break;
    case 2: Edit(flights,a);
        break;
    case 3: Delete(flights,a);
       break;
    case 4:
      return;
    default:
     cout<<"Invalid Input"<<endl;
  }
  goto m;
}

int main()
{
    int chooseOneFromMenu = 0;
    char exitSurity;
    flight* flights[100]={0};
    int a=0;
    flights[a++]=new flight(123,"Delhi","Mumbai",1730,2130);

     flights[0]->arr[0][0]=new seat("Raju",7498535326,893742,"A1",123,10000);
     flights[0]->arr[1][7]=new seat("Guju",7623562567,192937,"B8",123,5000);
     flights[0]->arr[2][16]=new seat("Biju",6174525378,726548,"C17",123,5000);
     flights[0]->arr[3][18]=new seat("Kaju",9153274612,178332,"D19",123,5000);
     flights[0]->arr[3][27]=new seat("jiju",9175532212,562184,"D28",123,5000);
     flights[0]->arr[0][9]=new seat("tiju",7498491026,867243,"A10",123,5000);

     flights[a++]=new flight(321,"Amritsar","jaipur",1600,1720);

     flights[1]->arr[5][1]=new seat("Rahul",9498535326,193712,"F2",321,10000);
     flights[1]->arr[1][7]=new seat("Virat",9623452567,194917,"B8",321,5000);
     flights[1]->arr[2][0]=new seat("Sachin",9674525378,726118,"C1",321,10000);
     flights[1]->arr[3][19]=new seat("Dravid",7153274812,478342,"D20",321,5000);
     flights[1]->arr[3][21]=new seat("Saurav",8175538212,562764,"D22",321,5000);
     flights[1]->arr[0][10]=new seat("Yuvraj",6498891026,861143,"A11",321,5000);

     flights[a++]=new flight(786,"kullu","Delhi",1050,1200);

     flights[2]->arr[0][0]=new seat("Gaurav",8934535326,893742,"A1",786,10000);
     flights[2]->arr[1][7]=new seat("Manish",6789162567,192937,"B8",786,5000);
     flights[2]->arr[2][15]=new seat("Riya",6712325378,726548,"C16",786,5000);
     flights[2]->arr[3][0]=new seat("Kajal",9157674612,178332,"D1",786,10000);
     flights[2]->arr[2][27]=new seat("jannat",9142432122,562184,"C28",786,5000);
     flights[2]->arr[0][9]=new seat("taranpreet",7489681026,867243,"A10",786,5000);

     sortFlights(flights,a);
    menu:
    cout << "Welcome To Airlines Reservation System" << endl << endl;
    cout << "Airlines Reservation System Menu" << endl;
    cout << "1. Reserve Seat." << endl;
    cout << "2. User Ticket." << endl;
    cout << "3. Flights Schedule." << endl;
    cout << "4. Display Passengers." << endl;
    cout << "5. Flight Details." << endl;
    cout << "6. Administrator Options."<<endl;
    cout << "7. Exit Program." << endl;
    cout << "Choose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        ReserveSeat(flights,a);
        break;
    case 2:
        UserTicket(flights,a);
        break;
    case 3:
        FlightSchedule(flights,a);
        break;
    case 4:
       DisplayPassenger(flights,a);
      break;
     case 5:
        FlightDetails(flights,a);
        break;
    case 6:
         AdminOptions(flights,a);
         break;
    case 7:
         cout<<"Thankyou";
         return  0;
    default:
    cout<<"Invalid Input\n";
        goto menu;
    }
    goto menu;
    return 0;
}
