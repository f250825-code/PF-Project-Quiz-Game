#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <ctime>
#include <cstdlib>
#include<cctype>

using namespace std;
//functions 
void menu();
int subject();              //take subjects
int difficulty();           //take diffculty level
int loadQuestions(string &filename, string ques[],
	string A[], string B[], string C[], string D[], char ans[], int MAX); 
void displayQuestion(int total);
void saveScore(string playername, int finalscore);//scores calculations
void Leaderboard();
void reviewWrong(int totalAsked); 
void showlifelines(int &index, int total, int used[]);
void applyswap(int &index, int total, int used[]);
void adminmode();



//variables
int sub, diff;
const int MAX = 30;
string filename; 
string question[MAX];   // stores question 
string optionA[MAX];    // option 
string optionB[MAX];    // option 
string optionC[MAX];    // option 
string optionD[MAX];    // option
char correct[MAX];      // correct
int score = 0;
//for review
char userGiven[10];    // stores user's answers
int askedIndex[10];   // stores which question was asked
//for lifelines
int lifeline_5050 = 0;
int lifeline_skip = 0;
int lifeline_time = 0;
int lifeline_swap = 0;


int main()
{
	int choice;
	while (true)
	{
		menu();
		cin >> choice;
		if (choice == 1)
		{
			cout << "Starting Quiz.....";
			sub = subject();
			diff = difficulty();
			cin.ignore(); // remove newline left by cin in difficulty function
			int total = loadQuestions(filename, question,
				optionA, optionB, optionC, optionD,
				correct, MAX);

			if (total == 0)
				cout << "No question loaded";
			else
				displayQuestion(total);
			score = 0;//so new game cant take score form last game 
		}
		else if (choice == 2)
		{
			cout << "Leaderboard loading....";
			Leaderboard();
		}
		else if (choice == 3)
		{
			adminmode(); 
		}
		else if (choice == 4)
		{
			cout << "Goodbye";
			break;
		}
		else
		{
			cout << "Invalid Choice! Please Enter correct option.\n";
		}

	}
	system("pause");
	return 0;
}
void menu()
{
	cout << "\n==============================\n";
	cout << "      CONSOLE QUIZ GAME       \n";
	cout << "==============================\n";
	cout << "1. Start New Quiz\n";
	cout << "2. View Leaderboard\n";
	cout << "3. Admin Mode\n";          
	cout << "4. Exit\n";      
	cout << "Enter your choice: ";
}


