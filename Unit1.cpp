#include <iostream>
#include <vcl.h>
#include <cmath>
#include <alloc>
#include <string>

#pragma hdrstop

#include "Unit1.h"
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

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int nomer;

	for (nomer = 1; nomer < 2; nomer++)
	{

		int q=0, l=0, m=0, p=0;
		dL = 0;
		bool numfound = false;
		char *measuretext[] = {" ", "км/ч", "км", "ч", "мин"};

		ADOQuery1->Close();
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("SELECT * FROM `tablica` WHERE `nomer` =:param1");
		ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
		ADOQuery1->Open();
		AnsiString text = ADOQuery1->FieldByName("zadacha")->AsString;
		Memo_mass->Lines->Add(text);

		String word;

		do
		{
			q = text.Pos(" ");

			if (q == 0)
			{
				word = text;
			}

			else
			{
				word = text.SubString(1, q-1) ;
				text =  text.SubString(q+1, text.Length());
			}

			l = word.Length();
			p = word.Pos(",");
			m = word.Pos(".");

			if (l==m || l==p)
			{
			word = word.SubString(1, word.Length()-1);
			}

			if (numfound == true)
			{

				if(word=="ч"||word=="час"||word=="часа")
				{
					inputData [dL-1 ].measure = ttime;
				}

				else if(word=="км/ч"||word=="км/ч,"||word=="км/ч.")
				{
					inputData [dL-1 ].measure = tvelocity ;
				}

				else if(word=="км"||word=="км,"||word=="км.")
				{
					inputData [dL-1 ].measure = tacc;
				}

				else if(word=="мин"||word=="минут")
				{
					inputData [dL-1 ].measure = tmin;
				}

				numfound = false;
			}

			try
			{
				inputData[dL].value = word.ToDouble();
				numfound = true;
				dL++;
			}

			catch(const Exception& e)
			{

			}

			if(word=="два")
			{
				inputData [ dL ].value = 2;
				numfound = true;
				dL++;
				inputData [ dL-1 ].measure = ttime;
			}

			else if(word=="следующий")
			{
				inputData [ dL ].value = 1;
				numfound = true;
				dL++;
				inputData [ dL-1 ].measure = ttime;
			}

		} while (q);

//		for(i = 0; i < dL; i++)
//		{
//			Memo2->Lines->Add(FloatToStr(inputData[i].value)+ " " + measuretext[inputData[i].measure]);
//		}

	}
	nomer = 1;

//-----------------------------------------------------------------------------

	for (nomer = 1; nomer < 2; nomer++)
	{

		int iv=0, it=0, is=0, im=0;
		int i=0, j=0, n=0;
		double S=0, T=0, V=0;
		double v[10], t[10], s[10];

		for (int i=0; i < dL; i++)
		{

			if (inputData[i].measure == tvelocity)
			{
				v[iv] = inputData[i].value;
				iv++;
			}

			if (inputData[i].measure == tacc)
			{
				s[is] = inputData[i].value;
				is++;
			}

			 if (inputData[i].measure == ttime)
			{
				t[it] = inputData[i].value;
				it++;
			}
		}

		if (t[0]>s[0])
		{
			for (n=0; n<it; n++)
			{
				T=T+t[n];
				S=S+v[n]*t[n];
			}
		}

		else
		{
			for (j=0; j<is; j++)
			{
				T=T+s[j]/v[j];
				S=S+s[j];
			}
		}

		if (T==0)
		{
			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add("UPDATE `tablica` SET `otvet`=0 WHERE `nomer` =:param1");
//			ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
//			ADOQuery1->Open();

//			ADOQuery1->FieldByName("otvet")->AsString = 0;
			Memo3->Lines->Add("Ошибка, деление на ноль");
		}

		else
		{
			V=S/T;
			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add("UPDATE `tablica` SET `otvet`=V WHERE `nomer` =:param1");
//			ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
//			ADOQuery1->Open();

//			ADOQuery1->FieldByName("otvet")->AsString = V;
			Memo3->Lines->Add(V);
		}

	}
}


//---------------------------------------------------------------------------

