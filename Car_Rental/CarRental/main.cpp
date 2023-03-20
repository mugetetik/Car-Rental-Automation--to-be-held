#include "cars.h"
#include "login.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;

// String methods 

int str_len(char c[])    //returns length
{
	int length=0;
	while(c[length]!='\0')  //stringin sonunda \0 bulunuyor onu almayınca lenghti buluyorsun
	{
		length++;
	}
	return length;
}

string conv_to_str(char* a,int size)
{
	int i;
	string s = "";
	for(i=0;i<size;i++)
	{
		s = s + a[i];
	}
	return s;
}
int isSubstring(string s1, string s2) 
{ 
    int M = s1.length(); 
    int N = s2.length(); 
    for (int i = 0; i <= N - M; i++) { // A loop to slide pat[] one by one
        int j; 
        for (j = 0; j < M; j++) //For current index i, check for pattern match
            if (s2[i + j] != s1[j]) 
                break; 
        if (j == M) 
            return i; 
    } 
    return -1;
} 

// Functions for car class

void Cars::getdata()
{
	cout<<"Enter name of car: ";
	scanf(" %[^\n]s",name);
	while(1)
	{
		cout<<"Enter ID of the car: ";
		cin>>ID;
		if(ID/10000 == 0 && ID/1000!=0)
			break;
		else
			cout<<"4 Digit please"<<endl;
	}
	while(1)
	{
		cout<<"Booked status(1 for yes/0 for no): ";
		cin>>booked;
		if(booked==1||booked==0)
			break;
		else
			cout<<"Enter (1 for yes/0 for no)"<<endl;
	}
}
void Cars::putdata()
{
	if(booked==1)
		cout<<"\t"<<"|"<<setw(20)<<name<<" |"<<setw(5)<<ID<<" |"<<setw(4)<<"Yes"<<" |"<<endl;
	else
		cout<<"\t"<<"|"<<setw(20)<<name<<" |"<<setw(5)<<ID<<" |"<<setw(4)<<"No"<<" |"<<endl;
}
void Cars::modify() //function to modify the records
{
	int ch;
	cout<<"Current details are"<<endl;
	putdata();
	cout<<"Modify:\n 1.Name\n 2.ID\n 3.Booked?\n 4.All\n Your choie: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			cout<<"Enter new name of the Car: ";
			cin>>name;
			break;
		case 2:
			cout<<"Enter new ID: ";
			cin>>ID;
			break;
		case 3:
			cout<<"Booking status?(1 for yes/0 for no): ";
			cin>>booked;
			break;
		case 4:
			getdata();
			break;
		default:
			cout<<"Wrong option selected, refer menu"<<endl;
	}
}

// Functions for Login_admin class 

void Login_admin::login_admin(char user_n[], char pass[])
{
	string name;
	int round = 0;
	ifstream fin("admin_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No admin Data Available!"<<endl;
		fin.close();
		return;
	}
	else{
		while(fin>>username>>password)
		{
			if(strcmp(user_n,username)==0 && strcmp(pass,password)==0)
			{
				name = conv_to_str(user_n,str_len(user_n));
				size_t found = name.find("@admin"); 
				cout<<"Hello "<<name.substr(0,found)<<endl;
				round = 1;
				do_work();
			}
			else if(strcmp(user_n,username)==0)
			{
				cout<<"Entered password is incorrect"<<endl;
				round = 1;
			}
		}
		fin.close();
		if(round==0)
		{
			cout<<"This User does not exist!"<<endl;
		}
	}
}

void Login_admin::Read_user_data()
{
	ifstream fin("login_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No User Data Available!"<<endl;
		fin.close();
		return;
	}
	while(fin>>username>>password)
	{
		cout<<"|"<<setw(20)<<username<<"|"<<setw(10)<<password<<"|"<<endl;
	}
	fin.close();
}
void Login_admin::Export_user_data()
{
	ifstream fin("login_data.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No User Data Available!"<<endl;
		fin.close();
		return;
	}
	ofstream fout("Login_data.csv",ios::out);
	fout<<"USERNAME"<<","<<"PASSWORD"<<endl;
	while(fin>>username>>password)
	{
		fout<<username<<","<<password<<endl;
	}
	fin.close();
	fout.close();
}
void Login_admin::add_car(){
	char ch='y';
	ofstream fout("cars.txt",ios::out|ios::app);
	while(ch=='y'|ch=='Y')
	{
		c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\nDo you wish to add more(y/n): ";
		cin>>ch;
	}
	cout<<"\nData added to file\n"<<endl;
	fout.close();
}

