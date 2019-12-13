#include"init.h"

void splitline() {
	cout << "\n" << endl;
}

//handle error selection
void handleErrorMessage() {
	cout << "The input is illegal, please input again" << endl;
	splitline();
}

void exitsystem() {
	cout << "Welcome you again! " << endl;
	exit(0);
}

int getInt() {
	int temInt;
	try {
		cin >> temInt;
		return temInt;
	}
	catch (...) {
		handleErrorMessage();
		return temInt;
	}
}

void splitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

class module {
private:
	string strWelcome = "Welcome to Examination System , please select your identity.";
	string strStartChoice1 = "1. Student ; 2. Teacher ; 3. Exit ";//start choice 
	string strStartChoice2 = "Please input the number you  choose.";//start tip
	string strChoice1 = "Please select your operation";
	string strChoice2 = "1. Sign in ; 2. Return ; 3. Exit";
	//string strErrorMessage = "Your choice is wrong , please select again.";
	string PasswordError1 = "Your account number or password is wrong.";
	string PasswordError2 = "1. Input again ; 2. Return";
	string strSignIn1 = "Please input your account number and password.";//signin message
	string strSignIn2 = "Account number : ";
	string strSignIn3 = "Password : ";
	int StartChoice;
	string ANumber;

public:
	module() {
		std::vector<std::string> R;
		splitString(handleStart(start()), R, ",");//1: Student; 2: Teacher.
		StartChoice = R[1][0] - '0';
		ANumber = R[0];
	}

	~module() {
		cout << "Welcome you again!" << endl;
	}

	//System start
	string start() {
		string myChoice;
		cout << strWelcome << endl << strStartChoice1 << endl << strStartChoice2 << endl;
		splitline();
		cin >> myChoice;
		splitline();

		if (myChoice != "1" && myChoice != "2" && myChoice != "3") {
			handleErrorMessage();
			myChoice = start();
		}
		return myChoice;
	}

	//handle start message
	string handleStart(string choice) {
		string ReturnI;
		//string ReturnIs[2];
		std::vector<std::string> ReturnIs;
		switch (choice[0] - '0') {
		case 1: ReturnI = handleStartChoiceis1(handleStartChoice()); break;
		case 2: ReturnI = handleStartChoiceis2(handleStartChoice()); break;
		case 3: exitsystem(); break;
		default: break;
		}
		splitString(ReturnI, ReturnIs, ",");
		//string ReturnIs[2] = strtok(ReturnI, ",");
		switch (ReturnIs[1][0] - '0') {
		case 0:return handleStart(start()); break;
		case 1:return ReturnI; break;
		case 2:return ReturnI; break;
		default: exitsystem();
		}
	}

	//handle myChoice is 1
	string handleStartChoice() {
		string Choice;
		cout << strChoice1 << endl << strChoice2 << endl;
		splitline();
		cin >> Choice;
		splitline();
		if (Choice != "1" && Choice != "2" && Choice != "3") {
			handleErrorMessage();
			Choice = handleStartChoice();
		}
		return Choice;
	}

	string handleStartChoiceis1(string n) {
		if (n == "3") exitsystem();
		else if (n == "2") {
			return handleStart(start());
		}
		string StudentAccountNumber;
		string StudentPassword;
		cout << strSignIn1 << endl;
		cout << strSignIn2;
		cin >> StudentAccountNumber;
		cout << strSignIn3;
		cin >> StudentPassword;
		splitline();
		if (judgeStudentPassword(StudentAccountNumber, StudentPassword))
			return (StudentAccountNumber + ",1");
		else {
			string r = passworderror();
			if (r == "1") return handleStartChoiceis1("1");
			else if (r == "2") return "0,0";
		}
	}

	string handleStartChoiceis2(string n) {
		if (n == "3") exitsystem();
		else if (n == "2") {
			return handleStart(start());
		}
		string TeacherAccountNumber;
		string TeacherPassword;
		string ReturnString;
		cout << strSignIn1 << endl;
		cout << strSignIn2;
		cin >> TeacherAccountNumber;
		cout << strSignIn3;
		cin >> TeacherPassword;
		splitline();
		if (TeacherAccountNumber == "B00000" && TeacherPassword == "abcd") {
			ReturnString = TeacherAccountNumber + ",2";
			return ReturnString;//return 2 if he is teacher and return 1 while student
		}
		else {
			string r = passworderror();
			if (r == "1") return handleStartChoiceis2("1");
			else if (r == "2") return "0,0";
		}
	}

	//Handle password is error
	string passworderror() {
		string choice;
		cout << PasswordError1 << endl;
		cout << PasswordError2 << endl;
		splitline();
		cin >> choice;
		splitline();
		if (choice != "1" && choice != "2") {
			handleErrorMessage();
			return passworderror();
		}
		return choice;
	}

	int getStartChoice() {
		return StartChoice;
	}

	string getAnumber() {
		return ANumber;
	}

