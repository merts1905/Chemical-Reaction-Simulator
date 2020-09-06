#include<iostream>/////for displaying the output
#include<algorithm>////for build in algo functions
#include<map>//////for mapping the data on values
#include<string>///for string usage
#include<vector>///for array implementation
#include<sstream>///for streaming the values
using namespace std;////name space
///////////////////////////////////////////////////////////////////////////////////////
map<char, int> elementVal = { { 'H', 1 },////given values hydrogen with 1 valency
						    { 'O', 2 },////oxygen with 2 valency
						    { 'K', 3 },///potassium with 3 valency
						    { 'C', 4 } };///carbon with 4 valency
/////////////////////////////////////////////////////////////////////////////////////////////

class Stability////class
{
private:///private members
	int element[5];///element array
	char dataArr[5];////data array
	vector< pair<char, int>> ValueOfElement;///vector for saving value

public:
	/////////////////////////////////////////////////////////////////////
	Stability()/////////////constructor//////////////////////////////////
	{
		dataArr[0] = ' ';//setting the array
		dataArr[1] = 'H';//setting the array
		dataArr[2] = 'O';//setting the array
		dataArr[3] = 'K';//setting the array
		dataArr[4] = 'C';//setting the array
		//dataArr[5] = 'H';

	}
	///////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	//////member function////////////////////////////////////////
	void showData()//////////////////////////////////////////////Displaying the Data on the Console
	{
		int saveElem[5] = { 0 };//int array
		map< string, vector<string> > doubleAttached;/////map to store and map the values
		int NonhydrogenVal = ValueOfElement.size();////getting size of array

		if (NonhydrogenVal == 0)///checking the size
		{
			cout << "H1 ---> H2";////displaying the msg
			cout << endl << "H2--->H1";/////showing the data
			cout << endl << "Linear value : H2" << endl;//showing the data
			return;////returning to end of the function
		}
		for (int jj = 1; jj <= 4; jj++)///loop
		{
			for (int ii = 1; ii <= element[jj]; ii++)//loop
			{
				string save; ///string to save the data
				save = save + dataArr[jj];/////adding the data
				save = save + to_string(ii); //adding the data
				doubleAttached[save] = vector<string>();   //adding the data              
			}
		}

		string save, saveLast, saveNext;///variables
		vector<string> sValueOfElement(NonhydrogenVal); ////vector array of non hydrogen values             
		for (int ii = 0; ii < NonhydrogenVal; ii++)///loop
		{
			char itm = ValueOfElement[ii].first;///getting the 1st value
			int del = elementVal[itm];///////getting that element
			saveElem[del] = saveElem[del] + 1;///saving the element
			sValueOfElement[ii] = sValueOfElement[ii] + itm;///adding the new bonded elemment
			sValueOfElement[ii] = sValueOfElement[ii] + to_string(saveElem[del]);////saving its elements
		}

		for (int ii = 0; ii < NonhydrogenVal; ii++)//loop
		{
			int previousLink = (ii + NonhydrogenVal - 1) % NonhydrogenVal;/////finding the prevoius alocated links
			char ele = ValueOfElement[ii].first;///////getting the first value
			int hydrogenVal = elementVal[ele] - ValueOfElement[previousLink].second - ValueOfElement[ii].second;/////subtracting the value
			int newLink = (ii + 1) % NonhydrogenVal;////finding the new link 
			save = sValueOfElement[ii];///saving the data
			saveLast = sValueOfElement[previousLink];////saving previous link element
			saveNext = sValueOfElement[newLink];////saving new link element

			for (int ii = 1; ii <= hydrogenVal; ii++)///loop
			{
				string simple = "H";///staring from H element
				saveElem[1] = saveElem[1] + 1;/////saving the data 
				simple = simple + to_string(saveElem[1]);/////concatinating with the string
				doubleAttached[save].push_back(simple);///adding the data
				doubleAttached[simple].push_back(save);//adding the data
			}
			for (int ii = 1; ii <= ValueOfElement[ii].second; ii++)//loop
			{
				doubleAttached[save].push_back(saveNext);//adding the data to map
			}
			for (int ii = 1; ii <= ValueOfElement[previousLink].second; ii++)////loop
			{
				doubleAttached[save].push_back(saveLast);//adding the data
			}
		}

		for (auto elemnt : doubleAttached)///looop
		{
			cout << elemnt.first << " ---> ";///dislplaying the msg
			for (auto secondValu : elemnt.second)///innner element to save the bounded elements
			{
				cout << secondValu << ' ';////displaying the data
			}
			cout << '\n';
		}

	}/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////
	void DivideString(string value)//////////////////////////public function to sow the bound between elements
	{
		int integer;///local variable
		char kind;///local variable
		stringstream dataStream(value);///stream variable
		for (int i = 0; i <= 4; i++)///loop
			element[i] = 0;//setting the values

		while (dataStream >> integer >> kind)/////loop for checking the values
			element[elementVal[kind]] = element[elementVal[kind]] + integer;////saving the values
	}//////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	

