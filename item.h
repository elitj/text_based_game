#include<string>
#include<iostream>
using namespace std;

//next: container functions and action-at-a-distance

class item
{
 public:
  item();
  item(string itemName);
  item(string itemName,string n1);
  item(string itemName,string n1,string n2);
  item(string itemName,string n1,string n2,string n3);
  item(string itemName,string n1,string n2,string n3,string n4);
  ~item();
  void setLongForm(string a);
  string getLongForm();
  void addName(string a);
  bool isNamed(string a);
  int nameCount();
  string getName(int a);
  void setLook(string a);
  string getLook();
  void setPronoun(string a); // "it", "he", "she"
  string getPronoun();
  void setState(int a, string b); // a= 1-4
  string getState(int a);
  bool isVisible();
  void makeVisible();
  void makeInvisible();
  bool isChained();
  void chain();
  void unchain();
  void putUnder(item &a);
  void putOver(item &a);
  void putNextTo(item &a);
  void putBehind(item &a);
  void putInFrontOf(item &a);
  void putInside(item &a);
  void setLink(item &a);
  void resetPrep(int a);
  void resetExternals();
  void setPrepositions(bool a,bool b,bool c,bool d,bool e,bool f,bool g);
  bool getPreposition(int index); //index 0-6
  item* goUnder(); item* goOver(); item* goNextTo(); item* goBehind();
  item* goInFrontOf(); item* goContaining(); item* getLink();
  void makeContainer();
  int countContents();
  void listContents();
  void putContaining(item &a);
  void remove(string a);
  item* goInside(int a);
  void addVerb(string a, int b);
  void updateVerb(string a, int b);
  int getVerbState(string a); //default zero
  int getEventState();
  void setEventState(int a);
  
 private:
  string longform;
  string names[4];
  int na; // # of aliases
  string look;
  string pronoun;
  string state[4];
  bool visible;
  bool chained;
  item *under; // a.under = &b  should be read: "a is under b"
  item *over;
  item *nextTo;
  item *behind;
  item *inFrontOf;
  item *inside;
  item *linked;
  bool prepositions[7];
  /* ordered as above.
     For Prepositions ("behind" used as example):
     false = the item is not behind anything
     true = the item is behind something   */
  item *containing[10]; // containers hold up to ten things
  int co; // default -1 not a container, else how many things inside
  string *verbs;
  int *verbStates;
  int ve; // # of verbs
  int eventState;
  string wordWrap(string);
};
