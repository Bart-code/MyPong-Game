//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Label2Click(TObject *Sender)
{
        Form2 -> Visible =false;
        Form1 -> Visible =true;
        Form1 -> Label2Click(Form1);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label4Click(TObject *Sender)
{
        Application -> Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label3Click(TObject *Sender)
{
        Form3 -> Visible = true;
        Form2 -> Visible = false;
}
//---------------------------------------------------------------------------
