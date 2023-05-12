#include<iostream>
#include<random>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#define EP 1.00e-06
#define INF 1000000000
#define PI 3.14159265358979323846

using namespace std;


vector<vector<double> > g;
vector<int> X, Y;

struct Id{
  string name;
  int number;
};
int seed;
const int DIGITS_NUMBER = 4;  //digits of id number displayed in id
Id id;
string dir;
const string ext = ".ccpdp";

char type; //'e' for euclidian, 'n' for a general graph(without coordinates)
           //'d' for euclidian with constraint, 'c' for general with constraint
int A,V;  //Number of vertex(2*A) and agents



void writeInstance();

//Create a random metric graph with A agents and max distance max
//  if it have a "type" of separation:
//    'n' for general graph
//    'q' for quadrants
//    'p' for cut in cycles (pizza like)
//  how many "separation" it have
//  Separator Wall: how distant from the separator line point have to be from 0 to 1
void createRandomGraph(int A, double max);
void createRandomGraph(int A, double max,
                       char typeSeparation);
void createRandomGraph(int A, double max,
                       char typeSeparation,
                       int separation1, int separation2);
void createRandomGraph(int A, double max,
                       char typeSeparation,
                       int separation1, int separation2,
                       double sWall);
void euclidize(char type, int separation1, int separation2, double max, double sWall);
void euclidizeQuadrant(int vSeparation, int hSeparation, double max, double sWall);
void calcEuclidianGraph();

//     void symmetrize(double max);
//     void dijkstra(int source);
//     void euclidizeCircle(int rSeparation, int aSeparation, double max, double sWall);

string getNumberId(int digits); //get the next available number (with 4 digits) in that dir

string myitos(int a, int digits);

int getSeed();

// exemplo: ./CCPDP 24 5 q 2 0.2

/* argv:
 *   -dir
 *   -A (número de agentes/ V = 2*A)
 *   -idNumber: seed
 *   -type:
 *     -'q' para quadrantes
 *       -division: divisões ( dxd quadrantes )
 *       -sWall: muro separador ( 0.0 - 1.0 )
 *     -'p' para polar
 *   
 */
int main(int argc, char* argv[]){
  
  
  if(argc!=7){cerr << "ERROR: ./CCPDP dir A(int) idNumber(int) type(char) division(int) sWall(float)\n"; return 0;}
  
  int division;
  double sWall;
  
  dir       =      argv[1];
  A         = atoi(argv[2]);
  id.number = atoi(argv[3]);
  type      =      argv[4][0];
  division  = atoi(argv[5]);
  sWall     = atof(argv[6]);
  
  srand(id.number);
  
  if(type!='q'){cerr << "ERROR: just 'q'\n"; return 0;}
  
  system( ( "mkdir -p " + dir ).c_str());      
  
  createRandomGraph(A, 100000, type, division, division, sWall);
  writeInstance();
  
  return 0;
}

string getId(){return id.name + "." + myitos(id.number, DIGITS_NUMBER);}








void createRandomGraph(int A, double max){
  createRandomGraph(A, max, 'n', 0, 0, 0.0);
}
void createRandomGraph(int A, double max,
                       char type_separation){
  createRandomGraph(A, max, type_separation, 0, 0, 0.0);
}
void createRandomGraph(int A, double max,
                       char type_separation,
                       int separation1, int separation2){
  createRandomGraph(A, max, type_separation, separation1, separation2, 0.0);

}
void createRandomGraph(int nAgents, double max,
                       char type_separation,
                       int separation1, int separation2,
                       double sWall){
  ostringstream idStream;
  idStream << "rg-" << myitos(A, 3) << "-" << type_separation;
  if(type_separation=='n'){}
  else {idStream << "-" << separation1 << "x" << separation2;}
  if(sWall>0.0+EP)idStream  << "-W" << sWall;
  id.name = idStream.str();
  idStream << "-" << getNumberId(DIGITS_NUMBER);

  A = nAgents;
  V = 2*A;
  g.resize(V);
  for(int i=0; i<V; ++i)
    g.at(i).resize(V);
  X.resize(V);
  Y.resize(V);
  type = type_separation;
  
  cout << "Creating a random Graph with "
       << A << " agents and "
       << V << " vertices." << endl
       << " Type of graph is " << type << "\n with " << separation1 << " separations of type 1 and "
       << separation2 << " separations of type 2. " << endl
       << " W = " << sWall << endl;//*/

  switch(type_separation){
    case 'n':
      type = 'n';
//      symmetrize(max);
      break;
    case 'q':
    case 'p':
      type = 'e';
      euclidize(type_separation, separation1, separation2, max, sWall);
      //writeFile();
      break;
    default:
      //MENSAGEM DE ERRO!!!
      break;
  }

}


