#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <algorithm>
#include <QThread>
#include <QDir>
#include<math.h>

/*
 * This source file is where game happens. Game begins in constructor.
 * */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // *1 declaration of header files
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    window =new QWidget(this); //Game window.
    buttongroup=new QButtonGroup();//ButtonGroup for buttons.
    layout =new QHBoxLayout(); //Layout.
    board=new QHBoxLayout();
    gameInfo=new QVBoxLayout();
    cards=new QVBoxLayout();//Layout for cards.
    players=new QVBoxLayout();// Layout for players.
    scores=new QVBoxLayout();//Layout for scores.
    playerNames=new QHBoxLayout(); //Layout for player names.
    tim=new QVBoxLayout();//Layout for time information wrt players.
    p1i=new QVBoxLayout();//Layout for player1 info.
    p2i=new QVBoxLayout();//Layout for player2 info.
    game=new QVBoxLayout();//Layout for game.
    upi=new QHBoxLayout();//Layout for upper interface. Our game window will consist 2 main layouts: cards and upi.
    sctim=new QHBoxLayout(); //Layout for scores
    newG=new QPushButton("New Game");//Button for new game.
    prevR=new QPushButton("Prev Results");//Button for previous results.
    nextR=new QPushButton("Next Results");//Button for next results.
    Exit=new QPushButton("Exit");//Button for exit.
    p1s=new QLabel();//Label for player 1 score.
    p1t=new QLabel();//Label for player 1 time.
    p2s=new QLabel();//Label for player 2 score.
    p2t=new QLabel();//Label for player 2 time.
    pla1=new QLabel();//Information for players pla1, pla2,pla3 are declared.
    pla2=new QLabel();
    pla3=new QLabel();
    sc=new QLabel(); //Label for scores.
    ti=new QLabel(); //Label for time information.
    label_1=new QLabel();
    label_2=new QLabel();

    countD=0;
    highest=0; //Highest score.
    gameCount=1;  //Holds total #of games.
    P1Score=0;//Player1 score.
    P2Score=0;//Player 2 score.
    P1Time=0;//Player 1 time.
    P2Time=0;//Player 2 time.
    count=0;//counter for file I/O
    playerTurn=1; //Holds player turn.
    TracedGame=1; //Tracker number to hold which game's results will be displayed.
    QString randomSample[200]={"doornik" , "fluster" , "evasive" , "cotonou" , "tartini" , "rescued" , "kokanee" , "wielder" , "eutopia" , "tallowy" , "coveter" , "skepful" , "ithacan" , "rackets" , "undrawn" , "oxysalt" , "hammier" , "paletot" , "precast" , "sopping" , "bluetit" , "cornell" , "plumbic" , "beefier" , "kirundi" , "abraser" , "burgher" , "excuser" , "crasher" , "bothies" , "bethany" , "kiangsu" , "untread" , "adorsed" , "ransome" , "mopiest" , "lugworm" , "bistros" , "catreus" , "annatol" , "unebbed" , "exurbia" , "england" , "persian" , "cyanite" , "piefort" , "psykter" , "manasic" , "rattail" , "discard" , "footpad" , "eyewink" , "sagging" , "capelin" , "harshen" , "frisket" , "evident" , "ctesius" , "touched" , "plumbum" , "obovate" , "mirkier" , "gumshoe" , "lustier" , "despair" , "goldoni" , "stature" , "pythius" , "subaqua" , "quaffer" , "hircine" , "genesee" , "adjudge" , "avestan" , "stoving" , "biliary" , "pehlevi" , "bizerte" , "lallans" , "married" , "killoch" , "premont" , "leaving" , "locusta" , "barruly" , "vicente" , "gelling" , "resurge" , "odoacer" , "lorrain" , "probing" , "crating" , "anurous" , "oswaldo" , "keramic" , "pyjamas" , "pitfall" , "microhm" , "canales" , "aminity" , "addible" , "chaufer" , "heyduke" , "hohokus" , "unhoary" , "impaler" , "giraffe" , "granary" , "nunlike" , "irkutsk" , "forfeit" , "dulosis" , "maypole" , "patness" , "churner" , "accompt" , "joggler" , "pimento" , "assurer" , "bravely" , "cowgirl" , "hottish" , "barring" , "chignon" , "andvari" , "lequear" , "pastime" , "zymurgy" , "clerisy" , "siddons" , "ruttish" , "lavater" , "notions" , "aliases" , "peatier" , "emblaze" , "malaise" , "sapsago" , "delavan" , "dundalk" , "quoting" , "brigand" , "diverge" , "soaring" , "amplify" , "fulbert" , "lineman" , "camphor" , "caseous" , "eckhart" , "chenier" , "swifter" , "abysmal" , "diptych" , "drammen" , "wending" , "dispart" , "skinner" , "procure" , "sagunto" , "gagging" , "jeritza" , "plastid" , "rootlet" , "schlepp" , "reverer" , "aphakic" , "caballo" , "zamarra" , "scoring" , "passion" , "soirï¿¥ï¾½e" , "nunnery" , "hymnist" , "lassoer" , "toprail" , "barnaul" , "stalely" , "prelude" , "hogmane" , "schberg" , "pygidia" , "striate" , "manners" , "arenite" , "rgenise" , "complot" , "pledgee" , "snecker" , "eductor" , "passage" , "marleen" , "tantrik" , "wulfila" , "doggone" , "sipping" , "leprous" , "homonid" , "humilis" , "cambrai" };


    time=QTime::currentTime();//For random number generation, timer is assigned.
    //*1
    //2* create random number depends on current time
    qsrand((uint)time.msec());
    //*2
    /*
     * 3* numbers are selected randomly between 0-199 so that we can pick 15 words randomly from 200 words dictionary.
     * */
    for(int i=0;i<15;i++){
        int tem=qrand()%200;
        while(rands.indexOf(tem)>-1){
            tem=qrand()%200;
        }
        rands.append(tem);

    }
    //*3
    //4*Sorts 15 random numbers.
    std::sort(rands.begin(), rands.end());
    //*4
    //5* Picking words from word sample array.
    for(int i=0;i<15;i++){
        myWords.append(randomSample[rands[i]]);
    }
    //*5

    //6* Adds buttons in buttongroup. At the end of loop, all buttons are connected in button group.
    for(int i=0 ; i < 30 ; i++) {
        button[i] = new QPushButton("?");
        layout->addWidget(button[i]);
        buttongroup->addButton(button[i],i);
        count++;
         //Adds in 6 x 5 order.
        if(count%6==0){
            cards->addLayout(layout);
            layout=new QHBoxLayout();
        }


    }
    //*6
    //7*Connects object.
    QObject::connect(buttongroup, SIGNAL(buttonClicked(int)), this, SLOT(handler(int)));
    //*7


    //8* sets time and score info
    gam="Score";
    hi="Time (secs)";

    sc->setText(gam);
    ti->setText(hi);
    tim->addWidget(sc);
    tim->addWidget(ti);
    newG->setEnabled(false);
    prevR->setEnabled(false);
    nextR->setEnabled(false);
    //*8
    //9* Connects 3 objects.
    QObject::connect(newG, SIGNAL(clicked()), this, SLOT(newGame())); //New Game button with quit.
    QObject::connect(prevR, SIGNAL(clicked()), this, SLOT(showPreviousGame())); //Shows previous games.
    QObject::connect(nextR, SIGNAL(clicked()), this, SLOT(showNextGame())); //Shows next games.
    //*9
    //10* Adds 3 widgets.
    gameInfo->addWidget(newG);
    gameInfo->addWidget(prevR);
    gameInfo->addWidget(nextR);
    //*10
    //*11 Quit signal.
    QObject::connect(Exit, SIGNAL(clicked()), this, SLOT(Quit()));
    gameInfo->addWidget(Exit);
    //*11

    //12* Fills array with 0 so that we can place words correctly.
    for(int h=0;h<30;h++){
        isFree[h]=0;

    }
    //*12


    //13* Places words in buttons before game begins. Each word has 2 places. 2 Places are chosen randomly.
    for(int z=0;z<15;z++){

        QString currentName=myWords.at(z);
        int rh=qrand()%30;
        int rh1=qrand()%30;
        while(isFree[rh]==1){
            rh=qrand()%30;
        }

        isFree[rh]=1;
        buttonNames[rh]=currentName;
        while(isFree[rh1]==1){
            rh1=qrand()%30;
        }

        isFree[rh1]=1;
        buttonNames[rh1]=currentName;
    }
    //*13