/*
void __fastcall TForm1::Button5Click(TObject *Sender)
{
	int z=0, iv=0, it=0, is=0, im=0;
	String text = Memo1->Lines->GetText();
	z = text.Pos("Расстояние");
	if (z == 0)
	{
		Memo3->Lines->Add("Условие найдено");
		double x=0, x1=0, x2=0, a=0, b=0, c=0, tt=0, xx=0;
		double v[10], t[10], s[10], m[10];
		int i;
		for (i = 0; i < dL; i++)
		{
			if (inputData[i].measure == tvelocity)
			{
				v[iv] = inputData[i].value;
				iv++;
			}
			if (inputData[i].measure == tacc)
			{
				s[is] = inputData[i].value;
				is++;
			}
			 if (inputData[i].measure == ttime)
			{
				t[it] = inputData[i].value;
				it++;
			}
			if (inputData[i].measure == tmin)
			{
				m[im] = inputData[i].value;
				im++;
			}
		}
		tt=t[0]-m[0]/60;
		xx=tt*v[0]*v[0]-s[0]*v[0]*2;
		x=sqrt(xx/tt);
		Memo3->Lines->Add(x);
	}
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
		Memo3->Lines->Add("Условие найдено");
//		prouzvod[0]=231;
//		prouzvod[1]=462;
//		prouzvod[2]=1;
//		prouzvod[3]=4;
//		prouzvod[4]=11;
		double a=0, b=0, c=0, x1=0, x2=0, g=0;
		double chislo1=0, chislo2=0, menshe=0, vremya=0;
		chislo1=prouzvod[0];
		chislo2=prouzvod[1];
		menshe=prouzvod[3];
		vremya=prouzvod[4];
		//chislo1/x-chislo2/x+bolshe=vremya
		if (prouzvod[2]==1)
		{
			a=1;
			b=chislo2/vremya-chislo1/vremya+menshe;
			c=-(chislo1/vremya)*menshe;
			g=(b*b-4*a*c);
			if (g>0)
			{
				 x1=(-1*b+sqrt(g))/(2*a);
				 x2=(-1*b-sqrt(g))/(2*a);
			}
			else
			{
				Memo3->Lines->Add("Нет решения");
			}
			if (x1>0)
			{
				Memo3->Lines->Add(x1);
			}
			else
			{
				Memo3->Lines->Add(x2);
			}
		}
		else
		{
			a=1;
			b=chislo1/vremya-chislo2/vremya+menshe;
			c=-(chislo2/vremya)*menshe;
			g=(b*b-4*a*c);
			if (g>0)
			{
				 x1=(-1*b+sqrt(g))/(2*a);
				 x2=(-1*b-sqrt(g))/(2*a);
			}
			else
			{
				Memo3->Lines->Add("Нет решения");
			}
			if (x1>0)
			{
				Memo3->Lines->Add(x1);
			}
			else
			{
				Memo3->Lines->Add(x2);
			}
		}
}

void __fastcall TForm1::Button7Click(TObject *Sender)
{
		int iv=0, it=0, is=0, im=0;
		Memo3->Lines->Add("Условие найдено");
		double x1=0, x2=0, a=0, b=0, c=0, g=0;
		double v[10], t[10], s[10];
		int i=0;
		for (i = 0; i < dL; i++)
		{
			if (inputData[i].measure == tvelocity)
			{
				v[iv] = inputData[i].value;
				iv++;
			}
			if (inputData[i].measure == tacc)
			{
				s[is] = inputData[i].value;
				is++;
			}
			 if (inputData[i].measure == ttime)
			{
				t[it] = inputData[i].value;
				it++;
			}
		}
		a=s[1]/v[0]-t[0];
		b=-s[0]*v[0];
		c=-v[0]*v[0]*(s[1]/v[0]-t[0]);
		g=(b*b-4*a*c);
		if (g>0)
		{
			x1=(-1*b+sqrt(g))/(2*a);
			x2=(-1*b-sqrt(g))/(2*a);
		}
		else
		{
			Memo3->Lines->Add("Нет решения");
		}
		if (x1>0)
		{
			Memo3->Lines->Add(x1);
		}
		else
		{
			Memo3->Lines->Add(x2);
		}
		//Memo3->Lines->Add(a);
}
*/

void __fastcall TForm1::Button4Click(TObject *Sender)
{

		//	jdbc_server_init(0, NULL, NULL);
		//	JDBC* db = jdbc_init(NULL);
		//	jdbc_real_connect(db, "lab4db", "root", "password", "aidb", 0, NULL, 0);
		//	AnsiString query = "SELECT * FROM test1 where id='" + Edit1->Text + "'";
		//	jdbc_query(db, query.c_str());
		//	JDBC_RES* result = jdbc_store_result(db);
		//	JDBC_ROW row = jdbc_fetch_row(result);
		//	if (row) {
		//	Label1->Caption = row[1];
		//	}else{
		//	Label1->Caption = "Error";
		//	}
		//	jdbc_close(db);
		//	jdbc_server_end();


			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add("SELECT * FROM `slova` WHERE `sinonim` =:param1");
			ADOQuery1->Parameters->ParamByName("param1")->Value = Edit2->Text;
			ADOQuery1->Open();
			AnsiString str = ADOQuery1->FieldByName("groups")->AsString;
			Label2->Caption=str;

}


