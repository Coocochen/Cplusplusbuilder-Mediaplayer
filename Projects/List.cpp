//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "chen.h"
#include "List.h"
#include "mylove.h"
#include "songword.h"
#include <sstream>      //ʹ���ַ�����Ҫ������ͷ
#include <string>       //��׼c++�е��ַ���������ͷ�ļ�
#include <fstream>      //��׼c++�е��ļ�������ͷ
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
using namespace std;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
 CoocoMediaPlayer-> MediaPlayer1->Close();
 AnsiString ListItem = ListBox1->Items->Strings[ListBox1->ItemIndex];
 //�ҳ������ļ���
 int startIndex2 = ListItem.LastDelimiter(":");
  int endIndex2 = ListItem.Length();
  CoocoMediaPlayer->MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
  //�ҳ�����
  AnsiString filePath =CoocoMediaPlayer-> MediaPlayer1->FileName;
  int startIndex = filePath.LastDelimiter("\\");
  int endIndex = filePath.LastDelimiter(".");
  AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

  CoocoMediaPlayer->Label1->Caption = songName;
  CoocoMediaPlayer->Label1->Left = 0;
  CoocoMediaPlayer->MediaPlayer1->Open();
  CoocoMediaPlayer->MediaPlayer1->Play();
  CoocoMediaPlayer->SpeedButton2->Visible = true;
  CoocoMediaPlayer->SpeedButton4->Visible = false;
  CoocoMediaPlayer->flag2 = 1;
  CoocoMediaPlayer->FindSongWord(CoocoMediaPlayer->MediaPlayer1->FileName);


}

//---------------------------------------------------------------------------