/*
 * *14 These 4 lines add players' score and time information.
 * */
    p1s->setText(QString::number(P1Score));
    p1t->setText(QString::number(P1Time));
    p2s->setText(QString::number(P2Score));
    p2t->setText(QString::number(P2Time));
    p1i->addWidget(p1s);
    p1i->addWidget(p1t);
    p2i->addWidget(p2s);
    p2i->addWidget(p2t);
    gam="Player 1";
    hi="Player 2";
    pla1->setText(gam);
    pla2->setText(hi);
    pla3->setText("");
    //*14
    /*15*
     * These lines are for #of games and highest.
     * */
    playerNames->addWidget(pla3);
    playerNames->addWidget(pla1);
    playerNames->addWidget(pla2);
    gam="Game no: "+QString::number(gameCount);
    hi="Highest score: "+QString::number(highest);
    label_1->setText(gam);
    label_2->setText(hi);
    scores->addWidget(label_1);
    scores->addWidget(label_2);
    players->addLayout(playerNames); //Player names are added.
    //*15

    // 16* Assembles all board with its components.
    sctim->addLayout(tim);
    sctim->addLayout(p1i);
    sctim->addLayout(p2i);
    players->addLayout(sctim);
    upi->addLayout(players);
    upi->addLayout(board);
    board->addLayout(scores);
    board->addLayout(gameInfo);
    game->addLayout(upi);
    game->addLayout(cards);
    window->resize(800,800);
    window->setLayout(game);
    //*16
    //
}
//Destructor.
MainWindow::~MainWindow()
{
    delete ui;
}
/*
 *This method checks whether 2 strings in button are the same. If same, buttons will be disabled. Otherwise,
 * these buttons will be enabled again. ControllerArray is declared for keeping button and index with format<QPushButton*int>
 * pair.
 * */
