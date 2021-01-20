//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Background;
        TImage *Ball;
        TImage *RightBat;
        TImage *LeftBat;
        TTimer *BallTimer;
        TButton *StartButton;
        TTimer *LeftBatTimerMoveUp;
        TTimer *LeftBatTimerMoveDown;
        TTimer *RightBatTimerMoveUp;
        TTimer *RightBatTimerMoveDown;
        TMediaPlayer *MediaPlayer1;
        TImage *leftLife1;
        TImage *leftLife2;
        TImage *leftLife3;
        TImage *rightLife1;
        TImage *rightLife2;
        TImage *rightLife3;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        void __fastcall BallInit( void );
        bool __fastcall takeLeftLife( void );
        bool __fastcall takeRightLife( void );
        void __fastcall gameWin( AnsiString whoWin);
        void __fastcall OnTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall StartButtonClick(TObject *Sender);
        void __fastcall LeftBatTimerMoveUpTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall LeftBatTimerMoveDownTimer(TObject *Sender);
        void __fastcall RightBatTimerMoveUpTimer(TObject *Sender);
        void __fastcall RightBatTimerMoveDownTimer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Label2Click(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
