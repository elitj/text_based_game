#include<string>
#include<iostream>
#include"room.h"
using namespace std;

  //  ----------------
  //  GLOBAL VARIABLES
  //  ----------------

typedef void (*verbPtr)();
const int VERB_TABLE_SIZE = 500;
const int ITEM_TABLE_SIZE = 500;
string verbNames[VERB_TABLE_SIZE]; // first value is default
verbPtr verbFunctions[VERB_TABLE_SIZE]={NULL};
int verbTypes[VERB_TABLE_SIZE];
int totalVerbs = 0; // this is incremented as verbs are added
string itemNames[ITEM_TABLE_SIZE];
item* itemPointers[ITEM_TABLE_SIZE];
int totalItems = 0; // incremented as items are added
string cVerb, cNoun1, cNoun2, cPrep;
room inventory("INVENTORY");
room *currentRoom;
int timeState;
item *x1; // item 1
item *x2; // item 2
bool alive = true; // player is alive or dead

  //  --------------------------------
  //  UTILITY FUNCTIONS: DO NOT DELETE
  //  --------------------------------

void parse(string command);
void preVerb(int index);
void event(int eventState, int verbIndex);
void addV(string verbName, void (*ptr)(), int type);
void addI(string itemName, item* itemPtr);


  //  ----------------------
  //  VERB COMMAND FUNCTIONS
  //  ----------------------

void vUnknown();      void vQuit();        void vHelp();
void vNothing();
void vInventory();    void vLook();
void vTake();         void vDrop();        void vGo();
void vNorth();        void vNortheast();   void vEast();
void vSoutheast();    void vSouth();       void vSouthwest();
void vWest();         void vNorthwest();   void vUp();
void vDown();         void vUse();         void vWear();
void vEat();          void vDrink();
void vCombine();      void vTurn();        void vPut();
void vKill();         void vBreak();       void vKiss();
void vBurn();         void vClimb();       void vCut();
void vDig();          void vRemove();
void vArrange();
void vCalculate();
void vItemize();
void vSaunter();

  //  -------------
  //  MAIN FUNCTION
  //  -------------