	string getStudentNameandClass(string number) {
		ifstream inFile1("K1.csv", ios::in);
		string lineStr;
		vector<vector<string>> strArray;
		while (getline(inFile1, lineStr))
		{
			stringstream ss(lineStr);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == number) {
				return lineArray[1] + "," + lineArray[2];
				break;
			}
		}
		inFile1.close();
		ifstream inFile2("K2.csv", ios::in);
		while (getline(inFile2, lineStr))
		{
			stringstream ss(lineStr);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == number) {
				return lineArray[1] + "," + lineArray[2];
				break;
			}
		}
		inFile2.close();
	}

	//judge student's password
	bool judgeStudentPassword(string StudentAccountNumber, string StudentPassword) {
		bool JudgeStudentPassword = false;
		ifstream inFile3("AccountMessage.csv", ios::in);
		string lineStr;
		vector<vector<string>> strArray;
		while (getline(inFile3, lineStr))
		{ 
			stringstream ss(lineStr);
			string str;
			vector<string> lineArray; 
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == StudentAccountNumber) {
				JudgeStudentPassword = (lineArray[1] == StudentPassword);
				break;
			}
		}
		inFile3.close();
		//JudgeStudentPassword = (lineArray[1] == StudentPassword);
		return JudgeStudentPassword;
	}
};

void initAccountMessage() {
	ofstream outFile;
	outFile.open("AccountMessage.csv", ios::out);
	outFile << "Account Number" << ',' << "Password" << endl;
	outFile << "A0000" << ',' << "A0000" << endl;
	outFile << "A0001" << ',' << "A0001" << endl;
	outFile << "A0010" << ',' << "A0010" << endl;
	outFile << "A0011" << ',' << "A0011" << endl;
	outFile << "A0100" << ',' << "A0100" << endl;
	outFile << "A0101" << ',' << "A0101" << endl;
	outFile << "A0110" << ',' << "A0110" << endl;
	outFile << "A0111" << ',' << "A0111" << endl;
	outFile << "A1000" << ',' << "A1000" << endl;
	outFile << "A1001" << ',' << "A1001" << endl;
	outFile << "A1010" << ',' << "A1010" << endl;
	outFile << "A1011" << ',' << "A1011" << endl;
	outFile << "A1100" << ',' << "A1100" << endl;
	outFile << "A1101" << ',' << "A1101" << endl;
	outFile << "A1110" << ',' << "A1110" << endl;
	outFile << "A1111" << ',' << "A1111" << endl;
	outFile.close();
}

void initClassList() {
	ofstream outFile1;
	outFile1.open("K1.csv", ios::out);
	string Class1 = "K1";
	outFile1 << "Account Number" << ',' << "Name" << "," << "Class" << endl;
	outFile1 << "A0000" << ',' << "James" << "," << Class1 << endl;
	outFile1 << "A0001" << ',' << "Rando" << "," << Class1 << endl;
	outFile1 << "A0010" << ',' << "Green" << "," << Class1 << endl;
	outFile1 << "A0011" << ',' << "Howard" << "," << Class1 << endl;
	outFile1 << "A0100" << ',' << "Davis" << "," << Class1 << endl;
	outFile1 << "A0101" << ',' << "McGee" << "," << Class1 << endl;
	outFile1 << "A0110" << ',' << "Cousins" << "," << Class1 << endl;
	outFile1 << "A0111" << ',' << "Caruso" << "," << Class1 << endl;
	outFile1.close();

	ofstream outFile2;
	outFile2.open("K2.csv", ios::out);
	string Class2 = "K2";
	outFile2 << "Account Number" << ',' << "Name" << "," << "Class" << endl;
	outFile2 << "A1000" << ',' << "Evring" << "," << Class2 << endl;
	outFile2 << "A1001" << ',' << "Durant" << "," << Class2 << endl;
	outFile2 << "A1010" << ',' << "George" << "," << Class2 << endl;
	outFile2 << "A1011" << ',' << "Paul" << "," << Class2 << endl;
	outFile2 << "A1100" << ',' << "Harden" << "," << Class2 << endl;
	outFile2 << "A1101" << ',' << "Wesbrook" << "," << Class2 << endl;
	outFile2 << "A1110" << ',' << "Leonard" << "," << Class2 << endl;
	outFile2 << "A1111" << ',' << "Griffin" << "," << Class2 << endl;
	outFile2.close();
}

