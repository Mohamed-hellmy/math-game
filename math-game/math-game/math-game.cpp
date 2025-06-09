#include <iostream>
#include <string>

using namespace std;

enum enQusLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };
enum TwoNumbers { FirstNumber = 1, SecondNumber = 2 };
enum enAnswerType { Correct = 1, Wrong = 2, Draw = 3 };

struct stFinalResult
{
    short QusNumber;
    enQusLevel QusLevel;
    enOperType OperType;
    short CorrectAnswer = 0;
    short WrongAnswer = 0;
};

int ReadPositiveNumber(string Message)
{
    int Number = 0;
    do
    {
        cout << Message;
        cin >> Number;
    } while (Number == 0);

    return Number;
}

char ReadText(string Message)
{
    char Text;
    cout << Message;
    cin >> Text;
    return Text;
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int NumberQusLevel(enQusLevel QusLevel)
{
    switch (QusLevel)
    {
    case Easy:
        return RandomNumber(1, 10);
    case Med:
        return RandomNumber(11, 50);
    case Hard:
        return RandomNumber(51, 100);
    case MixLevel:
        return RandomNumber(1, 100);
    default:
        return 0;
    }
}

enOperType ChooseMixOperation(enOperType OperationType)
{
    return (enOperType)RandomNumber(1, 4);
}

void PrintOperationType(enOperType OperationType)
{
    switch (OperationType)
    {
    case Add:
        cout << "+" << endl;
        break;
    case Sub:
        cout << "-" << endl;
        break;
    case Mul:
        cout << "*" << endl;
        break;
    case Div:
        cout << "/" << endl;
        break;
    default:
        cout << "Invalid Operation Type" << endl;
    }
}

void SetWinnerScreenColor(enAnswerType AnswerType)
{
    switch (AnswerType)
    {
    case enAnswerType::Correct:
        system("color 2F"); // Green
        break;
    case enAnswerType::Wrong:
        system("color 4F"); // Red
        cout << "\a"; // Beep
        break;
    case enAnswerType::Draw:
        system("color 6F"); // Yellow
        break;
    }
}

void ResetScreen()
{
    system("cls");
    system("Color 0F");
}

void PrintOperationResult(int FirstNumber, int SecondNumber, enOperType OperType, stFinalResult& FinalResult)
{
    int Result = 0;

    if (OperType == Div && SecondNumber == 0)
    {
        cout << "Division by zero is not allowed. Skipping this question." << endl;
        return;
    }

    switch (OperType)
    {
    case Add:
        Result = FirstNumber + SecondNumber;
        break;
    case Sub:
        Result = FirstNumber - SecondNumber;
        break;
    case Mul:
        Result = FirstNumber * SecondNumber;
        break;
    case Div:
        Result = FirstNumber / SecondNumber;
        break;
    default:
        cout << "Invalid Operation Type" << endl;
        break;
    }

    int UserAnswer = ReadPositiveNumber("Enter your answer: ");
    if (UserAnswer == Result)
    {
        enAnswerType enAnswerType = enAnswerType::Correct;
        cout << "Correct!" << endl;
        SetWinnerScreenColor(enAnswerType);
        FinalResult.CorrectAnswer++;
    }
    else
    {
        enAnswerType enAnswerType = enAnswerType::Wrong;
        SetWinnerScreenColor(enAnswerType::Wrong);
        cout << "Wrong! The correct answer is: " << Result << endl;
        FinalResult.WrongAnswer++;
    }
}

void QuestionOperation(stFinalResult& FinalResult)
{
    for (int Round = 1; Round <= FinalResult.QusNumber; Round++)
    {
        int FirstNumber = NumberQusLevel(FinalResult.QusLevel);
        int SecondNumber = NumberQusLevel(FinalResult.QusLevel);

        enOperType CurrentOp;
        if (FinalResult.OperType == Mix)
        {
            CurrentOp = ChooseMixOperation(FinalResult.OperType);
        }
        else
        {
            CurrentOp = FinalResult.OperType;
        }

        cout << "\nQuestion[" << Round << "/" << FinalResult.QusNumber << "]\n \n";
        cout << FirstNumber << "\n";
        PrintOperationType(CurrentOp);
        cout << SecondNumber << "\n";
        cout << "______________\n";
        PrintOperationResult(FirstNumber, SecondNumber, CurrentOp, FinalResult);
    }
}

void ShowGameOverScreen()
{
    cout << "\n\n------------------------------------------------------------\n\n";
    cout << "                 +++F I N A L   R E S U L T +++\n\n";
    cout << "------------------------------------------------------------\n\n";
}

void PrintFinalResult(stFinalResult& stFinalResult)
{
    cout << "Total Questions: " << stFinalResult.QusNumber << endl;
    cout << "Correct Answers: " << stFinalResult.CorrectAnswer << endl;
    cout << "Wrong Answers: " << stFinalResult.WrongAnswer << endl;
    if (stFinalResult.CorrectAnswer > stFinalResult.WrongAnswer)
    {
        cout << "You Win!" << endl;
        SetWinnerScreenColor(enAnswerType::Correct);
    }
    else if (stFinalResult.CorrectAnswer < stFinalResult.WrongAnswer)
    {
        cout << "You Lose!" << endl;
        SetWinnerScreenColor(enAnswerType::Wrong);
    }
    else
    {
        cout << "It's a Tie!" << endl;
        SetWinnerScreenColor(enAnswerType::Draw);
    }
}

void StartGame()
{
    stFinalResult stFinalResult;
    char Choice = 'y';

    do

    {
        ResetScreen();
        stFinalResult.QusNumber = ReadPositiveNumber("Enter the number of questions you want to answer: ");
        stFinalResult.QusLevel = (enQusLevel)ReadPositiveNumber("Enter the level of questions you want to answer (1: Easy, 2: Medium, 3: Hard, 4: Mix): ");
        stFinalResult.OperType = (enOperType)ReadPositiveNumber("Enter the type of operation you want to practice (1: Addition, 2: Subtraction, 3: Multiplication, 4: Division, 5: Mix): ");

        QuestionOperation(stFinalResult);
        ShowGameOverScreen();
        PrintFinalResult(stFinalResult);
        Choice = ReadText("You Want To Play Again: [y] / [n] ? ");
    } while (Choice == 'y' || Choice == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
