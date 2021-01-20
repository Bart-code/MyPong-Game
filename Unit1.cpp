//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "mmsystem.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

        float x, y, a, b, speed;
        bool ballDirect;
        int BallStartPositionX , BallStartPositionY;
        AnsiString winner = "";

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BallInit( void )
        {
            BallTimer -> Enabled = false;
            x = BallStartPositionX;
            y = BallStartPositionY;
            a=1; speed = 10;
            b = y - x*a ;
            ballDirect = true;
            Ball -> Left = BallStartPositionX;
            Ball -> Top = BallStartPositionY;
            StartButton -> Visible = true;
        }
//---------------------------------------------------------------------------

bool __fastcall TForm1::takeLeftLife( void )
        {
            PlaySound( "LOSERSOUNDEFFECT" , HInstance, SND_ASYNC|SND_RESOURCE);
            if( leftLife3 -> Visible == true )
            {
               leftLife3 -> Visible = false;
               return false;
            }
            if( leftLife2 -> Visible == true )
            {
               leftLife2 -> Visible = false;
               return false;
            }
            if( leftLife1 -> Visible == true )
            {
               leftLife1 -> Visible = false;
               return true;
            }
            return true;
        }
//---------------------------------------------------------------------------

bool __fastcall TForm1::takeRightLife( void )
        {
            PlaySound( "LOSERSOUNDEFFECT" , HInstance, SND_ASYNC|SND_RESOURCE);
            if( rightLife3 -> Visible == true )
            {
               rightLife3 -> Visible = false;
               return false;
            }
            if( rightLife2 -> Visible == true )
            {
               rightLife2 -> Visible = false;
               return false;
            }
            if( rightLife1 -> Visible == true )
            {
               rightLife1 -> Visible = false;
               return true;
            }
            return true;
        }
//---------------------------------------------------------------------------
void __fastcall TForm1::gameWin( AnsiString whoWin)
        {
           Ball -> Enabled = false;
           winner = whoWin;
           Label1 -> Caption = winner + " player win !";
           if( winner == "Purple" )
           Label1 -> Font -> Color = clFuchsia;
           else Label1 -> Font -> Color = clBlue;
           Label1 -> Visible = true;
           Label2 -> Visible = true;
           Label3 -> Visible = true;
           StartButton -> Visible = false;
           MediaPlayer1 -> Pause();
           PlaySound( "WINGAME" , HInstance, SND_ASYNC|SND_RESOURCE);
        }
//---------------------------------------------------------------------------

