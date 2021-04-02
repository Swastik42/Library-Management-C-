/*Header files*/
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<ctype.h>
#include<string>
using namespace std;
/*Files*/
fstream filebook("book.dat",ios::out | ios::in | ios::binary);
fstream filegoldmem("goldmem.dat",ios::out | ios::in | ios::binary);
fstream fileissuedet("issuedetails.dat",ios::out | ios::in | ios::binary);
int pos=0,i,flag=1;
/*Classes*/
class book
{
	private: int bookid;bool bavailable;
			 char blang[30],btype[30],bname[50],bauthor[50];
			 float bprice;
			 
	public : void inputbook()
			 {  cout<<"\nEnter the book details:";
			 	cout<<"\n1)Enter book id:(Eg:0001)";cin>>bookid;fflush(stdin);
			 	cout<<"\n2)Name of the book:(50 letters max)";gets_s(bname);fflush(stdin);
			 	cout<<"\n3)Author of the book:(50 letters max)";gets_s(bauthor);
			 	cout<<"\n4)Price of the book(Rs):";cin>>bprice;fflush(stdin);
			 	cout<<"\n5)Language of the book(30 letters max):";gets_s(blang);fflush(stdin);
			 	cout<<"\n6)The type of the book:";gets_s(btype);
			 	cout<<"\nOne book added Successfully!Records Updated!";
			 	bavailable=1;
			 }
			 
			 bool getbavailable()
			 {
			 	return bavailable;
			 }
			 
			 void displaybook()
			 {
			 	cout<<"\n Book details: ";
			 	cout<<endl<<"Book id:"<<"B"<<bookid<<
                      endl<<"Language of book:"<<blang<<
                      endl<<"Name of book:"<<bname<<
                      endl<<"Name of author:"<<bauthor<<
                      endl<<"Book price:(Rs)"<<bprice<<
					  endl<<"Book type:"<<btype<<endl;
			 }
			 int getbookid()
			 {return bookid;
			 }
			 void changeavail()
			 {bavailable=!bavailable;
			 }
			 char* getname()
			 {return bname;}
};

class date
{
	private: int day,month,year;
	
	public : void inputdate()
			 {
			 	cout<<"\nEnter the date(DD/MM/YYYY): ";
			 	cin>>day>>month>>year;
			 	
			 } 
             
             void outputdate()
    		 {
    		 	cout<<day<<":"<<month<<":"<<year<<endl;
			 }
    		 
    		 int returnmonth()
    		 {
    		 	return month;
			 }
		
};

class generalmember
{
	private: int memid;
			 char mname[30],mphone[30];
	
	public : void inputgenmem()
			 {
			 	cout<<"\nEnter member details: ";
			 	cout<<"\nEnter member id:(Eg:1987)";
			 	cin>>memid;
			 	cout<<"\nEnter member name:(Max 30 letters)";fflush(stdin);
			 	gets_s(mname);
			 	cout<<"\nEnter member phone number:";fflush(stdin);
			 	gets_s(mphone);
			 	
			 }
			 void outputgenmem()
			 {
			 	cout<<"\nMember details: ";
			 	cout<<endl<<"Member id:"<<memid<<endl<<"Member name:"<<mname<<endl<<"Member phone number:"<<mphone<<endl;
			 }
			 int getmemid()
			 {return memid;
			 }

};

class goldmember : public generalmember
{
	private: float fee;
			 date dob;
			 
	public : void inputgoldmem()
			 {  char c;
			 	inputgenmem();
			 	cout<<"\nAre you are a gold member(Y/N)";cin>>c;
			 	if(toupper(c)=='N')
			 	  {flag=0;
				   return;}
			 	else
			   {
			 	cout<<"\nEnter gold member details: ";
			 	cout<<"\nEnter gold member fee:(Rs) ";
			 	cin>>fee;
			 	cout<<"\nEnter gold member DOB: ";
			 	dob.inputdate();
		       } 
			 }
			 
