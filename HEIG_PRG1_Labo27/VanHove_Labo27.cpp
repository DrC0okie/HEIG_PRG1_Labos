// File:        VanHove_Labo26.cpp
// Author:      Timothee Van Hove
// Date:        03.12.2021
// Description: Reads a text file and encrypt it with RSA
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;
const int MASK = 0x000000ff;

const string ORIGINAL_FILE = "in.txt", ENCRYPTED_FILE = "encrypted.txt",
             DECRYPTED_FILE = "decrypted.txt";

const int MIN = 0, MAX_INT32 = numeric_limits<int32_t>::max(),
          VERIF_ITERATIONS = 10, MSG_WIDTH = 14, TEST_WIDTH = 2;

string readFile(string fileName);
bool writeFile(string fileName, string text);
int encode3Bytes(const unsigned char bArray[]);
string decode3Bytes(int bInt);
string encrypt(string text, int pubicValue, int keySize);
string decrypt(string text, int privateValue, int keySize);
int getRandomInt(int min, int max);
int extEuclidean(int a, int b, int &inverse);
int modularExp(long long base, int exp, int mod);
void checkPrimesInput(int &num1, int &num2);
void checkPublicValue(int &num1, int num2, int &inverse);
bool isPrime(int number);
bool streamError(int &num1);
bool primalityTest(int value);
bool inputVerification(int &prime);
bool isInRange(int number, int min, int max);
bool isCoprime(int num1, int num2, int &inverse_e);
bool verification(int publicValue, int privateValue, int keySize);

int main()
{
    int prime_p = 0, prime_q = 0;

    // User message for the input of p and q
    cout << "Enter 2 prime numbers, that once multipled are in range ["
         << MIN << " - " << MAX_INT32 << "] separated by spaces (p q): ";

    // User input stream, range, equality and primality verification for p and q
    checkPrimesInput(prime_p, prime_q);

    int phi = (prime_p - 1) * (prime_q - 1), publicValue_e, inverse_e;

    // User message for the input of the public value
    cout << "Enter a coprime number with " << phi
         << ", but strictly lower (e): ";

    // User input stream, range, and relative primality verification for e
    checkPublicValue(publicValue_e, phi, inverse_e);

    // Calculate the value of the private key for Alice
    int privateValue_d = inverse_e % phi, keySize_n = prime_p * prime_q;

    // Display the public & private key values
    cout << endl
         << "Public key : " << publicValue_e << ", "
         << keySize_n << endl
         << "Private key : " << privateValue_d << ", "
         << keySize_n << endl;

    //--------------------------------------------------------------

    string src = readFile(ORIGINAL_FILE), outText;

    string dest, encryptedStr;
    uint32_t tmp = 0;

    for (size_t i = 0; i < src.size() - 3; i += 3)
    {
        // Decompose original text to an int
        tmp = tmp | src.at(i + 2);
        tmp = tmp << 8;
        tmp = tmp | src.at(i + 1);
        tmp = tmp << 8;
        tmp = tmp | src.at(i);

        //  Encrypt the int
        uint32_t encrypted = modularExp(tmp, publicValue_e, keySize_n);

        //  retransform the int into string for the encrypted text
        encryptedStr.push_back((encrypted & MASK));
        encrypted = encrypted >> 8;
        encryptedStr.push_back((encrypted & MASK));
        encrypted = encrypted >> 8;
        encryptedStr.push_back((encrypted & MASK));
    }

    writeFile(ENCRYPTED_FILE, encryptedStr);
    src.clear();
    encryptedStr.clear();
        tmp = 0;

    // Retranform into an int for decryption
    encryptedStr = readFile(ENCRYPTED_FILE);

    for (size_t i = 0; i < encryptedStr.size(); i++)
    {
        tmp = tmp | (encryptedStr[i+2] & MASK);
        tmp = tmp << 8;
        tmp = tmp | (encryptedStr[i+1] & MASK);
        tmp = tmp << 8;
        tmp = tmp | (encryptedStr[i] & MASK);

        // decryption
        uint32_t decrypted = modularExp(tmp, privateValue_d, keySize_n);

        // Retransform into a string
        dest.push_back(decrypted & MASK);
        decrypted = decrypted >> 8;

        dest.push_back(decrypted & MASK);
        decrypted = decrypted >> 8;

        dest.push_back(decrypted & MASK);

        cout << dest << endl;
    }
    writeFile(DECRYPTED_FILE, dest);

    // string inText = readFile(ORIGINAL_FILE), outText;

    // if (inText != "")
    //     outText = encrypt(inText, publicValue_e, keySize_n);
    // else
    //     cout << "Error loading the file : " << ORIGINAL_FILE << endl;

    // writeFile(ENCRYPTED_FILE, outText);

    // inText.clear();
    // outText.clear();

    // inText = readFile(ENCRYPTED_FILE);
    // if (inText != "")
    //     outText = decrypt(inText,privateValue_d,keySize_n);
    // else
    //     cout << "Error loading the file : " << ENCRYPTED_FILE << endl;

    // writeFile(DECRYPTED_FILE, outText);
}