void initItemBankList() {
	ofstream outFile4;
	outFile4.open("ChoiceQuestionEasy.csv", ios::out);
	outFile4 << "Order Number" << ',' << "Score" << "," << "Stem" << "," << "Alternative" << "," << "Answer" << endl;
	outFile4 << "0" << ',' << "10" << "," << "1 + 1 = " << "," << "A: 1; B: 2; C: 3; D: 4." << "," << "B" << endl;
	outFile4 << "1" << ',' << "10" << "," << "1 + 2 = " << "," << "A: 1; B: 2; C: 3; D: 4." << "," << "C" << endl;
	outFile4 << "2" << ',' << "10" << "," << "1 + 3 = " << "," << "A: 1; B: 2; C: 3; D: 4." << "," << "D" << endl;
	outFile4 << "3" << ',' << "10" << "," << "1 + 4 = " << "," << "A: 3; B: 4; C: 5; D: 6." << "," << "C" << endl;
	outFile4 << "4" << ',' << "10" << "," << "1 + 5 = " << "," << "A: 3; B: 4; C: 5; D: 6." << "," << "D" << endl;
	outFile4.close();

	ofstream outFile5;
	outFile5.open("ChoiceQuestionDifficult.csv", ios::out);
	outFile5 << "Order Number" << ',' << "Score" << "," << "Stem" << "," << "Alternative" << "," << "Answer" << endl;
	outFile5 << "0" << ',' << "30" << "," << "010 * 010 = " << "," << "A: 64; B: 7; C: 8; D: 9." << "," << "A" << endl;
	outFile5 << "1" << ',' << "30" << "," << "0x10 * 0x10 = " << "," << "A: 10; B: 256; C: 15; D: 18." << "," << "B" << endl;
	outFile5 << "2" << ',' << "30" << "," << "11111(2) = " << "," << "A: 10; B: 15; C: 31; D: 30." << "," << "C" << endl;
	outFile5 << "3" << ',' << "30" << "," << "5 * 6 = " << "," << "A: 15; B: 20; C: 25; D: 30." << "," << "D" << endl;
	outFile5 << "4" << ',' << "30" << "," << "6 * 7 = " << "," << "A: 12; B: 24; C: 36; D: 42." << "," << "D" << endl;
	outFile5.close();

	ofstream outFile6;
	outFile6.open("CompletionEasy.csv", ios::out);
	outFile6 << "Order Number" << ',' << "Score" << "," << "Stem" << "," << "Alternative" << "," << "Answer" << endl;
	outFile6 << "0" << ',' << "20" << "," << "1 + 1 = " << "," << "Completion" << "," << "2" << endl;
	outFile6 << "1" << ',' << "20" << "," << "1 + 2 = " << "," << "Completion" << "," << "3" << endl;
	outFile6 << "2" << ',' << "20" << "," << "1 + 3 = " << "," << "Completion" << "," << "4" << endl;
	outFile6 << "3" << ',' << "20" << "," << "1 + 4 = " << "," << "Completion" << "," << "5" << endl;
	outFile6 << "4" << ',' << "20" << "," << "1 + 5 = " << "," << "Completion" << "," << "6" << endl;

	ofstream outFile7;
	outFile7.open("CompletionDifficult.csv", ios::out);
	outFile7 << "Order Number" << ',' << "Score" << "," << "Stem" << "," << "Alternative" << "," << "Answer" << endl;
	outFile7 << "0" << ',' << "60" << "," << "4 ** 5 = " << "," << "Completion" << "," << "1024" << endl;
	outFile7 << "1" << ',' << "80" << "," << "5 ** 6 = " << "," << "Completion" << "," << "15625" << endl;
	outFile7 << "2" << ',' << "100" << "," << "6 ** 7 = " << "," << "Completion" << "," << "279936" << endl;
	outFile7 << "3" << ',' << "50" << "," << "7 * 8 = " << "," << "Completion" << "," << "56" << endl;
	outFile7 << "4" << ',' << "150" << "," << "8 ** 9 = " << "," << "Completion" << "," << "134217728" << endl;
	outFile7.close();
}

void initItemBankNameList() {
	ofstream outFile5;
	string temItemNames[4] = { "ChoiceQuestionEasy","ChoiceQuestionDifficult","CompletionEasy","CompletionDifficult" };
	outFile5.open("ItemBankNameList.csv", ios::out);
	for (int t = 0; t < 4; t++) {
		outFile5 << temItemNames[t] << endl;
	}
	outFile5.close();
}

void initExaminationList() {
	ofstream outFile6;
	outFile6.open("ExaminationList.csv", ios::out);
	outFile6 << "Examination Name" << "," << "Class" << endl;
	outFile6.close();
}

void AddStudentList(string newstrStudentClass, string NewAccountNumber, string NewPassword, string NewStudentName) {
	ofstream appFile1;
	appFile1.open("AccountMessage.csv", ios::app);
	//outFile << "Account Number" << ',' << "Password" << endl;
	appFile1 << "NewAccountNumber" << ',' << "NewPassword" << endl;
	appFile1.close();

	ofstream appFile2;
	appFile2.open(newstrStudentClass + ".csv", ios::app);
	//outFile << "Account Number" << ',' << "Password" << endl;
	appFile2 << NewAccountNumber << ',' << NewStudentName << "," << newstrStudentClass << endl;
	appFile2.close();
}

//Currently only "create" operation is available;
class ItemBank {
public:
	ItemBank() {}
	~ItemBank() {}
	void createNewItemBank() {
		string temItemBankName;
		cin >> temItemBankName;
		while (!judgeNewItemBank(temItemBankName)) {
			cin >> temItemBankName;
		}
		ofstream appFile3;
		appFile3.open("ItemBankNameList.csv", ios::app);
		appFile3 << temItemBankName << endl;
		appFile3.close();
		string temOrderNumber, temStem, temAlternative, temAnswer;
		int temScore;
		ofstream outFile7;
		outFile7.open(temItemBankName + ".csv", ios::out);
		outFile7 << "Order Number" << ',' << "Score" << "," << "Stem" << "," << "Alternative" << "," << "Answer" << endl;
		int k = 0;
		while (true) {
			cout << "Order Number : " << k << endl;
			cout << "Score : ";
			temScore = getInt();
			cout << "Stem : " << endl;
			cin >> temStem;
			cout << "Alternative : " << endl;
			cin >> temAlternative;
			cout << "Answer : ";
			cin >> temAnswer;
			outFile7 << to_string(k) << "," << temScore << "," << temStem << "," << temAlternative << "," << temAnswer << endl;
			k++;
			splitline();
			string temS;
			cout << "Added a new question" << endl;
			cout << "Would you like to add again?\n(Y/N)";
			cin >> temS;
			while (temS != "Y" && temS != "y" && temS != "N" && temS != "n") {
				handleErrorMessage();
				cin >> temS;
			}
			if (temS == "N" || temS == "n")
				break;
		}
	}

