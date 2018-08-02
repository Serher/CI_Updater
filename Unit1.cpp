#define NO_WIN32_LEAN_AND_MEAN
#include <shlobj.h>

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <fstream>
//#define NO_WIN32_LEAN_AND_MEAN


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;





//---------------------------------------------------------------------------
AnsiString GetCurDir()
{
    TCHAR thBuffer[MAX_PATH];
    GetCurrentDirectory(sizeof(thBuffer),thBuffer);
    return AnsiString(thBuffer) + "\\";
}
//---------------------------------------------------------------------------
void CopyFileFromServer(AnsiString sName, AnsiString sPathTo)
{
    AnsiString sPathFrom = SERV_DIR + sName;
    if(sPathTo == "")
        sPathTo = GetCurDir();

    sPathTo+= sName;
    CopyFile(sPathFrom.c_str(), sPathTo.c_str(), false);
    /*
    if(!CopyFile(sPathFrom.c_str(), sPathTo.c_str(), false))
        DBM("CopyFileFailed!!! Path", sPathFrom);
    else
        DBM("AllGood!!! Path", sPathFrom);
    */
}
//---------------------------------------------------------------------------
void DBM(AnsiString str1, AnsiString str2)
{
    TMemo *Memo = Form1->Memo2;
    Memo->Lines->LoadFromFile("D:\\C++\\CLog.txt");
    if(str2 != "")
        str1+= " || "+str2;
    Memo->Lines->Add(str1);
    Memo->Lines->SaveToFile("D:\\C++\\CLog.txt");
}
//------------------------------------------------------------------------------
void DBM(AnsiString str1, int n)
{
    TMemo *Memo = Form1->Memo2;
    Memo->Lines->LoadFromFile("D:\\C++\\CLog.txt");
    if(str1 != "")
        str1+= " || "+IntToStr(n);
    else
        str1 = IntToStr(n);
    Memo->Lines->Add(str1);
    Memo->Lines->SaveToFile("D:\\C++\\CLog.txt");
}
//------------------------------------------------------------------------------
void ReplaceLine(TMemo *Memo, int nLine, AnsiString str)
{
    Memo->Lines->Delete(nLine);
    Memo->Lines->Insert(nLine, str);
}
//------------------------------------------------------------------------------
bool GetIsServerValid()
{
    AnsiString sPath = SERV_DIR + "ServerConfig.ini";
    std::ifstream F;
    F.open(sPath.c_str());
    if(F)
    {
        F.close();
        return true;
    }
return false;
}








//StringsContainer
//------------------------------------------------------------------------------
unsigned int StringsContainer::BreakString(AnsiString str, AnsiString sDivider)
{
    Vector.clear();

    AnsiString sTemp;
    int nDivLen = sDivider.Length();
    int nPos = str.AnsiPos(sDivider);
    while(nPos)
    {
        sTemp = str.SubString(0, nPos-1);
        Vector.push_back(sTemp);
        str.Delete(1, nPos+nDivLen-1);
        
        nPos = str.AnsiPos(sDivider);
    }
    if(str != "")
        Vector.push_back(str);//Запихиваем в вектор последнюю часть(то что осталось, если что-то осталось)

return Vector.size();
}
//------------------------------------------------------------------------------
int StringsContainer::IndexOf(AnsiString sValue)
{
    int nResult = -1;
    for(unsigned int i = 0; i<Vector.size(); i++)
    {
        if(Vector[i] == sValue)
        {
            nResult = i;
            return nResult;
        }
    }
return nResult;
}
//---------------------------------------------------------------------------





//UpdateModule
//------------------------------------------------------------------------------
AnsiString UpdateModule::GetConfigParam(AnsiString sParam)
{
    nParamLine = -1; //Номер строки в конфиг файле с искомым значением
    int i = 0;
    AnsiString sResult, sTemp;
    do
    {
        sTemp = Memo->Lines->Strings[i];
        if(sTemp == sParam)
        {
            sResult = Memo->Lines->Strings[++i];
            nParamLine = i;
        }
        i++;
    }while(i<Memo->Lines->Count && sResult == "");
return sResult;
}
//------------------------------------------------------------------------------
AnsiString UpdateModule::GetServerMainExeVersion()
{
    Memo->Lines->LoadFromFile(SERV_DIR + "ServerConfig.ini");
    return GetConfigParam("[EXE VERSION]");
}
//------------------------------------------------------------------------------
AnsiString UpdateModule::GetCurrentMainExeVersion()
{
    Memo->Lines->LoadFromFile(GetCurDir() + "Config.ini");
    return GetConfigParam("[EXE VERSION]");
}
//------------------------------------------------------------------------------
void UpdateModule::UpdateMainExe()
{                                                                               //DBM("UpdateMainExe", "Start!");
    AnsiString sServVersion = GetServerMainExeVersion();                        //DBM("sServVersion", sServVersion);
    AnsiString sCurVersion = GetCurrentMainExeVersion();                        //DBM("sCurVersion", sCurVersion);
    if(sServVersion != sCurVersion)
    {
        CopyFileFromServer("ConnectionInfo.exe");                               //DBM("after CopyFileFromServer", "!!!");
        ReplaceLine(Memo, nParamLine, sServVersion);
        Memo->Lines->SaveToFile(GetCurDir() + "Config.ini");
    }
}
//------------------------------------------------------------------------------
void RunMainExeAndCloseUpdater(AnsiString sExePath = "")
{                                                                               //DBM("RunMainExeAndCloseUpdater", "Start!");
    if(sExePath == "")
        sExePath = GetCurDir()+ "ConnectionInfo.exe";

    WinExec(sExePath.c_str(), 0);
    Form1->Close();
}


