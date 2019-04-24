//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
 void GetSongName()
 {
    AnsiString filePath=MediaPlayer1->FileName;
    int startIndex=filePath.LastDelimiter("\\");
    int endIndex=filePath.LastDelimiter(".");
    AnsiString songName=filePath.SubString(startIndex+1,endIndex-startIndex-1);
  }
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 /*OpenDialog1->Execute();
 MediaPlayer1->FileName=OpenDialog1->FileName;
 AnsiString filePath=MediaPlayer1->FileName;
 int startIndex=filePath.LastDelimiter("\\");
 int endIndex=filePath.LastDelimiter(".");
 AnsiString songName=filePath.SubString(startIndex+1,endIndex-startIndex-1);
 Label1->Caption=songName;
 MediaPlayer1->Open();
 */
 if (OpenDialog1->Execute())
{ MediaPlayer1->FileName=OpenDialog1->FileName;
  GetSongName()   ;
  Label1->Caption=songName;
  MediaPlayer1->Open();
  ListBox1->Items->Add(songName);
}
}
//---------------------------------------------------------------------------




void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
 MediaPlayer1->Close();
MediaPlayer1->FileName=ListBox1->Items->Strings[ListBox1->ItemIndex];
MediaPlayer1->Open();
MediaPlayer1->Play();
}
//---------------------------------------------------------------------------