void MainWindow::checker(){


        int currentButtonIndex1=controllerArray[0].second;
        int currentButtonIndex2 =controllerArray[1].second;
        //17* String comparison.
    int x = QString::compare((controllerArray[0].first)->text(), controllerArray[1].first->text(), Qt::CaseInsensitive);
    //*17
    if(x==0){//18* If strings are equal.
            //According to playerTurn, players' scores and time will be updated.
            if(playerTurn%2==1){
                P1Score++;
                p1s->setText(QString::number(P1Score));
                p1s->repaint();
            }else{
                P2Score++;
                p2s->setText(QString::number(P2Score));
                p2s->repaint();
            }
            //This is for whether game ends.
            isAllUsed.append(1);



        }else{
            //Sets buttons after mismatch.

            button[currentButtonIndex1]->setText("?");
            button[currentButtonIndex2]->setText("?");

            button[currentButtonIndex1]->setEnabled(true);
            button[currentButtonIndex2]->setEnabled(true);


        }
       //*18
        //19* Takes time difference for adding time. Time is added in seconds.
        int difference=time.elapsed();
        if(playerTurn%2==1){
            P1Time+=difference;
            p1t->setText(QString::number(P1Time/1000));

        }else{
            P2Time+=difference;
            p2t->setText(QString::number(P2Time/1000));

        }
        //*19
        controllerArray.erase(controllerArray.begin(),controllerArray.end());//Array's size will be 2.Therefore, array will be deleted after execution.
        playerTurn++;//PlayerTurn increases.

    //20* If game ends, new game button is enabled.
    if(isAllUsed.size()==15){
        newG->setEnabled(true);
    }
    //*20
}

/*
 * Our new slot functions. Event handler and quit. Handler handles with click events.
 * */
void MainWindow::handler(int i){
    controllerArray.append(qMakePair(button[i],i));
    //21*If size is 2, checker method will be activated.
    if(controllerArray.size()==2){
        button[i]->setEnabled(false);
        button[i]->setText(buttonNames[i]);
        button[i]->repaint();
        for(int counter=1;counter<=500000000;counter++);
        checker();
    }else{
        //22* Event starts when first button is clicked.
        time.start();
        button[i]->setEnabled(false);//Disables button until comparion is completed.
        button[i]->setText(buttonNames[i]);//Sets text of button.
        //*22
    }
    //*21
}
/*
 * Extra slot for Quitting application.
 *
 * */
void MainWindow::Quit(){
    QApplication::quit();
}
/*
 * Shows previous games' results as Player1's score and time, Player2's score and time.
 * */
