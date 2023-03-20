class Cars
{
	protected:
		char name[30];
		int ID;  //format 4 digit
		bool booked; // 1 or 0
	public:
		void getdata();
		void putdata();
		void modify();
		bool booked_status(){
			return booked;
		}
		int get_ID(){
			return ID;
		}
		char* get_name(){
			return name;
		}
		void bookit(){
			this->booked = 1;
		}
		void unbookit(){
			this->booked = 0;			
		}
}c;