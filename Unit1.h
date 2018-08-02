//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>




#include <vector>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TOpenDialog *OpenDialog1;
    TMemo *Memo2;
    TPanel *Panel1;
    TLabel *Label1;
    TTimer *RunDelay;
    TProgressBar *ProgressBar1;
    TTimer *ProgressBarDelay;
    TTimer *UpdateDelay;
    TLabel *Label2;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall RunDelayTimer(TObject *Sender);
    void __fastcall ProgressBarDelayTimer(TObject *Sender);
    void __fastcall UpdateDelayTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif




//Global Vars
const AnsiString SERV_DIR = "Y:\\SUPPORT\\ConnectionInfo\\";


//Funcs
AnsiString GetCurDir();
void CopyFileFromServer(AnsiString sName, AnsiString sPathTo = "");
void ReplaceLine(TMemo *Memo, int nLine, AnsiString str);
void DBM(AnsiString str1, AnsiString str2 = "");
void DBM(AnsiString str1, int n);


//---------------------------------------------------------------------------
class StringsContainer
{
    public:
    std::vector<AnsiString> Vector;

    StringsContainer(){Vector.clear();}
    unsigned int BreakString(AnsiString str, AnsiString sDivider);
    int IndexOf(AnsiString sValue);
};
//---------------------------------------------------------------------------
class UpdateModule
{
    TMemo *Memo;
    int nParamLine; //—юда записываетс€ номер строки в конфиг файле дл€ последующего ее изменени€

    AnsiString GetConfigParam(AnsiString sParam);

    public:
    UpdateModule(){Memo = 0; nParamLine = -1;}
    UpdateModule(TMemo *InitMemo){Memo = InitMemo; nParamLine = -1;}
    
    AnsiString GetServerMainExeVersion();
    AnsiString GetCurrentMainExeVersion();
    void UpdateMainExe();
};
//---------------------------------------------------------------------------
