#include<string>
#include<iostream>
#include<ctime>
#include"room.h"
using namespace std;

// A brief word on naming conventions:
// to avoid confusion:
// command string names are preceded by a 'c'.
// verb function names are preceded by a 'v'.
// item names are preceded by an 'i'.
// optionally you could precede rooms with an 'r'


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
void addI(item* itemPtr);
//string wW(string a);


  //  ----------------------
  //  VERB COMMAND FUNCTIONS
  //  ----------------------

void vUnknown();     void vQuit();        void vHelp();
void vNothing();
void vInventory();   void vLook();
void vTake();        void vDrop();        void vGo();
void vNorth();       void vNortheast();   void vEast();
void vSoutheast();   void vSouth();       void vSouthwest();
void vWest();        void vNorthwest();   void vUp();
void vDown();         

void vUse();         void vWear();
void vEat();         void vDrink();
void vCombine();     void vTurn();        void vPut();
void vPick();
void vKill();        void vBreak();       void vKiss();
void vBurn();        void vClimb();       void vCut();
void vDig();         void vRemove();

void vLie();         void vSit();         void vGive();
void vSleep();       void vWash();        void vBite();
void vFart();        void vFight();       void vHang();
void vCook();        void vOpen();        void vClose();
void vRub();         void vRide();        void vRing();
void vShoot();       void vStop();        void vDance();
void vDive();        void vDie();         void vDrive();
void vWake();

void vAsk();         void vPlay();
void vBuy();         void vHaggle();      void vGreet();
void vPay();         void vJump();        void vFly();

void vFlipper();     void vTilt(); //for pinball.

void vArrange();
void vCalculate();
void vItemize();

  //  -------------
  //  MAIN FUNCTION
  //  -------------