//subject taking function body
int subject() 
{
	int sub;
	           
	cout << "\n*************************\n";
	cout << "Select Subject:\n";
	cout << "1. Science\n";
	cout << "2. Computer\n";
	cout << "3. IQ \n";
	cout << "\n*************************\n";
	
	do {
		cout << "Enter choice: ";
		cin >> sub;

		if (cin.fail())  // to handle characters
		{         
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Numbers only (1-3).\n";
			continue;
		}

		if (sub < 1 || sub > 3) 
		{
			cout << "Invalid subject! Enter again (1-3).\n";
		}

	} while (sub < 1 || sub > 3);

	return sub;
}
//Difficulty taking function body
int difficulty()
{
	int diff;

	cout << "\n*************************\n";
	cout << "Select Difficulty level:\n";
	cout << "1. Easy\n";
	cout << "2. Medium\n";
	cout << "3. Hard\n";
	cout << "*************************\n";

	do {
		cout << "Enter Difficulty: ";
		cin >> diff;

		if (cin.fail()) //checks if any datatype issue or other thim=ngs like that
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Numbers only (1-3).\n";
			continue;
		}

		if (diff < 1 || diff > 3)
		{
			cout << "Invalid subject! Enter again (1-3).\n";
		}

	} while (diff < 1 || diff > 3);

	return diff;
}
int loadQuestions(string &filename, string ques[],
	string A[], string B[], string C[], string D[], char ans[], int MAX)
{
	ifstream fin;
	if (sub == 1) {
		if (diff == 1)
			filename = "science_easy.txt";//chng filname
		else if (diff == 2)
			filename = "science_medium.txt";//chng filename
		else
			filename = "science_hard.txt";//chng filename
	}
	if (sub == 2) {
		if (diff == 1)
			filename = "computer_easy.txt";//chng filname
		else if (diff == 2)
			filename = "computer_medium.txt";//chng filename
		else
			filename = "computer_hard.txt";//chng filename
	}
	if (sub == 3) {
		if (diff == 1)
			filename = "iq_easy.txt";//chng filname
		else if (diff == 2)
			filename = "iq_medium.txt";//chng filename
		else
			filename = "iq_hard.txt";//chng filename
	}
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "File not found!" << endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < MAX; i++)
		{

			getline(fin, ques[i]);
			getline(fin, A[i]);
			getline(fin, B[i]);
			getline(fin, C[i]);
			getline(fin, D[i]);
			fin.get(ans[i]);
			fin.ignore();      //  remove newline
		}
	}
	fin.close();
	return MAX;
}
void displayQuestion(int total)
{
	
	int used[MAX] = { 0 }; //to ensure no repitation
	int  count = 0,streak=0;
	srand(time(0));
	score = 0;
	//lifeline variable intializing with zero for every quiz
	lifeline_5050 = 0;
	lifeline_skip = 0;
	lifeline_time = 0;
	lifeline_swap = 0;

	cout<<"\n You have only 10 sec to answer";
	while (count < 10)
	{
		int index = rand() % total;

		if (used[index] == 1)
			continue;   // already asked

		used[index] = 1;

		cout << "\n------------------------------------\n";
		cout << "Question " << count + 1 << ":\n";
		cout << question[index] << "\n";
		cout << "A) " << optionA[index] << endl;
		cout << "B) " << optionB[index] << endl;
		cout << "C) " << optionC[index] << endl;
		cout << "D) " << optionD[index] << endl;
		count++;
		char userAns;
		cout << "Your Answer (A/B/C/D) OR Press L for Lifelines: ";
		time_t tstart = time(0);
		cin >> userAns;

		/* ---------- LIFELINE TRIGGER ---------- */
		if (userAns == 'L' || userAns == 'l')
		{
			showlifelines(index, total, used);

			cout << "Enter your Answer (A/B/C/D): ";
			//timer
			time_t tstart2 = time(0);
			cin >> userAns;
			time_t tfinish2 = time(0);

			time_t timetaken = difftime(tfinish2, tstart2);

			if (lifeline_time == 1)
			{
				if (timetaken > 20)
				{
					cout << "Time Limit Exceeded Even After Extension!\n";
					count++;
					continue;
				}
			}
			else
			{
				if (timetaken > 10)
				{
					cout << "Time Limit Exceeded!\n";
					count++;
					continue;
				}
			}
		}
		else
		{
			time_t tfinish = time(0);
			time_t timetaken = difftime(tfinish, tstart);

			if (lifeline_time == 1)
			{
				if (timetaken > 20)
				{
					cout << "Time Limit Exceeded Even After Extension!\n";
					count++;
					continue;
				}
			}
			else
			{
				if (timetaken > 10)
				{
					cout << "Time Limit Exceeded!\n";
					count++;
					continue;
				}
			}
		}

		//----------review-------------//
		userGiven[count] = userAns;
		askedIndex[count] = index;
		// convert to uppercase if lowercase entered
		if (userAns >= 'a' && userAns <= 'd')
			userAns = userAns - 32;

		if (userAns == correct[index])
		{
			cout << "Correct!\n";
			score+=2;
			streak++;
			if (streak == 3)
			{
				cout << "Combo 3X(+10)\n";
				score += 5;
			}
			if (streak == 5)
			{
				cout << "Combo 5X(+15)\n";
				score += 15;
				streak=0;
			}
		}
		else
		{
			cout << "Wrong!\n";
			cout << "Correct Answer: " << correct[index] << endl;
			streak = 0;
			if (diff == 1)
				score -= 2;
			else if (diff == 2)
				score -= 3;
			else if (diff == 3)
				score -=5;
		}
		
	}
	//Taking player name for leaderboard---->
	string playername;
	cout << "Enter your name for leaderboard: ";
	cin >> playername;
	saveScore(playername, score);
	// <--------
	cout << "\n====================================\n";
	cout << "Quiz Finished!\n";
	cout << "Your Score: " << score << "\n";
	cout << "====================================\n";
	char review;
	cout << "\nDo you want to review incorrect answers? (Y/N): ";
	cin >> review;

	if (review == 'Y' || review == 'y')
	{
		reviewWrong(count);
	}

}
//leaderboard filling
// good thing about save score is it can rewrite same names 
void saveScore(string playername, int finalScore)
{
	ifstream fin;
	fin.open("leaderboard.txt");

	string names[100];
	int scores[100];
	int count = 0;
	bool found = false;

	// --------- Load Existing Data ----------
	if (fin.is_open())
	{
		while (fin >> names[count] >> scores[count])
		{
			if (names[count] == playername)
			{
				scores[count] = finalScore;   // UPDATE SCORE
				found = true;
			}
			count++;
		}
		fin.close();
	}

	// --------- If Name Not Found, Add New ----------
	if (!found)
	{
		names[count] = playername;
		scores[count] = finalScore;
		count++;
	}

	// --------- Rewrite File ----------
	ofstream fout;
	fout.open("leaderboard.txt");

	if (!fout.is_open())
	{
		cout << "Error saving score!\n";
		return;
	}

	for (int i = 0; i < count; i++)
	{
		fout << names[i] << " " << scores[i] << endl;
	}

	fout.close();

	cout << "Score saved successfully!\n";
}