int main()
{
 
  /* the verb table is populated below by the addV function. It takes
     three arguments: the verb command string, an address for the verb
     function pointer, and an integer value from 0-6.  The integer 
     classifies syntactically what kind of verb it is so that the 
     preVerb function can give proper error messages. */
 
  addV("unknown_verb", &vUnknown, 0);  // this MUST be the first verb
  addV("quit", &vQuit, 0);            addV("q", &vQuit, 0);
  addV("help", &vHelp, 0);
  addV("nothing", &vNothing, 0);      addV("wait", &vNothing, 1);
  addV("inventory", &vInventory, 1);  addV("i", &vInventory, 1);
  addV("look", &vLook, 4);            addV("l", &vLook, 4);
  addV("examine", &vLook, 2);         addV("read", &vLook, 2);
  addV("take", &vTake, 2);            addV("grab", &vTake, 2);
  addV("drop", &vDrop, 2);
  addV("go", &vGo, 4);
  addV("north", &vNorth, 1);          addV("n", &vNorth, 1);
  addV("northeast", &vNortheast, 1);  addV("ne", &vNortheast, 1);
  addV("east", &vEast, 1);            addV("e", &vEast, 1);
  addV("southeast", &vSoutheast, 1);  addV("se", &vSoutheast, 1);
  addV("south", &vSouth, 1);          addV("s", &vSouth, 1);
  addV("southwest", &vSouthwest, 1);  addV("sw", &vSouthwest, 1);
  addV("west", &vWest, 1);            addV("w", &vWest, 1);
  addV("northwest", &vNorthwest, 1);  addV("nw", &vNorthwest, 1);
  addV("up", &vUp, 1);                addV("u", &vUp, 1);
  addV("down", &vDown, 1);            addV("d", &vDown, 1);
  addV("use", &vUse, 5);
  addV("wear", &vWear, 2);
  addV("eat", &vEat, 2);
  addV("drink", &vDrink, 2);
  addV("combine", &vCombine, 3);
  addV("turn", &vTurn, 4);
  addV("put", &vPut, 5);
  addV("kill", &vKill, 4);
  addV("break", &vBreak, 5);
  addV("kiss", &vKiss, 2);
  addV("burn", &vBurn, 5);
  addV("climb", &vClimb, 4);
  addV("cut", &vCut, 5);
  addV("dig", &vDig, 0);
  addV("remove", &vRemove, 5);
  addV("arrange", &vArrange, 2);
  addV("calculate", &vCalculate, 2);
  addV("itemize", &vItemize, 2);
  addV("saunter", &vSaunter, 1);

  //  -----------------------------------
  //  CONSTRUCTION OF SPECIFIC GAME WORLD
  //  -----------------------------------

  room cenote("BRIGHT CENOTE");
  currentRoom=&cenote;
  cenote.flagExplored();
  cenote.setLook("You are in a circular cavern standing on ancient Mayan steps carved two thousand years ago. The sun is coming in through the hole at the top of the cenote, shining right on the murky water, that still looks so fresh you could jump in and take a drink. There are vines hanging from the top, some of them are long enough to touch the water.  They look sturdy enough to climb. There are also some pits carved in the wall. There are some stairs leading off to the south.");
  room city("ANCIENT MAYAN CITY");
  city.setLook("The area looks fresh, newly built. The step pyramid is covered in paints of blue, yellow and red. The step pyramid directly to your west. There is a slab covered in sculpted faces. To the north, where there are more trees, there is movement. Below you is a cenote.");
  room tourist("TOURIST TRAP");
  tourist.setLook("You are surrounded by people, being jostled by typical tourists. You can make out through the crowd an information building to the northwest and a booth selling glittery stuff to the east. There are stairs leading down to a cenote to the north. There is a water fountain nearby.");
  room base("BASE OF THE STEP PYRAMID");
  base.setLook("You're standing in the sunlight, the paints glaringly bright.  The steps look very steep, with no railing, at something close to an exact 45 degree angle. To the east is an ancient mayan city, and above is the top of the pyramid.");
  room jungle("JUNGLE");
  jungle.setLook("The jungle is not as dense as you would imagine a jungle. The movement you saw is a procession of people, all wearing green. They are all carrying jars.");
  room top("TOP OF THE PYRAMID");
  top.setLook("You see a man in colorful robes, covered in feathers, with his back to you.  A woman sitting on a dais, who is smiling and looks very happy to see you, and a jug of water. From the top you can see the tops of the trees in the jungle, in a full 360 degrees, all jungle, except for the city right below you.An exceedingly bright sun makes the top hoter than below.");
  room info("INFORMATION BUILDING");
  info.setLook("The information building is almost completely empty except for a friendly looking old gentleman behind the counter, on which there is a rack of postcards. One wall is dominated by a large map. The rest of the room is filled with artifacts, half of which are mayan relics, the other half is covered in mounted jungle cats. The door exits to the southeast.");
  room booth("GLITTERY BOOTH");
  booth.setLook("The glittery booth is more crowded than the drinking fountain.  There are people jostling for the attention of a single, harassed-looking teenage girl, who is taking money and giving to the purchasers snow globes, which is ironic for a jungle climate.  They seem to be exceedingly popular though, because inside each snowglobe is a beating heart. To the west you see a crowded fountain.");
  cenote.connect(city,8);
  city.connect(cenote,9);
  cenote.connect(tourist,4);
  tourist.connect(cenote,0);
  city.connect(base,6);
  base.connect(city,2);
  base.connect(top,8);
  top.connect(base,9);
  tourist.connect(info,7);
  tourist.connect(booth,2);
  info.connect(tourist,3);
  booth.connect(tourist,6);
  
  //item iUnknown_Item("unknown_item");
  item iVines("vines");  iVines.chain();
  item iWater("water");  iWater.chain();
  item iSlab("slab"); iSlab.chain();
  item iBody("body"); iBody.chain();
  item iTea("teacup");
  item iFlask("flask");
  item iFlint("flint");
  item iTinder("tinder");
  item iWoman("woman");
  item iMan("man"); iMan.chain();
  item iJug("jug");
  item iDais("dais"); iDais.chain();
  item iOldy("gentleman"); iOldy.chain();
  item iRack("rack");
  item iMap("map"); iMap.chain();
  item iArtifacts("artifacts"); iArtifacts.chain();
  item iCats("cats"); iCats.chain();
  item iGirl("girl"); iGirl.chain();
  item iSnowglobe("snowglobe");
  item iCash("cash");
  iVines.setLook("The vines are well-nourished, the veins show through in the bright sunlight.  They are exceedingly dense and sturdy enough to climb.");
  iWater.setLook("The water looks deep, almost immeasurable.");
  iSlab.setLook("Covered in sculpted faces. They look fierce and angry.");
  iBody.setLook("He looks exceedingly fat, that must have been the reason why he fell down the stairs.  He is clothed in lavish robes of pink.");
  iTea.setLook("A royal dulton, handpainted, periwinkle teacup, with a gold-embossed rim. It looks potentially like 24-carat gold. It's filled with water.");
  iFlask.setLook("A skin flask with a stopper.");
  iFlint.setLook("Looks like it could make a fire.");
  iTinder.setLook("To be used with the flint.");
  iWoman.setLook("She is wearing simple brown robes and a shawl.");
  iMan.setLook("His back and shoulders look powerful and the regalness of the fabric and feathers on his robe is intimidating.");
  iJug.setLook("A simple clay jug filled with water.");
  iDais.setLook("A stone dais, painted red, yellow and blue.");
  iProcession.setLook("At the front of the procession are naked young women, dancing.  At the back are stoic, corpulent, bearded men holding bigger jars than the rest.");
  iOldy.setLook("He smiles automatically in acknowledgement. ");
  iRack.setLook("Each postcard is seventy-five cents.");
  iMap.setLook("The map is 3D. The paper plastered over a fiberglass topographic representation of the elevations of the region.  However it is clearly outdated, since it says the place that you are standing in is supposed to be just jungle..");
  iArtifacts.setLook("The artifacts are a collection of golden jaguars and stylized heads behind a thick plate of glass.  The artistic merit is unquestionable, as is the intricacy of detail. They look valuable.");
  iCats.setLook("Each cat stares with glass eyes, and was posed by the (clearly sick) taxidermist in ferocious poses, with snarling maws and extended paws.");
  iGirl.setLook("She's wearing too much makeup.");
  iSnowglobe.setLook("These are gross. You want one.");
  iCash.setLook("Tempting, very tempting.");

  // all junk must be added AFTER item traits are complete!!

  cenote.addJunk(iVines);
  cenote.addJunk(iWater);
  city.addJunk(iSlab);
  base.addJunk(iBody);
  base.addJunk(iTea);
  base.addJunk(iFlask);
  base.addJunk(iFlint);
  base.addJunk(iTinder);
  top.addJunk(iWoman);
  top.addJunk(iMan);
  top.addJunk(iJug);
  top.addJunk(iDais);
  info.addJunk(iOldy);
  info.addJunk(iRack);
  info.addJunk(iMap);
  info.addJunk(iArtifacts);
  info.addJunk(iCats);
  booth.addJunk(iGirl);
  booth.addJunk(iSnowglobe);
  booth.addJunk(iCash);

  //  addI("unknown_item",&iUnknown_Item); // must be in first position
  /*addI("gloves", &iWorkGloves);
  addI("schedule",&iSchedule);
  addI("panel",&iPanel);
  addI("engine",&iEngine);
  addI("cage",&iCage);
  addI("chalkboard",&iChalkboard);
  addI("flowers",&iFlowers);         addI("flowerpot",&iFlowers);
  addI("form",&iForm);
  addI("magazine",&iMagazine);
  addI("tv",&iTV);
  addI("car",&iHatchback);           addI("hatchback",&iHatchback);
  addI("porn",&iPorn);               addI("pornography",&iPorn);
  addI("floor",&iFloor);
  addI("cargo",&iCargo);
  addI("gyroscope",&iGyroscope);     addI("gyro",&iGyroscope);
  addI("boss",&iBoss);               addI("steve",&iBoss);
  */
  //  -------------------------
  //  END OF WORLD CONSTRUCTION
  //  -------------------------

  cout << "You are inside some caves." << endl << endl;
  vLook();

  //  --------------------------
  //  TURN PROCEDURE STARTS HERE
  //  --------------------------

  int temp,iter,j,k,l;  
  char simpleInput[200];
  string commandString;

  while(alive)
    {
      //cout << (*(*currentRoom).getJunk("flowers")).getVerbState("arrange") << endl;
      cVerb=""; // clear global variable states here!
      cNoun1="";
      cNoun2="";
      cPrep="";
      cin.getline(simpleInput,200); // raw input
      for(iter=0;iter<200;iter++) // convert to lowercase
	{
	  temp = static_cast<int>(simpleInput[iter]);
	  if(temp>64 && temp<91) temp += 32;
	  temp = static_cast<char>(temp);
	  simpleInput[iter] = temp;
	}
      commandString = simpleInput;
      parse(commandString);  // break input into words
      l = (*currentRoom).getEventState();
      k=0;  // zero signifies verb not found
      for(j=0;j<totalVerbs;j++)
	if(cVerb==verbNames[j]) {k=j;break;} // lookup verb function
      if (l!=0) event(l, k);  // events independent of commands
      // event function calls verb independently
      else preVerb(k); // grammar error message or function call
      timeState++;
      // Put formatting commands here 
      cout << endl << endl;
    }
      
  return 0;
}

  //  -----------------
  //  UTILITY FUNCTIONS
  //  -----------------