int main()
{

  srand((unsigned)time(0));
 
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
  addV("take", &vTake, 5);            addV("grab", &vTake, 2);
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
  addV("pick", &vPick, 2);
  addV("kill", &vKill, 4);
  addV("break", &vBreak, 5);
  addV("kiss", &vKiss, 2);
  addV("burn", &vBurn, 5);
  addV("climb", &vClimb, 4);
  addV("cut", &vCut, 5);
  addV("dig", &vDig, 0);
  addV("remove", &vRemove, 5);        addV("doff", &vRemove, 2);

  addV("lie", &vLie, 4);
  addV("sit", &vSit, 4);
  addV("give", &vGive, 3);
  addV("sleep", &vSleep, 4);
  addV("wash", &vWash, 2);
  addV("bite", &vBite, 2);
  addV("fart", &vFart, 4);
  addV("fight", &vFight, 5);
  addV("hang", &vHang, 2);
  addV("cook", &vCook, 3);
  addV("open", &vOpen, 5);
  addV("close", &vClose, 2);
  addV("rub", &vRub, 2);
  addV("ride", &vRide, 2);
  addV("ring", &vRing, 2);
  addV("shoot", &vShoot, 5);
  addV("stop", &vStop, 4);
  addV("dance", &vDance, 1);
  addV("dive", &vDive, 4);
  addV("die", &vDie, 1);
  addV("drive",&vDrive, 2);
  addV("wake", &vWake, 2);

  addV("ask", &vAsk, 5);
  addV("play", &vPlay, 2);            addV("practice", &vPlay, 2);
  addV("buy", &vBuy, 5);              addV("purchase", &vBuy, 5);
  addV("haggle", &vHaggle, 5);
  addV("greet", &vGreet, 2);
  addV("pay", &vPay, 5);
  addV("jump", &vJump, 1);            addV("leap", &vJump, 1);
  addV("fly", &vFly, 1);

  addV("left", &vFlipper, 1);         addV("right", &vFlipper, 1);
  addV("tilt", &vTilt, 1);

  addV("arrange", &vArrange, 2);
  addV("calculate", &vCalculate, 2);  addV("solve", &vCalculate, 2);
  addV("itemize", &vItemize, 2);

  item iUnknown_Item("unknown_item");
  item iSelf("Yours Truly","self","myself","me"); iSelf.chain();
  item iAll("all","all","everything"); iAll.chain();
  inventory.addJunk(iSelf);
  inventory.addJunk(iAll);
  addI(&iUnknown_Item); // must be in first position
  addI(&iSelf);
  iSelf.setPronoun("you");
  addI(&iAll);

  //  -----------------------------------
  //  CONSTRUCTION OF SPECIFIC GAME WORLD
  //  -----------------------------------

  iSelf.setLook("You look great.");
  room workroom("CHRONO-ENGINEERING ROOM");
  currentRoom=&workroom;
  workroom.flagExplored();
  workroom.setLook("Hard to believe you've spent three years of your life maintaining this hellhole.  This is the room where your company's expensive Chrono-digger shits out ancient debris in a pile on the floor.  The familiar oddities are all lying about: a panel of instruments on one wall, an engine whirring sporatically on another, occasionally churning out mud, and a small cage of plexiglass in your reading alcove, or \"happy place\". Lastly there is a dusty chalkboard with a long differential equation scrawled on it. There is a door to the north leading to the break room, and a door to the south leading into the main time-travel bay.");
  workroom.setState(1,"You are a lowly engineer for Renholm Time-travel Industries.  They don't pay you enough for this shit.  You've got tons of work to get done before the boss comes in later today, so you'd best get cracking.");
  room breakroom("BREAK ROOM");
  breakroom.setLook("This is a tiny cube with some lockers on one wall, a table and chair, and a TV with bad reception, tuned to 'The WB'.  To the south is the Chrono-Engineering room, and a door to the north leads to the parking lot.");
  room timetravelbay("TIME TRAVEL BAY");
  timetravelbay.setLook("This is something like a hangar, with large, vaulted ceilings. Through large holes in the floor you can see incredibly rapidly spinning gyroscopes suspended above gaping darkness. To the east your way is blocked by electrical fields.  To the west there is a large pile of cargo containers. There is a door to the north and a small closet to the northeast.");
  room closet("JANITOR'S CLOSET");
  closet.setLook("Various janitor equipment is lying on the shelves here. The floor creaks as you walk about. To the south is the time travel bay.");
  closet.addVerb("look",1);
  closet.setState(1,"Various janitor equipment is lying on the shelves here. The floor creaks as you walk about. To the south is the time travel bay. An open hatch leads downward into darkness.");
  room parkinglot("PARKING LOT");
  parkinglot.setLook("The dessicated, inhuman coldness of a square mile of asphalt, coupled with the absolute lack of any weeds or life forms not explicitly authorized, reminds you that you are truly working in a wasteland within a wasteland.  In the distance you can see a Starbucks.  Your hatchback is still parked in its normal spot. The building entrance is back to the south.");
  room darkness("DARK MAINTENENCE SHAFT");
  darkness.setLook("A very dark, very narrow shaft. You can't see anything more than a few feet above or below.");
  parkinglot.connect(breakroom,4);
  breakroom.connect(parkinglot,0);
  breakroom.connect(workroom,4);
  workroom.connect(breakroom,0);
  workroom.connect(timetravelbay,4);
  timetravelbay.connect(workroom,0);
  timetravelbay.connect(closet,1);
  closet.connect(timetravelbay,4);
  closet.connect(darkness,9); closet.setDoor(9,0);
  darkness.connect(closet,8);
  item iWorkGloves("pair of gloves","gloves"); iWorkGloves.addVerb("wear",1);
  item iSchedule("schedule","schedule");
  item iPanel("panel","panel","instruments"); iPanel.chain();
  item iEngine("humming engine", "engine"); iEngine.chain();
  item iCage("cage","cage"); iCage.chain();
  item iChalkboard("chalkboard","chalkboard","equation"); 
  iChalkboard.chain();
  item iFlowers("vase of flowers","flowers","vase","flowerpot");
  item iForm("simple form","form");
  iForm.addVerb("itemize",1);
  iForm.setState(1,"An expense form from the last month. It has all the expenditures itemized.");
  item iMagazine("magazine","magazine","mag");
  item iTV("tv","tv","television"); iTV.chain();
  item iHatchback("car","car","hatchback"); iHatchback.chain();
  item iPorn("porno mag","porn","porno","pornography");
  item iHatch("hatch","hatch"); iHatch.chain(); iHatch.makeInvisible();
  item iCargo("cargo container","cargo"); iCargo.chain();
  item iGyroscope("gyroscope","gyroscope","gyro"); iGyroscope.chain();
  item iBoss("your boss","boss","steve"); iBoss.chain(); iBoss.makeInvisible();
  item iPrintout("printout","printout","print"); iPrintout.makeInvisible();
  item iTotebag("canvas totebag","tote","totebag");
  iWorkGloves.setLook("A well-worn pair of work gloves.");
  iSchedule.setLook("A list of tasks to do today: \n 1) Get the gyroscopic Holtzmann generators . \n 2) Itemize your monthly expenditures.  A form has been provided. \n 3) Spruce up the room a little.  This place is depressing.");
  iPanel.setLook("The panel holds an array of instruments for monitoring and adjusting the gyroscopes beyond the bay door to the south.");
  iPanel.addVerb("look",1);
  iPanel.setState(1,"Looking at the panel reveals the gyroscopic pairings are no longer synchronized. There is a printout detailing their motion lying on top. Sometimes you wonder if the instruments wouldn't respond better to a more 'blunt force' approach.");
  iPrintout.setLook("From the looks of the readings, these gyroscopes are out of sync due to some perturbing force being generated by the time fields. For a moment some glimmer of realization hits you as you visualize 5-D manifolds, and then... it is gone.");
  iPanel.putNextTo(iPrintout); iPrintout.putNextTo(iPanel);
  iEngine.setLook("This is a simple mechanical engine that catches whatever comes out of the Holtzmann time field six stories below, and puts it through chemical analysis.  By the look of the mud that's currently spewing out, your superiors are killing rabbits today.");
  iCage.setLook("The cage is recessed into the wall.  Inside there is a mechanical arm and twelve rabbits.");
  iChalkboard.setLook("On the upper half of the chalkboard is scrawled a complex differential equation. You recognize this as the Holtzmann problem of inverse time fields. The mathematicians upstairs have given a whack at a few approximations, but so far every rabbit that goes back in time returns a second later with a somewhat more mud-like consistency. You'd wager the real solution set to the equation is years off.");
  iFlowers.setLook("A tasteful vase containing three long-stemmed rare orchids and some marsh grasses.");
  iForm.setLook("An expense form for the last month.  It's blank.");
  iMagazine.setLook("National Geographic.");
  iTV.setLook("The opiate of the masses.");
  iHatchback.setLook("Your trusty 1982 Plymouth Horizon.");
  iPorn.setLook("Penthouse: May 2003.");
  iHatch.setLook("A riveted metal hatch, solidly shut.");
  iCargo.setLook("Several large cargo containers ");
  iTotebag.setLook("It's your NPR totebag for donating at the $35 level. It has a picture of Terry Gross.");
  iGyroscope.setLook("These giant gyroscopes are slightly recessed into the floor. A long way down you can see their twin gyroscopes in the black pits below. Even at the high speed the gyroscopes are revolving at, you can still detect a slight abbheration in their motion.");
  iBoss.setLook("Steve looks more manicured and polished than your average middle-manager. He's clean shaven, tall, a tad bit overweight, not quite smart enough to do your job, but plenty smart enough to steal the credit for it.");
  iFlowers.addVerb("arrange",1);
  iFlowers.setState(1,"You set the flowers on a stand next to your reading nook and arrange them according to the Japanese art of ikebana.  After five minutes you have given them a stillness and serenity that makes the room look even more soulless and depressing in contrast.");
  iFlowers.setState(2,"Why the fuck would you want to rearrange them?  They are already perfectly arranged.");
  iFlowers.setState(3,"I bet you're the kind of person who goes to city council meetings to get them to put up new road bumps and stoplights near your house. And because of people like you I've got an extra 5 minutes tacked on to my drive to work every day waiting at a stoplight with no traffic. Yeah, I need an extra hour to my work week like Iraq needs a few more roadside bombs. All because some tool can't leave well enough alone. If it ain't broke, don't fix it.");
  iFlowers.setState(4,"Seriously, no.");
  iPorn.addVerb("take",1);
  iPorn.setState(1,"Picking up the porn magazine up off the ground reveals a previosly-unnoticed hatch beneath it in the riveted floor.  It has a handle to one side.");
  iPorn.putOver(iHatch);
  iHatch.putUnder(iPorn);
  iHatch.addVerb("open",1);
  iHatch.setState(1,"Opening the hatch reveals a narrow shaft in the floor.  The metal rungs on the wall of the shaft quickly disappear in the darkness.");
  iHatch.setState(2,"A riveted metal hatch, leading down to a vertical shaft with footholds to one side.");
  iTotebag.makeContainer();
  iMagazine.putInside(iTotebag); iMagazine.makeInvisible();
  iTotebag.putContaining(iMagazine);

  workroom.addJunk(iWorkGloves);
  inventory.addJunk(iSchedule);
  workroom.addJunk(iPanel);
  workroom.addJunk(iEngine);
  workroom.addJunk(iCage);
  workroom.addJunk(iChalkboard);
  workroom.addJunk(iFlowers);
  workroom.addJunk(iBoss);
  workroom.addJunk(iPrintout);
  inventory.addJunk(iForm);
  breakroom.addJunk(iTotebag);
  breakroom.addJunk(iTV);
  breakroom.addJunk(iMagazine);
  parkinglot.addJunk(iHatchback);
  closet.addJunk(iPorn);
  closet.addJunk(iHatch);
  timetravelbay.addJunk(iCargo);
  timetravelbay.addJunk(iGyroscope);

  room inventory2("INVENTORY");
  room inventoryStorage("INVENTORY");
  room upperStreet("COBBLESTONE STREET VISTA");
  upperStreet.setLook("You see a compass carved into the road.  From that compass you orient yourself; the road here slopes north and downward to the bay, south up the hill out of sight.  Glimpses between buildings show you a town that expands in all directions, covered in hills which are covered in buildings, covered in terra cotta roofs covered in vines.  On the western side of the street is a darkened store inside which you can hear faint bluegrass music.  The other side of the street is also shaded, a pub of some kind.");
  upperStreet.setState(1,"You are standing in the middle of a cobblestone street with light traffic; the road stretches downward to a wide, shimmering bay in one direction, and curves upward out of sight.  The building facades around you look old-fashioned, as from a kingdom by the sea in an old poem.  Wooden signs advertise... well you can't quite make out what they are saying.  Their symbols look odd, and yet by looking at the jagged, quick strokes you get instant impressions in your mind as to what they represent.");
  upperStreet.setState(2,"You realize you are dreaming.");
  upperStreet.setState(3,"If you are not careful you might wake up.  Somehow this world seems a better option for the moment.  As if to punctuate that thought, a shimmer flashes up the street as the buildings and objects momentarily lose their shape and focus.  You tell yourself to be cool.");
  room hillside("STEEP COBBLESTONE STREET");
  hillside.setLook("The street is its steepest at this point. A cool mist flows from the hilltop to the southwest, following the road and burning off quickly as it straightens in the sun to the north. The street is quieter here, flanked by quiet apartments with doors to the east and west. To the southeast you see a boarded-up hole in a building wall, half-buried in the ground");
  room tunnel("NARROW TUNNEL");
  tunnel.setLook("The tunnel's walls are damp.  It is exceedingly dark and narrow.  You can make out a few blinking lights far below you.");
  room fountain("FOUNTAIN");
  fountain.setLook("Mist flows thickly around you from the southwest to the northeast, following the course of the road.  The cobblestone street opens up wider here to make room for an elaborate two-tiered fountain.  Water is pouring from the mouths of four wood nymphs carved in stone, cascading down their naked bodies to the higher tier.  Below, it emerges from holes in rock carved to look like cliffs, into the lower pool.  You're high enough to get a good view of the city from here; despite the mist you can see the main features of the city. A wide bay far below to the north, tall cliffs to the northwest with a village of some kind atop them.  There are other hills to the northeast overlooking the bay, with two identical towers rising up from one such urban hillside. Behind you you can see little beyond the ever-thickening fog.");
  room banjoStore("BILL'S BANJO BAZAAR");
  banjoStore.setLook("You're in a banjo store, which is an odd thing for a 17th-century mediterranean city to have, but hey, it's a dream. The pine walls are covered mostly in banjos, but there are a few fiddles here too. Lively bluegrass music is playing from an unknown source.");
  room tavern("DIM TAVERN");
  tavern.setLook("The patrons here are all playing pinball. They don't much look in the mood to talk.  There's a deaf, dumb and blind kid in one corner surrounded by beautiful women. The bartender sizes you up while drying pint glasses.");
  room pinball1("PINBALL: PLUNGER CORRIDOR");
  pinball1.setLook("You are a round, shiny metal ball. To one side of you is a tightly coiled plunger, the other side is a long corridor. You get the feeling that you might want to limit yourself to \"FIRE\" (plunger), \"TILT\", \"LEFT\" (flipper), \"RIGHT\" (flipper), and \"WAIT\" commands for the duration.");
  pinball1.setEventState(4);
  room pinball2("PINBALL");
  pinball2.setLook("You are careening wildly through a pinball version of your high school. All around you, you see flat metal miniatures of teachers and students you once knew, and you smash into all of them wildy with a total lack of any control. Lockers ring bells as you hit them, then you rocket outside to the sports fields on a curving metal chute. Your old romantic fling pulls you into an empty stairwell as you rack up the points, then get ejected out to start the circuit once again.");
  pinball2.setEventState(4);
  room pinball3("PINBALL: UPPER FLIPPERS");
  pinball3.setLook("You're starting to head for the upper flippers, which are shaped like college counselors.");
  pinball3.setEventState(4);
  room pinball4("PINBALL: LOWER FLIPPERS");
  pinball4.setLook("You're starting to fall toward the boiler room, which looks like game over.  The only thing between you and it are two flippers shaped like integrals.");
  pinball4.setEventState(4);
  room gameOver("GAME OVER");
  gameOver.setLook("You age fifteen years and return to school as building maintenance staff.");
  room middleStreet("COBBLESTONE STREET");
  middleStreet.setLook("Here in the heart of the city the street harbors more traffic, including several oxcarts. The real smells of the city are detectable here: steaming aromas of spiced dishes, laundry hanging from roofs, dust and refuse, salt and fish from the sea. There is a covered market to the west. To the east is a two-story building with beautiful, scantily-clad women visible in the windows and on the balcony.");
  room country("COUNTRY STORE");
  country.setLook("The market is uninteresting except for a little country store in the back. A deranged-looking gypsy with a grim face is selling countries. The canopy opens to the street to the east, and a shaded courtyard to the northwest.");
  room brothel("BROTHEL");
  brothel.setLook("Much of the ground floor of this brothel is draped in sheer fabrics, and awash in the smell of hookah smoke. There are plush couches and expensive paintings on the walls. The madame eyes you expectantly.");
  room brothel2("UPSTAIRS BROTHEL");
  brothel2.setLook("The upstairs is partitioned into smaller, semi-private alcoves. There is a short balcony here. Most of the women are partially nude, looking sated and bemused.");
  room dream2("DREAM WITHIN A DREAM");
  dream2.setLook("You dog. You see lake. You like lake. You see stick. You like stick. You see master. You like master.");
  room crossroads("CROSSROADS");
  crossroads.setLook("This is easily the most congested part of the city you've seen. Oxcarts, pedestrians, horses and riders, are all coming and going quickly. You get the feeling you are in the way of traffic. The roads go off in all four cardinal directions. You see an open manhole in the middle of the broad intersection.");
  room sewer("SEWER");
  sewer.setLook("A sludge-filled sewer. Tunnels lead off north, south, east and west, and a . You see four turtles here, and a rat.");
  room courtyard("COURTYARD");
  courtyard.setLook("The sky is thick with clouds overhead, and a hard pulse of rain has forced all the book vendors to the stone archways at the fringes of the courtyard. The tall oaks of the courtyard are slick with rain, and the bats that gird their limbs shift their positions wearily. A street leads east and west, and narrower passages lead to the southeast and the northwest.");
  room gateway("LARGE IRON GATE");
  gateway.setLook("The street here runs east-west. There is a large iron gate, similar to a portcullis, here. It is raised, but all traffic is being screened by a solitary guard. The traffic going through all appears wealthy, and the buildings on the other side of the gate are nobly, lavishly constructed. Even the street beyond looks cleaner and in better repair.  As you look more closely at the guard, you realize the guard is you.");
  room winding("WINDING STREET");
  winding.setLook("You are atop a hill. The street winds in an s-shape here, otherwise continuing to the east and west.  Along the central curve of the S, two identical towers rise high on either side of the street (southwest and northeast).");
  room embank1("CENTRAL EMBANKMENT");
  embank1.setLook("The central north-south street ends here at a wide embankment to the bay, which is another twenty feet or so below the street. The embankment continues to the east and west, and a narrow stairway leads down to the water itself. You can see high cliffs to the west.");
  room embank2("WEST EMBANKMENT");
  embank2.setLook("The sun is glinting off the rocks here, where tiny bright-colored fish dart in and out of the crevices. A young couple sits close together on the ledge. The street runs east-west, and on the south side there is an old theatre with a large marquee lit up by flashing lights. To the west you can smell the smells of a fish market");
  room embank3("EAST EMBANKMENT");
  embank3.setLook("This part of the embankment is shaded by the tall hill directly to your south. It appears the whole area to the south is fenced off by a high fence. To the east the shadow gets even darker. To the west is the central part of the embankment. To the north you see nothing but the sparkling bay, and a killer whale.");
  room bay("SHARK-INFESTED BAY");
  bay.setLook("Well done, you're in a deep bay with a strong undertow, and a large orca coming your way.");
  room theatre("OLD THEATRE");
  theatre.setLook("This theatre has an old vaudevillian stage and a giant film screen. There are some art nouveau murals on the walls. Most of the seats are occupied by mandrills.");
  room cliffside("FOOT OF TALL CLIFFS");
  cliffside.setLook("Directly above you loom tall cliffs looking directly over the bay. There appears to be no way of scaling them from here. To the east is an embankment that follows the curved line of the bay. Directly to the south you can see, smell and hear the city's bustling fish market.");
  room fishMarket("FISH MARKET");
  fishMarket.setLook("Carts are being loaded with large fish, almost too big to be held. And yet they are being tossed in the air by very muscular men, who shout boisterously as they pitch them. There is one main vendor stand where a bearded dwarf is standing on a milk crate, shouting prices and bartering with a small crowd.");
  room t1f1("WESTERN TOWER, ENTRY");
  t1f1.setLook("The entryway to the northeast leads back out to the street. The floor and walls are all bare. There is a stone stairway spiralling up to the second floor.");
  room t1f2("WESTERN TOWER, SECOND FLOOR");
  t1f2.setLook("The second floor is much the same as the first. There is a window to the northeast looking out to the street below and to the other tower. Stairways lead up and down.");
  room t1f3("WESTERN TOWER, THIRD FLOOR");
  t1f3.setLook("Most of the external walls of the tower here have crumbled away. Somehow, magically, the level above you is suspended by nothing more than a few planks of rotting wood. You certainly can't climb up here, as the stairway is completely gone, save for a hole above you. The only obvious exit is down.");
  room t1f4("WESTERN TOWER, FOURTH FLOOR");
  t1f4.setLook("The floor here is crumbling with holes, through which you can feel the wind whipping and see the level below. There is a window to the northeast and a crumbling staircase leading upward.");
  room t1f5("WESTERN TOWER, FIFTH FLOOR");
  t1f5.setLook("This floor of the tower has been furnished with a persian rug, an armchair and two bookcases. A shaft of light from a window to the southwest divides the room. Outside you can see the central dividing street of the city. Atop its hill you see a large stone fountain.");
  room t1f6("WESTERN TOWER, SIXTH FLOOR");
  t1f6.setLook("The tower at this height is swaying noticeably. There is a bed in one corner. A staircase leads down, and upwards there is an oaken door.");
  room t1f7("ROOF OF WESTERN TOWER");
  t1f7.setLook("This view makes you wish you were a bird. You have a superb view of the entire city around you, tempered only by the fact that the swaying of the tower is making you a bit queasy. You can see the mouth of the horseshoe-shaped bay, where fully rigged sailing ships are coming in for the evening. The sun is descending in the sky, making a small village above the cliffs to the west appear as though it were on fire. All the houses and shops below are lit in rich ochre hues, accented by their particular elevations among the city's hills. And at the top of the ridge you see a billowing wall of fog making slow headway against the sun. One for the photo album.");
  room t2f1("EASTERN TOWER, ENTRY");
  t2f1.setLook("Ugh, you don't want to stay in here more than a few minutes. The feng shui is just all wrong. There is a door leading up and a street exit to the southwest.");
  room t2f2("EASTERN TOWER, SECOND FLOOR");
  t2f2.setLook("placeholder, sorry");
  room t2f3("EASTERN TOWER, THIRD FLOOR");
  t2f3.setLook("another placeholder");
  room t2f4("EASTERN TOWER, FOURTH FLOOR");
  t2f4.setLook("third placeholder of 5");
  room t2f5("EASTERN TOWER, FIFTH FLOOR");
  t2f5.setLook("fourth");
  room t2f6("EASTERN TOWER, SIXTH FLOOR");
  t2f6.setLook("fifth");
  room t2f7("ROOF OF EASTERN TOWER");
  t2f7.setLook("The view is alright. Somehow it's just way better on the other tower.");
  workroom.connect(upperStreet,9);
  upperStreet.connect(hillside,4);
  hillside.connect(upperStreet,0);
  hillside.connect(tunnel,3);
  tunnel.connect(hillside,7);
  tunnel.connect(workroom,3);
  hillside.connect(fountain,5);
  fountain.connect(hillside,1);
  fountain.connect(workroom,5);
  upperStreet.connect(banjoStore,6);
  banjoStore.connect(upperStreet,2);
  upperStreet.connect(tavern,2);
  tavern.connect(upperStreet,6);
  tavern.connect(pinball1,9);
  pinball1.connect(pinball2,9);
  pinball2.connect(pinball3,8);
  pinball2.connect(pinball4,9);
  pinball3.connect(pinball2,9);
  pinball3.connect(pinball4,8);
  pinball4.connect(pinball2,8);
  pinball4.connect(pinball3,9);
  pinball4.connect(gameOver,0);
  gameOver.connect(workroom,9);
  pinball2.connect(tavern,0);
  upperStreet.connect(middleStreet,0);
  middleStreet.connect(upperStreet,4);
  middleStreet.connect(country,6);
  country.connect(middleStreet,2);
  middleStreet.connect(brothel,2);
  brothel.connect(middleStreet,6);
  brothel.connect(brothel2,8);
  brothel2.connect(brothel,9);
  brothel2.connect(dream2,8);
  dream2.connect(brothel2,9);
  middleStreet.connect(crossroads,0);
  crossroads.connect(middleStreet,4);
  crossroads.connect(sewer,9);
  sewer.connect(crossroads,8);
  crossroads.connect(courtyard,6);
  courtyard.connect(crossroads,2);
  courtyard.connect(country,3);
  country.connect(courtyard,7);
  gateway.connect(crossroads,6);
  crossroads.connect(gateway,2);
  winding.connect(gateway,6);
  winding.connect(workroom,2);
  embank1.connect(crossroads,4);
  crossroads.connect(embank1,0);
  embank2.connect(embank1,2);
  embank1.connect(embank2,6);
  embank3.connect(embank1,6);
  embank1.connect(embank3,2);
  bay.connect(embank1,4);
  embank1.connect(bay,0);
  embank2.connect(bay,0);
  embank3.connect(bay,0);
  bay.connect(workroom,9);
  embank3.connect(workroom,2);
  theatre.connect(embank2,0);
  embank2.connect(theatre,4);
  cliffside.connect(embank2,2);
  embank2.connect(cliffside,6);
  fishMarket.connect(cliffside,0);
  cliffside.connect(fishMarket,4);
  fishMarket.connect(courtyard,3);
  courtyard.connect(fishMarket,7);
  gateway.connect(winding,2);
  winding.connect(gateway,6);
  winding.connect(t1f1,5);
  t1f1.connect(winding,1);
  winding.connect(t2f1,1);
  t2f1.connect(winding,5);
  t1f1.connect(t1f2,8);
  t1f2.connect(t1f1,9);
  t1f2.connect(t1f3,8);
  t1f3.connect(t1f2,9);
  t1f2.connect(t2f2,1);
  t2f2.connect(t1f2,5);
  t2f2.connect(t2f3,8);
  t2f3.connect(t2f2,9);
  t2f3.connect(t2f4,8);
  t2f4.connect(t2f3,9);
  t2f4.connect(t1f4,5);
  t1f4.connect(t2f4,1);
  t1f4.connect(t1f3,9);
  t1f4.connect(t1f5,8);
  t1f5.connect(t1f4,9);
  t1f5.connect(t1f6,8);
  t1f6.connect(t1f5,9);
  t1f6.connect(t1f7,8);
  t1f7.connect(t1f6,9);
  t1f7.connect(t2f7,1);
  t2f7.connect(t1f7,5);
  t2f7.connect(t2f6,9);
  t2f6.connect(t2f7,8);
  t2f6.connect(t2f5,9);
  t2f5.connect(t2f6,8);
  t1f7.connect(workroom,8);
  
  item iCompass("stone compass", "compass"); iCompass.chain();
  iCompass.setLook("You've already oriented yourself. Now quit looking at it or you'll get confused!");
  item iMusic("music","music","bluegrass"); iMusic.chain();
  iMusic.setLook("The music looks vaguely like miniscule vibrations in the air.");
  item iHole("hole","hole"); iHole.chain();
  iHole.setLook("The hole is actually a narrow tunnel.");
  item iLights("lights","lights"); iLights.chain();
  iLights.setLook("The lights appear to be coming from your work console.");
  item iFountain("fountain","fountain"); iFountain.chain();
  iFountain.setLook("The nymphs are mesmerizing and sensual. The wet stone feels surprisingly like skin.");
  item iNymphs("nymphs","nymphs","nymph"); iNymphs.chain();
  iNymphs.setLook("On closer inspection, the nymphs are slowly moving. They are talking to each other in a language you don't understand.");
  item iMist("mist","fog","mist"); iMist.chain();
  iMist.setLook("It's misty.");
  item iDoubloon("doubloon","doubloon","coin");
  iDoubloon.setLook("It's an old pirate coin, with a picture of Captain Greenbeard, the notorious seasick pirate of the south seas.");
  item iZ("Z-dollar bill","z","bill");
  iZ.setLook("What an incredible stroke of luck to find this! You're not quite sure how much this is worth, but something tells you it'll buy items of fine quality. It has a picture of Zachary Taylor on the front, and the National Zoo on the reverse.");
  item iBanjo("banjo","banjo"); iBanjo.addVerb("play",1);
  iBanjo.setLook("It's a Deering banjo, quality-made, strung for a lefty. Which you are. That's right, deal with it. Your lifespan is on average ten years shorter, you'll forever be blamed for bumping into others while eating, and power tools designed for righties will be inherent death traps. Among fifty other inconveniences you probably never thought of.");
  iBanjo.setState(1,"You play the banjo in the emptiest corner of the area. A wave of depression hits you as you hear curses being thrown your way from the apartments lining the nearest street.");
  iBanjo.setState(2,"After several more hours of play, the threats subside from the village folk and people start walking past you again without making rude gestures.");
  iBanjo.setState(3,"A few hours pass enjoyably as you exhaust the songs Ken taught you and begin to experiment on your own.");
  iBanjo.setState(4,"After a long pickin' session, you have a sizeable crowd cheering and clapping along. You chuckle, bow, and after a round of applause the crowd disperses..");
  item iCharisma("crapload of charisma","charisma","cred");
  iCharisma.makeInvisible();
  iCharisma.setLook("The charisma is vaguely Che Guevara-shaped.");
  item iKen("ken","kenneth","ken"); iKen.chain();
  iKen.setLook("It's your best friend Ken. He's short, with short brown hair and a well-trimmed beard. He's got a friendly grin. He's ever-so-slightly levitating.");
  iKen.addVerb("banjo",3);
  iKen.addVerb("greet",1);
  iKen.addVerb("fiddle",2);
  iKen.setState(1,"\"Why hellOOO there. Didn't expect you'd be lucid dreaming on the job.\" He chuckles.");
  iKen.setState(2,"\"The fiddle? Oh, no, it's just window dressing.");
  iKen.setState(3,"\"Well OF COURSE I'll teach you how to play,\" he says, grinning widely. \"It's all in the knees, see...\"  Three hours go by, and Ken ends by telling you to practice, or, failing that, maybe just buy some records.");
  iKen.setState(4,"\"Get yerself a good rockin chair and yer on yer way.\"");
  item iFiddle("fiddle","fiddle"); iFiddle.addVerb("play",1);
  iFiddle.setLook("You prefer the banjo, actually");
  item iKid("kid","kid","wizard"); iKid.chain();
  iKid.setLook("This guy must be a pinball wizard. From the looks of his sleek nose you conclude he must have an extremely refined sense of smell.");
  item iPinball("pinball machine","pinball"); iPinball.chain();
  iPinball.setLook("Various pinball machines are positioned around the room: Icelandic Gardener, Shamwow Hero, Taxonomy Expert, Blunt Trauma, and Infinite Regress Pinball about Pinball, to name a few. The one that calls out to you most plaintively, though, looks to be specifically tailored to your own high school experience, and promises to reshape your destiny, if you but have the skills.");
  item iBartender("bartender","bartender"); iBartender.chain();
  iBartender.setLook("He's got decent facial hair, as any bartender should (male or female). Specifically his beard has been shaved into a Fibonacci spiral. He's quite aware of his own beard coolness level.");
  item iHat("prize hat","prize","hat");
  iHat.setLook("This hat is so cool, so desirable, you're positively certain it must be allegorical, standing in for some abstract concept of which you're only subconsciously aware.");
  item iAroma("aroma","aroma","aromas"); iAroma.chain();
  iAroma.setLook("You can't quite place it.");
  item iGypsy("gypsy","gypsy"); iGypsy.chain();
  iGypsy.setLook("He's wearing a bandana and his chest is partially bared, showing off pectorals honed from real labor, not self-indulgent exercise.");
  item iCuba("cuba","cuba");
  iCuba.setLook("It's set in the Caribbean, and is vaguely vacuum-cleaner-shaped.");
  item iMongolia("mongolia","mongolia");
  iMongolia.setLook("You can see 1:1,000,000 scale nomads crossing the Gobi on asian camels. It seems to be covered in Yurts.");
  item iYemen("yemen","yemen");
  iYemen.setLook("The writer of this program really doesn't know enough about Yemen to say anything pithy here.");
  item iSmoke("smoke","smoke","hookah"); iSmoke.chain();
  iSmoke.setLook("The smoke from the hookah has something of an apple flavor.");
  item iPainting("painting","paintings","painting"); iPainting.chain();
  iPainting.setLook("The painting that catches your eye is of a fully rigged ship in a violent storm. Men are frantically battening down the rigging, in danger of pitching over the edge. The whole ship is listing to the right, and a thick wave is splashing over the deck.");
  item iCouches("couches","couch","couches"); iCouches.chain();
  item iMadame("madame","madame"); iMadame.chain();
  iMadame.setLook("She's an older, smart-looking woman. Her hair is wrapped in a tight bun. She's wearing a shawl.");
  item iAlcoves("alcoves","alcoves","alcove"); iAlcoves.chain();
  iAlcoves.setLook("They look inviting.");
  item iWomen("women","women"); iWomen.chain();
  iWomen.setLook("They are a strange amalgam of every woman you've ever loved or lusted after.");
  item iLake("lake","lake"); iLake.chain();
  iLake.setLook("Ruff Ruff, woof, splash.");
  item iStick("stick","stick");
  iStick.setLook("Stick! Stick! Yes, Stick!");
  item iMaster("master","master"); iMaster.chain();
  iMaster.setLook("Master smells just like he should.");
  item iHunger("hunger for fish","hunger");
  iHunger.setLook("Nothing else will do but fish.");
  item iTraffic("traffic","traffic"); iTraffic.chain();
  item iManhole("manhole","manhole"); iManhole.chain();
  item iLeonardo("leonardo","leonardo"); iLeonardo.chain();
  iLeonardo.setLook("He's wearing a blue bandana and a katana blade.");
  item iDonatello("donatello","donatello"); iDonatello.chain();
  iDonatello.setLook("He's wearing a purple bandana and tinkering with something.");
  item iRafael("rafael","rafael"); iRafael.chain();
  iRafael.setLook("He's wearing a red bandana and dismisses you sarcastically.");
  item iMichelangelo("michelangelo","michelangelo"); iMichelangelo.chain();
  iMichelangelo.setLook("He's wearing an orange bandana and eating a foul-looking pizza.");
  item iSplinter("splinter","splinter","rat"); iSplinter.chain();
  iSplinter.setLook("He looks wise.");
  item iRain("rain","rain"); iRain.chain(); // in Spain
  item iOaks("oaks","oaks","oak"); iOaks.chain();
  item iBats("bats","bats","bat"); iBats.chain();
  item iVendors("vendors","vendors","vendor"); iVendors.chain();
  item iGate("gate","gate","portcullis"); iGate.chain();
  item iSelf2("second you","doppleganger"); iSelf2.chain(); // special state
  iSelf2.setLook("He looks exactly like you, right down to his abstract dreamlike inventory items.");
  item iStairway("stairway","stairway","stairs","staircase"); iStairway.chain();
  item iOrca("killer whale","orca","whale");
  iOrca.setLook("The orca looks like... aaahhh! ahhhhh!!!! Oh GOD NO!!!!!");
  item iMandrill("lots and lots of mandrills","mandrills","mandrill"); iMandrill.chain();
  iMandrill.setLook("It's hard to describe exactly how creepy it is walking into a darkened room filled with mandrills. Most of them are looking silently at you.");
  item iScreen("screen","screen","stage","movie"); iScreen.chain();
  iScreen.setLook("The screen over the stage is currently showing a movie. Say \"Watch movie\" if you'd like to watch it.");
  item iMurals("murals","murals","mural"); iMurals.chain();
  iMurals.setLook("Greek gods eating popcorn.");
  item iFish("fish flying through the air","fish"); iFish.chain();
  item iSturgeon("sturgeon","sturgeon");
  iSturgeon.setLook("One sturgeon has been cooked on the grill.");
  item iDwarf("dwarf","dwarf","midget"); iDwarf.chain();
  iDwarf.setLook("He don't take no guff.");
  item iWindow("window","window"); iWindow.chain();
  item iRug("rug","carpet","rug"); iRug.chain();
  item iArmchair("armchair","armchair"); iArmchair.chain();
  item iBookcase("bookcase","bookcase","bookcases"); iBookcase.chain();
  iBookcase.setLook("A wide assortment of reading.");
  item iBed("bed","bed"); iBed.chain();
  
  upperStreet.addJunk(iCompass);
  upperStreet.addJunk(iMusic);
  hillside.addJunk(iHole);
  tunnel.addJunk(iLights);
  fountain.addJunk(iFountain);
  fountain.addJunk(iNymphs);
  fountain.addJunk(iMist);
  fountain.addJunk(iDoubloon);
  fountain.addJunk(iZ);
  banjoStore.addJunk(iBanjo);
  banjoStore.addJunk(iCharisma);
  banjoStore.addJunk(iKen);
  banjoStore.addJunk(iFiddle);
  tavern.addJunk(iKid);
  tavern.addJunk(iPinball);
  tavern.addJunk(iBartender);
  tavern.addJunk(iHat);
  middleStreet.addJunk(iAroma);
  country.addJunk(iGypsy);
  country.addJunk(iCuba);
  country.addJunk(iMongolia);
  country.addJunk(iYemen);
  brothel.addJunk(iSmoke);
  brothel.addJunk(iPainting);
  brothel.addJunk(iCouches);
  brothel.addJunk(iMadame);
  brothel2.addJunk(iAlcoves);
  brothel2.addJunk(iWomen);
  dream2.addJunk(iLake);
  dream2.addJunk(iStick);
  dream2.addJunk(iMaster);
  dream2.addJunk(iHunger);
  crossroads.addJunk(iTraffic);
  crossroads.addJunk(iManhole);
  sewer.addJunk(iLeonardo);
  sewer.addJunk(iDonatello);
  sewer.addJunk(iRafael);
  sewer.addJunk(iMichelangelo);
  sewer.addJunk(iSplinter);
  courtyard.addJunk(iRain);
  courtyard.addJunk(iOaks);
  courtyard.addJunk(iBats);
  courtyard.addJunk(iVendors);
  gateway.addJunk(iGate);
  gateway.addJunk(iSelf2);
  // don't want to add staircase, maybe delete? same w/ window
  bay.addJunk(iOrca);
  theatre.addJunk(iMandrill);
  theatre.addJunk(iScreen);
  theatre.addJunk(iMurals);
  t1f5.addJunk(iRug);
  t1f5.addJunk(iArmchair);
  t1f5.addJunk(iBookcase);
  t1f6.addJunk(iBed);
  


  addI(&iWorkGloves);
  addI(&iSchedule);
  addI(&iPanel);
  addI(&iEngine);
  addI(&iCage);
  addI(&iChalkboard);
  addI(&iFlowers);
  addI(&iForm);
  addI(&iMagazine);
  addI(&iTV);
  addI(&iHatchback);
  addI(&iPorn);
  addI(&iHatch);
  addI(&iCargo);
  addI(&iGyroscope);
  addI(&iBoss);
  addI(&iPrintout);
  addI(&iTotebag);
  addI(&iCompass);
  addI(&iMusic);
  addI(&iHole);
  addI(&iLights);
  addI(&iFountain);
  addI(&iNymphs);
  addI(&iMist);
  addI(&iDoubloon);
  addI(&iZ);
  addI(&iBanjo);
  addI(&iCharisma);
  addI(&iKen);
  addI(&iFiddle);
  addI(&iKid);
  addI(&iPinball);
  addI(&iBartender);
  addI(&iAroma);
  addI(&iGypsy);
  addI(&iCuba);
  addI(&iMongolia);
  addI(&iYemen);
  addI(&iSmoke);
  addI(&iPainting);
  addI(&iCouches);
  addI(&iMadame);
  addI(&iAlcoves);
  addI(&iWomen);
  addI(&iLake);
  addI(&iStick);
  addI(&iMaster);
  addI(&iHunger);
  addI(&iTraffic);
  addI(&iManhole);
  addI(&iLeonardo);
  addI(&iDonatello);
  addI(&iRafael);
  addI(&iMichelangelo);
  addI(&iSplinter);
  addI(&iRain);
  addI(&iOaks);
  addI(&iBats);
  addI(&iGate);
  addI(&iVendors);
  addI(&iSelf2);
  addI(&iStairway);
  addI(&iOrca);
  addI(&iMandrill);
  addI(&iScreen);
  addI(&iMurals);
  addI(&iFish);
  addI(&iSturgeon);
  addI(&iDwarf);
  addI(&iWindow);
  addI(&iRug);
  addI(&iArmchair);
  addI(&iBookcase);
  addI(&iBed);

  //  -------------------------
  //  END OF WORLD CONSTRUCTION
  //  -------------------------

  cout << (*currentRoom).getState(1); << endl << endl;
  vLook();

  //  --------------------------
  //  TURN PROCEDURE STARTS HERE
  //  --------------------------

  int temp,iter,j,k,l;  
  char simpleInput[200];
  string commandString;

  while(alive)
    {
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
  string prepTable[51] = {"about","above","across","along","apart",
			  "around","at","away","back","below",
			  "beneath","beside","d","down","e",
			  "east","for","forward","from","of",
			  "off","in","inside","into","n",
			  "ne","near","north","northeast","northwest",
			  "nw","on","onto","out","outside",
			  "over","s","se","south","southeast",
			  "southwest","sw","through","to","u",
			  "under","up","upon","w","west",
			  "with"};
  for(int j=0;j<51;j++)
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
	      cout << "Try simplifying your command \'" << cVerb 
		   << "\'." << endl;
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
	    {cout << "Error message for a strange verb." << endl; return;}
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
	  if(!(*x1).isVisible())
	    {
	      cout << "You don't see any " << cNoun1 << " here." << endl;
	      return;
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
	  if(!(*x2).isVisible())
	    {
	      cout << "You don't see any " << cNoun2 << " here." << endl;
	      return;
	    }
	}  //if the command is not filtered out by now, the verb is called.
      (*verbFunctions[index])();
      timeState++;
    }
}

