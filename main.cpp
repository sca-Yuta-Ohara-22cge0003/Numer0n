#include <algorithm>
#include <charconv>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void instruction();
int EnterNumber();
int EnterHundredsPlace();
int EnterTensPlace(int not1);
int EnterOnesPlace(int not1, int not2);
int CheckHitByte(string THE_NUMBER, char guessPlace, int hitPlase);

int guessH;
int guessT;
int guessO;

char guessHundredsPlace;
char guessTensPlace;
char guessOnesPlace;

int main() {
  // setup
  int game = 0;

  vector<string> HundredsPlace; //ベクトルの宣言
  HundredsPlace.push_back("0");
  HundredsPlace.push_back("1");
  HundredsPlace.push_back("2");
  HundredsPlace.push_back("3");
  HundredsPlace.push_back("4");
  HundredsPlace.push_back("5");
  HundredsPlace.push_back("6");
  HundredsPlace.push_back("7");
  HundredsPlace.push_back("8");
  HundredsPlace.push_back("9");

  vector<string> TensPlace; //ベクトルの宣言
  TensPlace.push_back("0");
  TensPlace.push_back("1");
  TensPlace.push_back("2");
  TensPlace.push_back("3");
  TensPlace.push_back("4");
  TensPlace.push_back("5");
  TensPlace.push_back("6");
  TensPlace.push_back("7");
  TensPlace.push_back("8");
  TensPlace.push_back("9");

  vector<string> OnesPlace; //ベクトルの宣言
  OnesPlace.push_back("0");
  OnesPlace.push_back("1");
  OnesPlace.push_back("2");
  OnesPlace.push_back("3");
  OnesPlace.push_back("4");
  OnesPlace.push_back("5");
  OnesPlace.push_back("6");
  OnesPlace.push_back("7");
  OnesPlace.push_back("8");
  OnesPlace.push_back("9");

  // vector<string> UsedNumber;

  srand(static_cast<unsigned int>(time(0)));
  random_shuffle(HundredsPlace.begin(), HundredsPlace.end());
  random_shuffle(TensPlace.begin(), TensPlace.end());
  random_shuffle(OnesPlace.begin(), OnesPlace.end());

  while (HundredsPlace[0] == TensPlace[0] || HundredsPlace[0] == OnesPlace[0] ||
         TensPlace[0] == OnesPlace[0]) {
    if (HundredsPlace[0] == TensPlace[0] || HundredsPlace[0] == OnesPlace[0]) {
      srand(static_cast<unsigned int>(time(0)));
      random_shuffle(HundredsPlace.begin(), HundredsPlace.end());
    }

    if (TensPlace[0] == OnesPlace[0]) {
      srand(static_cast<unsigned int>(time(0)));
      random_shuffle(TensPlace.begin(), TensPlace.end());
    }
  }
  const string THE_NUMBER = HundredsPlace[0] + TensPlace[0] + OnesPlace[0];

  int guessNumberInt;
  string guessNumberString;

  int hitPlase;

  int hit;
  int byte;

  instruction();

  // mainloop
  while (hit != 3) {
    hit = 0;
    byte = 0;
    hitPlase = 0;

    guessHundredsPlace = (EnterHundredsPlace() + '0');
    guessTensPlace = (EnterTensPlace(guessH) + '0');
    guessOnesPlace = (EnterOnesPlace(guessH, guessT) + '0');

    guessNumberString =
        to_string(guessH) + to_string(guessT) + to_string(guessO);

    if (THE_NUMBER.find(guessHundredsPlace) != string::npos) {
      hit += CheckHitByte(THE_NUMBER, guessHundredsPlace, hitPlase);
      byte += (1 - CheckHitByte(THE_NUMBER, guessHundredsPlace, hitPlase));
    }
    hitPlase++;

    if (THE_NUMBER.find(guessTensPlace) != string::npos) {
      hit += CheckHitByte(THE_NUMBER, guessTensPlace, hitPlase);
      byte += (1 - CheckHitByte(THE_NUMBER, guessTensPlace, hitPlase));
    }
    hitPlase++;

    if (THE_NUMBER.find(guessOnesPlace) != string::npos) {
      hit += CheckHitByte(THE_NUMBER, guessOnesPlace, hitPlase);
      byte += (1 - CheckHitByte(THE_NUMBER, guessOnesPlace, hitPlase));
    }

    cout << guessNumberString << " : " << hit << "HIT " << byte << "BYTE"
         << endl
         << endl;

    game++;
    guessH = 0;
    guessT = 0;
  }

  cout << "\nNice! Number is " << THE_NUMBER << "!!";

  return 0;
}

void instruction() {
  cout << "HIT : Numbers and positions are the same." << endl;
  cout << "BYTE : Positions are different, but numbers are included." << endl;

  cout << "\nLet's guess the number of 3 digits!\n\n";
}

int EnterHundredsPlace() {
  int hTemp;

  cout << "Enter your guess of hundreds place : ";
  cin >> hTemp;
  while (hTemp - 10 >= 0) {
    cout << "\nPlease enter a single-digit number\n";
    cout << "Enter your guess of hundreds place : ";
    cin >> hTemp;
  }
  guessH = hTemp;

  return hTemp;
}

int EnterTensPlace(int not1) {
  int tTemp;

  cout << "Enter your guess of tens place : ";
  cin >> tTemp;
  while (tTemp - 10 >= 0 || tTemp == not1) {
    if (tTemp - 10 >= 0) {
      cout << "\nPlease enter a single-digit number\n";
      cout << "Enter your guess of tens place : ";
    } else if (tTemp == not1) {
      cout << "\nThis number is used.\n";
      cout << "Enter your guess of tens place : ";
    }
    cin >> tTemp;
  }
  guessT = tTemp;

  return tTemp;
}

int EnterOnesPlace(int not1, int not2) {
  int oTemp;

  cout << "Enter your guess of ones place : ";
  cin >> oTemp;
  while (oTemp - 10 >= 0 || oTemp == not1 || oTemp == not2) {
    if (oTemp - 10 >= 0) {
      cout << "\nPlease enter a single-digit number\n";
      cout << "Enter your guess of ones place : ";
    } else if (oTemp == not1 || oTemp == not2) {
      cout << "\nThis number is used.\n";
      cout << "Enter your guess of ones place : ";
    }
    cin >> oTemp;
  }
  guessO = oTemp;

  return oTemp;
}

int CheckHitByte(string THE_NUMBER, char guessPlace, int hitPlase) {
  bool getHit = false;
  int hit = 0;

  for (int i = 0; i < THE_NUMBER.length(); ++i) {
    if (THE_NUMBER[i] == guessPlace && i == hitPlase) {
      getHit = true;
    }
  }
  if (getHit == false) {
    return hit;
  } else {
    return ++hit;
  }
}