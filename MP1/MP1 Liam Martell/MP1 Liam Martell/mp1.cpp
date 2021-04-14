/*DATE
  Liam Martell
  The function of this program is to assist in the sale of donuts by 
  calculating the price of user inputted donuts, then displaying the change
  */

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	
		//Initial variable declarations
		const double REG_PRICE = 0.75;			//Price of a regular donut
		const double REG_DOZEN = 7.99;			//Price for a dozen regular
		const double FANCY_PRICE = 0.85;		//Price of a fancy donut
		const double FANCY_DOZEN = 8.49;		//Price for a dozen fancy
		const double TAX = 0.075;				//Tax value
		int reg = 0;							//# of reg donuts
		int fancy = 0;							//# of fancy donuts
		double total = 0;						//total price after tax

		//Asking customer for number of donuts
		cout << "Number of regular donuts ordered: ";
		cin >> reg;
		cout << "Number of fancy donuts ordered: ";
		cin >> fancy;

		//calculating price of donuts
		if (reg < 12 && fancy < 12)					//less than a dozen of each
		{
			double regPrice = (reg * REG_PRICE);
			double fancyPrice = (fancy * FANCY_PRICE);
			double donutPrice = (regPrice + fancyPrice);
			total = donutPrice + (donutPrice * TAX);
		}
		else if (reg >= 12 && fancy < 12)			//more than a dozen regular and less than a dozen fancy
		{
			int regMod = reg % 12;
			int regDozen = (reg - regMod) / 12;
			double regPrice = (regDozen * REG_DOZEN) + (regMod * REG_PRICE);
			double fancyPrice = (fancy * FANCY_PRICE);
			double donutPrice = (regPrice + fancyPrice);
			total = donutPrice + (donutPrice * TAX);

		}
		else if (reg < 12 && fancy >= 12)			//less than a dozen regular and more than a dozen fancy
		{
			int fancyMod = fancy % 12;
			int fancyDozen = (fancy - fancyMod) / 12;
			double fancyPrice = (fancyDozen * FANCY_DOZEN) + (fancyMod * FANCY_PRICE);
			double regPrice = (reg * REG_PRICE);
			double donutPrice = (regPrice + fancyPrice);
			total = donutPrice + (donutPrice * TAX);

		}
		else									   //more than a dozen of each
		{
			int regMod = reg % 12;
			int regDozen = (reg - regMod) / 12;
			double regPrice = (regDozen * REG_DOZEN) + (regMod * REG_PRICE);
			int fancyMod = reg % 12;
			int fancyDozen = (fancy - fancyMod) / 12;
			double fancyPrice = (fancyDozen * FANCY_DOZEN) + (fancyMod * FANCY_PRICE);
			double donutPrice = (regPrice + fancyPrice);
			total = donutPrice + (donutPrice * TAX);

		}
		cout << "Customer owes: $" << fixed << setprecision(2) << total;

		//Calculating change variables and prompts
		double paid = 0.00;								//The amount of money the customer pays
		cout << endl << "Customer pays: $";
		cin >> paid;
		double change = paid - total;					//The change owed
		int dollars = 0;								//The number of dollars in change 
		int quarters = 0;								//The number of quarters in change
		int dimes = 0;									//The number of dimes in change
		int nickles = 0;								//The number of nickles in change
		int pennies = 0;								//The number of pennies in change


		//Outputting change; case if change is owed
		if (change >= 0.01)
		{
			cout << "Change owed is $" << change << " - ";
			//While loops increase the change type and subtract the types value until there is no more of that change type owed
			while (change >= 1.00)
			{
				dollars++;
				change = change - 1;
			}

			while (change > .25)
			{
				quarters++;
				change = change - 0.25;
			}
			/*change = change + 0.0025;	*/		//To round up change for dimes
			while (change > 0.09)
			{
				dimes++;
				change = change - 0.10;
			}

			while (change >= 0.05)
			{
				nickles++;
				change = change - 0.05;

			}

			change = change + .005;			//This is in here to force it to round correctly for the pennies

			while (change >= 0.009)
			{

				pennies++;
				change = change - 0.01;

			}



			//Final formatting for the change required for single and double change types
			if (dollars > 1) { cout << dollars << " dollars, "; }
			else if (dollars == 1) { cout << dollars << " dollar, "; }
			if (quarters > 1) { cout << quarters << " quarters, "; }
			else if (quarters == 1) { cout << quarters << " quarter, "; }
			if (dimes > 1) { cout << dimes << " dimes, "; }
			else if (dimes == 1) { cout << dimes << " dime, "; }
			if (nickles > 1) { cout << nickles << " nickles, "; }
			else if (nickles == 1) { cout << nickles << " nickle, "; }
			if (pennies > 1) { cout << pennies << " pennies. " << endl; }
			else if (pennies == 1) { cout << pennies << " penny. " << endl; }

		}
		//Cases for exact change or not enough payment
		else if (change < 0) { cout << "Need more money" << endl; cout << change << endl << paid << endl << total; }
		else { cout << endl << "Exact payment recieved - no change owed." << endl; }
	

}