void event(int eventState, int verbIndex)
{
  /* inside this function is where all of the automatic or time-based
     events will occur which will broadly affect any command.  These can
     either suppress the command entirely, color how it happens, or make
     something additional happen. Include a return statement if the
     switch value is meant to suppress the verb. */
  switch(eventState)
    {
    case 1: // counters that don't do anything
      preVerb(verbIndex);
      break;
    case 2: cout << "You feel a wave of drowsiness come over you" << endl;
      (*currentRoom).addVerb("sleep",1);
      (*currentRoom).setEventState(3);
    case 3:
      preVerb(verbIndex);
      break;
    case 4: 
      if(cVerb!="tilt" && cVerb!="left" && cVerb!="right" &&
	 cVerb!="wait" && cVerb!="look")
	cout << "You can't do that, you're a pinball." << endl;
      else preVerb(verbIndex);
      break;
    default:
      cout << "Error in event function" << endl;
    }
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

void addI(item* itemPtr)
{
  if(totalItems>=ITEM_TABLE_SIZE)
    {
      cout << "ERROR: ITEM TABLE LENGTH EXCEEDED";
      exit(1);
    }
  for(int a=0;a<(*itemPtr).nameCount();a++)
    {
  itemNames[totalItems]=(*itemPtr).getName(a);
  itemPointers[totalItems]=itemPtr;
  totalItems++;
    }
}

  //  ----------------------
  //  VERB COMMAND FUNCTIONS
  //  ----------------------

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
  if(cNoun1=="")
    {
      cout << (*currentRoom).getName() << endl
	   << (*currentRoom).getLook() << endl;
      (*currentRoom).listJunk();
    }
  else if(cPrep=="inside" || cPrep=="in")
    {
      if((*x1).countContents()==-1)
	cout << "And I suppose you have x-ray vision?" << endl;
      else if((*x1).getVerbState("open")!=2)
	cout << "You'll have to open in first." << endl;
      else if((*x1).countContents()==0)
	cout << "The " << (*x1).getLongForm() << " is empty." << endl;
      else
	{
	  for(int i=0;i<(*x1).countContents();i++)
	    (*(*x1).goInside(i)).makeVisible();
	  cout << "Inside the " << (*x1).getLongForm() << " you see: " << endl;
	  (*x1).listContents();
	}
    }
  else if((*x1).isNamed("self"))
    {
      int num = inventory.numJunk();
      bool naked = true;
      string temp;
      cout << "You are wearing ";
      for(int a=num-1;a>1;a--)
	if((*inventory.getJunkByIndex(a)).isChained())
	  {
	    temp = (*inventory.getJunkByIndex(a)).getLongForm();
	    x1 = inventory.getJunkByIndex(a);
	    cout << endl << "a " << temp;
	    naked = false;
	  }
      if(naked) cout << "nothing.";
      cout << endl;
    }
  else if((*x1).getLook()=="")
    cout << "You see nothing special about the " 
	 << (*x1).getLongForm() << "." << endl;
  else switch((*x1).getVerbState("look"))
    {
    case 0: cout << (*x1).getLook() << endl;
      if((*x1).countContents()>0 &&
	 (*x1).getVerbState("open")==2)
	cout << "The " << (*x1).getLongForm() 
	     << " appears to be containing something." << endl;
      break;
    case 1: 
      cout << (*x1).getLook() << endl // looking at item reveals
	   << (*x1).getState(1) << endl; // another item nearby
      (*(*x1).goNextTo()).makeVisible();
      (*(*x1).goNextTo()).resetPrep(2);
      (*x1).resetPrep(2);
      (*x1).updateVerb("look",0);
      break;
    case 2: cout << (*x1).getState(2) << endl; break;
    default: cout << "Bad \'look\' verbstate" << endl; break;
    }
}

