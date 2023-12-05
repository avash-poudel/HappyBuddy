#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>

enum IDs {
	loginID = 1,
	signupID = 2,
	submitID = 3,
	logoutID = 4,
    homeID = 5,
    userID = 6,
    passID = 7,
    question1ID = 8,
    question2ID = 9,
    question3ID = 10,
    question4ID = 11,
    question5ID = 12,
    question6ID = 13,
    question7ID = 14,
    question8ID = 15,
    question9ID = 16,
    depressionSubmitID = 17,
    anxietySubmitID = 18,
    stressSubmitID = 19,
};

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    wxFont headerFont = wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	panel = new wxPanel(this);
	headlineText = new wxStaticText(panel, wxID_ANY, "HappyBuddy", wxPoint(40, 50), wxSize(300, -1), wxALIGN_CENTER_HORIZONTAL);
    headlineText->SetFont(headerFont);
	login = new wxButton(panel, loginID, "Login", wxPoint(110, 140));
	signUp = new wxButton(panel, signupID, "Sign Up", wxPoint(195, 140));
	userLabel = new wxStaticText(panel, wxID_ANY, "Username:", wxPoint(90, 90), wxDefaultSize, 0, wxStaticTextNameStr);
	passLabel = new wxStaticText(panel, wxID_ANY, "Password:", wxPoint(90, 120), wxDefaultSize, 0, wxStaticTextNameStr);
	userInput = new wxTextCtrl(panel, userID, "", wxPoint(170, 90));
	passInput = new wxTextCtrl(panel, passID, "", wxPoint(170, 120));
	ageLabel = new wxStaticText(panel, wxID_ANY, "Age:", wxPoint(90, 150), wxDefaultSize, 0, wxStaticTextNameStr);
	ageInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(170, 150), wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS));
	submit = new wxButton(panel, submitID, "Submit", wxPoint(160, 180));
    depressionSubmit = new wxButton(panel, depressionSubmitID, "Submit", wxPoint(350, 630));
    anxietySubmit = new wxButton(panel, anxietySubmitID, "Submit", wxPoint(350, 630));
    stressSubmit = new wxButton(panel, stressSubmitID, "Submit", wxPoint(350, 630));
    home = new wxButton(panel, homeID, "Home", wxPoint(300,10));
    home->Hide();
    depressionSubmit->Hide();
    anxietySubmit->Hide();
    stressSubmit->Hide();
    userLabel->Hide();
	passLabel->Hide();
	userInput->Hide();
	passInput->Hide();
	ageLabel->Hide();
	ageInput->Hide();
	submit->Hide();
	this->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this, loginID);
    this->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this, signupID);
    home->Bind(wxEVT_BUTTON, &MainFrame::OnHomeClick, this, homeID);
    submit->Bind(wxEVT_BUTTON, &MainFrame::OnSubmitClick, this, submitID);
    depressionSubmit->Bind(wxEVT_BUTTON, &MainFrame::OnDepressionSubmit, this, depressionSubmitID);
    anxietySubmit->Bind(wxEVT_BUTTON, &MainFrame::OnAnxietySubmit, this, anxietySubmitID);
    stressSubmit->Bind(wxEVT_BUTTON, &MainFrame::OnStressSubmit, this, stressSubmitID);

	this->SetSize(wxSize(400, 300));
    CreateStatusBar();
}

void MainFrame::OnButtonClick(wxCommandEvent& evt) {
    int id = evt.GetId();

    if (id == loginID || id == signupID)
    {
        userLabel->Show();
        passLabel->Show();
        userInput->Show();
        passInput->Show();
        submit->Show();
        home->Show();
        if (id == signupID)
        {
            ageLabel->Show();
            ageInput->Show();
        }
        login->Hide();
        signUp->Hide();
    }
    panel->Layout();
}