//------------------------------------------------------------------------------
void CreateShortCut(const AnsiString &file, AnsiString sPath, AnsiString sLocalDir)
{
    // IShellLink позволит нам создать ярлык.   
    // IPersistFile сохранит ярлык на жесткий диск С. 
    IShellLink* pLink;
    IPersistFile* pPersistFile;
 
    // Первым делом инициализируем COM библиотеку
    if(SUCCEEDED(CoInitialize(NULL)))
    {
        // Если инициализация прошла успешно, то получим
        // объект IShellLink вызвав CoCreateInstance.
        if(SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pLink)))
        {
            // если все прошло успешно - заполним атрибуты ярлыка
            pLink->SetPath(file.c_str());
            pLink->SetWorkingDirectory(sLocalDir.c_str());
            pLink->SetDescription("Апдейтер программы ConnectionInfo");
            pLink->SetShowCmd(SW_SHOW);

            // Теперь необходимо сохранить ярлык диске. Объект
            // IShellLink также содержит интерфейс IPersistFile.
            // Получим интерфейс IPersistFile вызвав QueryInterface.
            if(SUCCEEDED(pLink->QueryInterface(IID_IPersistFile, (void **)&pPersistFile)))
            {
                // Если все успешно, вызовем метод Save
                // объекта IPersistFile для сохранения/записи ярлыка.
                WideString strShortCutLocation(sPath + "\\ConnectionInfo.lnk");
                pPersistFile->Save(strShortCutLocation.c_bstr(), TRUE);
                pPersistFile->Release();
            }
            pLink->Release();
        } 
        // После вызова CoInitialize необходимо вызвать CoUninitialize 
        CoUninitialize();
    }
}

//http://www.cyberforum.ru/cpp-builder/thread638376.html
/*
void __fastcall TMain::Button17Click(TObject *Sender)
{
    AnsiString Dir;
    char stol[MAX_PATH];
    LPITEMIDLIST pidl;
    SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
    SHGetPathFromIDList(pidl, stol);
    Dir= stol;
    CreateLink(Edit1->Text ,"%WINDIR%" ,Dir+"\\Съемный диск "+Edit1->Text.SubString(1,1)+".lnk","Съемный диск","",SW_SHOWNORMAL);
}
*/

//------------------------------------------------------------------------------
void CreateShortcutOnDesktop(const AnsiString &file, AnsiString sLocalDir)
{
    AnsiString Dir;
    char stol[MAX_PATH];
    LPITEMIDLIST pidl;
    SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
    SHGetPathFromIDList(pidl, stol);
    Dir = stol;

    CreateShortCut(file, Dir, sLocalDir);
}







//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
    AnsiString sPath = GetCurDir()+ "Config.ini";                               //DBM("sPath || " + sPath);
    //Пробуем открыть инишку
    std::ifstream F;
    F.open(sPath.c_str());
    if(F)//просто обновление
    {
        F.close();                                                              //DBM("File Exist!");

        if(GetIsServerValid())
        {
            UpdateDelay->Enabled = true; //запускае апдейт через 2 сек
        }
        else
        {
            //Что-то выдать
            Label2->Visible = false; //Надпить обновление программы
            ProgressBar1->Visible = false;
            Panel1->Visible = true;
        }

    }
    else //"Инсталяция"
    {
        //Открыть диалог
        if(OpenDialog1->Execute())
        {
            //читаем выбранный путь
            AnsiString sExeLocalPath, sLocalDir = OpenDialog1->FileName;
            //разбиваем путь, чтобы пересобрать без имени файла
            StringsContainer stCont;
            stCont.BreakString(sLocalDir, "\\");
            //пересобираем
            sLocalDir = "";
            for(int i = 0; i<stCont.Vector.size()-1; i++)
                sLocalDir += stCont.Vector[i] + "\\";

            if(GetIsServerValid())
            {
                ProgressBarDelay->Enabled = true; //Включает ProgressBar
                CopyFileFromServer("ConnectionInfo.exe", sLocalDir);
                CopyFileFromServer("AdresBase.xlsx", sLocalDir);
                CopyFileFromServer("MessageBell.mp3", sLocalDir);
                //Self
                CopyFileFromServer("CI_Updater.exe", sLocalDir);
                //Config file
                Memo1->Lines->LoadFromFile(SERV_DIR + "ServerConfig.ini");
                Memo1->Lines->SaveToFile(sLocalDir + "Config.ini");

                sExeLocalPath = sLocalDir + "ConnectionInfo.exe";
                CreateShortcutOnDesktop(sExeLocalPath, sLocalDir);
                RunDelay->Enabled = true;
                //RunMainExeAndCloseUpdater(sExeLocalPath);
            }
            else
            {
                //Что-то выдать
                Label2->Visible = false; //Надпить обновление программы
                ProgressBar1->Visible = false;
                Panel1->Visible = true;
            }
        }
        else
            Form1->Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RunDelayTimer(TObject *Sender)
{                                                                               //DBM("Timer1Timer", "Start!");
    RunMainExeAndCloseUpdater();
    Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProgressBarDelayTimer(TObject *Sender)
{
    int nPos = ProgressBar1->Position;
    nPos+=25;
    if(nPos>100)
    {
        nPos = 100;
        ProgressBarDelay->Enabled = false;
    }
    ProgressBar1->Position = nPos;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UpdateDelayTimer(TObject *Sender)
{
    ProgressBarDelay->Enabled = true; //Включает ProgressBar
    UpdateModule updmod = UpdateModule(Memo1);
    updmod.UpdateMainExe();
    UpdateDelay->Enabled = false;
    RunDelay->Enabled = true; //пауза перед запуском основной проги
}
//---------------------------------------------------------------------------

