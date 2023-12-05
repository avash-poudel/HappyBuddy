#pragma once

#include "User.h"
#include "User.h"
#include <wx/wx.h>
#include <vector>
#include <sstream>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	std::string currentUser;
	std::vector<std::string> saveToFile;
	wxPanel* panel;
	wxButton* home;
	wxStaticText* display;

	int stresslvl = 0;
	int depressionlvl = 0;
	int anxietylvl = 0;

	//home page
	wxStaticText* headlineText;
	wxButton* login;
	wxButton* signUp;
	wxButton* depressionSubmit;
	wxButton* anxietySubmit;
	wxButton* stressSubmit;
	wxButton* diagnosisButton;

	//login and sign up page
	wxStaticText* userLabel;
	wxStaticText* passLabel;
	wxStaticText* ageLabel;
	wxTextCtrl* userInput;
	wxTextCtrl* passInput;
	wxTextCtrl* ageInput;
	wxButton* submit;	

	//ask questions page
	std::vector<wxStaticText*> depressionQuestionnaire;
	std::vector<wxTextCtrl*> depressionAnswers;
	std::vector<wxStaticText*> anxietyQuestionnaire;
	std::vector<wxTextCtrl*> anxietyAnswers;
	std::vector<wxStaticText*> stressQuestionnaire;
	std::vector<wxTextCtrl*> stressAnswers;

	//advice page
	wxStaticText* diagnosis;
	wxStaticText* advice;

	void OnButtonClick(wxCommandEvent& evt);
	void OnHomeClick(wxCommandEvent& evt);
	void OnSubmitClick(wxCommandEvent& evt);
	void OnDepressionSubmit(wxCommandEvent& evt);
	void OnAnxietySubmit(wxCommandEvent& evt);
	void OnStressSubmit(wxCommandEvent& evt);
	void ShowAdviceAndDiagnosisStress(wxCommandEvent& evt);
	void ShowAdviceAndDiagnosisAnxiety(wxCommandEvent& evt);
	void ShowAdviceAndDiagnosis(wxCommandEvent& evt);
};

