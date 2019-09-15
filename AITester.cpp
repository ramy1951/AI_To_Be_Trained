// identification comments code block
// Ramy Fekry
// Lab Assignment 15, Artificial Intelligence With Learning
// Editor used: Visual Studio
// Compiler used: MinGW GNU

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

struct Movie 
{
  string sayThis;
  Movie* yes;
  Movie* no;
};

void ID(string lab);
Movie* serializeUp(ifstream&);
void deallocate(Movie*);

int main()
{
  ID("Lab Assignment 15, Artificial Intelligence With Learning");
  Movie* top = 0;

  // serialize the top and all nodes below it
  ifstream fin;
  fin.open("ai.txt");
  if (fin.good())
  {  
    // create a node and fill with line from file, and attach all descendent nodes
    top = serializeUp(fin);
    fin.close();
  }
  else
  {
    top = new Movie;
    top->sayThis = "Star Wars";
    top->yes = top->no = 0;
  }

  Movie* p = top;
  cout << "Tell me about the movie you are watching and I'll identify it\n";
  string yesOrNo;

  while (true)
  {
    // see if "p" points to an answer OR a question...
    if (p->yes != 0) // it's a question
    { 
      cout << p->sayThis << "[yes/no]";
      cin >> yesOrNo;
      cin.ignore(1000, 10);
      if (yesOrNo == "yes"|| yesOrNo =="y" || yesOrNo =="Y") p = p->yes;
      if (yesOrNo == "no"|| yesOrNo =="n" ||  yesOrNo=="N") p = p->no;// advance the "p" pointer to its yes or no
    } 
    else
    {
        cout << p->sayThis << "\n"; 
        break;
    }
    } // end of while
    deallocate(top);
} // end of main

Movie* serializeUp(ifstream& fin)
{
  string buf;
  getline(fin, buf);
  if (buf == "EOF") return 0;

  Movie* p = new Movie;
  p->sayThis = buf;
  p->yes = serializeUp(fin);
  p->no = serializeUp(fin);
  return p;
} 

void ID(string lab)
{
  cout << "Ramy Fekry \n\n";
  cout << lab << "\n";  
  cout << "Editor(s) used: Visual Studio\n";
  cout << "Compiler(s) used: MinGW GNU\n";
  cout << "File: " << __FILE__ << "\n"; 
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n";
  cout << "Hi I hope you like my program \n\n";
}

void deallocate(Movie* p)
{
  if (p == 0) return;
  deallocate(p->yes);
  deallocate(p->no);
  delete p;
}