#include<string>
#include"item.h"
#include<iostream>
using namespace std;

item::item()
{
  longform = "unnamed item";
  na = 0;
  look = "";
  pronoun = "it";
  visible = true;
  chained = false;
  under = NULL; over = NULL; nextTo = NULL; behind = NULL;
  inFrontOf = NULL; inside = NULL; linked = NULL;
  containing[0]=NULL; containing[1]=NULL; containing[2]=NULL; 
  containing[3]=NULL; containing[4]=NULL; containing[5]=NULL; 
  containing[6]=NULL; containing[7]=NULL; containing[8]=NULL; 
  containing[9]=NULL;
  co = -1;
  prepositions[0]=false; prepositions[1]=false; prepositions[2]=false;
  prepositions[3]=false; prepositions[4]=false; prepositions[5]=false;
  prepositions[6]=false;
  verbs = new string[10];
  verbStates = new int[10];
  ve = 0;
  eventState = 0;
}

item::item(string itemName)
{
  longform = itemName;
  na = 0;
  look = "";
  pronoun = "it";
  visible = true;
  chained = false;
  under = NULL; over = NULL; nextTo = NULL; behind = NULL;
  inFrontOf = NULL; inside = NULL; linked = NULL;
  containing[0]=NULL; containing[1]=NULL; containing[2]=NULL; 
  containing[3]=NULL; containing[4]=NULL; containing[5]=NULL; 
  containing[6]=NULL; containing[7]=NULL; containing[8]=NULL; 
  containing[9]=NULL;
  co = -1;
  prepositions[0]=false; prepositions[1]=false; prepositions[2]=false;
  prepositions[3]=false; prepositions[4]=false; prepositions[5]=false;
  prepositions[6]=false;
  verbs = new string[10];
  verbStates = new int[10];
  ve = 0;
  eventState = 0;
}

item::item(string itemName, string n1)
{
  longform = itemName;
  names[0] = n1;
  na = 1;
  look = "no attributes";
  pronoun = "it";
  visible = true;
  chained = false;
  under = NULL; over = NULL; nextTo = NULL; behind = NULL;
  inFrontOf = NULL; inside = NULL; linked = NULL;
  containing[0]=NULL; containing[1]=NULL; containing[2]=NULL; 
  containing[3]=NULL; containing[4]=NULL; containing[5]=NULL; 
  containing[6]=NULL; containing[7]=NULL; containing[8]=NULL; 
  containing[9]=NULL;
  co = -1;
  prepositions[0]=false; prepositions[1]=false; prepositions[2]=false;
  prepositions[3]=false; prepositions[4]=false; prepositions[5]=false;
  prepositions[6]=false;
  verbs = new string[10];
  verbStates = new int[10];
  ve = 0;
  eventState = 0;
}

item::item(string itemName, string n1, string n2)
{
  longform = itemName;
  names[0] = n1;
  names[1] = n2;
  na = 2;
  look = "no attributes";
  pronoun = "it";
  visible = true;
  chained = false;
  under = NULL; over = NULL; nextTo = NULL; behind = NULL;
  inFrontOf = NULL; inside = NULL; linked = NULL;
  containing[0]=NULL; containing[1]=NULL; containing[2]=NULL; 
  containing[3]=NULL; containing[4]=NULL; containing[5]=NULL; 
  containing[6]=NULL; containing[7]=NULL; containing[8]=NULL; 
  containing[9]=NULL;
  co = -1;
  prepositions[0]=false; prepositions[1]=false; prepositions[2]=false;
  prepositions[3]=false; prepositions[4]=false; prepositions[5]=false;
  prepositions[6]=false;
  verbs = new string[10];
  verbStates = new int[10];
  ve = 0;
  eventState = 0;
}

item::item(string itemName, string n1, string n2, string n3)
{
  longform = itemName;
  names[0] = n1;
  names[1] = n2;
  names[2] = n3;
  na = 3;
  look = "no attributes";
  pronoun = "it";
  visible = true;
  chained = false;
  under = NULL; over = NULL; nextTo = NULL; behind = NULL;
  inFrontOf = NULL; inside = NULL; linked = NULL;
  containing[0]=NULL; containing[1]=NULL; containing[2]=NULL; 
  containing[3]=NULL; containing[4]=NULL; containing[5]=NULL; 
  containing[6]=NULL; containing[7]=NULL; containing[8]=NULL; 
  containing[9]=NULL;
  co = -1;
  prepositions[0]=false; prepositions[1]=false; prepositions[2]=false;
  prepositions[3]=false; prepositions[4]=false; prepositions[5]=false;
  prepositions[6]=false;
  verbs = new string[10];
  verbStates = new int[10];
  ve = 0;
  eventState = 0;
}
item::item(string itemName, string n1, string n2, string n3, string n4)
{
  longform = itemName;
  names[0] = n1;
  names[1] = n2;
  names[2] = n3;
  names[3] = n4;
  na = 4;
  look = "no attributes";
  pronoun = "it";
  visible = true;
  chained = false;
  under = NULL; over = NULL; nextTo = NULL; behind = NULL;
  inFrontOf = NULL; inside = NULL; linked = NULL;
  containing[0]=NULL; containing[1]=NULL; containing[2]=NULL; 
  containing[3]=NULL; containing[4]=NULL; containing[5]=NULL; 
  containing[6]=NULL; containing[7]=NULL; containing[8]=NULL; 
  containing[9]=NULL;
  co = -1;
  prepositions[0]=false; prepositions[1]=false; prepositions[2]=false;
  prepositions[3]=false; prepositions[4]=false; prepositions[5]=false;
  prepositions[6]=false;
  verbs = new string[10];
  verbStates = new int[10];
  ve = 0;
  eventState = 0;
}