void vTake()
{
  if((*x1).isNamed("self"))
    cout << "The only thing you should be taking yourself for is a fool." 
	 << endl;
  if(cPrep=="off"  && cNoun2=="") vRemove();
  else if(cPrep=="off")
    cout << "Functionality not yet added" << endl;
  if(cPrep=="from" && cNoun2!="") vRemove();
  else if((*x1).isNamed("all"))
    {
      int num = (*currentRoom).numJunk();
      for(int a=num-1;a>=0;a--)
	if(!(*(*currentRoom).getJunkByIndex(a)).isChained() &&
	   (*(*currentRoom).getJunkByIndex(a)).isVisible())
	  {
	    cNoun1 = (*(*currentRoom).getJunkByIndex(a)).getName(0);
	    x1 = (*currentRoom).getJunkByIndex(a);
	    cout << (*x1).getLongForm() << ": ";
	    vTake();
	  }
    }
  else if(inventory.hasJunk(cNoun1))
    cout << "You're already carrying that." << endl;
  else if((*x1).getPronoun()!="it")
    cout << "No, " << (*x1).getPronoun() << "\'s not your type." << endl;
  else if((*x1).isChained())
    cout << "You can't move that." << endl;
  else if((*x1).getEventState()==1)
    cout << "It's fine where it is." << endl;
  else if(cNoun2=="")
    {
      int status = (*x1).getVerbState("take");
      int index;
      string temp;
      switch(status)
	{
	case 0:
	  inventory.addJunk(*(*currentRoom).takeJunk(cNoun1));
	  cout << "Taken." << endl;
	  break;
	case 1: // taking reveals something underneath.
	  cout << "Taken." << endl << (*x1).getState(1) << endl;
	  (*(*x1).goUnder()).makeVisible();
	  (*(*x1).goUnder()).resetPrep(0);
	  (*x1).resetExternals();
	  (*x1).updateVerb("take",0);
	  inventory.addJunk(*(*currentRoom).takeJunk(cNoun1));
	  index = (*currentRoom).getVerbState("look");
	  temp = (*currentRoom).getState(index);
	  (*currentRoom).setLook(temp);
	  break;
	default:
	  cout << "Bad verb state for \'take\'." << endl;
	  break;
	}
    }
  else if(cPrep=="from") vRemove();
  else cout << "I don't know what you mean." << endl;
  return;
}