void parse(string command)
{
  string word[4]={"","","",""};
  int pos;
  int index=0;
  pos=command.find(" ",0);
  while(pos!=string::npos && index<3)
    {
      while(pos==0)
	{
	  command.erase(0,1);
	  pos=command.find(" ",0);
	}
      word[index].assign(command,0,pos);
      command.erase(0,pos+1);
      if(!(word[index]=="the" || word[index]=="a" ||
	   word[index]=="an" || word[index]=="and")) // ignored words
	index++;
      pos=command.find(" ",0);
    }
  word[index]=command;
  if(word[0].length()==0) 
    {
      word[0]="nothing"; 
      return;
    }
  cVerb=word[0];
  cNoun2=word[3];
  string prepTable[49] = {"about","above","across","along","apart",
			  "around","at","away","back","below",
			  "beneath","beside","down","e","east",
			  "for","forward","from","of","off",
			  "in","inside","into","n","ne",
			  "near","north","northeast","northwest","nw",
			  "on","onto","out","outside","over",
			  "s","se","south","southeast","southwest",
			  "sw","through","to","under","up",
			  "upon","w","west","with"};
  for(int j=0;j<49;j++)
    if(word[1]==prepTable[j])
      {
	cPrep=word[1];
	cNoun1=word[2];
	return;
      }
  for(int k=0;k<49;k++)
    if(word[2]==prepTable[k])
      {
	cPrep=word[2];
	cNoun1=word[1];
	return;
      }
  cNoun1=word[1];
  cNoun2=word[2];
  return;
}