string readFile(string fileName)
{
    string tmp;
    ifstream is(fileName, ifstream::binary);
    if (is)
    {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char *buffer = new char[length];

        cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read(buffer, length);

        if (is)
            cout << "all characters read successfully." << endl;
        else
            cout << "error: only " << is.gcount() << " could be read";
        is.close();
        tmp = buffer;
    }
    return tmp;
}

bool writeFile(string fileName, string text)
{
    ofstream myfile(fileName);
    if (myfile.is_open())
    {
        cout << "Writing " << text.length() << " characters... ";
        myfile << text;
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
        return false;
    }
    cout << "all characters written successfully." << endl;
    return true;
}

int encode3Bytes(const unsigned char bArray[])
{
    uint32_t tmp = 0;
    tmp = tmp | bArray[2];
    tmp = tmp << 8;
    tmp = tmp | bArray[1];
    tmp = tmp << 8;
    tmp = tmp | bArray[0];

    return tmp;
}

string decode3Bytes(int bInt)
{
    string decodedInt;
    decodedInt.resize(3);
    decodedInt.at(0) = bInt & MASK;
    bInt = bInt >> 8;
    decodedInt.at(1) = bInt & MASK;
    bInt = bInt >> 8;
    decodedInt.at(2) = bInt & MASK;

    return decodedInt;
}

string encrypt(string text, int publicValue, int keySize)
{
    string encryptedPackets;
    unsigned char bArray[3] = {0, 0, 0};

    for (size_t i = 0; i < text.size() - 3; i += 3)
    {
        bArray[0] = text.at(i);
        bArray[1] = text.at(i + 1);
        bArray[2] = text.at(i + 2);
        int packet = encode3Bytes(bArray);

        // encrypt the packet and put it in output string
        encryptedPackets.push_back(packet);
    }
    return encryptedPackets;
}

// string decrypt(string text, int privateValue, int keySize)
// {
//     string decryptedPackets;
//     unsigned char bArray[3] = {0, 0, 0};

//     for (size_t i = 0; i < text.size() - 3; i += 3)
//     {
//         int decryptedPacket = modularExp(stoi(text.at(i)), privateValue, keySize);

//         bArray[0] = text.at(i);
//         cout << (int)bArray[0];
//         bArray[1] = text.at(i + 1);
//         bArray[2] = text.at(i + 2);
//         int encryptedPacket = encode3Bytes(bArray);

//         decryptedPackets = decode3Bytes(decryptedPacket);
//         cout << decryptedPackets << endl;
//         // encrypt the packet and put it in output string
//     }
//     return decryptedPackets;
// }

/** @brief Verification that for 10 random messages, the algorithm can encrypt,
 *  decrypt and get the original message
 * @param publicValue The public value in the public key of Alice
 * @param privateValue The private value in the private key of Alice
 * @param keySize The key size (same in the public and private key)
 * @return true if the verification is successful, false if not*/
bool verification(int publicValue, int privateValue, int keySize)
{
    cout << endl
         << "Verifying with " << VERIF_ITERATIONS
         << " random messages, distributed on [1 - "
         << keySize - 1 << "]" << endl;

    for (int i = 1; i <= VERIF_ITERATIONS; i++)
    {
        // Get a unique message
        int originalMessage = getRandomInt(1, keySize - 1);

        // Message encryption
        int encryptedMsg = modularExp(originalMessage, publicValue, keySize);

        // Message decryption
        int decryptedMsg = modularExp(encryptedMsg, privateValue, keySize);

        // Outputs the result of the current test
        cout << "Test " << setw(TEST_WIDTH) << left << i
             << " Message: " << setw(MSG_WIDTH) << left << originalMessage
             << " Encrypted message: " << setw(MSG_WIDTH) << left << encryptedMsg
             << " Decrypted message: " << decryptedMsg << endl;

        // Automatic verification
        if (decryptedMsg != originalMessage)
        {
            cout << "For message " << originalMessage << ", decryption failed";
            return false;
        }
    }
    return true;
}

/** @brief Checks if the 2 inputs are integers, in range, not equal and prime
 * @param in1 The 1st user input (p). Used as output it the check succeeds
 * @param in2 The 2nd user input (q). Used as output it the check succeeds*/
void checkPrimesInput(int &in1, int &in2)
{
    while (true)
    {
        // stream input error verification
        if (streamError(in1) || streamError(in2))
            continue;

        // range verification
        if (!isInRange(in1, MIN, MAX_INT32) || !isInRange(in2, MIN, MAX_INT32 / in1))
            continue;

        // Equality verification
        if (in1 == in2)
        {
            cout << "The numbers must be different. Retry (p, q): ";
            continue;
        }

        // primality verification
        if (!isPrime(in1) || !isPrime(in2))
            continue;
        else
            break;
    }
}