void vDrop()
{
  if((*x1).isNamed("all"))
    {
      int num = inventory.numJunk();
      for(int a=num-1;a>1;a--)
	if(!(*inventory.getJunkByIndex(a)).isChained())
	  {
	    cNoun1 = (*inventory.getJunkByIndex(a)).getName(0);
	    x1 = inventory.getJunkByIndex(a);
	    cout << (*x1).getLongForm() << ": ";
	    vDrop();
	  }
    }
  else if(!inventory.hasJunk(cNoun1)) // need invis state here
    cout << "You're not carrying a " << cNoun1 << endl;
  else if((*x1).isChained())
    cout << "I'm... going to ignore that." << endl;
  else
    {
      (*currentRoom).addJunk(*inventory.takeJunk(cNoun1));
      cout << "Dropped." << endl;
    }
}

void vGo()
{
  int choice;
  if(cNoun1!="") {cout << "I'd rather not." << endl; return;}
  if(cPrep=="north"||cPrep=="n") choice = 0;
  else if(cPrep=="northeast"||cPrep=="ne") choice = 1;
  else if(cPrep=="east"||cPrep=="e") choice = 2;
  else if(cPrep=="southeast"||cPrep=="se") choice = 3;
  else if(cPrep=="south"||cPrep=="s") choice = 4;
  else if(cPrep=="southwest"||cPrep=="sw") choice = 5;
  else if(cPrep=="west"||cPrep=="w") choice = 6;
  else if(cPrep=="northwest"||cPrep=="nw") choice = 7;
  else if(cPrep=="up"||cPrep=="u") choice = 8;
  else if(cPrep=="down"||cPrep=="d") choice = 9;
  else {cout << "Go where?" << endl; return;}
  switch((*currentRoom).getDoor(choice))
    {
    case 1:
      currentRoom = (*currentRoom).followDoor(choice);
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      break;
    default:
      cout << "You can't go that way." << endl;
    }
}