void preVerb(int index)
{

  if(cNoun1!="" && !(*currentRoom).hasJunk(cNoun1)
     && !inventory.hasJunk(cNoun1))
    cout << "You don't see any " << cNoun1 << " here." << endl;
  else if(cNoun2!="" && !(*currentRoom).hasJunk(cNoun2)
	  && !inventory.hasJunk(cNoun2))
    cout << "You don't see any " << cNoun2 << " here." << endl;
  else
    { 
      int type = verbTypes[index];
      switch(type)
	{
	case 0: break;
	case 1: 
	  if(cNoun1!="") 
	    {cout << "You're not making sense." << endl; return;}
	  break;
	case 2: 
	  if(cNoun1=="")
	    {cout << cVerb << " what?" << endl; return;}
	  if(cNoun2!="")
	    {
	      cout << "I'm just a simple man who " << cVerb 
		   << "s things one at a time." << endl;
	      return;
	    }
	  break;
	case 3:
	  if(cNoun1=="")
	    {cout << cVerb << " what?" << endl; return;}
	  if(cNoun2=="")
	    {cout << cVerb << " " << cNoun1 << " with what?" << endl; return;}
	  break;
	case 4:
	  if(cNoun2!="")
	    {cout << cVerb << " can't take two objects" << endl; return;}
	  break;
	case 5:
	  if(cNoun1=="")
	    {cout << cVerb << " what?" << endl; return;}
	  break;
	case 6:
	  if(cNoun1!="" && cNoun2=="")
	    {cout << "Error message for a strage verb." << endl; return;}
	  break;
	default:
	  cout << "Error in preVerb function" << endl; return;
	}
      if(cNoun1!="")
	{
	  for(int i=0;i<totalItems;i++)
	    if(cNoun1==itemNames[i])
	      {
		x1=itemPointers[i];
		break;
	      }
	}
      if(cNoun2!="")
	{
	  for(int j=0;j<totalItems;j++)
	    if(cNoun2==itemNames[j])
	      {
		x2=itemPointers[j];
		break;
	      }
	}
      (*verbFunctions[index])();
    }
}