			 void outputgoldmem()
			 {
			 	outputgenmem();
			 	cout<<"\nGold member details: ";
			 	cout<<endl<<"fee:"<<fee;cout<<"\nDate of Birth:"; dob.outputdate();
			 }
			 int getmonth()
			   { return dob.returnmonth();}
};
class IssueDet                                                         
{
	int memid,bookid;
	char bookname[50];
	date issuedate;
  public:
  	void inputdata()
  	{
  		cout<<"\nEnter member ID to issue book:";cin>>memid;
  		cout<<"\nEnter book id:";cin>>bookid;
  		cout<<"\nEnter the book name:";fflush(stdin);
  		gets_s(bookname);
	}
	int availability()                  //To check for the availability of book
	{filebook.clear();
	 filebook.seekg(0);
	 filebook.seekp(0);
	  book boi;
	 while(filebook.read((char*)&boi,sizeof(boi)))
	 {if (boi.getbookid()==bookid)
	   {if (boi.getbavailable())
	       {filebook.seekp(pos);
	        boi.changeavail();                          //changes  availibility of book in file
	        filebook.write((char*)&boi,sizeof(boi));
	        filebook.flush();
		    return 1;
		   }
	    else 
	     return 0;
	   }
	  pos=filebook.tellg();
	 }
	}
	void issue()
	{
		cout<<"\nEnter issue date below:";
		issuedate.inputdate();
	}  
	int getmemid()
	{ return memid;
	}
	char outputdata()
	{   char c;
		cout<<"\nThe member has issued the following book:";
		cout<<"\nThe book ID:"<<bookid;
		cout<<"\nThe book name:"<<bookname;
		cout<<"\nDoes the member want to return the book?(Y/N)";cin>>c;
		return toupper(c);
	}
	int getbookid()
	{return bookid;
	}
};
/*Functions*/
book addbook()
  {book b;int chk;
   do
    {b.inputbook();
     cout<<"Recheck book details:";
     b.displaybook();
     cout<<"enter <1> if ok, <0> to redo";
     cin>>chk;
    }while(chk==0);
    return b;
   }
 void RemoveMem()
 {  int memid;char c;
 	cout<<"\nEnter ID of member you want to remove:";cin>>memid;
 	fileissuedet.clear();
 	filebook.clear();
 	filegoldmem.clear();
 	fileissuedet.seekg(0);
 	filebook.seekg(0);
 	filebook.seekp(0);
 	filegoldmem.seekg(0);
 	goldmember goldmem;
 	ofstream fout1("Temp1.dat",ios::out|ios::binary),fout2("Temp2.dat",ios::out|ios::binary);
 	IssueDet issuedet;    
 	while(fileissuedet.read((char*)&issuedet,sizeof(issuedet)))   //checks for unreturned books
 	{   if(issuedet.getmemid()==memid)
 		  { if(issuedet.outputdata()=='N')
 		    { fout1.write((char*)&issuedet,sizeof(issuedet));
		      fout1.flush();
			   return;}                            
 		    book boi;
 		  	while(filebook.read((char*)&boi,sizeof(boi)))         //returns book
	        {if (boi.getbookid()==issuedet.getbookid())
	          {filebook.seekp(pos);
	           boi.changeavail();
	           filebook.write((char*)&boi,sizeof(boi));
	           filebook.flush();
		      }
	         pos=filebook.tellg();
            }
		  }
		else
		  {fout1.write((char*)&issuedet,sizeof(issuedet));
		   fout1.flush();}   
	}pos=0;
 	while(filegoldmem.read((char*)& goldmem, sizeof(goldmem)))     //deletes member from file
                { if(memid!=goldmem.getmemid())
                    { fout2.write((char*)&goldmem,sizeof(goldmem));
					  fout2.flush();}
                  else
                    { cout<<"\nThe Member details are:";
                      goldmem.outputgoldmem();
                      cout<<"\nAre you sure you want to delete this member?(Y/N)";cin>>c;
                      if (toupper(c)=='N')
                        { fout2.write((char*)&goldmem,sizeof(goldmem));
					      fout2.flush();}
                      else
                        cout<<"\nMember records deleted successfully!";
                    }
                }        
	fileissuedet.close();fout1.close();fout2.close();filegoldmem.close();
	remove("issuedetails.dat");remove("goldmem.dat");
	rename("Temp1.dat","issuedetails.dat");rename("Temp2.dat","goldmem.dat");
}
void ReturnBook(int memid)
{
 	fileissuedet.clear();
 	filebook.clear();
 	fileissuedet.seekg(0);
 	filebook.seekp(0);
 	filebook.seekg(0);
 	IssueDet issuedet;
 	ofstream fout1("Temp1.dat",ios::out|ios::binary);
 	while(fileissuedet.read((char*)&issuedet,sizeof(issuedet)))   
 	{   if(issuedet.getmemid()==memid)
 		  { if(issuedet.outputdata()=='N')                        
 		    { fout1.write((char*)&issuedet,sizeof(issuedet));
		      fout1.flush();
			   return;}                            
 		    book boi;
 		  	while(filebook.read((char*)&boi,sizeof(boi)))         //returns book
	        {if (boi.getbookid()==issuedet.getbookid())
	          {filebook.seekp(pos);
	           boi.changeavail();
	           filebook.write((char*)&boi,sizeof(boi));
	           filebook.flush();
		      }
	         pos=filebook.tellg();
            }
		  }
		else
		  {fout1.write((char*)&issuedet,sizeof(issuedet));
		   fout1.flush();}   
	}pos=0;
		fileissuedet.close();fout1.close();
		remove("issuedetails.dat");rename("Temp1.dat","issuedetails.dat");   
}                       	
/*Main Function*/
int main()
{
	cout<<"\n/////////Hello Welcome to The Library://///////";
	int chk=0,memid=0;   
    /*Menu*/
	while(chk==0)       {int opt;
     cout<<"\nWelcome to the Main menu!!"<<endl<<"Please select an option:(1-9)";
     cout<<"\n Do you want to add a book? Then press <1>."<<
          "\n Do you want to add a member? Then press <2>."<<
          "\n Do you want to view all the library members? Then press <3>."<<
          "\n Do you want to remove a member? Then press <4>."<<
          "\n Do you want to issue a book? Then press <5>."<<
          "\n Do you want to return a book? Then press <6>."<<
          "\n Do you want to know the members having birthdays in a month? Then press <7>."<<
          "\n Do you want to see the available books? Then press <8>."<<
          "\n Do you want exit the library? Then press <9>";
    cin>>opt;
    switch(opt)
      {case 1:filebook.clear();
	          book boi;
              boi=addbook();filebook.seekp(0,ios::end);
			  filebook.write((char*)& boi, sizeof(boi));
              filebook.flush();
              break;
       case 2:goldmember gom;
       	      gom.inputgoldmem();if (flag)
       	     {filegoldmem.clear();
			  filegoldmem.seekp(0,ios::end);
       	      filegoldmem.write((char*)& gom, sizeof(gom));filegoldmem.flush();
       	      cout<<"\nOne member added succesfully!Records Updated!";}flag=1;
              break;
       case 3:filegoldmem.seekg(0);  
	          i=1;goldmember goldmem;
	          filegoldmem.clear();
              while(filegoldmem.read((char*)& goldmem, sizeof(goldmem)))
                { cout<<"\n"<<i<<")";
                  goldmem.outputgoldmem();
                  i++;
                }
			  if(i==1)
			  {cout<<"\nNo Members in the Library!";}             
              break;
       case 4:RemoveMem();
               filegoldmem.open("goldmem.dat",ios::out | ios::in | ios::binary);
               fileissuedet.open("issuedetails.dat",ios::out| ios::in | ios::binary);
              break;
       case 5:IssueDet issuedet;
	          issuedet.inputdata();
              if (issuedet.availability())
                { issuedet.issue();
                  fileissuedet.clear();
                  fileissuedet.seekp(0,ios::end);
                  fileissuedet.write((char*)&issuedet,sizeof(issuedet));
                  fileissuedet.flush();
                  cout<<"\nBook Issued successfuly!Records Updated!";
				}
              else 
                cout<<"\nBook NOT Available:";pos=0;
              
              break;
       case 6:cout<<"\nEnter the member ID who has issued the book:";cin>>memid;
	           ReturnBook(memid);
               fileissuedet.open("issuedetails.dat",ios::out | ios::in | ios::binary);
               break;
       case 7:int mon;i=1;
              cout<<"\nEnter this month's number:";
              cin>>mon;
              filegoldmem.clear();
              filegoldmem.seekg(0);
              goldmember golm;
              cout<<"\nDetails of all the registered members born in this month is/are:\n";
              while(filegoldmem.read((char*)& golm, sizeof(golm)))
                { if(golm.getmonth()==mon)
                     {cout<<""<<i<<")";golm.outputgoldmem();}            
                }
              if(i==1)
			     {cout<<"\nNo Members in the Library with that birthmonth!";} 
              break;
       case 8:  i=1;char* name;cout<<"\nThe available books are:";
                filebook.clear();
                filebook.seekg(0);book bk;
	            while(filebook.read((char*)& bk, sizeof(bk)))
                 { if(bk.getbavailable())
                     {cout<<"\n"<<i<<")";
                      name=bk.getname();
					  cout<<name;
                      i++;}
                 }    
				if(i==1)
				   cout<<"\nOops No available Books!Sorry For the Inconvenience.";                      
              break;
        case 9: exit(1);
                break;
        default:cout<<"\nPlease Enter appropriate key;";
      }
     cout<<"\nDo you want to continue? press <0> to continue, <1> to stop";
     cin>>chk;
     }
     filebook.close();
     filegoldmem.close();
     fileissuedet.close();
     fflush (stdin);
     getchar();
     return 0;
     /*End Of Program*/
}