void vNorth() {cPrep = "n"; vGo();}
void vNortheast() {cPrep = "ne"; vGo();}
void vEast() {cPrep = "e"; vGo();}
void vSoutheast() {cPrep = "se"; vGo();}
void vSouth() {cPrep = "s"; vGo();}
void vSouthwest() { cPrep = "sw"; vGo();}
void vWest() { cPrep = "w"; vGo();}
void vNorthwest() { cPrep = "nw"; vGo();}
void vUp() { cPrep = "u"; vGo();}
void vDown() { cPrep = "d"; vGo();}

void vUse()
{
  if(cNoun2=="")
    {
      switch((*x1).getVerbState("use"))
	{
	case 0:
	  cout << "You'll have to be more specific." << endl;
	  break;
	default: cout << "Error in verb use" << endl;
	}      
    }
  else
    {
      switch((*x2).getVerbState("use"))
	{
	case 0:
	  cout << "Those two items can't be used together." << endl;
	  break;
	default: cout << "Error in verb use" << endl;
	} 
    }
}

void vWear()
{
  if((*x1).isNamed("all"))
    cout << "Sadly, your dreams of becoming a fashion model are long since gone by the wayside." << endl;
  else if((*x1).getPronoun()!="it")
    cout << "Clearly, society has let you fall through the cracks." << endl;
  else if(!inventory.hasJunk(cNoun1))
    cout << "You need to pick that up first." << endl;
  else if((*x1).isChained())
    cout << "You're already wearing that." << endl;
  else switch((*x1).getVerbState("wear"))
    {
    case 0:
      cout << "You can't wear that." << endl;
      break;
    case 1:
      (*x1).chain();
      cout << "You are now wearing the " << cNoun1 << "." << endl;
      break;
    default: cout << "Error in verb wear" << endl;
    }
}

