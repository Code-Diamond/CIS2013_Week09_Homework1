//Standard input output stream
#include <iostream>
//Locale for toupper
#include <locale>
//In case string not built in
#include <string>
//For input and output streams
#include <fstream>
//For using time as a seed
#include <time.h>
//Contains libraries for rng
#include <cstdlib>

using namespace std;

//Functions
int rng(int);

// c  l  d

//Main
int main()
{
    //Character array
    char c[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};

    //Create input and output file streams
    ofstream ofs;
    ifstream ifs;
    //Create a file named otp.dat
    ofs.open("otp.dat");
    //Error typically happens from read or write priveleges
    if(ofs.fail())
    {
        cout << "Unable to open the one time pad.";
        exit(1);
    }

    //Use time as a seed for the rng
    srand(time(NULL));

    //Generates the One Time Pad file
    //Ten lines
    for(int i = 0; i < 10; i++)
    {
        //Fifty Characters
        for(int j = 0; j < 50; j++)
        {
            //Write a random character to the file
            ofs << c[rng(27)-1];
        }
        ofs << endl;
    }
    string d;
    cout << "Would you like to \"Encrypt\" or \"Decrypt\"?: ", cin >> d, cout << endl;

    //Create a locale object
    locale l;
    //Loop through the d string and turn it into uppercase
    for (int i = 0; i < d.length(); i++)
    {
        d[i] = toupper(d[i],l);
    }

    string e;

    //If the user types in encrypt
    if(d == "ENCRYPT")
    {
        cout << "Type in what you want to encrypt on the following line. . .\n", cin >> e;
        //Open the otp
        ifs.open("otp.dat");
        if(ifs.fail())
        {
            cout << "There was an error opening the file.";
            exit(1);
        }
        char currentKey;

        for(int i = 0; i < e.length(); i++)
        {
            ifs >> currentKey;
            for(int j = 0; j < 27; j++)
            {
                if(currentKey == c[j])
                {
                    cout << currentKey << " : " << j << endl;
                }
            }

        }
    }
    //If the user types in decrypt
    if(d == "DECRYPT")
    {
        cout << "Hey";
    }
  
    return 0;
}

//Function that generates a random number
int rng(int max)
{
    int randomN = 1 + rand() % max;
    return randomN;
}