void __fastcall TForm1::OnTimer(TObject *Sender)
{
        // Ruch prostoliniowy pi³ki
      if ( ballDirect ) x = x + speed;
      else  x = x - speed;
      y = a*x + b;
      Ball -> Left = x;
      Ball -> Top = y;
       // Warunek odbicia od sciany górnej
      if( Ball -> Top - Ball -> Height + 50 < 0 )
      {
          a=-a;
          b=-b;
          PlaySound( "BOUNCESOUND" , HInstance, SND_ASYNC|SND_RESOURCE);
      }
      // Warunek odbicia od sciany dolnej
      if ( Ball -> Top + Ball -> Height >=  Background -> Height )
      {
          a=-a;
          b = (-2)* a * Ball -> Left + b;
          PlaySound( "BOUNCESOUND" , HInstance, SND_ASYNC|SND_RESOURCE);

      }

      //Warunek przejscia pi³ki przez lew¹ granicê t³a
      if( Ball -> Left < LeftBat -> Left + LeftBat -> Width +5 )
      {    //Warunek odbicia od lewej paletki
          if( ( Ball -> Top + Ball -> Height > LeftBat -> Top ) &&
              ( Ball -> Top < LeftBat -> Top + LeftBat -> Height) )
          {
                a=-a;
                //Zmiana k¹ta
                if( Ball -> Top + Ball -> Height < LeftBat -> Top +  0.4 * LeftBat -> Height)
                {
                        a -= 0.5;
                        speed += 1;
                }
                if( Ball -> Top > LeftBat -> Top +  0.6 * LeftBat -> Height)
                {
                        a += 0.5;
                        speed -= 1;
                }
                b = Ball -> Top - Ball -> Left * a ;
                if( ballDirect == true ) ballDirect = false;
                else ballDirect = true;
                PlaySound( "BATHIT" , HInstance, SND_ASYNC|SND_RESOURCE);
                 speed++;
          }
          else
          {
                BallInit();
                if ( takeLeftLife() ) gameWin( "Blue");
          }
      }

      //Warunek przejscia pi³ki przez praw¹ granicê t³a
       if( Ball -> Left + Ball -> Width +5 > RightBat -> Left )
       {  //Warunek odbicia od prawej paletki
          if( ( Ball -> Top  < RightBat -> Top + RightBat -> Height ) &&
              ( Ball -> Top + Ball -> Height > RightBat -> Top ) )
           {
                a=-a;
                //Zmiana k¹ta
                if( Ball -> Top + Ball -> Height < RightBat -> Top +  0.3 * RightBat -> Height)
                {
                        a += 0.5;
                        speed += 1;
                }
                if( Ball -> Top > RightBat -> Top +  0.6 * RightBat -> Height)
                {
                        a -= 0.5;
                        speed -= 1;
                }
                b = Ball -> Top - Ball -> Left * a ;
                if( ballDirect == true ) ballDirect = false;
                else ballDirect = true;
                PlaySound( "BATHIT" , HInstance, SND_ASYNC|SND_RESOURCE);
                speed++;
            }
           else
           {
                BallInit();
                if ( takeRightLife() ) gameWin( "Purple");
           }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
     BallStartPositionX = Ball -> Left;;
     BallStartPositionY = Ball -> Top;
     BallInit();
     //if( Form1 -> Visible == true)
     PlaySound( "BACKGROUNDMUSIC" , HInstance, SND_ASYNC|SND_RESOURCE);
     //MediaPlayer1 -> FileName = "BACKGROUNDMUSIC";
     //MediaPlayer1 -> Open();
     Form2 -> Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
        Form1 -> SetFocus();
        BallTimer -> Enabled = true;
        //MediaPlayer1 -> Play();
        StartButton -> Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if( Key == 'Q' || Key == 'q' )  LeftBatTimerMoveUp -> Enabled = true;
        if( Key == 'A' || Key == 'a' )  LeftBatTimerMoveDown -> Enabled = true;
        if( Key == VK_UP   )  RightBatTimerMoveUp -> Enabled = true;
        if( Key == VK_DOWN )  RightBatTimerMoveDown -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftBatTimerMoveUpTimer(TObject *Sender)
{
     if ( LeftBat -> Top - 5 > Background -> Top )LeftBat -> Top -= 5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftBatTimerMoveDownTimer(TObject *Sender)
{
      if ( LeftBat -> Top + LeftBat -> Height + 5 < Background -> Height )
       LeftBat -> Top += 5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightBatTimerMoveUpTimer(TObject *Sender)
{
      if ( RightBat -> Top - 10 > Background -> Top ) RightBat -> Top -= 5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightBatTimerMoveDownTimer(TObject *Sender)
{
       if ( RightBat -> Top + RightBat -> Height + 5 < Background -> Height )
       RightBat -> Top += 5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if( Key == 'Q' || Key == 'q' )  LeftBatTimerMoveUp -> Enabled = false;
      if( Key == 'A' || Key == 'a' )  LeftBatTimerMoveDown -> Enabled = false;
      if( Key == VK_UP  )  RightBatTimerMoveUp -> Enabled = false;
      if( Key == VK_DOWN )  RightBatTimerMoveDown -> Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        MediaPlayer1 -> Close();
        Application -> Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label2Click(TObject *Sender)
{
      Label1 -> Visible = false;
      Label2 -> Visible = false;
      Label3 -> Visible = false;
      leftLife1 -> Visible = true;
      leftLife2 -> Visible = true;
      leftLife3 -> Visible = true;
      rightLife1 -> Visible = true;
      rightLife2 -> Visible = true;
      rightLife3 -> Visible = true;
      StartButton -> Visible = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label3Click(TObject *Sender)
{
        Form1 -> Visible = false;
        Form2 -> Visible = true;
}
//---------------------------------------------------------------------------