	//void addTitle(string temitembankname) {}
	bool judgeNewItemBank(string temibname) {
		ifstream inFile13;
		inFile13.open("ItemBankNameList.csv", ios::in);
		string st;
		while (getline(inFile13, st)) {
			if (temibname == st) {
				cout << "The itembank already exist" << endl;
				return false;
			}
		}
		inFile13.close();
		return true;
	}
};

class Examination {
private:
	string newExamName;
	string newAttendClass;
	int AllowedAttend = 0;//Number of times allowed to attend
	string strGuide1 = "Please create a new examination by following the guidance.";
	string strGuide2 = "Please input the name of examination : ";
	string strGuide3 = "Please input the class that attend the examination : ";
	string strGuide4 = "Please input the maximum number of times allowed to take the exam : ";
	//string strErrorMessage = "The input is illegal, please input again";
	string strCreateGuide1 = "Please input the name of itembank : ";
	string strCreateGuide2 = "Please input the number of questions : ";
	string strCreateGuide3 = "Please input the score : ";
	string strCreateGuide4 = "Would you like to continue adding itembank?\n[Y/N]  ";
	double AverageScore;
	string ItemNames[10];
	string newItemNames[10];
	int newQuestionNumber[10] = { 0 }, newItemScores[10] = { 0 };
	int newSumQuestionNumber = 0;
	int ItemBankAddedNumber = 0;
	int TotalItemBankNumber;
	double ScoreModifications;
	double ScoreModification[10];

public:
	//Init Examination
	Examination() {
		TotalItemBankNumber = getItemNames();
		startGuide();
		createExamination();
		newExaminationMessage();
		calculateScoreModifications();
		calculatenewSumQuestionNumber();
		createTextPaper();
		cout << "Creating a new examination......" << endl;
		splitline();
		updateExaminationList();
		cout << "Create success!" << endl;
		splitline();
	}

	~Examination() {}
	
	void startGuide() {
		string InExamName, InAttendClass, InAllowedAttend;
		cout << strGuide1 << endl;
		splitline();
		cout << strGuide2 << endl;
		splitline();
		cin >> newExamName;
		splitline();
		cout << strGuide3 << endl;
		splitline();
		cin >> newAttendClass;
		splitline();
		while (judgeAttendClassIsLegal(newAttendClass) == false) {
			handleErrorMessage();
			cin >> newAttendClass;
			splitline();
		}
		cout << strGuide4 << endl;
		splitline();
		while (AllowedAttend == 0) {
			try {
				cin >> AllowedAttend;
				splitline();
				break;
			}
			catch (...) {
				handleErrorMessage();
			}
		}
	}

	//use more Itembanks
	void createExamination() {
		ofstream outFile3;
		ifstream inFile8;
		string FileName = getExaminationFileName();
		inFile8.open(newAttendClass + ".csv", ios::in);
		outFile3.open(FileName + "_Score_Sheet.csv", ios::out);
		string lineStr;
		outFile3 << "Account Number" << ',' << "Name" << "," << "Class" << "," << "Best Score" << "," << "Allowed Attend Left" << endl;
		getline(inFile8, lineStr);
		while (getline(inFile8, lineStr)) {
			outFile3 << lineStr << "," << to_string(0) << "," << to_string(AllowedAttend) << endl;
		}
		outFile3.close();
		inFile8.close();
	}

	void newExaminationMessage() {
		string temItemBankName, temstrJudge, ItemBankName;
		int temQuestionNumber, temItemScore;
		bool temJudge = true;
		string FileName = getExaminationFileName();
		cout << "Already exist these itembanks:" << endl;
		splitline();
		for (int q = 0; q < TotalItemBankNumber; q++) {
			cout<< ItemNames[q] <<endl;
		}
		try {
			do {
				do {
					cout << strCreateGuide1;
					//splitline();
					cin >> temItemBankName;
				} while (!judgeItemBankNameIsLegal(temItemBankName, ItemBankAddedNumber));
				cout << strCreateGuide2;
				cin >> temQuestionNumber;
				cout << strCreateGuide3;
				cin >> temItemScore;
				newItemNames[ItemBankAddedNumber] = temItemBankName;
				newQuestionNumber[ItemBankAddedNumber] = temQuestionNumber;
				newItemScores[ItemBankAddedNumber] = temItemScore;
				ItemBankAddedNumber++;
				if (ItemBankAddedNumber == TotalItemBankNumber) break;
				do {
					cout << strCreateGuide4;
					cin >> temstrJudge;
					splitline();
					if (temstrJudge == "Y" || temstrJudge == "y") {
						temJudge = true;
						break;
					}
					else if (temstrJudge == "N" || temstrJudge == "n") {
						temJudge = false;
					}
					else {
						handleErrorMessage();
					}
				} while (temJudge == true);
			} while (temJudge == true);
		}
		catch (...) {
			handleErrorMessage();
			newExaminationMessage();
		}
	}

	void calculateScoreModifications() {
		int sum = 0;
		for (int i = 0; i < 4; i++) {
			sum += newItemScores[i];
		}
		ScoreModifications = 100.0 / sum;
	}

	void calculateScoreModification(int temn, int temSum) {
		ScoreModification[temn] = newItemScores[temn] / double(temSum);
	}