/** @brief Checks if the input is an integer, in range, and coprime with phi
 * @param input The user input (e). Used as output if the check succeeds
 * @param phi The value used for the coprime verification (p-1 * p-1)
 * @param inverse The inverse of e used as output*/
void checkPublicValue(int &input, int phi, int &inverse)
{
    while (true)
    {
        // stream input error verification
        if (streamError(input))
            continue;

        // range verification
        if (!isInRange(input, MIN + 1, phi - 1))
            continue;

        // Relative primality verification & ouput inverse
        if (!isCoprime(phi, input, inverse))
            continue;
        else
            break;
    }
}

/** @brief Function that checks if the input stream is in error
 * @param input The user input (used as output)
 * @return true if an error is detected, false if not*/
bool streamError(int &input)
{
    if (!(cin >> input))
    {
        cout << "Input stream error! Please retry with the good input type : ";
        cin.clear();
        cin.ignore(MAX_INT32, '\n');
        return true;
    }
    return false;
}

/** @brief Checks if the number is prime
 * @param number The number to test the primality
 * @return true if the number is probably prime, false if not*/
bool isPrime(int number)
{
    if (!primalityTest(number))
    {
        cout << number << " is not prime, please retry : ";
        return false;
    }
    return true;
}

/** @brief Checks if the 2 numbers are coprime using the extEuclidean algorithm
 * @details num1 must always be > num2
 * @param num1 The first number to test
 * @param num2  The second number to test
 * @param inverse Inverse of num2 % num1 (used as output)
 * @return true if num1 and num2 are coprime, false if not*/
bool isCoprime(int num1, int num2, int &inverse)
{
    if (extEuclidean(num1, num2, inverse) != 1)
    {
        cout << num1 << " is not coprime with " << num2 << ", please retry: ";
        return false;
    }
    return true;
}

/** @brief Checks if the number is whithin the given range
 * @param number value to test
 * @param min lowest value of the range
 * @param max highest value of the range
 * @return true if the number is within the range, false if not*/
bool isInRange(int number, int min, int max)
{
    if (number < min || number > max)
    {
        cout << "The number " << number << " must be in range [" << min
             << " - " << max << "]. Please retry: ";
        return false;
    }
    return true;
}

/** @brief Primality test based on Fermat primality test
 * and Solovay–Strassen primality test
 * @details Run 10 times the tests with random numbers to decrease the chances
 * of getting an Euler–Jacobi pseudoprime
 * @param primeTest The number to test
 * @return true if primeTest is probably prime, false if not*/
bool primalityTest(int primeTest)
{
    // Elimination of simple results
    if (primeTest < 2)
    { // 0, 1 are not prime
        return false;
    }
    else if (primeTest == 2)
    { // 2 is prime
        return true;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            // Get a random number
            int random = getRandomInt(2, primeTest - 1), exp = primeTest - 1;

            // Fermat primality test
            if (modularExp(random, exp, primeTest) != 1)
                return false;

            // Solovay–Strassen primality test
            int modExp = 1;
            while (exp % 2 == 0 && modExp == 1)
            {
                exp /= 2;
                modExp = modularExp(random, exp, primeTest);
                if (modExp != 1 && modExp != primeTest - 1)
                    return false;
            }
        }
    }
    return true;
}

/** @brief Extended Euclidean algorithm that computes the GCD and
 * the multiplicative inverse of num2 % num1 if they are coprime
 * @param num1 The first number
 * @param num2 The second number
 * @param inverse Inverse of num2 % num1 if they are coprime (used as output)
 * @return The gcd of num1 and num2 */
int extEuclidean(int num1, int num2, int &inverse)
{
    int gcd = num1, new_gcd = num2, d = 0, new_d = 1;

    while (new_gcd != 0)
    {
        // Get the quotient from old gcd / new gcd
        int quotient = gcd / new_gcd;

        // Save temp values to use it later
        int temp_gcd = gcd;
        int temp_d = d;

        // Update the 2 values
        gcd = new_gcd;
        d = new_d;

        // Get the gcd and the temp. muliplicative inverse
        new_gcd = temp_gcd - quotient * new_gcd;
        new_d = temp_d - quotient * new_d;
    }
    // Add a to the temp muliplicative inverse if it's < 0
    if (d < 0)
        d += num1;

    inverse = d;
    return gcd;
}

/** @brief Get a random Int number in specified range
 * @param min the lower boud of the range
 * @param max the upper boud of the range
 * @return the random integer*/
int getRandomInt(int min, int max)
{
    static random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distr(min, max);
    return distr(generator);
}

/** @brief Modular exponentiation
 * @details The base is a long long type to avoid overflows
 * @param base The base
 * @param exp  The exponent
 * @param mod The modulus
 * @return The result of modular exponentiation */
int modularExp(long long base, int exp, int mod)
{
    int result = 1;

    while (exp > 0)
    {
        if (!(exp % 2))
        { // Exponent is even
            base = base * base % mod;
            exp /= 2;
        }
        else
        { // Exponent is odd
            result = result * base % mod;
            exp--;
        }
    }
    return result;
}