void vEat()
{
  int status = (*x1).getVerbState("eat");
  switch(status)
    {
    case 0:
      cout << "You can't eat that." << endl;
      break;
    default: cout << "Nothing's edible yet." << endl;
    }
}

void vDrink() 
{
  int status = (*x1).getVerbState("drink");
  switch(status)
    {
    case 0:
      cout << "You can't drink that." << endl;
      break;
    default: cout << "Nothing's drinkable yet." << endl;
    }
}

void vCombine()
{
  cout << "Those things won't go together." << endl;
}
void vTurn() {}

void vPut() 
{
  if(cNoun2=="")
    {
      if(cPrep=="on")
	{
	  cPrep=="";
	  vWear();
	  return;
	}
      if(cPrep=="down")
	{
	  cPrep=="";
	  vDrop();
	  return;
	}
      else cout << "Say what?" << endl;
    }
  else
    {
      if(cPrep=="in" || cPrep=="inside")
	{
	  if((*x1).isNamed("self"))
	    cout << "Sadly, the days of climbing into cozy containers have long since faded into memory." << endl;
	  else if(!inventory.hasJunk(cNoun1))
	    cout << "You're not carrying any " << cNoun1 << endl;
	  else if(!inventory.hasJunk(cNoun2))
	    cout << "You're not carrying any " << cNoun2 << endl;
	  else if((*x2).countContents()==-1) cout << "Yeah, right." << endl;
	  else if(x1==x2) 
	    cout << "You were never very good at origami." << endl;
	  else if((*x1).isNamed("all"))
	    for(int i=2;i<inventory.numJunk();i++)
	      {
		if(!(*inventory.getJunkByIndex(i)).isChained())
		  {
		    cNoun1 = (*inventory.getJunkByIndex(i)).getName(0);
		    x1 = inventory.getJunkByIndex(i);
		    cout << (*x1).getLongForm() << ": ";
		    vPut();
		  }
	      }
	  else if((*x2).countContents()>9)
	    cout << "There's no room in the " << (*x2).getLongForm() 
		 << " for the " << (*x1).getLongForm() << endl;
	  else if((*x1).getPreposition(5))
	    cout << "First take it out of what it's in now." << endl;
	  else
	    {
	      (*x1).putInside(*x2);
	      (*x2).putContaining(*x1);
	      cout << "Done." << endl;
	    }
	}
      else cout << "Functionality not yet added." << endl;
    }
}

void vPick() 
{
  if(cPrep=="up") vTake();
  else cout << "Functionality not yet added." << endl;
}

void vKill() 
{
  if(cNoun1=="self")
    {
    cout << "Gladly." << endl;
    alive = false;
    }
  else cout << "Calm down." << endl;
}
void vBreak() 
{
  int status = (*x1).getVerbState("break");
  switch(status)
    {
    case 0:
      cout << "You wail into the " << cNoun1 << " with abandon, but it ends up in no worse shape than when you started." << endl;
      break;
    default: cout << "Nothing's breakable yet." << endl;
    }
}