//---------------------------------------------------------------------------

void __fastcall TForm1::razbivkaClick(TObject *Sender)
{
	int p=0, i=0, l=0, m=0, n=0, k=0;
	dL = 0;
	char *measuretext[] = {" ", "км/ч", "км", "ч", "мин"};
	int nomer;

	for (nomer = 1; nomer < 2; nomer++)
	{

		ADOQuery1->Close();
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("SELECT * FROM `tablica` WHERE `nomer` =:param1");
		ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
		ADOQuery1->Open();
		AnsiString text = ADOQuery1->FieldByName("zadacha")->AsString;

//		AnsiString str = ADOQuery1->FieldByName("otvet")->AsString;
//		String text = Memo1->Lines->GetText();

		String word;     																	//(char **) преобразование к типу
		words = 0;                                                                         	//NULL - указатель на 0
		char *pc = 0;
		words_number = 0;

		do
		{
			p = text.Pos(" ");

			if (p == 0)
			{
				word = text;
			}

			else
			{
				word = text.SubString(1, p-1) ;
				text = text.SubString(p+1, text.Length());
			}

			l = word.Length();
			n = word.Pos(",");
			m = word.Pos(".");
			k = word.Pos("—");

			if (l==m || l==n || l==k)
			{
				word = word.SubString(1, word.Length()-1);
			}

			pc = (char *)malloc(word.Length()+1);

			if (pc == NULL)
			{
				return;
			}

			words_number++;

			if (words == NULL)
			{
				words = (char **)malloc(words_number * sizeof(char *));                           //sizeof возвращает количесвто байт заполненное этим типом
			}

			else
			{
				words = (char **)realloc(words, words_number * sizeof(char *));
			}

			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, word.c_str(), -1, pc, word.Length()+1, NULL, NULL);
			words[words_number - 1] = pc;

		}while (p);

//		for(i = 0; i < words_number; i++)
//		{
//			Memo_mass->Lines->Add(words[i]);
//		}

	}
	nomer = 1;


//---------------------------------------------------------------------------

		for (nomer = 1; nomer < 2; nomer++)
		{

		float rt;
		float result;


		randomize();
		for(int i = 0; i < words_number; i++)
		{
			rt = scanf(words[i], "%f", &result);

			if (rt>0)
			{
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("UPDATE `tablica` SET `zadacha`= rand()%30+" " WHERE `nomer` =:param1");
				ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
				ADOQuery1->Open();
			}

			else
			{
				String query;
				query = ("SELECT `sinonim` FROM `slova` WHERE `groups` =(SELECT `groups` FROM `slova` WHERE `sinonim`=\"");
				query = query + words[i]+"\")";
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add(query);
				ADOQuery1->Open();
				AnsiString str = ADOQuery1->FieldByName("sinonim")->AsString;

				if (str=="")
				{
					ADOQuery1->Close();
					ADOQuery1->SQL->Clear();
					ADOQuery1->SQL->Add("UPDATE `tablica` SET `zadacha`=:param2 WHERE `nomer` =:param1");
//					ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
//					ADOQuery1->Parameters->ParamByName("param2")->Value = words[i]+' ';
//					ADOQuery1->Open();

//					ADOQuery1->FieldByName("zadacha")->AsString = ADOQuery1->FieldByName("zadacha")->AsString + words[i] + " ";
					Memo_slova->Text=Memo_slova->Text+words[i]+" ";
				}

				else
				{
					ADOQuery1->Close();
					ADOQuery1->SQL->Clear();
					ADOQuery1->SQL->Add("UPDATE `tablica` SET `zadacha`=param2 WHERE `nomer` =:param1");
//					ADOQuery1->Parameters->ParamByName("param1")->Value = nomer;
//					ADOQuery1->Parameters->ParamByName("param2")->Value = str+' ';
//					ADOQuery1->Open();

//					ADOQuery1->FieldByName("zadacha")->AsString = ADOQuery1->FieldByName("zadacha")->AsString + str + " ";
					Memo_slova->Text=Memo_slova->Text+str+" ";
				}

			}
		}
	}
}

//---------------------------------------------------------------------------

