#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
string u;
void listTests();
void checkUserSession();
void createTest(){
  system("clear");
  cout<<"Enter test name"<<endl;
  string test;
  cin>>test;
  string command = "cd tests; mkdir "+test ;
  system(command.c_str());
  cout<<"Now select test name to create question"<<endl;
  system("cd tests;ls");

}
void designQues(){
  system("clear");
  system("cd tests;ls");
  cout<<endl<<"These are the available tests.\nEnter the name of the tests you want to create the questions for..."<<endl;
  string test;
  cin>>test;
  cout<<"Enter the name of the question you want to create!\n";
  string ques;
  cin>>ques;
  string command = "cd tests;cd "+test+";"+"mkdir "+ques;
  system(command.c_str());
  fstream file;
  string path = "tests/"+test+"/"+ques+"/"+"ques.txt";
  file.open(path.c_str(),ios::out);
  if(!file) cout<<"Error creating file\n";
  else{
      system("clear");
      cout<<"Now start typing the question...\n";
      cout<<"NOTE: to mark the end of the question, enter '@'\n";
      string text="null";
      while(text!="@"){
        getline(cin,text);
        text=text;
        if(text!="@")file<<text<<endl;
      }
      if(text=="@");
      file.close();
    }
  path = "tests/"+test+"/"+ques+"/"+"input.txt";
  file.open(path.c_str(),ios::out);
  if(!file) cout<<"Error opening test case file\n";
  else{
    cout<<"Enter Input for you question and enter '@' to stop..\n";
    string text="null";
    while(text!="@"){
      getline(cin,text);
      if(text!="@")file<<text<<endl;
    }
    if(text=="@");
    file.close();
  }
  path = "tests/"+test+"/"+ques+"/"+"output.txt";
  file.open(path.c_str(),ios::out);
  if(!file) cout<<"Error opening test case file\n";
  else{
    cout<<"Enter Output for you question's Test Case and enter '@' to stop..\n";
    string text="null";
    while(text!="@"){
      getline(cin,text);
      if(text!="@")file<<text<<endl;
    }
    if(text=="@");
    file.close();
  }

}
void attemptTest(){
  string testName,quesName,command,path,text="null";
  //making user record
  command = "mkdir "+u;
  system(command.c_str());

  system("cd tests;ls");
  cout<<"              ->These are the available tests\n";
  cout<<"              ->Enter any name of the available tests to attempt it...\n\n";
  cin>>testName;
  cout<<endl;
  path = "cd tests;cd "+testName+";ls";
  system(path.c_str());
  path = "cd "+u+";mkdir "+testName;
  system(path.c_str());
  cout<<"              ->These are the available questions\n";
  cout<<"              ->Enter name of the question to attempt it\n\n";
  cin>>quesName;
  system("clear");
  path = "cd tests;cd "+testName+";cd "+quesName+";cat ques.txt";
  system(path.c_str());
  cout<<endl<<endl<<"Input format :"<<endl;
  path = "cd tests;cd "+testName+";cd "+quesName+";cat input.txt";
  system(path.c_str());
  cout<<"Output Format :"<<endl;
  path = "cd tests;cd "+testName+";cd "+quesName+";cat output.txt";
  system(path.c_str());
  cout<<endl<<endl;
  path = "cd "+u+";cd "+testName+";mkdir "+quesName;
  system(path.c_str());
  //input from user
  path = u+"/"+testName+"/"+quesName+"/solution.cpp";
  fstream file;
  file.open(path.c_str(),ios::out);
  if(!file) cout<<"Error in opening test"<<endl;
  else{
    cout<<endl<<"INSTRUCTION: Correct output will give you 10 marks else 0 marks"<<endl;
    cout<<"->Write the program below and enter '@' in the end when you are done!"<<endl<<endl;
    while(text!="@"){
    getline(cin,text);
    if(text!="@") file<<text<<endl;
   }
  }
  file.close();
  command = "cd "+u+";cd "+testName+";cd "+quesName+";g++ solution.cpp";
  system(command.c_str());
  cout<<endl<<"The output from your program:"<<endl;
  command = "cd "+u+";cd "+testName+";cd "+quesName+";./a.out";
  system(command.c_str());
  command = "cd "+u+";cd "+testName+";cd "+quesName+";./a.out > compareSol.txt";
  system(command.c_str());
  //asigning marks
  fstream adminFile;
  fstream userFile;
  string adminOut,userOut;
  path = "tests/"+testName+"/"+quesName+"/output.txt";
  adminFile.open(path.c_str(),ios::in);
  if(!adminFile) cout<<"Error in adminFile evaluation"<<endl;
  else{
    getline(adminFile,adminOut);
  }
  path = u+"/"+testName+"/"+quesName+"/compareSol.txt";
  userFile.open(path.c_str(),ios::in);
  if(!userFile) cout<<"Error in userFile evaluation"<<endl;
  else{
    getline(userFile,userOut);
  }
  adminFile.close();
  userFile.close();
  if(adminOut==userOut){
    path = u+"/"+testName+"/"+quesName+"/marks.txt";
    fstream file;
    file.open(path.c_str(),ios::out);
    if(!file) cout<<"Error in final success evaluation"<<endl;
    else file<<"10"<<endl;
    cout<<endl<<"Congratulation, you scored 10 marks"<<endl;
    file.close();
  }
  else{
    path = u+"/"+testName+"/"+quesName+"/marks.txt";
    fstream file;
    file.open(path.c_str(),ios::out);
    if(!file) cout<<"Error in final failed evaluation"<<endl;
    else file<<"0"<<endl;
    cout<<endl<<"You scored 0 marks"<<endl;
    file.close();
  }
           checkUserSession();
}
void viewMarks(){
  string test,ques,command;
  cout<<endl<<"    These are the tests you have attempted :"<<endl;
    command = "cd "+u+";ls";
    system(command.c_str());
 cout<<endl<<"Enter the name of the test you want to see"<<endl;
    cin>>test;
    cout<<endl;
    command = "cd "+u+";cd "+test+";ls";
 cout<<"    These are the questions you have attempted :"<<endl;
    system(command.c_str());
 cout<<endl<<"Enter the name of the question to see you marks for it."<<endl;
 cin>>ques;
 string out = "You marks for question "+ques+" is: ";
 command= "echo "+out+";cd "+u+";cd "+test+";cd "+ques+";cat marks.txt";
 system(command.c_str());
          checkUserSession();
}
void checkUserSession(){
  int userChoice;
  cout<<endl<<endl<<"Enter : "<<endl;
  cout<<"   1) To attempt more test"<<endl;
  cout<<"   2) To view marks of test attempted"<<endl;
  cout<<"   3) To log out"<<endl;
  cin>>userChoice;
       if(userChoice==1) attemptTest();
  else if(userChoice==2) viewMarks();
  else if(userChoice==3) cout<<"Logging you out"<<endl<<endl;
  else cout<<"\nInvalid option selected\n";

}
void user(){
  system("clear");
  cout<<"         |       |  ----- |      ----  ----  |-\\ /-|  -----     |     |  /----  ----   -----      "<<endl;
  cout<<"         |       |  |__   |     |     |    | |  |  |  |__       |     |  \\__    |__    |___/        "<<endl;
  cout<<"         (   |   )  |     |     |     |    | |     |  |         |     |      \\  |      |   \\      "<<endl;
  cout<<"          (__|__)   |____ |____ |____ |____| |     |  |____      \\___/    ___/  |____  |    \\     "<<endl;
  cout<<"                                "<<endl;
  cout<<"                                "<<endl;
  cout<<"                                "<<endl;
  int userChoice;
  cout<<endl<<"Enter :"<<endl;
  cout<<"    1) To attempt the test "<<endl;
  cout<<"    2) To view your marks "<<endl;
  cin>>userChoice;
       if(userChoice==1)  attemptTest();
  else if(userChoice==2)  viewMarks();
}
int login(){
  string adminName = "pranav0408" ;
  string adminPass = "pranav@0408" ;
  string name;
  string password;
  system("clear");
  cout<<"                                       |       ______    /-------  _______  /\\     |                                    "<<endl;
  cout<<"                                       |       |     |  |             |     | \\    |                                    "<<endl;
  cout<<"                                       |       |     |  |     ____    |     |  \\   |                                    "<<endl;
  cout<<"                                       |       |     |  |        |    |     |   \\  |                                    "<<endl;
  cout<<"                                       |       |     |  |        |    |     |    \\ |                                    "<<endl;
  cout<<"                                       |______ |_____|   \\______/  ___|___  |     \\|                                    "<<endl;
  cout<<endl;
  cout<<"                                             --------------------------------------------------             "<<endl;
  cout<<"                                             |                                                |             "<<endl;
  cout<<"                                             |                                                |             "<<endl;
  cout<<"                                             |                                                |             "<<endl;
  cout<<"                                                    Enter UserName :     ";
  cin>>name;cout<<endl;
  cout<<"                                                    Enter Password :     ";
  cin>>password;cout<<endl;
  cout<<"                                             |                                                |             "<<endl;
  cout<<"                                             |                                                |             "<<endl;
  cout<<"                                             |                                                |             "<<endl;
  cout<<"                                             --------------------------------------------------             "<<endl;

  if( name==adminName && password==adminPass ){
    return 1;
  }
  else{
    u=name;
  }

}
int admin(){
  system("clear");
  cout<<"         |       |  ---- |      ----  ----  |-\\ /-|  ----         /\\    -|---    /\\  /\\  -----   |\\   | "<<endl;
  cout<<"         |       | |__   |     |     |    | |  |  | |__          /  \\    |   |  |  \\/  |   |     | \\  | "<<endl;
  cout<<"         (   |   ) |     |     |     |    | |     | |           /----\\   |   |  |      |   |     |  \\ | "<<endl;
  cout<<"          (__|__)  |____ |____ |____ |____| |     | |____      |      | _|___|  |      | __|__   |   \\| "<<endl;
  cout<<"                                "<<endl;
  cout<<"                                "<<endl;
  cout<<"                                "<<endl;

  cout<<endl<<" Hello admin. Please choose anyone of the following options"<<endl;
  cout<<"         1) Create tests      "<<endl;
  cout<<"         2) Design questions for the existing tests"<<endl;
  cout<<"         3) List availabe tests"<<endl;
  cout<<"         4) Log Out"<<endl;
  int adminOption;
  cin>>adminOption;
        if(adminOption==1) createTest();
   else if(adminOption==2) designQues();
   else if(adminOption==3) listTests();
   else if(adminOption==4) {cout<<endl<<"Logging you out..."<<endl<<endl;return 0;}
   else cout<<"Invalid Option selected.Now loggin out!"<<endl;
}
void checkAdminSession(){
  int repeat;
  cout<<"If you want to go to main menu, enter 1 else any other key to quit\n";
  cin>>repeat;
  if(repeat==1) admin();
  else cout<<"Now logging out..."<<endl;
}
void listTests(){
  system("cd tests;ls");
  checkAdminSession();
}
int main(){
      int check = login();
      if(check==1){
            int session=admin();
            if(session==0) return 0;
            checkAdminSession();
            }
      else
            user();

}