void event(int eventState, int verbIndex)
{
  /* inside this function is where all of the automatic or time-based
     events will occur which will broadly effect any command.  These can
     either suppress the command entirely, color how it happens, or make
     something additional happen. Include a return statement if the
     switch value is meant to suppress the verb. */
  switch(eventState)
    {
    case 1:
      break;
    default:
      cout << "Error in event function" << endl;
    }
  preVerb(verbIndex);
}

void addV(string verbName, void (*ptr)(), int type)
{
  if(totalVerbs>=VERB_TABLE_SIZE)
    {
      cout << "ERROR: VERB TABLE LENGTH EXCEEDED";
      exit(1);
    }
  verbNames[totalVerbs]=verbName;
  verbFunctions[totalVerbs]=ptr;
  verbTypes[totalVerbs]=type;
  totalVerbs++;
}

void addI(string itemName, item* itemPtr)
{
  if(totalItems>=ITEM_TABLE_SIZE)
    {
      cout << "ERROR: ITEM TABLE LENGTH EXCEEDED";
      exit(1);
    }
  itemNames[totalItems]=itemName;
  itemPointers[totalItems]=itemPtr;
  totalItems++;
}

void vUnknown()
{
  cout << "I don't know that word." << endl;
}

void vQuit()
{
  string ans;
  cout << "Are you sure you want to quit? (Y or N) ";
  cin >> ans;
  if(ans=="Y"||ans=="y") exit(1);
  cout << endl;
}

void vHelp() 
{
  cout << "Common commands are: " << endl
       << "\'Q\' to quit" << endl
       << "\'L\' to look around or at something" << endl
       << "\'I\' to check your inventory" << endl
       << "\'NE\' to go northeast, etc." << endl
       << "\'Take\' to pick up items, \'Drop\' to drop them" << endl
       << "\'Wear\' to wear an item" << endl
       << "\'Remove\' to take it off or take something out of a container" 
       << endl
       << "Some phrasal verbs are recognized, such as \'Turn on light\', etc."
       << endl
       << "If a command doesn't work, try rephrasing it more simply." << endl;
  cout << "Commands are limited to four words, the first being a verb."
       << endl
       << "Using the arrow keys before typing will cause the game to " 
       << "misread your command" << endl << "Nothing is case-sensitive." 
       << endl << "Good luck!" << endl;
}

void vNothing() {cout << "You wait." << endl;}

void vInventory() {inventory.listJunk();}

void vLook()
{
  if(cNoun1!="")
    {
	cout << (*x1).getLook() << endl;
	return;
    }
  cout << (*currentRoom).getName() << endl 
       << (*currentRoom).getLook() << endl;
  (*currentRoom).listJunk();
}

void vTake()
{

  if(inventory.hasJunk(cNoun1))
    {
      cout << "You're already carrying that." << endl;
      return;
    }
  //change
  if((*x1).isChained())
    {
      cout << "You can't move that." << endl;
      return;
    }
  if((*x1).getEventState()==1)
    {
      cout << "It's fine where it is." << endl;
      return;
    }
  else
    {
      inventory.addJunk((*currentRoom).takeJunk(cNoun1));
      cout << "Taken." << endl;
    }
  return;
}

void vDrop()
{
  if(!inventory.hasJunk(cNoun1)) // need invis state here
    {
      cout << "You're not carrying a " << cNoun1 << endl;
      return;
    }
  else 
    {
      (*currentRoom).addJunk(inventory.takeJunk(cNoun1));
      cout << "Dropped." << endl;
    }
  return;
}