	void calculatenewSumQuestionNumber() {
		for (int i = 0; i < 4; i++) {
			newSumQuestionNumber += newQuestionNumber[i];
		}
	}

	double getScoreModifications() {
		return ScoreModifications;
	}

	int getItemNames() {
		int k = 0;
		ifstream inFile10;
		inFile10.open("ItemBankNameList.csv", ios::in);
		string temstr;
		while (getline(inFile10, temstr)) {
			ItemNames[k] = temstr;
			k++;
		}
		return k;
	}

	int getnewSumQuestionNumber() {
		return newSumQuestionNumber;
	}
	
	void createTextPaper() {
		ofstream outFile4;
		int k = 1;//Count number of questions added into the text paper.
		outFile4.open(getExaminationFileName() + "_TextPaper.csv", ios::out);
		outFile4 << "Order Number" << ',' << "Stem" << "," << "Alternative" << "," << "Answer" << "," << "Score" 
			<< "," << "ItemBank Name" << "," << "Order Number in ItemBank" << "," << "Weight" << endl;
		vector<vector<string>> strArray;
		for (int j = 0; j < ItemBankAddedNumber; j++) {
			int temSums = 0;
			ifstream inFile9(newItemNames[j] + ".csv", ios::in);
			string lineStr;
			getline(inFile9, lineStr);
			//int n = lineStr.size();//Column
			//vector<vector<string>> strArray;
			strArray.clear();
			while (getline(inFile9, lineStr))
			{
				stringstream ss(lineStr);
				string str;
				vector<string> lineArray;
				while (getline(ss, str, ','))
					lineArray.push_back(str);
				strArray.push_back(lineArray);
			}
			int m = strArray.size();//line
			int n = strArray[0].size();//column
			if (m < newQuestionNumber[j]) {
				cout << "Question number is illegal, please create input again." << endl;
				splitline();
				cout << "Error itembank Name : " << newItemNames[j] << endl;
				cout << "Error message : the input number of questions should be no more than " << m << "." << endl;
				cout << "Question numbers : ";
				cin >> newQuestionNumber[j];
				splitline();
				createTextPaper();
				return;
			}
			srand((unsigned int)(time(NULL)));
			int A[10];//random
			for (int i = 0; i < newQuestionNumber[j]; i++) {
				A[i] = rand() % m;
				for (int t = 0; t < i; t++) {
					if (A[i] == A[t]) {
						i--;
						break;
					}
				}
			}
			for (int i = 0; i < newQuestionNumber[j]; i++) {
				stringstream newss;
				int r;
				newss << strArray[A[i]][1];
				newss >> r;
				temSums += r;
			}
			calculateScoreModification(j, temSums);
			for (int i = 0; i < newQuestionNumber[j]; i++) {
				outFile4 << to_string(k) << "," << strArray[A[i]][2] << "," << strArray[A[i]][3] << "," << strArray[A[i]][4]
					<< "," << strArray[A[i]][1] << "," << newItemNames[j] << "," << strArray[A[i]][0] << "," << to_string(ScoreModification[j]) << endl;
				k++;
			}
		}
		outFile4.close();
	}

	void updateExaminationList() {
		ofstream appFile0;
		appFile0.open("ExaminationList.csv", ios::app);
		appFile0 << newExamName << "," << newAttendClass << endl;
		appFile0.close();
	}

	string getExaminationFileName(){
		string ExaminationFileName = newExamName + "(" + newAttendClass + ")";
		return ExaminationFileName;
	}

	//judge error message about attend class
	bool judgeAttendClassIsLegal(string ClassName) {
		if (ClassName != "K1" && ClassName != "K2")
			handleErrorMessage();
		if (ClassName == "K1" || ClassName == "K2")
			return true;
		else return false;
	}

	//judge error message about ItemBank name
	bool judgeItemBankNameIsLegal(string temstrItemBankName, int temItemBankAddedNumber) {
		for (int i = 0; i < 4; i++) {
			if (temstrItemBankName == ItemNames[i]) {
				for (int j = 0; j < ItemBankAddedNumber; j++) {
					if (temstrItemBankName == newItemNames[j]) {
						handleErrorMessage();
						return false;
					}
				}
				return true;
			}
		}
		handleErrorMessage();
		return false;
	}
};

class Student {
private:
	string StudentID, StudentName, StudentClass;
	string strHelloStudent = "Hello, ";
	string attendExamination[10];
	int AttenExaminations;
	int RemainingTimes[10];
	double StudentBestScore[10];
public:
	Student(string ID, string Name, string Class) {
		StudentID = ID;
		StudentName = Name;
		StudentClass = Class;
		cout << strHelloStudent << Name << endl;
		splitline();
		getattendExamination();
		getRemainingTimesAndStudentBestScore();
	}