void Login_admin::display_car()
{
	ifstream fin("cars.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No CAR Data Available!"<<endl;
		fin.close();
		return;
	}
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		c.putdata();
		cout<<endl; 
	}
	fin.close();
}

void Login_admin::Export()
{	
	ofstream fout("cars.csv");
	//writing hatchback file to excel cars file
	ifstream fin1("cars.txt",ios::in); //open hatchback
	fout<<"CAR"<<endl;
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0)
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"Yes"<<endl;
		else
			fout<<c.get_name()<<","<<c.get_ID()<<","<<"No"<<endl;
	}
	fout<<endl;
	fin1.close();//close hatchback
	fout.close();//close the excel file
}
void Login_admin::search_car()
{
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be searched: ";
	cin>>entered_id;
	//searching the hatchback file
	ifstream fin1("cars.txt",ios::in);
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			c.putdata();
			found = 'y';
		}
	}
	fin1.close();
	if(found =='y'){return;}
	if(found =='n'){cout<<"\nCar of ID "<<entered_id<<"is not in the file.\n";}
	return;
}
void Login_admin::modify_car() //fuction to modify the records of file
{
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be searched: ";
	cin>>entered_id;
	
	//searching and modifying the hatchback file
	fstream fio1("cars.txt",ios::in|ios::out);
	fio1.seekg(0);
	while(!fio1.eof())
	{
		int loc = fio1.tellg(); //storing the current location in loc
		fio1.read((char*)&c,sizeof(c));
		if(c.get_ID()==entered_id)
		{
			c.modify();
			found = 'y';
			fio1.seekg(loc); //moving the pointer to current location
			fio1.write((char*)&c,sizeof(c));
			cout<<"\nYour record of ID "<<entered_id<<" has been updated"<<endl;
			break;
		}
	}
	fio1.close();
	if(found =='y'){return;}
	if(found =='n'){cout<<"\nCar of ID "<<entered_id<<"is not in the file.\n";}
	return;
}
void Login_admin::delete_c() //function to delete the records of file
{	
	int entered_id;
	char found  = 'n';
	cout<<"\nEnter the ID to be deleted: ";
	cin>>entered_id;
	
	//fstream fio1("cars.txt",ios::in|ios::out|ios::app);
	ifstream fin1("cars.txt",ios::in);
	ofstream fout1("temp1.txt",ios::out|ios::app);
	while(fin1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID()==entered_id)
		{
			found = 'y';
		}
		else{
			fout1.write((char*)&c,sizeof(c)); //writing to temp file
		}
	}
	fin1.close();
	fout1.close();
	remove("cars.txt");
	rename("temp1.txt","cars.txt");
	if(found=='y'){
		cout<<"Record successfully deleted"<<endl;
		return;
	}
	
	else{
		cout<<"Record not found"<<endl;
	}
}
void Login_admin::do_work()
{
	int ch;
	do{
		cout<<"\nChoose option \n 1.Add Data \n 2.Display Data \n 3.Search Data \n 4.Modify Data \n 5.Delete Data\n 6.Export Car data\n 7.To see all the users\n 8.Export user data\n 9.Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Add Car Data\n";
				add_car();
				break;
			case 2:
				cout<<"Display Record\n";
				display_car();
				break;
			case 3:
				cout<<"Search Record\n";
				search_car();
				break;
			case 4:
				cout<<"Modify Record\n";
				modify_car();
				break;
			case 5:
				cout<<"Delete Record\n";
				delete_c();
				break;
			case 6:
				cout<<"Export car data in process"<<endl;
				Export();
				break;
			case 7:
				cout<<"User Data"<<endl;
				Read_user_data();
				break;
			case 8:
				cout<<"Export file in process"<<endl;
				Export_user_data();
				break;
			case 9:
				cout<<"Thank You for using the program :)"<<endl;
				break;
			default:
				cout<<"Wrong choice\n";
		}
	}while(ch!=9);
	return;
}