void MainWindow::showPreviousGame(){

        //23* Usual case for setting text, score and time.
      if(TracedGame>1){
        TracedGame--;

        nextR->setEnabled(true);
        //24* Extracts games results from source.
        QList<int> extracter=playerStats[TracedGame-1];

        int prevP1score=extracter[0];
        int prevP1time=extracter[1];
        int prevP2score=extracter[2];
        int prevP2time=extracter[3];
        //*24
        //25* sets label text.
        p1s->setText(QString::number(prevP1score));
        p1t->setText(QString::number(prevP1time));
        p2s->setText(QString::number(prevP2score));
        p2t->setText(QString::number(prevP2time));
        //*25

        gam="Player 1";
        hi="Player 2";
        pla1->setText(gam);
        pla2->setText(hi);
        pla3->setText("");
        //Game number and highest is updated.
        gam="Game no: "+QString::number(TracedGame);
        hi="Highest score: "+QString::number(highest);
        label_1->setText(gam);
        label_2->setText(hi);

    }//*23
      //26* Setting disable previous button for index.
    if(TracedGame==1){
        prevR->setEnabled(false);
    }
    //*26
}
/*
 * Shows next game results with players' scores and times.
 * */

void MainWindow::showNextGame(){

        //27* Usual case for showing previous page.
     if(TracedGame<gameCount-1){
        TracedGame++;
        prevR->setEnabled(true);
        QList<int> extracter=playerStats[TracedGame-1];

        int prevP1score=extracter[0];
        int prevP1time=extracter[1];
        int prevP2score=extracter[2];
        int prevP2time=extracter[3];
        p1s->setText(QString::number(prevP1score));
        p1t->setText(QString::number(prevP1time));
        p2s->setText(QString::number(prevP2score));
        p2t->setText(QString::number(prevP2time));

        gam="Game no: "+QString::number(TracedGame);
        hi="Highest score: "+QString::number(highest);
        label_1->setText(gam);
        label_2->setText(hi);
    }else{
        p1s->setText(QString::number(P1Score));
        p1t->setText(QString::number(P1Time/1000));
        p2s->setText(QString::number(P2Score));
        p2t->setText(QString::number(P2Time/1000));

        pla3->setText("");
        gam="Game no: "+QString::number(gameCount);
        hi="Highest score: "+QString::number(highest);
        label_1->setText(gam);
        label_2->setText(hi);
        nextR->setEnabled(false);
    }
     //*27
     //28* Edge case for TracedGame==gameCount
     if(TracedGame==gameCount-1){
         TracedGame++;
     }//*28
}

/*
 * Starts a new game with updated records. Code is almost the same with constructor.
 * Resets player scrores, times and puts them in array.
 *
 * */