	Student(string ID) {
		StudentID = ID;
		ifstream inFile6("K1.csv", ios::in);
		string lineStr;
		//vector<vector<string>> strArray;
		while (getline(inFile6, lineStr))
		{
			stringstream ss(lineStr);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == ID) {
				StudentName = lineArray[1];
				StudentClass = lineArray[2];
				break;
			}
		}
		inFile6.close();
		ifstream inFile7("K2.csv", ios::in);
		while (getline(inFile7, lineStr))
		{
			stringstream ss(lineStr);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == ID) {
				StudentName = lineArray[1];
				StudentClass = lineArray[2];
				break;
			}
		}
		inFile7.close();
		cout << strHelloStudent << StudentName << endl;
		splitline();
		getattendExamination();
		getRemainingTimesAndStudentBestScore();
	}

	~Student() {
		//cout << "Goodbye, " << StudentName << endl;
		//splitline();
	}

	void guideStudent() {
		int temStudentChoice;
		cout << "what would you like to do?" << endl;
		cout << "1. Attend examination ; 2. Query results ; 3. Exit ;" << endl;
		splitline();
		temStudentChoice = getInt();
		splitline();
		switch (temStudentChoice) {
		case 1:guideStudent1(); break;
		case 2:guideStudent2(); break;
		case 3:guideStudent3(); break;
		default: {
			handleErrorMessage();
			guideStudent();
		}
		}
	}

	//Attend examination
	void guideStudent1(){
		quiryExamination1();
		splitline();
		int t;
		t = getInt();
		while (!judgeOrderLegal(t)) {
			handleErrorMessage();
			t = getInt();
		}
		if (t == 0) {
			guideStudent();
			return;
		}
		funcattendExamination(attendExamination[t - 1], t - 1);
		int temStudentChoice1;
		cout << "what else would you like to do?" << endl;
		cout << "1. Return ; 2. Exit" << endl;
		splitline();
		while (true) {
			try {
				cin >> temStudentChoice1;
				if (temStudentChoice1 == 1 || temStudentChoice1 == 2) {
					break;
				}
				handleErrorMessage();
			}
			catch (...) {
				handleErrorMessage();
			}
		}
		splitline();
		switch (temStudentChoice1) {
		case 1:guideStudent(); break;
		case 2:exitsystem(); break;
		default: handleErrorMessage();
		}
	}

	//Query examination results
	void guideStudent2(){
		quiryExamination2();
		int temStudentChoice2;
		cout << "what else would you like to do?" << endl;
		cout << "1. Return ; 2. Exit" << endl;
		splitline();
		while (true) {
			try {
				cin >> temStudentChoice2;
				if (temStudentChoice2 == 1 || temStudentChoice2 == 2) {
					break;
				}
				handleErrorMessage();
			}
			catch (...) {
				handleErrorMessage();
			}
		}
		splitline();
		switch (temStudentChoice2) {
		case 1:guideStudent(); break;
		case 2:exitsystem(); break;
		default: handleErrorMessage();
		}
	}

	void guideStudent3() {
		exitsystem();
	}

	string getStudentName() {
		return StudentName;
	}

	string getStudentID() {
		return StudentID;
	}

	string getStudentClass() {
		return StudentClass;
	}

	//Display the remaining times.
	void quiryExamination1() {
		cout << "The remaining times of your examination are as follows." << endl;
		for (int i = 0; i < AttenExaminations; i++) {
			cout << "0. ";
			cout.width(10);
			cout << "Return" << endl;
			cout << int(i + 1) << ". ";
			cout.width(10);
			cout << attendExamination[i];
			cout << ":  " << RemainingTimes[i] << endl;
		}
	}

	//Display the best score.
	void quiryExamination2() {
		cout << "The best score of your examinations are as follows." << endl;
		for (int i = 0; i < AttenExaminations; i++) {
			cout.width(10);
			cout << attendExamination[i];
			cout << ":  " << StudentBestScore[i] << endl;
		}
	}

	void funcattendExamination(string temExaminationName, int temN) {
		double temScore = 0;
		double temSumScore = 0;
		double temModification;
		ifstream inFile16;
		inFile16.open(temExaminationName + "(" + StudentClass + ")_TextPaper.csv", ios::in);
		string s1;
		vector<vector<string>> Content;
		while (getline(inFile16, s1)) {
			stringstream ss(s1);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			Content.push_back(lineArray);
		}
		int m = Content.size();
		int n = Content[0].size();
		inFile16.close();
		for (int i = 1; i < m; i++) {
			double temgrade, temweight;
			stringstream ss1;
			stringstream ss2;
			ss1 << Content[i][4];
			ss1 >> temgrade;
			ss2 << Content[i][7];
			ss2 >> temweight;
			temSumScore += temgrade * temweight;
			cout << Content[i][0] << ". " << Content[i][1] << endl;
			cout << Content[i][2] << endl;
			//splitline();
			cout << "Your answer is : ";
			cin >> s1;
			splitline();
			if (ClearHeadTailSpace(s1) == Content[i][3]) {
				temScore += temgrade * temweight;
			}
		}
		temModification = 100.0 / temSumScore;
		int t;
		string s2;
		while (true) {
			cout << "You have fulfiled the examination, would you like to change your answer?" << endl;
			cout << "[Y/N]  ";
			cin >> s1;
			if (s1 == "N" || s1 == "n")
				break;
			else if (s1 == "Y" || s1 == "y") {
				cout << "Which question do you want to change(input the order) : ";
				t = getInt();
				if (t < 1 || t >= m) {
					handleErrorMessage();
					continue;
				}
				else {
					double temgrade, temweight;
					stringstream ss1;
					stringstream ss2;
					ss1 << Content[t][4];
					ss1 >> temgrade;
					ss2 << Content[t][7];
					ss2 >> temweight;
					temScore -= temgrade * temweight;
					cout << "Your new answer : ";
					cin >> s2;
					splitline();
					if (ClearHeadTailSpace(s2) == Content[t][3]) {
						temScore += temgrade * temweight;
					}
				}
			}
			else handleErrorMessage();
		}
		temScore *= temModification;
		cout << "Your score is : " << double(int(100 * temScore + 0.5) / 100.0) << endl;
		splitline();
		ofstream outFile8;
		ifstream inFile17;
		inFile17.open(temExaminationName + "(" + StudentClass + ")_Score_Sheet.csv");
		string s3;
		vector<vector<string>> Content1;
		while (getline(inFile17, s3)) {
			stringstream sss(s3);
			string str;
			vector<string> lineArray;
			while (getline(sss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == StudentID) {
				int temsint;
				stringstream ss3;
				ss3 << lineArray[4];
				ss3 >> temsint;
				lineArray[4] = to_string(temsint - 1);
				if (temScore > StudentBestScore[temN]) {
					lineArray[3] = to_string(temScore);
					StudentBestScore[temN] = temScore;
				}
			}
			Content1.push_back(lineArray);
		}
		int a = Content1.size();//Line
		int b = Content1[0].size();//Array
		int r = b - 1;
		outFile8.open(temExaminationName + "(" + StudentClass + ")_Score_Sheet.csv");
		for (int m = 0; m < a; m++) {
			for (int n = 0; n < r; n++) {
				outFile8 << Content1[m][n] << ",";
			}
			outFile8 << Content1[m][r] << endl;
		}
		inFile17.close();
		outFile8.close();
		cout << "Your best score is : " << double(int(10 * StudentBestScore[temN] + 0.5) / 10.0) << endl;
	}

	void getattendExamination() {
		AttenExaminations = 0;
		ifstream inFile14;
		inFile14.open("ExaminationList.csv", ios::in);
		string line;
		while (getline(inFile14, line)) {
			stringstream ss(line);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[1] == StudentClass) {
				attendExamination[AttenExaminations] = lineArray[0];
				AttenExaminations++;
			}
		}
	}

	void getRemainingTimesAndStudentBestScore() {
		for (int i = 0; i < AttenExaminations; i++) {
			ifstream inFile15;
			inFile15.open(attendExamination[i] + "(" + StudentClass + ")_Score_Sheet.csv", ios::in);
			string temstr;
			while (getline(inFile15, temstr)) {
				stringstream ss(temstr);
				string str;
				vector<string> lineArray;
				while (getline(ss, str, ','))
					lineArray.push_back(str);
				if (lineArray[0] == StudentID) {
					stringstream s1;
					stringstream s2;
					s1 << lineArray[3];
					s1 >> StudentBestScore[i];
					s2 << lineArray[4];
					s2 >> RemainingTimes[i];
					//StudentBestScore[i] = lineArray[3];
					//RemainingTimes[i] = to_(lineArray[4]);
				}
			}
		}
	}

	bool judgeOrderLegal(int n) {
		if (n < 0 || n > AttenExaminations)
			return false;
		if (RemainingTimes[n - 1] == 0)
			return false;
		return true;
	}

	string& ClearHeadTailSpace(string& str)
	{
		if (str.empty())
		{
			return str;
		}

		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ") + 1);
		return str;
	}
};

