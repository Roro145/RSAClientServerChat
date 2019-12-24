#include "Network.h"
#include <iostream>

#include <math.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;


//Requires: Two integers
//Effects: Returns the Greatest common divisor of the two variables
int gcd(int a, int b);

//Requires: a word that is input by user, two prime numbers for encryption keys
//Effects: Encrypts the given word using RSA encryption
string encryptWordRSA(string inputWord, int prime1, int prime2);


string encryptWordRSA(string inputWord, int prime1, int prime2){
    //Constant used in this function:
    int k = 2;

    //This is the first part of the public key "n"
    double n = prime1 * prime2;

    //In the case of prime numbers phi(n) = (prime1 - 1) * (prime2 - 1)
    double phi = (prime1 - 1) * (prime2 - 1);

    //Generate an integer e such that 1 < e < phi  & gcd (phi, e) = 1 (coprime)
    //E is the public value
    double E = 0;
    //25 attempts to generate a possible integer E, want to ensure that it is randomized
    for(int x = 0; x < 25; x++){
        //CurentRand generates a possible value for E
        int currentRand = rand() % (int)phi + 1;

        if(gcd(phi, currentRand) == 1){
            //E is the second part of our public key
            E = currentRand;
            break;
        }
    }
    if(E == 0){
        cout << "Error could not generate a random E" << endl;
    }

    E = 3;

    //Determines the private key which is stored locally
    
    double privKey = 1/E;
    privKey = fmod(privKey, phi);

    cout << "Keys: " << endl;
    cout << "Private - privKey: " << privKey << endl;
    cout << "Public - E: " << E << " n: " << n << endl;


    vector <int> inputVals;
    for(int x = 0; x < inputWord.size(); x++){
        inputWord[x] = tolower(inputWord[x]);
        //Converts the ASCII values to integer ones
        inputVals.push_back((int)inputWord[x] - 96);
    }

    double c = 0;

    for(int y = 0; y < inputVals.size(); y++){
        c += inputVals[y] * pow(10, inputVals.size() - y -1);
    }

    cout << "Original: " << c << endl;

    double encryptedInt = pow(c, E);
    encryptedInt = fmod(encryptedInt, n);
    
    cout << "ENCRYPTED: ";

    return to_string(encryptedInt);

}

int gcd(int a, int b){
    int upperCheck;
    if(a > b){
        upperCheck = b;
    }
    else{
        upperCheck = a;
    }

    bool gcdFound = false;
    while(!gcdFound){
        if(a % upperCheck == 0 && b % upperCheck == 0){
            gcdFound = true;
        }
        else{
            upperCheck -= 1;
        }
    }
    return upperCheck;
}


int main(){

    string mainWord;
    cout << "Enter the word to encrypt" << endl;
    cin >> mainWord;
    
    string returnval = encryptWordRSA(mainWord, 11, 13);
    cout << returnval << endl;
    
    int size = returnval.length();
    char char_array[size+1];
    
    strcpy(char_array, returnval.c_str());
    
    cout << dataSent("127.0.0.1", 5000, char_array) << "\n";
}
 