void vGo()
{
  if(cNoun1!="") {cout << "I'd rather not." << endl; return;}
  if(cPrep=="north"||cPrep=="n") {vNorth(); return;}
  if(cPrep=="northeast"||cPrep=="ne") {vNortheast(); return;}
  if(cPrep=="east"||cPrep=="e") {vEast(); return;}
  if(cPrep=="southeast"||cPrep=="se") {vSoutheast(); return;}
  if(cPrep=="south"||cPrep=="s") {vSouth(); return;}
  if(cPrep=="southwest"||cPrep=="sw") {vSouthwest(); return;}
  if(cPrep=="west"||cPrep=="w") {vWest(); return;}
  if(cPrep=="northwest"||cPrep=="nw") {vNorthwest(); return;}
  if(cPrep=="up"||cPrep=="u") {vUp(); return;}
  if(cPrep=="down"||cPrep=="n") {vDown(); return;}
  cout << "Go where?" << endl;
}

void vNorth()
{
  if ((*currentRoom).getDoor(0)==1)
    {
      currentRoom = (*currentRoom).followDoor(0);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vNortheast()
{
  if ((*currentRoom).getDoor(1)==1)
    {
      currentRoom = (*currentRoom).followDoor(1);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vEast()
{
  if ((*currentRoom).getDoor(2)==1)
    {
      currentRoom = (*currentRoom).followDoor(2);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vSoutheast()
{
  if ((*currentRoom).getDoor(3)==1)
    {
      currentRoom = (*currentRoom).followDoor(3);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vSouth()
{
  if ((*currentRoom).getDoor(4)==1)
    {
      currentRoom = (*currentRoom).followDoor(4);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vSouthwest()
{
  if ((*currentRoom).getDoor(5)==1)
    {
      currentRoom = (*currentRoom).followDoor(5);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vWest()
{
  if ((*currentRoom).getDoor(6)==1)
    {
      currentRoom = (*currentRoom).followDoor(6);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vNorthwest()
{
  if ((*currentRoom).getDoor(7)==1)
    {
      currentRoom = (*currentRoom).followDoor(7);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vUp()
{
  if ((*currentRoom).getDoor(8)==1)
    {
      currentRoom = (*currentRoom).followDoor(8);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vDown()
{
  if ((*currentRoom).getDoor(9)==1)
    {
      currentRoom = (*currentRoom).followDoor(9);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      return;
    }
  cout << "You can't go that way." << endl;
  return;
}

void vUse()
{
  cout << "Now's not the time to use that." << endl;
}

void vWear()
{
  cout << "You've been a lifelong nudist and see no reason for changing now." 
       << endl;
}

void vEat() {}

void vDrink() {}

void vCombine()
{
  cout << "Those things won't go together." << endl;
}
void vTurn() {}

void vPut() {}

void vKill() 
{
  cout << "Calm down." << endl;
}
void vBreak() {}

void vKiss() {}

void vBurn() {}

void vClimb() {}

void vCut() {}

void vDig() {}

void vRemove() {}

void vArrange()
{
  int status = (*x1).getVerbState("arrange");
  switch(status)
    {     
    case 0:
      if((*x1).isChained()) 
	cout << "You don't want to try arranging that." << endl;
      else if((*currentRoom).hasJunk(cNoun1))
	cout << "You need to pick that up first." << endl;
      else cout << "You'd rather not. You have a strong aversion to arranging things that should not be arranged. Maybe it goes back to your arranged marriage to a woman you barely knew in a town outside Bangalore.  Sure, those five years had their high points, but it's not an experience you'd like to force.  You're going to stick to arranging things only when the time is absolutely right."
		<< endl;
      break;
    case 1:
      if((*currentRoom).hasJunk(cNoun1)) 
	cout << "You need to pick that up first." << endl;
      else 
	{
	  cout << (*x1).getState(status) << endl;
	  (*x1).setEventState(1);
	  (*x1).updateVerb("arrange",2);
	  (*currentRoom).addJunk(inventory.takeJunk("flowers"));
	}
      break;
    case 2:
    case 3:
    case 4:
      cout << (*x1).getState(status) << endl;
      break;
    default:
      cout << "Bad verb state for cNoun1." << endl;
      break;
    }
  return;
}


void vCalculate() {}
void vItemize() {}
void vSaunter() {}

