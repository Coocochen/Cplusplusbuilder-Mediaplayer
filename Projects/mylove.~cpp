//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 #include <sstream>      //使用字符串流要包含此头
#include <string>       //标准c++中的字符串类所需头文件
#include <fstream>      //标准c++中的文件流所需头
#include "mylove.h"
#include "chen.h"
#include "List.h"
#include "songword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
using namespace std;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
CoocoMediaPlayer-> MediaPlayer1->Close();
 AnsiString ListItem = ListBox1->Items->Strings[ListBox1->ItemIndex];
 //找出播放文件名
 int startIndex2 = ListItem.LastDelimiter(":");
  int endIndex2 = ListItem.Length();
  CoocoMediaPlayer->MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
  //找出歌名
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
  CoocoMediaPlayer->flag2 = 0;
  CoocoMediaPlayer->FindSongWord(CoocoMediaPlayer->MediaPlayer1->FileName);
  
}
//---------------------------------------------------------------------------