//Leaderboard display
void Leaderboard()
{
	ifstream fin;
	fin.open("leaderboard.txt");

	if (!fin.is_open())
	{
		cout << "No leaderboard found yet!\n";
		return;
	}

	string names[100];
	int scores[100];
	int count = 0;

	while (fin >> names[count] >> scores[count])
	{
		count++;
	}
	fin.close();

	// --------- scores arrranging ----------
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (scores[j] > scores[i])
			{
				int tempScore = scores[i];
				scores[i] = scores[j];
				scores[j] = tempScore;

				string tempName = names[i];
				names[i] = names[j];
				names[j] = tempName;
			}
		}
	}

	// --------- DISPLAY TOP 10 ----------
	cout << "\n========= LEADERBOARD (TOP SCORES) =========\n";
	int limit = (count < 5) ? count : 5;

	for (int i = 0; i < limit; i++)
	{
		cout << i + 1 << ". " << names[i] << " ---> " << scores[i] << endl;
	}

	cout << "===========================================\n";
}

void reviewWrong(int totalAsked)
{
    cout << "\n========= REVIEW (INCORRECT ONLY) =========\n";

    bool anyWrong = false;

    for (int i = 0; i < totalAsked; i++)
    {
        int idx = askedIndex[i];

        if (userGiven[i] != correct[idx])
        {
            anyWrong = true;
            cout << "\nQ" << i + 1 << ": " << question[idx] << endl;
            cout << "Your Answer: " << userGiven[i] << endl;
            cout << "Correct Answer: " << correct[idx] << endl;
        }
    }

    if (!anyWrong)
        cout << "\nExcellent! No wrong answers to review.\n";

    cout << "===========================================\n";
}
//------------lifelines definition--------------
void showlifelines(int &index, int total, int used[])
{
	int choice;

	cout << "\n========== LIFELINES ==========\n";
	if (lifeline_5050 == 0)  cout << "1. 50/50\n";
	if (lifeline_time == 0)  cout << "2. Time Extend (+10 sec)\n";
	if (lifeline_skip == 0)  cout << "3. Skip Question\n";
	if (lifeline_swap == 0)  cout << "4. Swap Question\n";
	cout << "5. Cancel\n";
	cout << "Choose lifeline: ";
	cin >> choice;

	// ---------- 50 / 50 ----------
	if (choice == 1 && lifeline_5050 == 0)
	{
		lifeline_5050 = 1;
		int removed = 0;

		cout << "\n50/50 Applied:\n";

		if (correct[index] != 'A' && removed < 2) { cout << "A removed\n"; removed++; }
		if (correct[index] != 'B' && removed < 2) { cout << "B removed\n"; removed++; }
		if (correct[index] != 'C' && removed < 2) { cout << "C removed\n"; removed++; }
		if (correct[index] != 'D' && removed < 2) { cout << "D removed\n"; removed++; }
	}

	// ---------- TIME EXTEND ----------
	else if (choice == 2 && lifeline_time == 0)
	{
		lifeline_time = 1;
		cout << "Time Extended by 10 seconds for this question!\n";
	}

	// ---------- SKIP QUESTION ----------
	else if (choice == 3 && lifeline_skip == 0)
	{
		lifeline_skip = 1;
		cout << "Question Skipped!\n";
		used[index] = 1;
		return;   // move to next question automatically //
	}

	// ---------- SWAP QUESTION ----------//
	else if (choice == 4 && lifeline_swap == 0)
	{
		lifeline_swap = 1;
		applyswap(index, total, used);
		cout << "Question Swapped!\n";
	}

	else
	{
		cout << "Invalid or Already Used Lifeline!\n";
	}
}
//------swap logic-----------//
void applyswap(int &index, int total, int used[])
{
	int newindex;
	do
	{
		newindex = rand() % total;
	} while (used[newindex] == 1);

	used[index] = 1;   // mark old as used
	index = newindex; // replace current question
}
void adminmode()
{
	string pass;
	cout << "\n=========== ADMIN MODE ===========\n";
	cout << "Enter Admin Password: ";
	cin >> pass;
	if (pass == "admin123")
	{
		cout << "\nAccess Granted!\n";
		cout << "----------------------------------\n";
		cout << "Admin Features\n";
		cout << "• Reset Leaderboard\n";
		cout << "• View Quiz Logs\n";
		cout << "• Manage Questions\n";
		cout << "----------------------------------\n";
		cout << "This module is under development.\n";
	}
	else
	{
		cout << "Wrong Password! Access Denied.\n";
	}

	cout << "==================================\n";
}