void euclidize(char type, int separation1, int separation2, double max, double sWall){
  if(separation1<=1&&separation2<=1){
    for(int i=0; i<V; i++){
      X.at(i) = rand()%((int)max+1);
      Y.at(i) = rand()%((int)max+1);
    }
    calcEuclidianGraph();
    return;
  }
  switch(type){
    case 'q':
      euclidizeQuadrant(separation1, separation2, max, sWall);
      break;
    case 'p':
      //euclidizeCircle(separation1, separation2, max, sWall);
      break;
    default:
      //MENSAGEM DE ERRO!!!
      break;
  }
}

void euclidizeQuadrant(int vSeparation, int hSeparation, double max, double sWall){
  int vDiv = vSeparation-1;                        //number of vertical divisions
  int hDiv = hSeparation-1;                        //number of horizontal divisions
  int vParts = vSeparation;                        //number of vertical parts
  int hParts = hSeparation;                        //number of horizontal parts
  int nParts = vParts*hParts;                      //number of parts
  double vBlock = max/(vParts);                    //size of vertical blocks
  double hBlock = max/(hParts);                    //size of horizontal blocks
  int vqBlock = ceil((double)A/(double)vParts);    //number of agents in each vertical block
  int hqBlock = ceil((double)A/(double)hParts);    //number of agents in each horizontal block
  int qBlock  = ceil((double)A/(double)nParts);    //number of agents in each block

  for(int i=0; i<A; i++){
    int j=i;
    bool REAL_RANDOM = true;                       //agents are set in a random quadrant
    if(REAL_RANDOM){j = rand()%A;}
    int quadrantNumber = j/qBlock;                 //quadrant are numbered horizontally then vertically
    int vPos = (j/hParts)%vParts;
    int hPos = j%hParts;

    Y.at(i  ) = rand()%((int)vBlock+1) + vPos * vBlock;
    Y.at(i+A) = rand()%((int)vBlock+1) + vPos * vBlock;
    X.at(i  ) = rand()%((int)hBlock+1) + hPos * hBlock;
    X.at(i+A) = rand()%((int)hBlock+1) + hPos * hBlock;

    if(sWall>0.0+EP && sWall<=1.0){
      Y.at(i  ) += (vPos * vBlock + vBlock/2 - Y.at(i  )) * sWall;
      Y.at(i+A) += (vPos * vBlock + vBlock/2 - Y.at(i+A)) * sWall;
      X.at(i  ) += (hPos * hBlock + hBlock/2 - X.at(i  )) * sWall;
      X.at(i+A) += (hPos * hBlock + hBlock/2 - X.at(i+A)) * sWall;
    }
  }
  calcEuclidianGraph();
  return;
}



void calcEuclidianGraph(){
  for(int i=0; i<V; i++)
    for(int j=0; j<V; j++){
      g.at(i).at(j) = sqrt( pow(X.at(i)-X.at(j), 2)
                           +pow(Y.at(i)-Y.at(j), 2) );
    }
  return;
}







void writeInstance(){
  ofstream output( dir + getId() + ext );
  
  output << "NAME: "<< getId() << endl;
  output << "TYPE: "<< type << endl;
  output << "COMMENT: " << endl;
  output << "DIMENSION: " << V << endl;
  if(type=='d' || type=='c')  output << "CONSTRAINT: " << 0 << endl;
  output << "EDGE_WEIGHT_TYPE: ATT" << endl;

  if(type=='e'||type=='d') {
    output << "NODE_COORD_SECTION" << endl;
    for (int i = 0; i<V; i++) {
      output << i+1 << " " << X.at(i) << " " << Y.at(i) << endl;
    }
  }
  else if(type=='n'||type=='c'){
    output << "EDGE_COST_SECTION" << endl;
    for (int i=0; i<V; i++) {
      for(int j=0; j<V; j++){
        if(i!=j) output << g.at(i).at(j);
        else output << 0 << endl;
      }
    }
  }

  output << "EOF";
  
  output.close();
  return;
}


//convert an int 'a' to string with 'digits' digits
string myitos(int a, int digits){
  string s;
  int n=0;
  int b = a;
  while(b>0){
    b/=10;
    n++;
  }
  digits-=n;
  if(digits<0){
    cerr << "ERROR IN MYITOS: " << a << ">9.9...*10^" << digits+n << " " << endl;
    return s;
  }
  ostringstream ostr;
  for(int i=0; i<digits; i++)
    ostr << '0';
  if(a>0)ostr << a;
  s = ostr.str();
  return s;
}


//get the next available number (with 4 digits)
string getNumberId(int digits){
  id.number;
  return myitos(id.number, digits);


}

int getSeed(){
  return id.number;
}