void vKiss() 
{
  int status = (*x1).getVerbState("kiss");
  switch(status)
    {
    case 0:
      if((*x1).getPronoun()=="it")
	cout << "You're not quite lonely enough." << endl;
      else
	cout << "You make to kiss " << cNoun1 << ", but " 
	     << (*x1).getPronoun() << " rebuffs your advances." << endl;
      break;
    default: cout << "No one's kissable yet." << endl;
    }
}

void vBurn() {}

void vClimb() 
{
  if(cNoun1=="") vUp();
  else cout << "Functionality not yet added." << endl;
}

void vCut() {}

void vDig() {}

void vRemove() 
{
  if((*x1).isNamed("self"))
    cout << "You meditate." << endl;
  else if(cNoun2!="" && cPrep=="from") // taking things out of containers
    {
      if((*x1).isNamed("all"))
	switch((*x2).countContents())
	  {
	  case -1: cout << "That can't be done." << endl; break;
	  case 0: cout << "The " << (*x2).getLongForm() << " is empty." 
		       << endl; break; 
	  default: 
	    for(int i=(*x2).countContents();i>0;i--)
	      {
		x1 = (*x2).goInside(i-1);
		cNoun1 = (*x1).getName(0);
		(*x1).makeVisible();
		vRemove();
	      }
	  }
      else if((*x1).getPreposition(5))
	if((*(*x1).goContaining()).isNamed(cNoun2))
	  {
	    (*x2).remove(cNoun1);
	    (*x1).resetExternals();
	    cout << "Done." << endl;
	  }
    }
  else if(cNoun2!="")
    cout << "If you want to take item A out of item B, say: \'Remove A from B\' ." << endl;
  else if(cNoun1=="all") // taking off clothes
    {
      int num = inventory.numJunk();
      for(int a=num-1;a>1;a--)
	if((*inventory.getJunkByIndex(a)).isChained())
	  {
	    cNoun1 = (*inventory.getJunkByIndex(a)).getName(0);
	    x1 = inventory.getJunkByIndex(a);
	    cout << (*x1).getLongForm() << ": ";
	    vRemove();
	  }
    }
  else if(!inventory.hasJunk(cNoun1) || !(*x1).isChained())
    cout << "You're not wearing that." << endl;
  else
    {
      (*x1).unchain();
      cout << "You take off the " << cNoun1 << "." << endl;
    }
}

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
	  (*currentRoom).addJunk(*inventory.takeJunk("flowers"));
	  (*currentRoom).setEventState((*currentRoom).getEventState()+1);
	}
      break;
    case 2:
    case 3:
    case 4:
      cout << (*x1).getState(status) << endl;
      if(status!=4) (*x1).updateVerb("arrange",status+1);
      break;
    default:
      cout << "Bad verb state for cNoun1." << endl;
      break;
    }
  return;
}

void vLie() 
{
  if(cNoun1=="") cout << "You lie down." << endl;
  else cout << "No thanks." << endl;
}
void vSit() {}
void vGive() 
{
  if(cPrep=="")
    {

    }
}
void vSleep() 
{
  int status = (*currentRoom).getVerbState("sleep");
  switch(status)
    {
    case 0:
      cout << "You're not tired." << endl;
      break;
    case 1: cout << "You fall asleep." << endl; //dream via down, state 1-3.
      currentRoom = (*currentRoom).followDoor(9);
      cout << (*currentRoom).getState(1) << endl << endl
	   << (*currentRoom).getState(2) << endl << endl
	   << (*currentRoom).getState(3) << endl;
      cout << (*currentRoom).getName() << endl;
      if(!(*currentRoom).isExplored())
	{
	  (*currentRoom).flagExplored();
	  cout << (*currentRoom).getLook() << endl;
	}
      (*currentRoom).listJunk();
      break;
      
    default: cout << "Error in verb: Sleep." << endl;
    }
}
void vWash() {}
void vBite() {}
void vFart() {}
void vFight() {}
void vHang() {}
void vCook() {}
void vOpen() 
{
  if(cNoun2=="")
    {
      switch((*x1).getVerbState("open"))
	{
	case 0: cout << "You can't open that." << endl; break;
	case 1: 
	  cout << (*x1).getState(1) << endl;
	  (*x1).addVerb("look",2); // this could be dangerous.
	  (*currentRoom).setDoor(9,1); //as could this.
	  (*x1).updateVerb("open",2);
	  break;
	case 2: cout << "It's already open." << endl; break;
	case 3: cout << (*x1).getState(3) << endl; break;
	default: cout << "Error in open function" << endl; break;
	}
    }
  else cout << "Unimplemented" << endl;
}
void vClose() {}
void vRub() {}
void vRide() {}
void vRing() {}
void vShoot() {}
void vStop() {}
void vDance() {}
void vDive() {}
void vDie() 
{
  cout << "OK." << endl;
  alive = false;
}
void vDrive() {}
void vWake() {}

void vAsk() 
{
  if(cPrep!="about")
    {
      cout << "If you want to ask someone about something, type:" << endl
	   << "Ask (person) about (thing)" << endl;
      return;
    }
  int status = (*x1).getVerbState((*x2).getName(0)); //slightly diff
  switch(status)
    {
    case 0:
      if((*x1).getPronoun()=="it")
	cout << "Talking to inanimate objects won't help your situation." << endl;
      else cout <<"Clearly, "<<(*x1).getLongForm()
		<<" isn't interested in talking about the "
		<<(*x2).getLongForm()<<"."<<endl;
      break;
    case 1: 
    case 2: cout << (*x1).getState(status) << endl; break;
    case 3: cout << (*x1).getState(3) << endl; //teaches you how to play
      (*x2).updateVerb("play",2);
      (*x1).updateVerb((*x2).getName(0),4);
      break;
    case 4: cout << (*x1).getState(4) << endl; break; //after learning
    default: cout << "Error in verb: calculate." << endl;
    }
}
void vPlay() 
{ 
  int status = (*x1).getVerbState("play");
  switch(status)
    {
    case 0: cout << "You're not really into the noise music scene." << endl;
      break;
    case 1: cout << "You don't know how." << endl; break;
    case 2:
    case 3:
    case 4: cout << (*x1).getState(status-1) << endl; 
      (*x1).updateVerb("play",status+1); break;
    case 5: cout << (*x1).getState(4) << endl;
      (*x1).updateVerb("play",6); break;
      (*(*currentRoom).getJunk("charisma")).makeVisible();
      inventory.addJunk(*(*currentRoom).takeJunk("charisma"));
    case 6: cout << (*x1).getState(4) << endl; break;
    default: cout << "Error in verb PLAY" << endl;
    }
}
void vBuy() {}
void vHaggle() {}
void vGreet() 
{
  int status = (*x1).getVerbState("greet");
  switch(status)
    {
    case 0: if((*x1).getPronoun()=="it") 
      cout << "Someone's been reading Goodnight Moon a few too many times." 
	   << endl;
    else
      {
	cout << (*x1).getLongForm() << " ignores your greeting." << endl;
      }
      break;
    case 1:
    case 2: cout << (*x1).getState(status) << endl; break;
    default: cout << "Error in verb Greet" << endl;
    }

}
void vPay() {}
void vJump() {}
void vFly() {}

void vFlipper() 
{

}
void vTilt() {}

void vCalculate() 
{
  int status = (*x1).getVerbState("calculate");
  switch(status)
    {
    case 0: cout << "Who do you think you are, Stephen Wolfram?";
      break;
    case 1: cout << (*x1).getState(1) << endl; //uncalculable
      break;
    case 2: cout << (*x1).getState(2) << endl;
      break;
    default: cout << "Error in verb: calculate." << endl;
    }
}
void vItemize() 
{
  int status = (*x1).getVerbState("itemize");
  switch(status)
    {
    case 0: cout << "That can't be itemized." << endl; break;
    case 1: (*x1).updateVerb("itemize",2);
      (*x1).setLook((*x1).getState(1));
      cout << "You itemize the " << (*x1).getLongForm() << "." << endl;
      (*currentRoom).setEventState((*currentRoom).getEventState()+1);
      break;
    case 2: cout << "That's already been itemized." << endl;
      break;
    default: cout << "Error in verb: itemize." << endl;
    }
}
