#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool isValidCrCardNum(string cardNum);    //check if the number of the card is valid or not
void appendChkDigit(string cardNum_NoLastDigit);  //put the last digit, based on the given instructions from the exercise


int main()
{
	bool ok = false;
	string cardNum, cardNum_NoLastDigit, answer;
	cout << "Please give the number of your card to check if it is VALID" << endl;
	getline(cin, cardNum, '\n');


	ok = isValidCrCardNum(cardNum);


	cout << "\nPlease give the number of your card without the last digit. The last digit will be calculated and completed from the function" << endl;
	getline(cin, cardNum_NoLastDigit, '\n');

	appendChkDigit(cardNum_NoLastDigit);


	return 0;
}

bool isValidCrCardNum(string cardNum)
{
	istringstream ssin;  //create a string stream to store the value from input of user

	bool multiplicationCheck = true; //use this bool variable to choose whether it will multiple with 2 or not
	int sizeOfString, sumOfTheCard = 0, moduleCheck;
	long long int numFromCard;   //use long long int, because the user will type 12-16 digits of number. So, it has fit all in one variable
	char checkTheString; //use the char variable, to check if the given input from the user, contains anything else besides from digits

	ssin.clear();         // clear the sream, just in any case
	ssin.str(cardNum);   // give to the 'ssin' stream the input number from the string
	ssin >> numFromCard;   // pass the number from the stream to the variable 'numFromCard'


	while (true)
	{
		if (ssin.fail())
		{
			cout << "You put not a number in the beggining" << endl;
			return false;
		}
		else
		{
			ssin >> checkTheString;

			if (ssin.eof())  //if the stream reached to the end of it
			{
				while (numFromCard > 0)
				{
					if (multiplicationCheck == true) //have already set it 'true' because I want the first time go inside this if statement
					{
						sumOfTheCard += (numFromCard % 10);
						multiplicationCheck = false;
					}
					else if (multiplicationCheck == false)
					{
						moduleCheck = 2 * (numFromCard % 10); //multiply by 2 every number that it is at even position in the number

						if ((moduleCheck / 10) == 0)   //if the multiplied by 2 number, gives 0 module, that means it is a single digit number
							sumOfTheCard += moduleCheck;
						else
							sumOfTheCard = sumOfTheCard + (moduleCheck % 10) + (moduleCheck / 10); //else that means it is a double digit number, so I have to add those 2 too

						multiplicationCheck = true;
					}

					numFromCard /= 10;
				}

				cout << "The sum of the card is: " << sumOfTheCard << endl << endl;

				if ((sumOfTheCard % 10) == 0)
				{
					cout << "The sum of the number can be divided exactly with 10" << endl;
					return true;
				}
				else
				{
					cout << "The number can't be divided exactly with 10"<< endl;
					return false;
				}
			}
			else
			{
				cout << "Somewhere inside the string I found character that is not a number" << endl;
				return false;
			}
		}
	}
}



void appendChkDigit(string cardNum_NoLastDigit)
{
	istringstream ssin2; // create a string stream to store the value from input of user. Number it 2,because I used the same name of the variable at the previous-above function (='isValidCrCardNum')

	long long int withoutLastDigit;
	int sizeOfString, i = 1, sumOfTheCardWithoutTheLastDigit = 0, moduleCheck2, roundUp, finalResultNumber;
	int *arrayOfNumbers;	//use a dynamic array to store the numbers of the card, so it will allocate the exact size
	bool multiplicationCheck2 = true, noneCharacter = false;
	char checkTheString2;

	ssin2.str(cardNum_NoLastDigit);						// give to the 'ssin' stream the input number from the string
	sizeOfString = cardNum_NoLastDigit.length();        //keep the size of the string.

	arrayOfNumbers = new int[sizeOfString];				// create an array, with exactly the size of the numbers of the string + 1

	ssin2 >> withoutLastDigit;							// pass the content from the stream to a variable

	while (true)
	{
		if (ssin2.fail())
		{
			cout << "You put not a number in the beggining" << endl;
			break;
		}
		else
		{
			ssin2 >> checkTheString2;

			if (ssin2.eof())
			{
				while (withoutLastDigit > 0)
				{
					if (multiplicationCheck2 == false)
					{
						arrayOfNumbers[sizeOfString - i] = withoutLastDigit % 10;     //store to the righter position-1 of the array, the every righter digit of the whole number. I keep the very last position of the array, for the last digit that will be completed from the function
						i++;                                                          //increase by 1 the variable, so in the next loop it will store the number to the next left position
						multiplicationCheck2 = true;
					}
					else if (multiplicationCheck2 == true)
					{
						moduleCheck2 = 2 * (withoutLastDigit % 10);        //if the statement is true, that means we are at even position, so we have to multiply the number with 2

						if (moduleCheck2 % 10 == 0)                        //the result of the multiplication is a single digit number
						{
							arrayOfNumbers[sizeOfString - i] = moduleCheck2;
							i++;
						}
						else
						{
							arrayOfNumbers[sizeOfString - i] = (moduleCheck2 % 10) + (moduleCheck2 / 10);   //the result of the multiplication is double digit number. We need to add these two, together
							i++;
						}

						multiplicationCheck2 = false;
					}
					withoutLastDigit /= 10;				//now we can remove the last digit, and move to next one
				}
				noneCharacter = true;    // use this variable to check if there is a character or not. If it becomes true, that means every character in the string was number, and not something else
				break;
			}
			else
			{
				cout << "Somewhere inside the string I found character that is not a number" << endl;
				break;
			}
			
		}
		
	}

	if (noneCharacter == true)    //that means the array contains only numbers, and not something else
	{
		for (i = 0; i < sizeOfString; i++)    // find the total sum of the card number, without the last digit
			sumOfTheCardWithoutTheLastDigit += arrayOfNumbers[i];

		cout << "The sum WITHOUT the last digit is: " << sumOfTheCardWithoutTheLastDigit << endl;

		if (sumOfTheCardWithoutTheLastDigit % 10 == 0) // if the sum is already divides exactly with 10, just put the number zero (0), at the end to complete the whole card number
		{
			cout << "The last digit will be the zero (0), because the is already module perfeclty by 10" << endl;
			arrayOfNumbers[sizeOfString] = 0; // put at the last position the number zero (0)
		}
		else
		{
			roundUp = sumOfTheCardWithoutTheLastDigit / 10; // divide the total sum with 10, and assing the result at a variable type of int. That means it's round up the result downwards.
															// e.g. if the total sum is 23, the division will give 2.3, in integer will be 2.

			roundUp++;                                                            // I increase one number up and the multiply it with 10. In that way, if I substract from the 'roundUp' variable the 'sumOfTheCardWithoutTheLastDigit', it will give the apprpriate number that is missing
			roundUp *= 10;                                                        // e.g The total sum is 23. I want to make this number to be moduled exactly with 10, so I will divide it by 10, it will give 2.3, to integer is 2. Increase one, so it's 3. Multiply with 10, so it's 30. Substract from 
			finalResultNumber = roundUp - sumOfTheCardWithoutTheLastDigit;	      // that the sum of the digits without the last digit, the 23 ==> 30-23 = 7. That means the last digit that is missing is 7!!

			cout << "The last digit on the card will be: " << finalResultNumber << endl;
			arrayOfNumbers[sizeOfString] = finalResultNumber;     //store at the end of the array, the digtit that I just found

		}

		cout << "\nThe final card number, with the last digit is: " << cardNum_NoLastDigit << " + " << arrayOfNumbers[sizeOfString] << endl;
	
		delete [] arrayOfNumbers;
	}

}

	