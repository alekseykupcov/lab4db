//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <stdio.h>


class TForm1 : public TForm
{
	__published:	// IDE-managed Components
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TMemo *Memo2;
	TMemo *Memo3;
	TADOTable *ADOTable1;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TADOQuery *ADOQuery1;
	TEdit *Edit2;
	TButton *Button4;
	TLabel *Label1;
	TEdit *Edit3;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *razbivka;
	TMemo *Memo_mass;
	TMemo *Memo_slova;
	TDBGrid *DBGrid2;
	TADOTable *ADOTable2;
	TDataSource *DataSource2;
	TLabel *Label2;


//	void __fastcall Button1Click(TObject *Sender);
//	void __fastcall Edit1Press(TObject *Sender, System::WideChar &Key);
	void __fastcall Button2Click(TObject *Sender);
//	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
//	void __fastcall Button5Click(TObject *Sender);
//	void __fastcall Button6Click(TObject *Sender);
//	void __fastcall Button7Click(TObject *Sender);
	void __fastcall razbivkaClick(TObject *Sender);
//	void __fastcall zamenaClick(TObject *Sender);


	private:	// User declarations
	public:		// User declarations

	__fastcall TForm1(TComponent* Owner);

	enum Tmeasure {tvelocity = 1, tacc = 2, ttime = 3, tmin = 4};

	struct TinputData
	{
		 double value;
		 Tmeasure measure;

	}inputData[10];

	int dL;
	double prouzvod[];
	char **words;
	int words_number;

};

extern PACKAGE TForm1 *Form1;

#endif
