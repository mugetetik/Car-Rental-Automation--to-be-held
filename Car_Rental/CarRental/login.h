class Login{
	protected:
		char username[100];
		char password[50];
};
class Login_user:public Login{
	public:
		void Register();
		int check_user_existence(char[]);
		void login(char user_n[], char pass[]);
		//display available cars
		int show_car();
		//book the available cars
		void book_car();
		//invoices
		//void invoice(int);
		void bill(int);   //void bill(float,int,char*);
		//do work function
		void do_user_work();
		void unbook();
		int search_car(int);
};
class Login_admin:public Login{
	public:
		void login_admin(char user_n[],char pass[]);
		//void register_admin();
		void Export_user_data(); //exporting user data to csv
		void Read_user_data();
		//this is file class in original code
		void search_car();
		void delete_c();
		void Export();
		void modify_car();
		void add_car();
		//display versions
		void display_car();
		//do work function
		void do_work();
};