void MainFrame::OnHomeClick(wxCommandEvent& evt) {
    wxMessageDialog* dialog = new wxMessageDialog(this, "You will be logged out. Continue?", "Are you sure you want to go home?", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    int responce = dialog->ShowModal();
    if (responce == wxID_YES) {
        headlineText->Show();
        login->Show();
        signUp->Show();
        userLabel->Hide();
        passLabel->Hide();
        userInput->Hide();
        passInput->Hide();
        ageLabel->Hide();
        ageInput->Hide();
        submit->Hide();
        home->Hide();
        wxLogStatus("");
        userInput->SetValue("");
        passInput->SetValue("");
        ageInput->SetValue("");
        home->SetPosition(wxPoint(300, 10));
        this->SetSize(wxSize(400, 300));
        this->Center();
    }
    dialog->Destroy();
}

void MainFrame::OnSubmitClick(wxCommandEvent& evt) {
    std::string username = std::string(userInput->GetValue().mb_str());
    std::string password = std::string(passInput->GetValue().mb_str());
    if (username == "" || password == "") {
        wxLogStatus("Invalid username or password.");
    }else if (ageInput->IsShown()) {
        //signup code
        std::string temp = std::string(ageInput->GetValue().mb_str());
        int isUser = User::userAuthentication(username, password, 0);
        if (temp == "") {
            wxLogStatus("Please enter an age.");
        }else if (isUser == 1) {
            wxLogStatus("Username already used.");
        }
        else {
            int age = stoi(temp);
            User tempUser{ username, password, age};
            tempUser.createUser(tempUser);
            wxLogStatus("Sign up successful.");
        }
    } else {
        //login code
        int isUser = User::userAuthentication(username, password, 1);
        if (isUser == 2) {
            wxString message = wxString::Format("Signing in with username %s.", username);
            currentUser = username;
            wxLogStatus(message);
            std::vector<std::string> userData = User::getUserData(username);
            if (userData.size() == 0) {
                this->SetSize(wxSize(800, 1000));
                this->Center();
                userLabel->Hide();
                userInput->Hide();
                passLabel->Hide();
                passInput->Hide();
                submit->Hide();
                home->SetPosition(wxPoint(695, 10));
                int yPos = 100;
                std::vector<std::string> questions;
                questions.push_back("We will now begin the questionaire to diagnose any depressive behavior disorder! Over the last 2 weeks, how often have you been\nbothered by any of the following problems? 0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day");
                questions.push_back("1. Little interest or pleasure in doing things");
                questions.push_back("2. Feeling down, depressed, or hopeless");
                questions.push_back("3. Trouble falling or staying asleep, or sleeping too much");
                questions.push_back("4. Feeling tired or having little energy");
                questions.push_back("5. Poor appetite or overeating");
                questions.push_back("6. Feeling bad about yourself or that you are a failure or have let yourself or your family down");
                questions.push_back("7. Trouble concentrating on things, such as reading the newspaper or watching television");
                questions.push_back("8. Moving or speaking so slowly that other people could have noticed.Or the opposite being so figety or restless that you have been\nmoving around a lot more than usual");
                questions.push_back("9. Thoughts that you would be better off dead, or of hurting yourself");
                for (int i = 0; i < questions.size(); i++) {
                    depressionQuestionnaire.push_back(new wxStaticText(panel, wxID_ANY, questions[i], wxPoint(30, i * 50 + yPos), wxDefaultSize));
                }
                depressionAnswers.push_back(new wxTextCtrl(panel, question1ID, "", wxPoint(40, 170)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question2ID, "", wxPoint(40, 220)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question3ID, "", wxPoint(40, 270)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question4ID, "", wxPoint(40, 320)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question5ID, "", wxPoint(40, 370)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question6ID, "", wxPoint(40, 420)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question7ID, "", wxPoint(40, 470)));
                depressionAnswers.push_back(new wxTextCtrl(panel, question8ID, "", wxPoint(40, 535)));
                depressionQuestionnaire[9]->SetPosition(wxPoint(30, 565));
                depressionAnswers.push_back(new wxTextCtrl(panel, question9ID, "", wxPoint(40, 585)));
                depressionSubmit->Show();
            }
            else {
                std::string displayData = "";
                for (int i = 0; i < userData.size(); i++) {
                    displayData += userData[i];
                }
                std::vector<std::string> values;
                for (int i = 0; i < 26; i++) {
                    std::string tempString = displayData.substr(0, displayData.find(','));
                    displayData = displayData.substr(displayData.find(',')+1);
                    values.push_back(tempString);
                }
                int num = 0;
                displayData = "";
                displayData += "User: " + values[num++] + "\n";
                displayData += "\nAnswers scale: 0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day\n";
                displayData += "\nDepression Questions:";
                displayData += "\n1. Little interest or pleasure in doing things";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n2. Feeling down, depressed, or hopeless";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n3. Trouble falling or staying asleep, or sleeping too much";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n4. Feeling tired or having little energy";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n5. Poor appetite or overeating";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n6. Feeling bad about yourself or that you are a failure or have let yourself or your family down";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n7. Trouble concentrating on things, such as reading the newspaper or watching television";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n8. Moving or speaking so slowly that other people could have noticed.Or the opposite being so figety or restless that you have been\nmoving around a lot more than usual";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n9. Thoughts that you would be better off dead, or of hurting yourself";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n\nAnxiety Questions:";
                displayData += "\n1. Feeling nervous, anxious or on edge";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n2. Not being able to stop or control worrying";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n3. Worrying too much about different things";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n4. Trouble relaxing";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n5. Being so restless that it is hard to sit still";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n6. Becoming easily annoyed or irritable";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n7. Feeling afraid as if something awful might happen";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n\nStress Questions:";
                displayData += "\n1. Do you have trouble staying focused on the present moment";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n2. How often do you feel overwhelmed with your life";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n3. Do you struggle to fall asleep at night";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n4. On average, do you get less than 7-8 hours of sleep a night";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n5. Poor appetite or overeating";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n6. Do you experience headaches or muscle tension";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n7. Trouble concentrating on things, such as reading the newspaper or watching television";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n8. Moving or speaking so slowly that other people could have noticed.Or the opposite being so figety or restless that you have been\nmoving around a lot more than usual";
                displayData += "\n\tYour Answer: " + values[num++];
                displayData += "\n9. Do you feel irritable, annoyed, or angry over trivial issues";
                displayData += "\n\tYour Answer: " + values[num++];
                userLabel->Hide();
                userInput->Hide();
                passLabel->Hide();
                passInput->Hide();
                submit->Hide();
                this->SetSize(wxSize(800, 1100));
                this->Center();
                display = new wxStaticText(panel, wxID_ANY, displayData, wxPoint(30,100), wxDefaultSize);
            }
        }
        else {
            wxString message = wxString::Format("Invalid password for %s.", username);
            wxLogStatus(message);
        }
    }
}

void MainFrame::OnDepressionSubmit(wxCommandEvent& evt) {
    bool invalid = false;
    int answer;
    for (int i = 0; i < depressionAnswers.size(); i++) {
        try {
            answer = stoi(std::string(depressionAnswers[i]->GetValue().mb_str()));
        }
        catch (...) {
            wxLogMessage("Invalid Input");
        }
        
        if (answer < 0 || answer > 3) {
            invalid = true;
        }
    }
    if (invalid) {
        wxLogMessage("Invalid Input");
    }
    else {
        saveToFile.push_back(currentUser);
        for (int i = 0; i < depressionAnswers.size(); i++) {
            saveToFile.push_back(std::string(depressionAnswers[i]->GetValue().mb_str()));
        }
        depressionSubmit->Hide();
        int yPos = 100;
        std::vector<std::string> questions;
        questions.push_back("We will now begin the questionaire to diagnose any anxiety disorder! Over the last 2 weeks, how often have you been bothered\nby any of the following problems? 0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day");
        questions.push_back("1. Feeling nervous, anxious or on edge");
        questions.push_back("2. Not being able to stop or control worrying");
        questions.push_back("3. Worrying too much about different things");
        questions.push_back("4. Trouble relaxing");
        questions.push_back("5. Being so restless that it is hard to sit still");
        questions.push_back("6. Becoming easily annoyed or irritable");
        questions.push_back("7. Feeling afraid as if something awful might happen");
        for (int i = 0; i < questions.size(); i++) {
            anxietyQuestionnaire.push_back(new wxStaticText(panel, wxID_ANY, questions[i], wxPoint(30, i * 50 + yPos), wxDefaultSize));
        }
        anxietyAnswers.push_back(new wxTextCtrl(panel, question1ID, "", wxPoint(40, 170)));
        anxietyAnswers.push_back(new wxTextCtrl(panel, question2ID, "", wxPoint(40, 220)));
        anxietyAnswers.push_back(new wxTextCtrl(panel, question3ID, "", wxPoint(40, 270)));
        anxietyAnswers.push_back(new wxTextCtrl(panel, question4ID, "", wxPoint(40, 320)));
        anxietyAnswers.push_back(new wxTextCtrl(panel, question5ID, "", wxPoint(40, 370)));
        anxietyAnswers.push_back(new wxTextCtrl(panel, question6ID, "", wxPoint(40, 420)));
        anxietyAnswers.push_back(new wxTextCtrl(panel, question7ID, "", wxPoint(40, 470)));
        for (int i = 0; i < depressionQuestionnaire.size(); i++) {
            depressionQuestionnaire[i]->Hide();
        }
        for (int i = 0; i < depressionAnswers.size(); i++) {
            depressionAnswers[i]->Hide();
        }
        anxietySubmit->Show();
    }
}

void MainFrame::OnAnxietySubmit(wxCommandEvent& evt) {
    bool invalid = false;
    int answer;
    for (int i = 0; i < anxietyAnswers.size(); i++) {
        try {
            answer = stoi(std::string(anxietyAnswers[i]->GetValue().mb_str()));
        }
        catch (...) {
            wxLogMessage("Invalid Input");
        }

        if (answer < 0 || answer > 3) {
            invalid = true;
        }
    }
    if (invalid) {
        wxLogMessage("Invalid Input");
    }
    else {
        for (int i = 0; i < anxietyAnswers.size(); i++) {
            saveToFile.push_back(std::string(anxietyAnswers[i]->GetValue().mb_str()));
        }
        anxietySubmit->Hide();
        int yPos = 100;
        std::vector<std::string> questions;
        questions.push_back("We will now begin the questionaire to diagnose any stress disorder! Over the last 2 weeks, how often have you been bothered\nby any of the following problems? 0 = not at all | 1 = several days | 2 = More than half the days | 3 = Nearly every day");
        questions.push_back("1. Do you have trouble staying focused on the present moment");
        questions.push_back("2. How often do you feel overwhelmed with your life");
        questions.push_back("3. Do you struggle to fall asleep at night");
        questions.push_back("4. On average, do you get less than 7-8 hours of sleep a night");
        questions.push_back("5. Poor appetite or overeating");
        questions.push_back("6. Do you experience headaches or muscle tension");
        questions.push_back("7. Trouble concentrating on things, such as reading the newspaper or watching television");
        questions.push_back("8. Do you feel like withdrawing from family, friends, and isolating yourself");
        questions.push_back("9. Do you feel irritable, annoyed, or angry over trivial issues");
        for (int i = 0; i < questions.size(); i++) {
            stressQuestionnaire.push_back(new wxStaticText(panel, wxID_ANY, questions[i], wxPoint(30, i * 50 + yPos), wxDefaultSize));
        }
        stressAnswers.push_back(new wxTextCtrl(panel, question1ID, "", wxPoint(40, 170)));
        stressAnswers.push_back(new wxTextCtrl(panel, question2ID, "", wxPoint(40, 220)));
        stressAnswers.push_back(new wxTextCtrl(panel, question3ID, "", wxPoint(40, 270)));
        stressAnswers.push_back(new wxTextCtrl(panel, question4ID, "", wxPoint(40, 320)));
        stressAnswers.push_back(new wxTextCtrl(panel, question5ID, "", wxPoint(40, 370)));
        stressAnswers.push_back(new wxTextCtrl(panel, question6ID, "", wxPoint(40, 420)));
        stressAnswers.push_back(new wxTextCtrl(panel, question7ID, "", wxPoint(40, 470)));
        stressAnswers.push_back(new wxTextCtrl(panel, question8ID, "", wxPoint(40, 520)));
        stressAnswers.push_back(new wxTextCtrl(panel, question9ID, "", wxPoint(40, 570)));
        for (int i = 0; i < anxietyQuestionnaire.size(); i++) {
            anxietyQuestionnaire[i]->Hide();
        }
        for (int i = 0; i < anxietyAnswers.size(); i++) {
            anxietyAnswers[i]->Hide();
        }
        stressSubmit->Show();
    }
}

void MainFrame::OnStressSubmit(wxCommandEvent& evt) {
    bool invalid = false;
    int answer;
    for (int i = 0; i < stressAnswers.size(); i++) {
        try {
            answer = stoi(std::string(stressAnswers[i]->GetValue().mb_str()));
        }
        catch (...) {
            wxLogMessage("Invalid Input");
        }

        if (answer < 0 || answer > 3) {
            invalid = true;
        }
    }
    if (invalid) {
        wxLogMessage("Invalid Input");
    }
    else {
        for (int i = 0; i < stressAnswers.size(); i++) {
            saveToFile.push_back(std::string(stressAnswers[i]->GetValue().mb_str()));
        }
        std::ofstream csv("UserData.csv");
        if (!csv.is_open())
        {
            wxLogMessage("Could not open CSV file");
        }
        else
        {
            std::string temp;
            for (int i = 0; i < saveToFile.size(); i++) {
                temp += saveToFile[i] + ",";
            }
            temp = temp.substr(0, temp.length() - 1);
            csv << temp << std::endl;
            csv.close();
        }
        for (int i = 0; i < stressQuestionnaire.size(); i++) {
            stressQuestionnaire[i]->Hide();
        }
        for (int i = 0; i < stressAnswers.size(); i++) {
            stressAnswers[i]->Hide();
        }
        stressSubmit->Hide();
    }
}