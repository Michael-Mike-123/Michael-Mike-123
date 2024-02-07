#include <iostream>
#include <climits> // for INT_MAX limits

using namespace std;

int main()
{
    //Using dynamic array, because can't put a variable with no value to determine array size
    //And the size is not declared at compile stage, even if you type smth like: arrayLimit = 4;
    int arrayLimit;
    int* numArray = new int[arrayLimit];

    int maxElement = INT_MIN;
    int minElement = INT_MAX;
    bool isAssigned = false;

    while(!isAssigned){
        cout << "Please enter an array size: ";
        cin >> arrayLimit;
        cout << endl;

        //Prevents user from entering anything other than int
        while (cin.fail())
        {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "You can only enter numbers!" << endl;
            cout << "Enter an array size: ";
            cin >> arrayLimit;
        }

        //Prevents user from entering a value, that is below or is a 0 (it can't be an array size)
        if(arrayLimit <= 0){
            cout << "Try again!";
            cout << endl;
            isAssigned = false;
        } else{
            isAssigned = true;
        }

        cout << endl;
    }

    for(int j = 0; j < arrayLimit; j++){
        cout << "Array element " << j << " = ";
        cin >> numArray[j];
        cout << endl;
    }

    //Checking a max value of an array and min
    for(int i = 0; i < arrayLimit; i++){
        //Checks for the highest element in array
        if(numArray[i] > maxElement){
            maxElement = numArray[i];
        }

        //Checks for the lowest
        if(numArray[i] < minElement){
            minElement = numArray[i];
        }
    }

    cout << "Max element of an array: " << maxElement << endl;
    cout << "Min element of an array: " << minElement << endl;

    delete[] numArray; //recovering allocated memory after using dynamic array

    return 0;
}

//CREDITS
//User input custom array size by Daniel: https://stackoverflow.com/questions/28625465/c-creating-an-array-with-a-size-entered-by-the-user
//Char input in int detector by Ryan Hallberg: https://stackoverflow.com/questions/11523569/how-can-i-avoid-char-input-for-an-int-variable