	////////////////////////////////////////////////////////////////////
	bool checkelementVal()///public function to check the links////////////// 
	{
		ValueOfElement.clear();////clearing the data
		int hydrogenVal = element[1]; ///local var                         
		int NonhydrogenVal = element[2];//local var
		NonhydrogenVal = NonhydrogenVal + element[3];///saving non hydrogen valencies
		NonhydrogenVal = NonhydrogenVal + element[4]; /// saving non hydrogen valencies
		int relation = 2 * element[2];///variable to hold total relations
		relation = relation + 3 * element[3];///calculaating relations
		relation=relation+4 * element[4];//saving relations
		if (NonhydrogenVal == 1)   ///checking the relations                         
		{
			ValueOfElement.push_back({ dataArr[relation], relation });/////saving the data
			return (hydrogenVal == relation);///returning the value
		}
		else if (NonhydrogenVal == 0)  //if non hydrogen are zero                      
		{
			
			return (hydrogenVal == 2);////so returning the hydrogen valency
		}
		else  //////otherwise                                       
		{
			relation =relation- hydrogenVal; /////subtracting hydrogen relation from the total relations                           
			if ((relation % 2) == 1)////checking remainders
			{
				return false;///returning 
			}
			relation = relation / 2;////dividing the relation as it makes a link
			relation =relation- (NonhydrogenVal - 1);  ////subtracting non hydrogen relation from the total relations                   
			if (relation < 0)//checking remaining relations
			{
				return false;////returning 
			}
			int z = 4;///local variable
			while (z>=2)///loop
			{
				for (int i = 1; i <= element[z]; i++)
				{
					ValueOfElement.push_back({ dataArr[z], 1 });///saving the data 
				}
				z--;///decrementing the value of z
			}
			ValueOfElement[NonhydrogenVal - 1].second = 0; ////setting non hydrogen second value to zero               

			for (int ii = 0; ii < NonhydrogenVal; ii++)///loop
			{
				if (relation <= 0)//checking for relation
				{
					break;///breaking the loop
				}
				int previousLink = (ii + NonhydrogenVal - 1) % NonhydrogenVal;///////finding the links without non hydrogen values
				int newLink = (ii + 1) % NonhydrogenVal;////saving new links required
				int k = elementVal[ValueOfElement[ii].first];///getting the 1st value
				k = k - ValueOfElement[ii].second;///subtracting 2nd value
				k = k -ValueOfElement[previousLink].second;///subtracting 2nd values of previous link
				int y = elementVal[ValueOfElement[newLink].first];///getting 1st value
				y = y - ValueOfElement[ii].second;///subtracting 2nd value of link
				y = y - ValueOfElement[newLink].second;/////subtracting 2nd value of link
				int currentValue = min(k,y);///finding the minimum and saving it
				int added = min(relation, currentValue);///again finding the minimum between previous and current
				ValueOfElement[ii].second = ValueOfElement[ii].second + added;////setting 2nd value with the new upcoming link
				relation = relation- added;////subtracting from total relation due to make of new relation
			}
			if (relation > 0)////checking relation
			{
				return false;//returning
			}
		}
		return true;///returning
	}
	////////////////////////////////////////
	//////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////




};////end of classs

void main()
{
	
	string d = "4H 1O 1C";///input string
	Stability s;/////making object of class
		cout << "\nTest value: " << d << '\n';///showing the test value
		s.DivideString(d);////calling the class member function
		bool ok = s.checkelementVal();////calling the member function and getting a value
		if (ok)///checking the value
		{
			s.showData();///showing the bounds between given input data
		}
		else
			cout << "Impossible";///showing the output
		cout << "\n --------------------\n";
		/////////////////////////////////////////////////
		///////////////////////////////////////////////

		d = "2K 1O";///input string
		cout << "\nTest value: " << d << '\n';///showing the test value
		s.DivideString(d);////calling the class member function
		ok = s.checkelementVal();////calling the member function and getting a value
		if (ok)///checking the value
		{
			s.showData();///showing the bounds between given input data
		}
		else
			cout << "Impossible";///showing the output
		cout << "\n --------------------\n";
		/////////////////////////////////////////////////
		///////////////////////////////////////////////

		d = "2K 2O";///input string
		cout << "\nTest value: " << d << '\n';///showing the test value
		s.DivideString(d);////calling the class member function
		ok = s.checkelementVal();////calling the member function and getting a value
		if (ok)///checking the value
		{
			s.showData();///showing the bounds between given input data
		}
		else
			cout << "Impossible";///showing the output
		cout << "\n --------------------\n";
		/////////////////////////////////////////////////
		///////////////////////////////////////////////

		d = "1K 1O";///input string
		cout << "\nTest value: " << d << '\n';///showing the test value
		s.DivideString(d);////calling the class member function
		ok = s.checkelementVal();////calling the member function and getting a value
		if (ok)///checking the value
		{
			s.showData();///showing the bounds between given input data
		}
		else
			cout << "Impossible";///showing the output
		cout << "\n --------------------\n";


	
}