// Functions for Login_user class

int Login_user::check_user_existence(char uname[] )
{
	int flag = 0;
	ifstream fin("login_data.txt",ios::in);
	while(fin>>username>>password)
	{
		if(strcmp(uname,username)==0){
			flag = 1;
		}
	}
	fin.close();
	if(flag==1)
	{
		return 1;
	}
	return 0;
}
void Login_user :: Register()
{
	char new_name[100];
	char pass[50];
	int val;
	ofstream fout("login_data.txt",ios::app);
	do{
		cout<<"Enter username(mail): ";
		cin>>new_name;
		//check username exists or not
		val = check_user_existence(new_name);
		if(val==1){cout<<"Username already exists use another one "<<endl;}
	}while(val==1);
	cout<<"Enter your preferred password: ";
	cin>>pass;
	fout<<new_name<<" "<<pass<<endl;
	fout.close();
}
int Login_user :: show_car()
{
	ifstream fin("cars.txt",ios::in);
	if(!(fin)) //check if the file is empty
	{
		cout<<"No Car Data Available!"<<endl;
		fin.close();
		return 1;
	}
	cout<<"\tFORMAT"<<endl;
	cout<<"\t"<<"|"<<setw(20)<<"NAME"<<" |"<<setw(5)<<"ID"<<" |"<<setw(4)<<"BOOKED"<<" |"<<endl;
	cout<<"\n\tAvailable cars are\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==0){
			c.putdata();
		}
	}
	fin.close();
	fin.open("cars.txt",ios::in);
	cout<<"\n\tUnvailable cars are\n"<<endl;
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(c.booked_status()==1){
			c.putdata();
		}
	}
	fin.close();
	return 0;
}

void Login_user :: book_car()
{
	int car_to_book;
	char found = 'n';
	int check;
	do{
		cout<<"Enter the ID of car to book: ";
		cin>>car_to_book;
		check = search_car(car_to_book);
		if(check == 0){
			cout<<"ID is wrong :( refer menu"<<endl;
		}
	}while(check==0);
	fstream fio("cars.txt",ios::in|ios::out);
	//check valid id
	fio.seekg(0);
	while(!fio.eof())
	{
		int loc = fio.tellg(); 
		fio.read((char*)&c,sizeof(c));
		if(c.get_ID() == car_to_book && c.booked_status() == 0){
			c.bookit();
			found = 'y';
			fio.seekg(loc);
			fio.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == car_to_book && c.booked_status() == 1)
		{
			cout<<"Sorry its Already booked"<<endl;
			found = 'y';
		}
	}
	fio.close();
	if(found=='n'){
		cout<<"Not Available!"<<endl;
		return;
	}
	else if(found == 'y'){
		//invoice function
		cout<<"You've chosen a car"<<endl;
		bill(car_to_book); //this->invoice(car_to_book,name_of_car);
		//cout<<"Thank You for Booking!"<<endl;
		return;
	}
}

void Login_user::unbook()
{
	char* name_of_car;
	int id_car;
	do{
	cout<<"Enter the ID of car you want to submit: ";
	cin>>id_car;
	if(id_car/10000!=0 && id_car/1000==0){cout<<"ID is of 4 digit please check your bill"<<endl;}
	}while(id_car/10000!=0 && id_car/1000==0);
	char found = 'n';
	fstream fio1("cars.txt",ios::in|ios::out);
	fio1.seekg(0);
	while(!fio1.eof())
	{
		int loc = fio1.tellg(); 
		fio1.read((char*)&c,sizeof(c));
		if(c.get_ID() == id_car && c.booked_status()==1){
			c.unbookit();
			name_of_car = c.get_name();
			found = 'y';
			fio1.seekg(loc);
			fio1.write((char*)&c,sizeof(c));
		}
		else if(c.get_ID() == id_car && c.booked_status()==0){
			name_of_car = c.get_name();
			cout<<"This ID is of "<<name_of_car<<"\nPlease enter the correct ID of Your car"<<endl;
			found = 'j';
		}
	}
	fio1.close();
	if(found == 'j'){return;}
	if(found == 'y'){
		cout<<"Hope You liked Our Car - "<<name_of_car<<" :)"<<endl;
		cout<<"Thank You for using our services!!"<<endl;
		return;
	}
	
	else if(found == 'n')
	{
		cout<<"OOPS! The Car you are submitting does not belong to us!!"<<endl;
	}
}
int Login_user::search_car(int id_car)
{
	char found = 'n';
	ifstream fio1("cars.txt",ios::in);
	while(fio1.read((char*)&c,sizeof(c)))
	{
		if(c.get_ID() == id_car){
			found = 'y';
		}
	}
	fio1.close();
	if(found == 'y'){
		return 1;
	}
	return 0;
}

