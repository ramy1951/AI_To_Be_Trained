// identification comments code block
// Ramy Fekry
// Artificial Intelligence With Learning (The Trainer end) [use AITester.cpp after training PC]
// Editor used: Visual Studio
// Compiler used: MinGW GNU

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ofstream;
using std::ifstream;

struct Movie 
{
  string sayThis;
  Movie* yes;
  Movie* no;
};

void ID(string);
Movie* serializeUp(ifstream&);
void serializeDown(ofstream&, Movie*);
void deallocate(Movie*);

int main()
{
  ID("Artificial Intelligence With Learning");
  Movie* top = 0;
  string buf;

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
 
  // the instructions to the user
  cout << "\nTell me what was in that movie and I'll identify it.\n";
 
  while (true)
   { 
     Movie* p = top; // move p through the tree
    while (true) // the p-loop
    {
      if (p->yes != 0 && p->no != 0) // it's a question
      {
        cout << p->sayThis;
        cout << "[yes/no]";
        getline(cin, buf);
        if (buf == "yes" || buf == "y" || buf == "Y") p = p->yes; // advance the "p" pointer to its yes or no
        if (buf == "no" || buf == "n" || buf == "N") p = p->no; // advance the "p" pointer to its yes or no 
      }
    else // it's an answer -- here's the opportunity to learn
      {
        cout << "It's " << p->sayThis << ".";
        cout << " Right? ";
        cin >> buf;
        cin.ignore(1000, 10);
        if (buf =="yes" || buf == "y" || buf == "Y")  break;
        if (buf == "no" || buf == "n" || buf == "N")
        {
          string answer;
          cout << "What is it, then? ";
          getline(cin, answer);
          Movie* yes = new Movie;
          Movie* no = new Movie;
          yes->yes = yes->no = 0;
          no->yes = no->no = 0;
          p->yes = yes; // make link...
          p->no = no; // ...to p's node
            
          string question;
          cout << "Dang! so what yes or no question should I ask to diffrentiate between "<< p->sayThis << " and " << answer << "?? ";
          getline(cin, question);

          cout << "Thanks whats the answer to \"" << question << "\" ? ";
          cin >> buf;
          cin.ignore(1000, 10);
          if (buf == "yes" || buf == "y" || buf == "Y")
          {
            yes->sayThis = answer;
            no->sayThis = p->sayThis;
          }
          else
          {
            yes->sayThis = p->sayThis;
            no->sayThis = answer;
          }
          p->sayThis = question;
        }
        }// end of else
        // if (p->yes == 0 && p->no == 0) break;
    } // end of inside while
      cout << "continue teach me? ";
      cin >> buf;
      cin.ignore(1000, 10);
    if (buf == "no" || buf == "n" || buf == "N") break;
  } // end of outter while

  // serialize top and all nodes below it
  ofstream fout;
  fout.open("ai.txt");
  serializeDown(fout, top);
  fout.close();

  deallocate(top);
} // end of main
void ID(string lab)
{
  // identification output code block
  cout << "Ramy Fekry \n\n";
  cout << lab << "\n";  
  cout << "Editor(s) used: Visual Studio\n";
  cout << "Compiler(s) used: MinGW GNU\n";
  cout << "File: " << __FILE__ << "\n"; 
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n";
  cout << "Hi I hope you like my program \n\n";
}

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

void serializeDown(ofstream& fout, Movie* p)
{
  // make sure there's something to serialize
  if (p == 0)
    fout << "EOF\n";
  else
  {
    fout << p->sayThis << "\n";
    serializeDown(fout, p->yes);
    serializeDown(fout, p->no);
  }
}

void deallocate(Movie* p)
{
  if (p == 0) return;
  deallocate(p->yes);
  deallocate(p->no);
  delete p;
}
