//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <sstream>      //使用字符串流要包含此头
#include <string>       //标准c++中的字符串类所需头文件
#include <fstream>      //标准c++中的文件流所需头
#include "List.h"
#include "chen.h"
#include "stdlib.h"
#include "mylove.h"
#include "songword.h"
using namespace std; 
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
int background = 1; //用于换肤
int p = 0; //用于歌词滚动
int flag2 = 0;
int sx;         
int startX;
int startY;
int index = -1;
int flag = 1;  //用于音量控制
int mylove[50];     //用于保存我喜欢选项
int trans[50];  //将我喜欢里的index转换为播放列表
TCoocoMediaPlayer *CoocoMediaPlayer;
//---------------------------------------------------------------------------
__fastcall TCoocoMediaPlayer::TCoocoMediaPlayer(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
 void TCoocoMediaPlayer::FindSongWord(AnsiString FileName)
 {
             //清空原来的歌词文件
          Form3->ListBox1->Items->Clear();
          Form3->ListBox2->Items->Clear();
          Form3->ListBox3->Items->Clear();
    //找到正在播放歌曲的歌词文件
          AnsiString str = Application->ExeName;
          int end = str.LastDelimiter("\\");
          str = str.SubString(0,end);
          AnsiString filePath =  MediaPlayer1->FileName;
          int startIndex = filePath.LastDelimiter("\\");
          int endIndex = filePath.LastDelimiter(".");
          AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

         AnsiString fileName =str+"songword\\"+songName+".lrc";

         //创建输入文件流
                ifstream lrcStream;
                lrcStream.open(fileName.c_str());
                //如果文件打开失败
                if(!lrcStream){
                        lrcStream.close();
                        return;
                }
                //如果文件打开成功
                char line[1024];
                string retString;
                //循环读取，每次读取一行存入line中
                while (!lrcStream.eof() ){ //eof()文件结束
                        memset(line,0,1024);
                        lrcStream.getline(line,1024);
                        retString += line;
                        retString += "\n";
                }

                lrcStream.close();
        //把接收到的AnsiString转换成string，再用string构造字符串流
        stringstream ss(retString);
        string item;
        //利用字符串流，把接收的字符串分割成一行行
        while (getline(ss, item, '\n')) {
                //把分割后的每行加入listbox
                Form3->ListBox1->Items->Add(item.c_str());
        }
        int i = 0;
        int start = 0;
       for(i = 0;i < Form3->ListBox1->Items->Count;i++ )
       {

            AnsiString ListWord = Form3->ListBox1->Items->Strings[i];
            //查找歌词何时开始
            startIndex = ListWord.LastDelimiter(":");
            endIndex = ListWord.LastDelimiter("]");
             AnsiString songTime = ListWord.SubString(startIndex+1,endIndex-startIndex-1);
              if(songTime == "0")
              {
                  start = i;
              }
          }
            //将歌词对应时间存在ListBox3中

            for(int j = start + 1; j < Form3->ListBox1->Items->Count;j++)
          {
            //将歌词存在listbox2中
            AnsiString ListWord = Form3->ListBox1->Items->Strings[j];
            startIndex = ListWord.LastDelimiter("]");
            endIndex = ListWord.Length();
            AnsiString songWord = ListWord.SubString(startIndex+1,endIndex-startIndex);
            Form3->ListBox2->Items->Add(songWord);

            //分

            startIndex = ListWord.LastDelimiter("[");
            endIndex = ListWord.LastDelimiter(":");
            AnsiString songMin = ListWord.SubString(startIndex+1,endIndex-startIndex-1);

            long double songMin2 = StrToFloat(songMin);
            //秒
             startIndex = ListWord.LastDelimiter(":");
            endIndex = ListWord.LastDelimiter(".");
            AnsiString songSec = ListWord.SubString(startIndex+1,endIndex-startIndex-1);

            long double songSec2 = StrToFloat(songSec);
            //毫秒
             startIndex = ListWord.LastDelimiter(".");
            endIndex = ListWord.LastDelimiter("]");
            AnsiString songMSec = ListWord.SubString(startIndex+1,endIndex-startIndex-1);

            long double songMSec2 = StrToFloat(songMSec);
            //时间
            long double songtime = songMin2*60*1000+songSec2*1000+songMSec2;
            int songtime2 = songtime/1000;
            AnsiString strTime =FloatToStr(songtime2);
            Form3->ListBox3->Items->Add(strTime);

          }
        };


void __fastcall TCoocoMediaPlayer::Button1Click(TObject *Sender)
{
 if (OpenDialog1->Execute())
{
  MediaPlayer1->FileName = OpenDialog1->FileName;

  AnsiString filePath = MediaPlayer1->FileName;
  int startIndex = filePath.LastDelimiter("\\");
  int endIndex = filePath.LastDelimiter(".");
  AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

  Label1->Caption = songName;
  MediaPlayer1->Open();
   //将播放名+地址放进ListBox
  for(int i=0;i<OpenDialog1->Files->Count;i++)
  {
    AnsiString song = OpenDialog1->Files->Strings[i];

    startIndex = song.LastDelimiter("\\");
    endIndex = song.LastDelimiter(".");
    songName = song.SubString(startIndex+1,endIndex-startIndex-1);
    AnsiString Listsong = songName+"             地址:"+song;
    Form1->ListBox1->Items->Add(Listsong) ;
  }
}
}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



void __fastcall TCoocoMediaPlayer::Timer1Timer(TObject *Sender)
{
   //歌名从左向右滚动
  Label1->Left = Label1->Left+1;
  if(Label1->Left > Panel1->Width)
  {
   Label1->Left = -Label1->Width;
   }
     //判断循环方式
     
   if(SpeedButton6->Visible)   //单曲循环
   {
         if(MediaPlayer1->Position == MediaPlayer1->Length)
         {
           MediaPlayer1->Position = MediaPlayer1->Start;
           MediaPlayer1->Play();
         }
         MediaPlayer1->Notify = true;
    }


    else if(SpeedButton8->Visible )     //列表循环
    {
        if(MediaPlayer1->Position == MediaPlayer1->Length)
        {
           if(flag2 == 1)
           {
            if(Form1->ListBox1->ItemIndex == Form1->ListBox1->Items->Count-1){
            Form1->ListBox1->ItemIndex = 0;
             } else{
            Form1->ListBox1->ItemIndex++;
                }

           ListItem = Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
         }
        else
    {
          if(Form2->ListBox1->ItemIndex == Form2->ListBox1->Items->Count-1){
                Form2->ListBox1->ItemIndex = 0;
            } else{
               Form2->ListBox1->ItemIndex++;
          }
         ListItem = Form2->ListBox1->Items->Strings[Form2->ListBox1->ItemIndex];
    }
     //找出播放文件名
     int startIndex2 = ListItem.LastDelimiter(":");
     int endIndex2 = ListItem.Length();
      MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
      //找出歌名
       AnsiString filePath = MediaPlayer1->FileName;
      int startIndex = filePath.LastDelimiter("\\");
      int endIndex = filePath.LastDelimiter(".");
      AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

       Label1->Caption = songName;
       Label1->Left = 0;
       MediaPlayer1->Open();
       MediaPlayer1->Play();
       FindSongWord(MediaPlayer1->FileName);
       SpeedButton2->Visible = true;
       SpeedButton4->Visible = false;
      }
        MediaPlayer1->Notify = true;
  

    }
     else  if(SpeedButton9->Visible)     //随机播放
     {
       if(MediaPlayer1->Position == MediaPlayer1->Length)
        {
           //判断播放列表
           if(flag2 == 1)
           {
            Form1->ListBox1->ItemIndex = rand()%Form1->ListBox1->Items->Count;

          ListItem = Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
           }
           else
           {
              Form2->ListBox1->ItemIndex = rand()%Form2->ListBox1->Items->Count;

           ListItem = Form2->ListBox1->Items->Strings[Form2->ListBox1->ItemIndex];
           }
     //找出播放文件名
     int startIndex2 = ListItem.LastDelimiter(":");
     int endIndex2 = ListItem.Length();
      MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
      //找出歌名
       AnsiString filePath = MediaPlayer1->FileName;
      int startIndex = filePath.LastDelimiter("\\");
      int endIndex = filePath.LastDelimiter(".");
      AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

       Label1->Caption = songName;
       Label1->Left = 0;
       MediaPlayer1->Open();
       MediaPlayer1->Play();
       
       SpeedButton2->Visible = true;
       SpeedButton4->Visible = false;
      }
        MediaPlayer1->Notify = true;
          

     }
     //进度条
     SpeedButton11->Left = MediaPlayer1->Position*(440 - 64)/MediaPlayer1->Length +64;

     //时间

     int time = MediaPlayer1->Position/1000;
     int min = time/60;
     int sec = time%60;
     AnsiString str = Application->ExeName;

     int end = str.LastDelimiter("\\");
     str = str.SubString(0,end);

     Image6->Picture->LoadFromFile(str+"image\\"+(min/10)+".bmp");
     Image7->Picture->LoadFromFile(str+"image\\"+(min%10)+".bmp");
     Image8->Picture->LoadFromFile(str+"image\\"+(sec/10)+".bmp");
     Image9->Picture->LoadFromFile(str+"image\\"+(sec%10)+".bmp");

     //判断是否我喜欢
     if(flag2 == 1 )      //当前为播放列表时
     {
    if( mylove[Form1->ListBox1->ItemIndex] == 1)
     {
        SpeedButton12->Visible = true;
        SpeedButton13->Visible = false;
     }
     else
     {
        SpeedButton12->Visible = false;
        SpeedButton13->Visible = true;

      }
     }


     //歌词向上滚动
     AnsiString Pos = FloatToStr(MediaPlayer1->Position/1000);

     int index = Form3->ListBox3->Items->IndexOf(Pos);
     if(index != -1)
     {
       if(index == 1)
       {
       Form3->Label1->Caption = "";
       Form3->Label2->Caption = Form3->ListBox2->Items->Strings[index-1] ;
       Form3->Label3->Caption = Form3->ListBox2->Items->Strings[index] ;
       Form3->Label4->Caption = Form3->ListBox2->Items->Strings[index+1] ;
       Form3->Label5->Caption = Form3->ListBox2->Items->Strings[index+2] ;
       }
       else if(index == 0)
       {
       Form3->Label1->Caption = "";
       Form3->Label2->Caption = "";
       Form3->Label3->Caption = Form3->ListBox2->Items->Strings[index] ;
       Form3->Label4->Caption = Form3->ListBox2->Items->Strings[index+1] ;
       Form3->Label5->Caption = Form3->ListBox2->Items->Strings[index+2] ;
       }
       else if(index == Form3->ListBox2->Count - 1)
       {
       Form3->Label1->Caption = Form3->ListBox2->Items->Strings[index-2];
       Form3->Label2->Caption = Form3->ListBox2->Items->Strings[index-1] ;
       Form3->Label3->Caption = Form3->ListBox2->Items->Strings[index] ;
       Form3->Label4->Caption = "" ;
       Form3->Label5->Caption = "" ;
        }
        else if(index == Form3->ListBox2->Count - 2)
        {
       Form3->Label1->Caption = Form3->ListBox2->Items->Strings[index-2];
       Form3->Label2->Caption = Form3->ListBox2->Items->Strings[index-1] ;
       Form3->Label3->Caption = Form3->ListBox2->Items->Strings[index] ;
       Form3->Label4->Caption = Form3->ListBox2->Items->Strings[index+1] ;
       Form3->Label5->Caption = "" ;
       }
       else
       {
       Form3->Label1->Caption = Form3->ListBox2->Items->Strings[index-2];
       Form3->Label2->Caption = Form3->ListBox2->Items->Strings[index-1] ;
       Form3->Label3->Caption = Form3->ListBox2->Items->Strings[index] ;
       Form3->Label4->Caption = Form3->ListBox2->Items->Strings[index+1] ;
       Form3->Label5->Caption = Form3->ListBox2->Items->Strings[index+2] ;
        }
        p = index;
       }
     else
     {
       Form3->Label3->Caption = Form3->ListBox2->Items->Strings[p];
     }

}
//---------------------------------------------------------------------------
 void __fastcall TCoocoMediaPlayer::SpeedButton5Click(TObject *Sender)
{
//上一首
 if(Form1->ListBox1->Items->Count == 0)
     {
        Label1->Caption = "无歌曲播放";
     }
     else
 {
   //判断播放为我喜欢列表还是播放列表
   if(flag2 == 1)
 {
if(Form1->ListBox1->ItemIndex == 0){
      Form1->ListBox1->ItemIndex = Form1->ListBox1->Items->Count-1;
} else{
    Form1->ListBox1->ItemIndex--;
    }

    ListItem = Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
   }
  else
  {
    if(Form2->ListBox1->ItemIndex == 0){
      Form2->ListBox1->ItemIndex =  Form2->ListBox1->Items->Count-1;
} else{
    Form2->ListBox1->ItemIndex--;
    }

    ListItem = Form2->ListBox1->Items->Strings[Form2->ListBox1->ItemIndex];
   }
   //找出播放文件名
  int startIndex2 = ListItem.LastDelimiter(":");
  int endIndex2 = ListItem.Length();
   MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
   //找出歌名
   AnsiString filePath = MediaPlayer1->FileName;
   int startIndex = filePath.LastDelimiter("\\");
   int endIndex = filePath.LastDelimiter(".");
   AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

    Label1->Caption = songName;
    Label1->Left = 0;
    MediaPlayer1->Open();
    MediaPlayer1->Play();
    SpeedButton2->Visible = true;
    SpeedButton4->Visible = false;
     FindSongWord(MediaPlayer1->FileName);
    }


}

//---------------------------------------------------------------------------





void __fastcall TCoocoMediaPlayer::SpeedButton2Click(TObject *Sender)
{
    //歌曲暂停
    MediaPlayer1->Stop();
    SpeedButton4->Visible = true;
    SpeedButton2->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton3Click(TObject *Sender)
{
//下一首
   if(Form1->ListBox1->Items->Count == 0)
     {
        Label1->Caption = "无歌曲播放";
     }
     else

{
   //判断播放为我喜欢列表还是播放列表
   if(flag2 == 1)       //播放列表
 {
if(Form1->ListBox1->ItemIndex == Form1->ListBox1->Items->Count-1){
      Form1->ListBox1->ItemIndex = 0;
} else{
    Form1->ListBox1->ItemIndex++;
    }

    ListItem = Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
   }
  else
  {
    if(Form2->ListBox1->ItemIndex == Form2->ListBox1->Items->Count-1){
      Form2->ListBox1->ItemIndex = 0;
} else{
    Form2->ListBox1->ItemIndex++;
    }

   ListItem = Form2->ListBox1->Items->Strings[Form2->ListBox1->ItemIndex];
   }
   //找出播放文件名
  int startIndex2 = ListItem.LastDelimiter(":");
  int endIndex2 = ListItem.Length();
   MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
   //找出歌名
   AnsiString filePath = MediaPlayer1->FileName;
   int startIndex = filePath.LastDelimiter("\\");
   int endIndex = filePath.LastDelimiter(".");
   AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

    Label1->Caption = songName;
    Label1->Left = 0;
    MediaPlayer1->Open();
    MediaPlayer1->Play();
    SpeedButton2->Visible = true;
    SpeedButton4->Visible = false;
    FindSongWord(MediaPlayer1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton1Click(TObject *Sender)
{
 if (OpenDialog1->Execute())
{
  MediaPlayer1->FileName = OpenDialog1->FileName;

  AnsiString filePath = MediaPlayer1->FileName;
  int startIndex = filePath.LastDelimiter("\\");
  int endIndex = filePath.LastDelimiter(".");
  AnsiString songName  = filePath.SubString(startIndex+1,endIndex-startIndex-1);

  Label1->Caption = songName;
  MediaPlayer1->Open();
   //将播放名+地址放进ListBox
  for(int i=0;i<OpenDialog1->Files->Count;i++)
  {
    AnsiString song = OpenDialog1->Files->Strings[i];

    startIndex = song.LastDelimiter("\\");
    endIndex = song.LastDelimiter(".");
    songName = song.SubString(startIndex+1,endIndex-startIndex-1);
    AnsiString Listsong = songName+"             地址:"+song;
    Form1->ListBox1->Items->Add(Listsong) ;
  }
}
    if(Form1->ListBox1->Items->Count == 0)
     {
        Label1->Caption = "无歌曲播放";
     }
     else
     {
    flag2 = 1;
     MediaPlayer1->Open();
      MediaPlayer1->Play();
      SpeedButton2->Visible = true;
      SpeedButton4->Visible = false;
      Timer1->Enabled = true;
      //初始化我喜欢
      for(int j = 0;j < 50; j++)
    {
       mylove[j] = 0;
    }
    for(int i = 0;i < 50; i++)
    {
       trans[i] = 0;
    }
    FindSongWord(MediaPlayer1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton4Click(TObject *Sender)
{
    //播放歌曲
     if(Form1->ListBox1->Items->Count == 0)
     {
        Label1->Caption = "无歌曲播放";
     }
     else
     {
     MediaPlayer1->Play();
     SpeedButton4->Visible = false;
     SpeedButton2->Visible = true;
     }

     
}
//---------------------------------------------------------------------------







void __fastcall TCoocoMediaPlayer::SpeedButton6Click(TObject *Sender)
{
  SpeedButton6->Visible = false;
  SpeedButton8->Visible = true;
  SpeedButton9->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton7Click(TObject *Sender)
{
      //显示列表窗体
      if(Form1->Visible == false){
          Form1->Left = CoocoMediaPlayer->Left - Form1->Width;
          Form1->Top = CoocoMediaPlayer->Top ;
          Form1->Show();
      }else{
          Form1->Hide();

          }
}
//---------------------------------------------------------------------------



void __fastcall TCoocoMediaPlayer::SpeedButton9Click(TObject *Sender)
{
   SpeedButton6->Visible = true;
   SpeedButton8->Visible = false;
   SpeedButton9->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton8Click(TObject *Sender)
{
   SpeedButton6->Visible = false;
   SpeedButton8->Visible = false;
   SpeedButton9->Visible = true;

}
//---------------------------------------------------------------------------


void __fastcall TCoocoMediaPlayer::SpeedButton10Click(TObject *Sender)
{
            this->Close();        
}
//---------------------------------------------------------------------------


void __fastcall TCoocoMediaPlayer::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
       if(Shift.Contains(ssLeft)){
         int moveX = X - startX;
         int moveY = Y - startY;
         CoocoMediaPlayer->Left = CoocoMediaPlayer->Left+moveX;
         Form1->Left = Form1->Left + moveX;
         Form2->Left = Form2->Left + moveX;
         Form3->Left = Form3->Left + moveX;
         CoocoMediaPlayer->Top = CoocoMediaPlayer->Top + moveY;
         Form1->Top = Form1->Top + moveY;
         Form2->Top = Form2->Top + moveY;
         Form3->Top = Form3->Top + moveY;
         }
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
         startX = X;
         startY = Y;
}
//---------------------------------------------------------------------------



void __fastcall TCoocoMediaPlayer::Image3MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if(Shift.Contains(ssLeft)){
         int moveX = X - startX;
         int moveY = Y - startY;
         CoocoMediaPlayer->Left = CoocoMediaPlayer->Left+moveX;
         Form1->Left = Form1->Left + moveX;
         Form2->Left = Form2->Left + moveX;
         Form3->Left = Form3->Left + moveX;
         CoocoMediaPlayer->Top = CoocoMediaPlayer->Top + moveY;
         Form1->Top = Form1->Top + moveY;
         Form2->Top = Form2->Top + moveY;
         Form3->Top = Form3->Top + moveY;
         }
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
         startX = X;
         startY = Y;        
}
//---------------------------------------------------------------------------






void __fastcall TCoocoMediaPlayer::SpeedButton11MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     sx = X;
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton11MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
     if(Shift.Contains(ssLeft)){
     int moveX = X - sx;
     SpeedButton11->Left = SpeedButton11->Left + moveX;
     MediaPlayer1->Position = MediaPlayer1->Length*(SpeedButton11->Left-64)/(440-64);
     MediaPlayer1->Play();
     }
}
//---------------------------------------------------------------------------


void __fastcall TCoocoMediaPlayer::TrackBar1Change(TObject *Sender)
{
   int volume =TrackBar1->Position*TrackBar1->Position*(65535/100);
   waveOutSetVolume(0,MAKELONG(0,MAKELONG(volume,volume)));
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton14Click(TObject *Sender)
{
    flag = flag + 1;
    if(flag % 2 == 0)
    {
      TrackBar1->Visible = true;
      }
      else
      {
       TrackBar1->Visible = false;
       }
}
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton13Click(TObject *Sender)
{
       //添加我喜欢
       if(Form1->ListBox1->Items->Count == 0)
     {
        Label1->Caption = "无歌曲播放";
     }
     else
     {
       SpeedButton12->Visible = true;
       SpeedButton13->Visible = false;
       mylove[Form1->ListBox1->ItemIndex] = 1;
       Form2->ListBox1->Items->Add(Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex]);
       index++;
       trans[index] = Form1->ListBox1->ItemIndex ;
       }
  }
//---------------------------------------------------------------------------


void __fastcall TCoocoMediaPlayer::SpeedButton12Click(TObject *Sender)
{

        if(flag2 == 1) //如果当前为播放列表则将歌曲从我喜欢列表中删除
      {
        SpeedButton12->Visible = false;
        SpeedButton13->Visible = true;
        mylove[Form1->ListBox1->ItemIndex] = 0;
        Form2->ListBox1->Items->Delete(Form2->ListBox1->ItemIndex);
        }
        if(flag2 == 0)//如果当前为我喜欢列表则删除歌曲并播放下一首
        {

          mylove[trans[Form2->ListBox1->ItemIndex]] = 0;
          index--;
          for( int i = Form2->ListBox1->ItemIndex;i < Form2->ListBox1->Items->Count-1;i++)
          {
                 trans[i] = trans[i+1];
          }
         //当我喜欢列表只有一首或零首
       if( Form2->ListBox1->Items->Count == 1)
        {
             Label1->Caption = "无歌曲播放";
             Form2->ListBox1->Items->Delete(Form2->ListBox1->ItemIndex);
             MediaPlayer1->Stop() ;
        }
        if( Form2->ListBox1->Items->Count == 0)
        {
             Label1->Caption = "无歌曲播放";
        }
        else
        {
          SpeedButton12->Visible = true;
        SpeedButton13->Visible = false;
          Form2->ListBox1->Items->Delete(Form2->ListBox1->ItemIndex);
         if(Form2->ListBox1->ItemIndex == Form2->ListBox1->Items->Count-1){
      Form2->ListBox1->ItemIndex = 0;
} else{
    Form2->ListBox1->ItemIndex++;
    }

    ListItem = Form2->ListBox1->Items->Strings[Form2->ListBox1->ItemIndex];
     int startIndex2 = ListItem.LastDelimiter(":");
  int endIndex2 = ListItem.Length();
   MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
   //找出歌名
   AnsiString filePath = MediaPlayer1->FileName;
   int startIndex = filePath.LastDelimiter("\\");
   int endIndex = filePath.LastDelimiter(".");
   AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

    Label1->Caption = songName;
    Label1->Left = 0;
    MediaPlayer1->Open();
    MediaPlayer1->Play();
    SpeedButton2->Visible = true;
    SpeedButton4->Visible = false;
    }
    }
 }
//---------------------------------------------------------------------------

void __fastcall TCoocoMediaPlayer::SpeedButton15Click(TObject *Sender)
{
         if(Form2->Visible == false){
          Form2->Left = CoocoMediaPlayer->Left - Form2->Width;
          Form2->Top = CoocoMediaPlayer->Top ;
          Form2->Show();
      }else{
          Form2->Hide();

          }
}
//---------------------------------------------------------------------------







void __fastcall TCoocoMediaPlayer::SpeedButton17Click(TObject *Sender)
{
       //当播放列表只有一首或零首
       if( Form1->ListBox1->Items->Count == 1)
        {
             Label1->Caption = "无歌曲播放";
             Form1->ListBox1->Items->Delete(Form1->ListBox1->ItemIndex);
             MediaPlayer1->Stop() ;
        }
        if( Form1->ListBox1->Items->Count == 0)
        {
             Label1->Caption = "无歌曲播放";
        }
        else
        {
          SpeedButton12->Visible = true;
        SpeedButton13->Visible = false;
          Form1->ListBox1->Items->Delete(Form1->ListBox1->ItemIndex);
          //播放下一首
         if(Form1->ListBox1->ItemIndex == Form1->ListBox1->Items->Count-1){
      Form1->ListBox1->ItemIndex = 0;
} else{
    Form1->ListBox1->ItemIndex++;
    }

    ListItem = Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
     int startIndex2 = ListItem.LastDelimiter(":");
  int endIndex2 = ListItem.Length();
   MediaPlayer1->FileName = ListItem.SubString(startIndex2+1,endIndex2-startIndex2);
   //找出歌名
   AnsiString filePath = MediaPlayer1->FileName;
   int startIndex = filePath.LastDelimiter("\\");
   int endIndex = filePath.LastDelimiter(".");
   AnsiString songName = filePath.SubString(startIndex+1,endIndex-startIndex-1);

    Label1->Caption = songName;
    Label1->Left = 0;
    MediaPlayer1->Open();
    MediaPlayer1->Play();
    FindSongWord(MediaPlayer1->FileName);
    SpeedButton2->Visible = true;
    SpeedButton4->Visible = false;
    }
}
//---------------------------------------------------------------------------





void __fastcall TCoocoMediaPlayer::SpeedButton18Click(TObject *Sender)
{

          //显示歌词窗体
      if(Form3->Visible == false){
          Form3->Left = CoocoMediaPlayer->Left ;
          Form3->Top = CoocoMediaPlayer->Top  ;
          Form3->Show();
      }else{
          Form3->Hide();

          }
         FindSongWord(MediaPlayer1->FileName);
    
}
//---------------------------------------------------------------------------










void __fastcall TCoocoMediaPlayer::SpeedButton16Click(TObject *Sender)
{
     AnsiString str = Application->ExeName;
     int end = str.LastDelimiter("\\");
     str = str.SubString(0,end);
     background = background * (-1);
     if(background == -1)  //换成海贼王皮肤
     {
         Image1->Visible = false;
         Image2->Visible = false;
         Form3->Image1->Visible = false;
         Form3->Image3->Visible = false;
         Form1->Image2->Visible = false;
         Form2->Image1->Visible = false;
         Label1->Font->Color = clWhite;
         Image4->Visible = false;
         SpeedButton11->Glyph->LoadFromFile(str+"image2\\"+"lufei.bmp");
         SpeedButton2->Glyph->LoadFromFile(str+"image2\\"+"kaishi2.bmp");
         SpeedButton4->Glyph->LoadFromFile(str+"image2\\"+"zanting2.bmp");
         SpeedButton3->Glyph->LoadFromFile(str+"image2\\"+"xia2.bmp");
         SpeedButton5->Glyph->LoadFromFile(str+"image2\\"+"shang2.bmp");
          SpeedButton17->Glyph->LoadFromFile(str+"image2\\"+"shanchu2.bmp");
          SpeedButton18->Glyph->LoadFromFile(str+"image2\\"+"ci2.bmp");
          SpeedButton10->Glyph->LoadFromFile(str+"image2\\"+"guanbi2.bmp");
          SpeedButton14->Glyph->LoadFromFile(str+"image2\\"+"yin2.bmp");
          SpeedButton1->Glyph->LoadFromFile(str+"image2\\"+"tianjia2.bmp");

     }
     else
     {
       Image1->Visible = true;
       Image2->Visible = true;
       Form3->Image1->Visible = true;
       Form3->Image3->Visible = true;
       Form1->Image2->Visible = true;
        Form2->Image1->Visible = true;
        Label1->Font->Color = clBlack;
        Image4->Visible = true;
        SpeedButton11->Glyph->LoadFromFile(str+"image2\\"+"hua.bmp");
         SpeedButton2->Glyph->LoadFromFile(str+"image2\\"+"kaishi1.bmp");
         SpeedButton4->Glyph->LoadFromFile(str+"image2\\"+"zanting1.bmp");
         SpeedButton3->Glyph->LoadFromFile(str+"image2\\"+"xia1.bmp");
          SpeedButton5->Glyph->LoadFromFile(str+"image2\\"+"shang1.bmp");
         SpeedButton17->Glyph->LoadFromFile(str+"image2\\"+"shanchu1.bmp");
         SpeedButton18->Glyph->LoadFromFile(str+"image2\\"+"ci1.bmp");
         SpeedButton10->Glyph->LoadFromFile(str+"image2\\"+"guanbi1.bmp");
         SpeedButton14->Glyph->LoadFromFile(str+"image2\\"+"yin1.bmp");
         SpeedButton1->Glyph->LoadFromFile(str+"image2\\"+"tianjia1.bmp");
     }
}
//---------------------------------------------------------------------------