void Login_user::bill(int carid)  //(float rate,int carid,char* name_of_car)
{
	int see_car,rate;
	string namethecar;
	int choice,n,bill_id;
	float pay,min_pay,penalty_rate;
	see_car = search_car(carid);
	if(see_car==1)
	{
		rate = 50;
		ifstream fin("cars.txt",ios::in);
		while(fin.read((char*)&c,sizeof(c)))
		{
			if(c.get_ID() == carid)
			{
				namethecar = c.get_name();
			}
		}
		fin.close();
	}
	system("cls");
	cout<<"Thank You for Booking! Please enter following info"<<endl;
	cout<<"Enter Time for which you want the car for rent"<<endl;
    cout<<" (1)Less than a day\n (2)Min 1 whole day\n Your choice: ";
    cin>>choice;
    fstream file1("Invoice.txt",ios::in);
	file1>>bill_id;
	bill_id=bill_id+1;
	file1.seekg(0);
	file1<<bill_id;
	file1.close();
	switch(choice)
	{
		case 1:
			//while(1)
			//{
				cout<<"Enter number of hours for which u want to get car on rent: ";
            	cin>>n;
				//if(n>0&&n<25){break;}
				//else{cout<<"Hrs between [1,24]"<<endl;}
			//}
			pay = n * rate;
			min_pay = 0.3 * pay;
			penalty_rate = 0.1 * rate + rate;
			cout<<endl;
			system("cls");
			cout<<"************************ BILL ********************************"<<endl;
			cout<<"|"<<setw(30)<<"Invoice Number"<<"|"<<setw(30)<<bill_id<<endl;
			cout<<"|"<<setw(30)<<"Customer Name"<<"|"<<setw(30)<<username<<endl;
			cout<<"|"<<setw(30)<<"Car Name"<<"|"<<setw(30)<<namethecar<<endl;
			cout<<"|"<<setw(30)<<"Car ID"<<"|"<<setw(30)<<carid<<endl;
			cout<<"|"<<setw(30)<<"Numbers of Hours"<<"|"<<setw(30)<<n<<endl;
			cout<<"|"<<setw(30)<<"Total Pay"<<"|"<<setw(30)<<pay<<endl;
			cout<<"|"<<setw(30)<<"Advance Pay "<<"|"<<setw(30)<<min_pay<<endl;
			cout<<"|"<<setw(30)<<"After use Pay"<<"|"<<setw(30)<<pay-min_pay<<endl;
			cout<<"|"<<setw(30)<<"Penalty per hour"<<"|"<<setw(30)<<penalty_rate<<endl;
			cout<<"***************************************************************"<<endl;
			break;
		case 2:
			//while(1)
			//{
				cout<<"Enter number of days for which u want to get car on rent(max a month): ";
           		cin>>n;
				//if(n>0&&n<32){break;}
				//else{cout<<"Days between [1,31]"<<endl;}
			//}
			pay = n * rate * 18; //18 = hours driven per day
			min_pay = 0.3 * pay;
			penalty_rate = 0.1 * rate + rate;
			cout<<endl;
			system("cls");
			cout<<"************************** BILL ******************************"<<endl;
			cout<<"|"<<setw(30)<<"Invoice Number"<<"|"<<setw(30)<<bill_id<<endl;
			cout<<"|"<<setw(30)<<"Customer Name"<<"|"<<setw(30)<<username<<endl;
			cout<<"|"<<setw(30)<<"Car Name"<<"|"<<setw(30)<<namethecar<<endl;
			cout<<"|"<<setw(30)<<"Car ID"<<"|"<<setw(30)<<carid<<endl;
			cout<<"|"<<setw(30)<<"Numbers of Hours"<<"|"<<setw(30)<<n<<endl;
			cout<<"|"<<setw(30)<<"Total Pay"<<"|"<<setw(30)<<pay<<endl;
			cout<<"|"<<setw(30)<<"Advance Pay "<<"|"<<setw(30)<<min_pay<<endl;
			cout<<"|"<<setw(30)<<"After use Pay"<<"|"<<setw(30)<<pay-min_pay<<endl;
			cout<<"|"<<setw(30)<<"Penalty per hour"<<"|"<<setw(30)<<penalty_rate<<endl;
			cout<<"**************************************************************"<<endl;
			break;
		default:
			cout<<"Wrong option selected"<<endl;
	}
}
void Login_user :: do_user_work()
{
	int choice;
	cout<<"Menu\n 1.Book a car\n 2.Submit the car\n Your choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			int collect;
			cout<<setw(30)<<"QUICK INFO"<<endl;
			cout<<"|"<<setw(10)<<"TYPE"<<" |"<<setw(15)<<"RATE(per hr)"<<" |"<<setw(20)<<"PENALTY RATE(per hr)"<<" |"<<endl;
			cout<<"|"<<setw(10)<<"CAR"<<" |"<<setw(15)<<50<<" |"<<setw(20)<<50*(0.1) + 50<<" |"<<endl;
			cout<<"\nBooking Point\n";
            collect= show_car();
            if(collect==0)
                book_car();
            break;
				
		case 2:
			unbook();
			break;
	}
	
}
void Login_user :: login(char user_n[], char pass[])
{
	string name;
	int round = 0;
	ifstream fin("login_data.txt",ios::in);
	while(fin>>username>>password)
	{
		if(strcmp(user_n,this->username)==0 && strcmp(pass,this->password)==0)
		{
			name = conv_to_str(user_n,str_len(user_n));
			size_t found = name.find("@");
			cout<<"Welcome back "<<name.substr(0,found)<<endl;
			round = 1;
			do_user_work();
		}
		else if(strcmp(user_n,this->username)==0)
		{
			cout<<"Entered Password is incorret"<<endl;
			round =1;
		}
	}
	fin.close();
	if(round == 0)
	{
		char ans;
		cout<<"You might want to consider registering(y/n): ";
			cin>>ans;
			if(ans=='y'||ans=='Y'){
				this->Register();
			}
			else{
				cout<<"Allright see ya!"<<endl;
			}
	}
}

// main code 

int main()
{
	Login_user l;
	Login_admin la;
	char username[100],password[50];
	int choosing;
	string user;
	do{
		cout<<"\n\t\t\tEnter:\n \t\t\t[1]Login\n \t\t\t[2]User Registeration\n \t\t\t[3]Exit Program\n \t\t\tYour Choice: ";
		cin>>choosing;
		switch(choosing)
	{
		case 1: //login function will seperate the user and admin.
			system("cls");
			cout<<"\t\t\tLogin"<<endl;
			cout<<"\n\tUsername - ";
			cin>>username;
			cout<<"\tPassword - ";
			cin>>password;
			user = conv_to_str(username,str_len(username));
			if(isSubstring("@admin",user)!=-1)
			{
				la.login_admin(username,password);
				choosing = 3;
			}
			else{
				l.login(username,password);
				choosing = 3;
			}
			break;
		case 2: //user registeration
			l.Register();
			cout<<"Thank You For Registering, We won't let you down!"<<endl;
			break;
		case 3:
			cout<<"Thank You for checking in, Have an Awesome Day!"<<endl;
			break;
		default:
			cout<<"Wrong option selected please refer menu"<<endl;
			exit(1);
	}
	}while(choosing!=3);
	return 0;
}