void MainWindow::newGame(){
    gameCount++; //29* Increases game number. *29
    //30*Word list is created again.
    QString randomSample[200]={"doornik" , "fluster" , "evasive" , "cotonou" , "tartini" , "rescued" , "kokanee" , "wielder" , "eutopia" , "tallowy" , "coveter" , "skepful" , "ithacan" , "rackets" , "undrawn" , "oxysalt" , "hammier" , "paletot" , "precast" , "sopping" , "bluetit" , "cornell" , "plumbic" , "beefier" , "kirundi" , "abraser" , "burgher" , "excuser" , "crasher" , "bothies" , "bethany" , "kiangsu" , "untread" , "adorsed" , "ransome" , "mopiest" , "lugworm" , "bistros" , "catreus" , "annatol" , "unebbed" , "exurbia" , "england" , "persian" , "cyanite" , "piefort" , "psykter" , "manasic" , "rattail" , "discard" , "footpad" , "eyewink" , "sagging" , "capelin" , "harshen" , "frisket" , "evident" , "ctesius" , "touched" , "plumbum" , "obovate" , "mirkier" , "gumshoe" , "lustier" , "despair" , "goldoni" , "stature" , "pythius" , "subaqua" , "quaffer" , "hircine" , "genesee" , "adjudge" , "avestan" , "stoving" , "biliary" , "pehlevi" , "bizerte" , "lallans" , "married" , "killoch" , "premont" , "leaving" , "locusta" , "barruly" , "vicente" , "gelling" , "resurge" , "odoacer" , "lorrain" , "probing" , "crating" , "anurous" , "oswaldo" , "keramic" , "pyjamas" , "pitfall" , "microhm" , "canales" , "aminity" , "addible" , "chaufer" , "heyduke" , "hohokus" , "unhoary" , "impaler" , "giraffe" , "granary" , "nunlike" , "irkutsk" , "forfeit" , "dulosis" , "maypole" , "patness" , "churner" , "accompt" , "joggler" , "pimento" , "assurer" , "bravely" , "cowgirl" , "hottish" , "barring" , "chignon" , "andvari" , "lequear" , "pastime" , "zymurgy" , "clerisy" , "siddons" , "ruttish" , "lavater" , "notions" , "aliases" , "peatier" , "emblaze" , "malaise" , "sapsago" , "delavan" , "dundalk" , "quoting" , "brigand" , "diverge" , "soaring" , "amplify" , "fulbert" , "lineman" , "camphor" , "caseous" , "eckhart" , "chenier" , "swifter" , "abysmal" , "diptych" , "drammen" , "wending" , "dispart" , "skinner" , "procure" , "sagunto" , "gagging" , "jeritza" , "plastid" , "rootlet" , "schlepp" , "reverer" , "aphakic" , "caballo" , "zamarra" , "scoring" , "passion" , "soirï¿¥ï¾½e" , "nunnery" , "hymnist" , "lassoer" , "toprail" , "barnaul" , "stalely" , "prelude" , "hogmane" , "schberg" , "pygidia" , "striate" , "manners" , "arenite" , "rgenise" , "complot" , "pledgee" , "snecker" , "eductor" , "passage" , "marleen" , "tantrik" , "wulfila" , "doggone" , "sipping" , "leprous" , "homonid" , "humilis" , "cambrai" };
    //*30

    nextR->setEnabled(false);
    //31* Game is finished and scores are updated.
    if(isAllUsed.size()==15){
        if(P1Score>highest){
            highest=P1Score;
        }else{
            highest=P2Score;
        }
        newG->setEnabled(false);
        isAllUsed.erase(isAllUsed.begin(),isAllUsed.end());
        label_2->setText("Highest score: "+QString::number(highest));
        label_2->repaint();
    }
    //*31
    TracedGame=gameCount;
    //32* Games data are deleted.
    rands.erase(rands.begin(),rands.end());
    myWords.erase(myWords.begin(),myWords.end());
    playerTurn=1;
    prevR->setEnabled(true);
    //*32
    //33* Random numbers are generated again.
    for(int i=0;i<15;i++){
        int tem=qrand()%200;
        while(rands.indexOf(tem)>-1){
            tem=qrand()%200;
        }
        rands.append(tem);

    }
    //*33
    std::sort(rands.begin(), rands.end());
    //34* Picking words from word sample array.
    for(int i=0;i<15;i++){
        myWords.append(randomSample[rands[i]]);
    }
    //*34

    QList<int> temporaryPlayerStats;
    //35* Player data is put into a list.
    temporaryPlayerStats.append(P1Score);
    temporaryPlayerStats.append(P1Time/1000);
    temporaryPlayerStats.append(P2Score);
    temporaryPlayerStats.append(P2Time/1000);
    playerStats.append(temporaryPlayerStats);
    //*35
    //36* Buttons are reset.
    for(int h=0;h<30;h++){
        button[h]->setText("?");
        button[h]->setEnabled(true);
        isFree[h]=0;
        buttonNames[h]="";


    }
    //*37
    for(int z=0;z<15;z++){

        QString currentName=myWords.at(z);
        int rh=qrand()%30;
        int rh1=qrand()%30;
        while(isFree[rh]==1){
            rh=qrand()%30;

        }
        isFree[rh]=1;
        buttonNames[rh]=currentName;
        while(isFree[rh1]==1){
            rh1=qrand()%30;
        }
        isFree[rh1]=1;
        buttonNames[rh1]=currentName;
    }
    P1Score=0;
    P2Score=0;
    P1Time=0;
    P2Time=0;
    //38* Resets player scores and times.
    p1s->setText(QString::number(P1Score));
    p1t->setText(QString::number(P1Time/1000));
    p2s->setText(QString::number(P2Score));
    p2t->setText(QString::number(P2Time/1000));
    gam="Player 1";
    hi="Player 2";
    pla1->setText(gam);
    pla2->setText(hi);
    pla3->setText("");
    gam="Game no: "+QString::number(gameCount);
    hi="Highest score: "+QString::number(highest);
    label_1->setText(gam);
    label_2->setText(hi);
    //*38
}
