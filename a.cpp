#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Base
{
public:
    int w;                    // weight in kg
    int h;                    // height in cm
    int age;                  // age in years
    char gender;              // gender 
    float bmi;                // bmi value
    float bmr;                // basal metabolic rate
    float tdee;               // total daily energy expenditure
    int targetCalories;       // target daily calorie intake
    vector<string> exercises; // suggested exercises

    void calc_bmi()
    {
        float hh = h / 100.0;
        bmi = w / (hh * hh);
        cout << "Your BMI: " << bmi << " | ";
    }

    void calc_bmr()
    {
        if (gender == 'M' || gender == 'm')
        {
            bmr = 88.362 + (13.397 * w) + (4.799 * h) - (5.677 * age);
        }
        else if (gender == 'F' || gender == 'f')
        {
            bmr = 447.593 + (9.247 * w) + (3.098 * h) - (4.330 * age);
        }
        else
        {
            throw invalid_argument("Invalid gender input");
        }
    }

    void calc_tdee()
    {
        float activityFactor;
        cout << "Select your activity level:\n";
        cout << "1. Sedentary (little or no exercise)\n";
        cout << "2. Lightly active (light exercise/sports 1-3 days/week)\n";
        cout << "3. Moderately active (moderate exercise/sports 3-5 days/week)\n";
        cout << "4. Very active (hard exercise/sports 6-7 days a week)\n";
        cout << "5. Super active (very hard exercise/sports & physical job)\n";
        cout << "Enter the number corresponding to your activity level: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            activityFactor = 1.2;
            break;
        case 2:
            activityFactor = 1.375;
            break;
        case 3:
            activityFactor = 1.55;
            break;
        case 4:
            activityFactor = 1.725;
            break;
        case 5:
            activityFactor = 1.9;
            break;
        default:
            activityFactor = 1.2;
            cout << "Invalid choice. Defaulting to Sedentary.\n";
        }

        tdee = bmr * activityFactor;
    }

    void determine()
    {
        try
        {
            if (bmi < 16.5)
            {
                cout << "You are severely underweight!";
                suggest_exercises("severely underweight");
                targetCalories = tdee + 700; // Increase calorie intake significantly to gain weight
            }
            else if (bmi >= 16.5 && bmi <= 18.5)
            {
                cout << "You are underweight!";
                suggest_exercises("underweight");
                targetCalories = tdee + 500; // Increase calorie intake to gain weight
            }
            else if (bmi >= 18.6 && bmi <= 24.9)
            {
                cout << "You are a healthy weight!";
                suggest_exercises("healthy");
                targetCalories = tdee; // Maintain current calorie intake
            }
            else if (bmi >= 25.0 && bmi <= 29.9)
            {
                cout << "You are overweight!";
                suggest_exercises("overweight");
                targetCalories = tdee - 500; // Decrease calorie intake to lose weight
            }
            else if (bmi >= 30.0 && bmi <= 40.0)
            {
                cout << "You are obese!";
                suggest_exercises("obese");
                targetCalories = tdee - 1000; // Decrease calorie intake significantly to lose weight
            }
            else
            {
                cout << "BMI out of range!";
                throw out_of_range("BMI out of range");
            }

            cout << "\nTarget daily calorie intake to reach a healthy weight: " << targetCalories << " kcal\n";
        }
        catch (exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void suggest_exercises(string category)
    {
        if (category == "severely underweight")
        {
            exercises = {"Light cardio (15 mins)", "Strength training (10 mins)", "Yoga (10 mins)"};
        }
        else if (category == "underweight")
        {
            exercises = {"Light cardio (20 mins)", "Strength training (15 mins)", "Yoga (15 mins)"};
        }
        else if (category == "healthy")
        {
            exercises = {"Cardio (30 mins)", "Strength training (30 mins)", "Yoga (20 mins)"};
        }
        else if (category == "overweight")
        {
            exercises = {"Cardio (45 mins)", "Strength training (30 mins)", "Pilates (20 mins)"};
        }
        else if (category == "obese")
        {
            exercises = {"Low-impact cardio (45 mins)", "Strength training (20 mins)", "Stretching (20 mins)"};
        }

        cout << "\nSuggested Exercises:\n";
        for (const string &exercise : exercises)
        {
            cout << "- " << exercise << endl;
        }
    }

    Base()
    {
        try
        {
            cout << "Enter your weight (kg): ";
            cin >> w;
            cout << "Enter your height (cm): ";
            cin >> h;
            cout << "Enter your age (years): ";
            cin >> age;
            cout << "Enter your gender (M/F): ";
            cin >> gender;
            calc_bmi();
            calc_bmr();
            calc_tdee();
            determine();
        }
        catch (exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

int main()
{
    Base obj;
    return 0;
}
