#include <iostream>
#include <locale>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
using namespace std;

//Functions
int rng(int);
void generateOTP();
//Global Variables

//User's encryption/decryption decision string
string d;
//Secret phrase
char e[1000];
//Encrypted Message
char f[1000];
//Locale object
locale l;
//Character array
char c[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
//Create input and output file streams
ofstream ofs;
ifstream ifs;

char loopController = 'Y';

//Main
int main()
{
    while(loopController=='Y' || loopController=='y')
    {
        //Create a file named otp.dat
        ofs.open("otp.dat");
        //Error typically happens from read or write privileges
        if(ofs.fail())
        {
            cout << "Unable to open the one time pad.";
            exit(1);
        }

        //Use time as a seed for the rng
        srand(time(NULL));

        generateOTP();

        cout << "Would you like to \"Encrypt\" or \"Decrypt\"?: ", cin >> d, cout << endl;


        //Loop through the d string and turn it into uppercase
        for (int i = 0; i < d.length(); i++)
        {
            d[i] = toupper(d[i],l);
        }
        //Trick to clear cin's error flags 
        cin.seekg(0,ios::end);
        cin.clear();


        
        //If the user types in encrypt
        if(d == "ENCRYPT")
        {
            cout << "Type in what you want to encrypt on the following line. . .\n";
            
            //Receive input
            cin.getline(e, 1000);
            //Get length
            int length = strlen(e);
            //Open the otp
            ifs.open("otp.dat");
            if(ifs.fail())
            {
                cout << "There was an error opening the file.";
                exit(1);
            }
            //Glean rotation key from the otpKey
            char otpKey;
            int rotationKey[length];
            for(int i = 0; i < length; i++)
            {
                ifs >> otpKey;
                for(int j = 0; j < 27; j++)
                {
                    if(otpKey == c[j])
                    {
                        cout << i << " - " << otpKey << " : " << j << endl;
                        rotationKey[i] = j;
                    }
                }
            }

            cout << "-------------" << endl;

            //Glean current key
            int currentKey[length];
            for(int i = 0; i < length; i++)
            {
                for(int j = 0; j < 27; j++)
                {
                    if(e[i] == c[j])
                    {
                        cout << i << " - " << e[i] << " : " << j << endl;
                        currentKey[i] = j;
                    }
                }
            }

            cout << "-------------" << endl;

            //Create final string for encrypted message

            for(int i = 0; i < length; i++)
            {
                int newKey = currentKey[i] + rotationKey[i];
                newKey = newKey % 27;
                cout << i << " - " << c[newKey] << endl;
            }

        }
        //If the user types in decrypt
        if(d == "DECRYPT")
        {
            cout << "Hey";
        }

        cout << "Would you like to continue? (y/n): ", cin >> loopController, cout << endl;
        //Close the file streams
        ofs.close();
        ifs.close();
    }

    return 0;
}



//Function that generates a random number
int rng(int max)
{
    int randomN = 1 + rand() % max;
    return randomN;
}

void generateOTP()
{
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
}