class Teacher {
private:
	string TeacherID, TeacherName; //TeacherClass;
	string strHelloTeacher = "Hello, ";

public:
	Teacher(string ID, string Name) {
		TeacherID = ID;
		TeacherName = Name;
		//TeacherClass = Class;
		cout << strHelloTeacher << TeacherName << endl;
		splitline();
	}

	Teacher() {
		TeacherID = "B00000";
		TeacherName = "Miss.Li";
		//TeacherClass = "K1";
		cout << strHelloTeacher << TeacherName << endl;
		splitline();
	}

	~Teacher() {
		//cout << "Goodbye, " << TeacherName << endl;
		//splitline();
	}

	void guideTeacher() {
		int temTeacherChoice;
		cout << "what would you like to do?" << endl;
		cout << "1. Create a new examination ; 2. Manage student list ; 3. Get average score ;" << endl;
		cout << "4. Manage the ItemBank ; 5. Exit" << endl;
		cout << "Currently only add function is available for option 2" << endl;
		splitline();
		temTeacherChoice = getInt();
		splitline();
		switch (temTeacherChoice) {
		case 1:guideTeacher1(); break;
		case 2:guideTeacher2(); break;
		case 3:guideTeacher3(); break;
		case 4:guideTeacher4(); break;
		case 5:guideTeacher5(); break;
		default: {
			handleErrorMessage();
			guideTeacher();
		}
		}
	}

	void guideTeacher1() {
		int temTeacherChoice1;
		Examination newExamination;
		cout << "what else would you like to do?" << endl;
		cout << "1. Return ; 2. Exit" << endl;
		splitline();
		while (true) {
			try {
				cin >> temTeacherChoice1;
				if (temTeacherChoice1 == 1 || temTeacherChoice1 == 2) {
					break;
				}
				handleErrorMessage();
			}
			catch (...) {
				handleErrorMessage();
			}
		}
		splitline();
		switch (temTeacherChoice1) {
		case 1:guideTeacher(); break;
		case 2:exitsystem(); break;
		default: handleErrorMessage();
		}
	}

