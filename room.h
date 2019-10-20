#include<string>
#include"item.h"

class room
{
 public:
  room();
  room(string roomName);
  ~room();
  void setName(string name);
  string getName();
  void setLook(string description);
  string getLook();
  void setState(int a, string b);
  string getState(int a);
  void setDoors(int a, int b, int c, int d, int e,
		int f, int g, int h, int i, int j);
  void setDoor(int index, int state);
  int getDoor(int index); // index 0-9
  void connect(room &next, int index);
  room* followDoor(int index);
  void flagExplored();
  bool isExplored();
  void addJunk(item &a);
  bool hasJunk(string word); // returns true if item is in room
  void listJunk();
  int numJunk();
  item* takeJunk(string word);  // returns object taken
  item* getJunk(string word);
  item* getJunkByIndex(int a); // used for 'drop all', etc.
  void addVerb(string a, int b);
  void updateVerb(string a, int b);
  int getVerbState(string a); // returns zero as default (no verb)
  void setEventState(int a);
  int getEventState();

 private:
  int Nd; int NEd; int Ed; int SEd; int Sd;
  int SWd; int Wd; int NWd; int Ud; int Dd;
  room *Ndoor; room *NEdoor; room *Edoor; room *SEdoor; room *Sdoor;
  room *SWdoor; room *Wdoor; room *NWdoor; room *Udoor; room *Ddoor;
  string name;
  string look;
  string state[4];
  item **junk;
  int ju;  // # of junk items
  string *verbs;
  int ve; // # of verbs
  int *verbStates; // zero is default (no effect)
  int eventState; // zero is default
  bool explored;
  string wordWrap(string);
};
