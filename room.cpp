#include<string>
#include"room.h"
#include<iostream>
using namespace std;

room::room()
{
  Nd = 0; NEd = 0; Ed = 0; SEd = 0; Sd = 0;
  SWd = 0; Wd = 0; NWd = 0; Ud = 0; Dd = 0;
  Ndoor = NULL; NEdoor = NULL; Edoor = NULL;
  SEdoor = NULL; Sdoor = NULL; SWdoor = NULL;
  Wdoor = NULL; NWdoor = NULL; Udoor = NULL;
  Ddoor = NULL;
  name = "unnamed room";
  look = "nothing to see here";
  junk = new item*[10];
  ju = 0;
  verbs = new string[10];
  ve = 0;
  verbStates = new int[10];
  eventState = 0; //default value
  explored = false;
}

room::room(string roomName)
{
  Nd = 0; NEd = 0; Ed = 0; SEd = 0; Sd = 0;
  SWd = 0; Wd = 0; NWd = 0; Ud = 0; Dd = 0;
  Ndoor = NULL; NEdoor = NULL; Edoor = NULL;
  SEdoor = NULL; Sdoor = NULL; SWdoor = NULL;
  Wdoor = NULL; NWdoor = NULL; Udoor = NULL;
  Ddoor = NULL;
  name = roomName;
  look = "nothing to see here, yet";
  junk = new item*[10];
  ju = 0;
  verbs = new string[10];
  ve = 0;
  verbStates = new int[10];
  eventState = 0; //default value
  explored = false;
}

room::~room(){}

void room::setName(string word) {name = wordWrap(word);}
string room::getName() {return name;}

void room::setLook(string description) {look = wordWrap(description);}
string room::getLook() {return look;}

void room::setState(int a, string b) {state[a-1]=wordWrap(b);}
string room::getState(int a) {return state[a-1];}

void room::setDoors(int a, int b, int c, int d, int e,
		    int f, int g, int h, int i, int j)
{
  Nd = a; NEd = b; Ed = c; SEd = d; Sd = e;
  SWd = f; Wd = g; NWd = h; Ud = i; Dd = j;
}

void room::setDoor(int index, int a)
{
  switch(index)
    {
    case 0: Nd = a; break;
    case 1: NEd = a; break;
    case 2: Ed = a; break;
    case 3: SEd = a; break;
    case 4: Sd = a; break;
    case 5: SWd = a; break;
    case 6: Wd = a; break;
    case 7: NWd = a; break;
    case 8: Ud = a; break;
    case 9: Dd = a; break;
    default: cout << "Bad setDoor index" << endl; break;
    }
}

int room::getDoor(int index)
{
  switch(index)
    {
    case 0: return Nd; break;
    case 1: return NEd; break;
    case 2: return Ed; break;
    case 3: return SEd; break;
    case 4: return Sd; break;
    case 5: return SWd; break;
    case 6: return Wd; break;
    case 7: return NWd; break;
    case 8: return Ud; break;
    case 9: return Dd; break;
    default: cout << "Bad getDoor index" << endl; break;
    }
  return -1;
}

void room::connect(room &next, int index)
{
    switch(index)
    {
    case 0: 
      if(Nd==0) Nd=1;
      Ndoor = &next; 
      break;
    case 1: 
      if(NEd==0) NEd=1;
      NEdoor = &next; 
      break;
    case 2: 
      if(Ed==0) Ed=1;
      Edoor = &next; 
      break;
    case 3: 
      if(SEd==0) SEd=1;
      SEdoor = &next; 
      break;
    case 4: 
      if(Sd==0) Sd=1;
      Sdoor = &next; 
      break;
    case 5: 
      if(SWd==0) SWd=1;
      SWdoor = &next; 
      break;
    case 6: 
      if(Wd==0) Wd=1;
      Wdoor = &next; 
      break;
    case 7: 
      if(NWd==0) NWd=1;
      NWdoor = &next; 
      break;
    case 8: 
      if(Ud==0) Ud=1;
      Udoor = &next; 
      break;
    case 9: 
      if(Dd==0) Dd=1;
      Ddoor = &next; 
      break;
    default: cout << "Bad connect index" << endl; break;
    }
}

room* room::followDoor(int index)
{
  switch(index)
    {
    case 0: return Ndoor; break;
    case 1: return NEdoor; break;
    case 2: return Edoor; break;
    case 3: return SEdoor; break;
    case 4: return Sdoor; break;
    case 5: return SWdoor; break;
    case 6: return Wdoor; break;
    case 7: return NWdoor; break;
    case 8: return Udoor; break;
    case 9: return Ddoor; break;
    default: cout << "Bad followDoor index" << endl; break;
    }
}

void room::flagExplored() {explored = true;}

bool room::isExplored() {return explored;}

void room::addJunk(item &a)
{
  if (ju>9 && ju%10==0)
    {
      item **temp = new item*[ju+10];
      for(int i=0;i<ju;i++)
	temp[i]=junk[i];
      delete [] junk;
      junk = temp;
    }
  junk[ju] = &a;
  ju++;
  return;
}

bool room::hasJunk(string word)
{
  for(int i=0;i<ju;i++)
    if((*junk[i]).isNamed(word)) return true; 
  return false;
}

void room::listJunk()
{
  int counter=0;
  for(int i=0;i<ju;i++)
    if((*junk[i]).isVisible() && !(*junk[i]).isChained() &&
       !(*junk[i]).getPreposition(5)) counter++;
  if(counter==0)
    {
      if(name=="INVENTORY")
	cout << "You are not carrying anything." << endl;
      return;
    }
  if(name=="INVENTORY")
    cout << "You are carrying: " << endl;
  else cout << "Around the room you see: " << endl;
  for(int j=0;j<ju;j++)
    if((*junk[j]).isVisible() && !(*junk[j]).isChained() &&
       !(*junk[j]).getPreposition(5))
      {
	cout << "a " << (*junk[j]).getLongForm();
	if((*junk[j]).countContents() > 0 && 
	   (*junk[j]).getVerbState("open")==2)
	  if((*(*junk[j]).goInside(0)).isVisible())
	    {
	      cout << " containing:" << endl;
	      (*junk[j]).listContents();
	    }
	cout << endl;
      }
}
 
int room::numJunk() {return ju;}     

item* room::takeJunk(string word) //must be paired with inv. function
{
  for(int i=0;i<ju;i++)
    if ((*junk[i]).isNamed(word))
      {
	item* temp = junk[i];
	for(int j=i;j<ju;j++)
	  junk[j] = junk[j+1];
	ju--;
	return temp;
      }
  cout << "Error: something went wrong in room.takeJunk(string)" << endl;
  item* dummy;
  return dummy;
}

item* room::getJunk(string word)
{
  for(int i=0;i<ju;i++)
    if((*junk[i]).isNamed(word)) 
      return junk[i];
  cout << "ERROR, junk item not found. check junk array." << endl;
  return junk[0];
}

item* room::getJunkByIndex(int a) {return junk[a];} // no error check

void room::addVerb(string a, int b)
{
  if (ve>9 && ve%10==0)
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

void room::updateVerb(string a, int b)
{
  for(int i=0;i<ve;i++)
    if(verbs[i]==a)
      {
	verbStates[i] = b;
	return;
      }
  cout << "Error: updateVerb passed word not in room list" << endl;
}

int room::getVerbState(string a)
{
  for(int i=0;i<ve;i++)
    if(verbs[i]==a)
      return verbStates[i];
  return 0;   //default value
}

void room::setEventState(int a) {eventState = a;}

int room::getEventState() {return eventState;}

string room::wordWrap(string a)
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