	void guideTeacher2() {
		string temClass, temNumber, temPassword, temName;
		while (true) {
			cout << "Please input the class of new student : ";
			cin >> temClass;
			if (temClass == "K1" || temClass == "K2") 
				break;
			handleErrorMessage();
		}
		cout << "Please input the ID of new student : ";
		cin >> temNumber;
		while (!judgeInputNumber(temNumber)) {
			cout << "The account number already exists, please input again." << endl;
			splitline();
			cout << "Please input the ID of new student : ";
			cin >> temNumber;
		}
		cout << "Please input the password of new student : ";
		cin >> temPassword;
		cout << "Please input the name of new student : ";
		cin >> temName;
		AddStudentList(temClass, temNumber, temPassword, temName);
		int temTeacherChoice2;
		cout << "what else would you like to do?" << endl;
		cout << "1. Return ; 2. Exit" << endl;
		splitline();
		while (true) {
			try {
				cin >> temTeacherChoice2;
				if (temTeacherChoice2 == 1 || temTeacherChoice2 == 2) {
					break;
				}
				handleErrorMessage();
			}
			catch (...) {
				handleErrorMessage();
			}
		}
		splitline();
		switch (temTeacherChoice2) {
		case 1:guideTeacher(); break;
		case 2:exitsystem(); break;
		default: handleErrorMessage();
		}
	}

	void guideTeacher3() {
		cout << getAvgScore() << endl;
		splitline();
		int temTeacherChoice3;
		cout << "what else would you like to do?" << endl;
		cout << "1. Return ; 2. Exit" << endl;
		splitline();
		while (true) {
			try {
				cin >> temTeacherChoice3;
				if (temTeacherChoice3 == 1 || temTeacherChoice3 == 2) {
					break;
				}
				handleErrorMessage();
			}
			catch (...) {
				handleErrorMessage();
			}
		}
		splitline();
		switch (temTeacherChoice3) {
		case 1:guideTeacher(); break;
		case 2:exitsystem(); break;
		default: handleErrorMessage();
		}
	}

	void guideTeacher4() {
		ItemBank newItemBank;
		newItemBank.createNewItemBank();
		splitline();
		int temTeacherChoice4;
		cout << "what else would you like to do?" << endl;
		cout << "1. Return ; 2. Exit" << endl;
		splitline();
		while (true) {
			try {
				cin >> temTeacherChoice4;
				if (temTeacherChoice4 == 1 || temTeacherChoice4 == 2) {
					break;
				}
				handleErrorMessage();
			}
			catch (...) {
				handleErrorMessage();
			}
		}
		splitline();
		switch (temTeacherChoice4) {
		case 1:guideTeacher(); break;
		case 2:exitsystem(); break;
		default: handleErrorMessage();
		}
	}

	void guideTeacher5() {
		exitsystem();
	}

	string getTeacherName() {
		return TeacherName;
	}

	string getTeacherID() {
		return TeacherID;
	}

	double getAvgScore() {
		double temAvgScore = 0;
		string temExamName, temClass;
		cout << "Please input the name of examination : ";
		cin >> temExamName;
		cout << "Please input the attend class : ";
		cin >> temClass;
		splitline();
		if (!judgeInput(temExamName, temClass)) {
			handleErrorMessage();
			return getAvgScore();
		}
		ifstream inFile11;
		string s;
		s = temExamName + "(" + temClass + ")" + "_Score_Sheet.csv";
		inFile11.open(s,ios::in);
		getline(inFile11, s);
		int temint = 0;
		while (getline(inFile11, s)) {
			temint++;
			vector<string> temvec;
			stringstream ss(s);
			string str;
			double temDouble = 0;
			while (getline(ss, str, ','))
				temvec.push_back(str);
			stringstream si;
			si << temvec[3];
			si >> temDouble;
			temAvgScore += temDouble;
		}
		return (temAvgScore / temint);
	}

	bool judgeInput(string EN, string C) {
		string str = EN + "(" + C + ")_Score_Sheet.csv";
		ifstream fin(str);
		if (!fin)
		{
			return false;
		}
		else return true;
	}

	bool judgeInputNumber(string strNumber) {
		string tems;
		ifstream inFile12;
		inFile12.open("AccountMessage", ios::in);
		getline(inFile12, tems);
		//vector<vector<string>> strArray;
		while (getline(inFile12, tems))
		{
			stringstream ss(tems);
			string str;
			vector<string> lineArray;
			while (getline(ss, str, ','))
				lineArray.push_back(str);
			if (lineArray[0] == strNumber) return false;
		}
		return true;
	}
};

int main() {
	//initClassList();
	//initAccountMessage();
	//initItemBankList();
	//initItemBankNameList();
	//initItemBankNameList();
	module NewModule;
	string NameFinished;
	if (NewModule.getStartChoice() == 1) {
		string NewStudentID = NewModule.getAnumber();
		string NewStudentName, NewStudentClass;
		std::vector<std::string> R;
		splitString(NewModule.getStudentNameandClass(NewStudentID), R, ",");
		//NameandClass = newModule.getStudentNameandClass(newStudentID);
		NewStudentName = R[0];
		NewStudentClass = R[1];
		NameFinished = NewStudentName;
		Student NewStudent(NewStudentID, NewStudentName, NewStudentClass);
		NewStudent.guideStudent();
	}

	else if (NewModule.getStartChoice() == 2) {
		string NewTeacherID = NewModule.getAnumber();
		Teacher NewTeacher = Teacher();
		string NewTeacherName = NewTeacher.getTeacherName();
		NameFinished = NewTeacherName;
		NewTeacher.guideTeacher();
	}
	cout << "Goodbye , " << NameFinished << endl;
	return 0;
}