item::~item() {}

void item::setLongForm(string a) {longform = wordWrap(a);}
string item::getLongForm() {return longform;}

void item::addName(string a)
{
  if(na>3)
    cout << "Error adding name to " << longform << "." << endl;
  else
    {
      names[na] = a;
      na++;
    }
}
int item::nameCount() {return na;}
string item::getName(int a) {return names[a];} //no error check
bool item::isNamed(string a)
{
  for(int iter=0;iter<na;iter++)
    if(names[iter]==a) return true;
  return false;
}

void item::setLook(string a) {look = wordWrap(a);}
string item::getLook() {return look;}

void item::setPronoun(string a) {pronoun = a;}
string item::getPronoun() {return pronoun;}

void item::setState(int a, string b) {state[a-1] = wordWrap(b);}
string item::getState(int a) {return state[a-1];}


bool item::isVisible() {return visible;}
void item::makeVisible() {visible = true;}
void item::makeInvisible() {visible = false;}

bool item::isChained() {return chained;}
void item::chain() {chained = true;}
void item::unchain() {chained = false;}

/* warning: the put functions below do not check for overwriting
other items or any sort of state.  make sure to add these checks
into the main verb "Put". Also, these should be called in pairs. */

void item::putUnder(item &a)
{
  prepositions[0]=true;
  under = &a;
}

void item::putOver(item &a)
{
  prepositions[1]=true;
  over = &a;
}

void item::putNextTo(item &a)
{
  prepositions[2]=true;
  nextTo = &a;
}

void item::putBehind(item &a)
{
  prepositions[3]=true;
  behind = &a;
}

void item::putInFrontOf(item &a)
{
  prepositions[4]=true;
  inFrontOf = &a;
}

void item::putInside(item &a)
{
  prepositions[5]=true;
  inside = &a;
}

void item::setLink(item &a)
{
  prepositions[6]=true;
  linked = &a;
}

void item::resetPrep(int a)
{
  prepositions[a] = false;
  switch(a)
    {
    case 0: under = NULL; break;
    case 1: over = NULL; break;
    case 2: nextTo = NULL; break;
    case 3: behind = NULL; break;
    case 4: inFrontOf = NULL; break;
    case 5: inside = NULL; break;
    case 6: linked = NULL; break;
    default: cout << "resetPrep fed bad arg." << endl;
    }
}

void item::resetExternals()
{
  under = NULL;
  over = NULL;
  nextTo = NULL;
  behind = NULL;
  inFrontOf = NULL;
  inside = NULL;
  prepositions[0] = false;
  prepositions[1] = false;
  prepositions[2] = false;
  prepositions[3] = false;
  prepositions[4] = false;
  prepositions[5] = false;
}

void item::setPrepositions(bool a,bool b,bool c,bool d,bool e,bool f,bool g)
{
  prepositions[0] = a;
  prepositions[1] = b;
  prepositions[2] = c;
  prepositions[3] = d;
  prepositions[4] = e;
  prepositions[5] = f;
  prepositions[6] = g;

}  //this should be rarely used

bool item::getPreposition(int index) {return prepositions[index];}

//opposite prepositions to reflect naming convention
item* item::goUnder() {return over;} 
item* item::goOver() {return under;}
item* item::goNextTo() {return nextTo;}
item* item::goBehind() {return inFrontOf;}
item* item::goInFrontOf() {return behind;}
item* item::goContaining() {return inside;}
item* item::getLink() {return linked;}

void item::makeContainer() 
{
  co = 0;
  verbs[ve] = "open";
  verbStates[ve] = 2;
  ve++;
}
int item::countContents() {return co;}
void item::listContents()
{
  for(int i=0;i<co;i++)
    cout << " a " << (*containing[i]).getLongForm() << endl;
}
void item::putContaining(item &a)
{
  if(co==-1 || co>9) return;
  containing[co] = &a;
  co++;
}
void item::remove(string a)
{
  for(int i=0;i<co;i++)
    if((*containing[i]).isNamed(a))
      {
	for(int j=i;j<co;j++)
	  containing[j]=containing[j+1];
	co--;
	return;
      }
}
item* item::goInside(int a) {return containing[a];}

void item::addVerb(string a, int b)
{
  if (ve>9 && ve%10==0)  // memory management
    {
      string *temp1 = new string[ve+10];
      int *temp2 = new int[ve+10];
      for(int i=0;i<ve;i++)
	{
	  temp1[i]=verbs[i];
	  temp2[i]=verbStates[i];
	}
      delete [] verbs;
      delete [] verbStates;
      verbs = temp1;
      verbStates = temp2;
    }
  verbs[ve] = a;
  verbStates[ve] = b;
  ve++;
  return;
}

void item::updateVerb(string a, int b)
{
  for(int i=0;i<ve;i++)
    if(verbs[i]==a)
      {
	verbStates[i] = b;
	return;
      }
  cout << "Error: updateVerb passed word not in item list" << endl;
}

int item::getVerbState(string a)
{
  for(int i=0;i<ve;i++)
    if(verbs[i]==a)
      return verbStates[i];
  return 0;   //default value
}

int item::getEventState() {return eventState;}

void item::setEventState(int a) {eventState = a;};

string item::wordWrap(string a)
{
  const int WIDTH = 70; // delete when implemented
  int index;
  string wrapped = "";
  while(a.length()>=WIDTH)
    {
      index = a.substr(0,WIDTH).find_last_of(" ");
      wrapped.append(a.substr(0,index));
      wrapped.append("\n");
      a = a.substr(index+1);
    }
  wrapped.append(a);
  return wrapped;
}
