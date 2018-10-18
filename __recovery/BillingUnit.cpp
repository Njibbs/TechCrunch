//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "BillingUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCallBilling *frmCallBilling;
//---------------------------------------------------------------------------
__fastcall TfrmCallBilling::TfrmCallBilling(TComponent* Owner)
	: TForm(Owner)
{
  //declaring headings for data
  HeadingData[0] = "CallDate";
  HeadingData[1] = "StartTime";
  HeadingData[2] = "EndTime";
  HeadingData[3] = "Extension";
  HeadingData[4] = "Called Nr";
  HeadingData[5] = "Provider";
  HeadingData[6] = "Duration";
  HeadingData[7] = "Cost";
  HeadingData[11] = "----------";



}
//---------------------------------------------------------------------------
AnsiString TfrmCallBilling::ExtractField(AnsiString OneRecordLine, int FieldInd, int FieldCount)
{
//05/04/2016,10:45:24,10:45:34,233,0846888816,Cell C
// 2.2 (10)
// declaring array dynamically
AnsiString* sFields = NULL;
sFields = new AnsiString[FieldCount];


AnsiString OneLine = OneRecordLine;
int CommaPos;
int iCount = 0;
//seperating data
while (OneLine.Pos(",") > 0)
{
   CommaPos = OneLine.Pos(",");
   sFields[iCount] = OneLine.SubString(1,CommaPos-1);
   OneLine = OneLine.Delete(1,CommaPos);
   iCount++;
}
 //return the field requested
sFields[iCount] = OneLine;
return sFields[FieldInd];


}
//---------------------------------------------------------------------------
void __fastcall TfrmCallBilling::FormCreate(TObject *Sender)
{
  //2.1 (3)
  //When the form is created data is loaded - TstringList is created dynamically
  myFileDataList = new TStringList;
  myFileDataList->LoadFromFile("MonthCallData.csv");

}
//---------------------------------------------------------------------------
void TfrmCallBilling::AddHeadings()
{
   AnsiString OneListLine;
   OneListLine = "";
	for (int i = 0; i < 8; i++) {
	  OneListLine = OneListLine + HeadingData[i] + "\t";
	}
   lstOutput->Items->Add(OneListLine);
   OneListLine = "";
	for (int i = 0; i < 8; i++) {
	  OneListLine = OneListLine + HeadingData[11]+ "\t";
	}
   lstOutput->Items->Add(OneListLine);

}
void __fastcall TfrmCallBilling::FormShow(TObject *Sender)
{ 
 //calling two class methods to run on form show
 AddHeadings();
 ListData();
}
//---------------------------------------------------------------------------
void TfrmCallBilling::ListData()
{ // 2.3  (12)
  int CallDuration;
  float CallCost;
  //Data is exctracted and displayed properly using tabs
  AnsiString OneListLine;
  OneListLine = "";

   for (int recordNr = 0; recordNr < 100; recordNr++)
  {



	for (int i = 0; i < 6; i++)
	 {
		OneListLine = OneListLine + ExtractField(myFileDataList->Strings[recordNr],i,6) + "\t";

	}
	  CallDuration = calcCallDuration(ExtractField(myFileDataList->Strings[recordNr],1,6)
	   ,ExtractField(myFileDataList->Strings[recordNr],2,6));
        // populating
	 user[recordNr].setValues(ExtractField(myFileDataList->Strings[recordNr], 0, 6),
	 ExtractField(myFileDataList->Strings[recordNr], 1, 6),
	 ExtractField(myFileDataList->Strings[recordNr], 2, 6),
	 ExtractField(myFileDataList->Strings[recordNr], 3, 6),
	 ExtractField(myFileDataList->Strings[recordNr], 4, 6),
	 ExtractField(myFileDataList->Strings[recordNr], 5, 6));
	OneListLine = OneListLine + IntToStr(CallDuration) + "\t";

	CallCost = calcCost(CallDuration);

	OneListLine = OneListLine + CurrToStrF(CallCost,ffCurrency,2) + "\t";


	lstOutput->Items->Add(OneListLine);
	OneListLine = "";
  }
}
//---------------------------------------------------------------------------

// 1.1  (7)
int TfrmCallBilling::calcCallDuration(AnsiString StartTime, AnsiString EndTime)
{
         // converting time to seconds using substrings
	//13:15:20
	int HH , MM , SS;
	int TotSecStart , TotSecEnd , Duration;

	TotSecStart = StrToInt(StartTime.SubString(1,2)) * 3600 +
				  StrToInt(StartTime.SubString(4,2)) * 60 +
				  StrToInt(StartTime.SubString(7,2));


	TotSecEnd =   StrToInt(EndTime.SubString(1,2)) * 3600 +
				  StrToInt(EndTime.SubString(4,2)) * 60 +
				  StrToInt(EndTime.SubString(7,2));

	Duration = TotSecEnd - TotSecStart;
	return Duration;
        //an alternative way to convert using a function plus the header
	/*
	TDateTime T1 , T2;
	T1 = StrToTime(StartTime);
	T2 = StrToTime(EndTime);
	return SecondsBetween(T2,T1);  // Needs   #include <DateUtils.hpp>
	*/

}

//---------------------------------------------------------------------------
void __fastcall TfrmCallBilling::btnCalcDurationClick(TObject *Sender)
{ // 1.2

 // pop up message to be displayed
  ShowMessage("The total seconds between " + edtStartTime->Text +
			  " and " + edtStartTime->Text + " is "  +
			  IntToStr(calcCallDuration(edtStartTime->Text,edtendtime->Text))
			  + " seconds");
}
//---------------------------------------------------------------------------
float TfrmCallBilling::calcCost(int Duration)
{
	return Duration * 0.0115;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCallBilling::btnSortExtensionClick(TObject *Sender)
{ // 2.4 [10]
   bool swopped = true;
   int iLast, iEnd;
   int out, c;
   int arrSize = myFileDataList->Count;
   iEnd = arrSize -1;
   // bubble sorting data
   while (swopped)
   {
      swopped = false;
      for ( c=0; c < iEnd; c++)
	  {
		 AnsiString Ext1 = ExtractField(myFileDataList->Strings[c],3,6);
		 AnsiString Ext2 = ExtractField(myFileDataList->Strings[c+1],3,6);
		 if (Ext1 > Ext2)
         {
			String txt = myFileDataList->Strings[c];
			myFileDataList->Strings[c] = myFileDataList->Strings[c+1];
			myFileDataList->Strings[c+1] = txt;
            swopped = true;
		 }
		 Application->ProcessMessages();
	  }
	  iEnd--;
      Application->ProcessMessages();
   }
 lstOutput->Clear();
 FormShow(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCallBilling::btnTopExtensionClick(TObject *Sender)
{
  // In this event we want to find the extension that has the highest value in its number

  int HighExTemp = 0;

  for (int recordNr = 0; recordNr < myFileDataList->Count; recordNr++) {
	  if (HighExTemp < StrToInt(ExtractField(myFileDataList->Strings[recordNr], 3, 6))) {
		 HighExTemp = StrToInt(ExtractField(myFileDataList->Strings[recordNr], 3, 6));
	  }
  }
  ShowMessage("Extension with the highest value is " +  IntToStr(HighExTemp));

}
//---------------------------------------------------------------------------

void __fastcall TfrmCallBilling::btnUniqueExtClick(TObject *Sender)
{
	AnsiString ExTemp = 0;
  for (int recordNr = 0; recordNr < myFileDataList->Count; recordNr++) {
	 ExTemp = ExtractField(myFileDataList->Strings[recordNr], 3, 6);
	 if (lstUniqueExtensions->Items->IndexOf(ExTemp) == -1) {
		lstUniqueExtensions->Items->Add(ExTemp);
	 }
  }
  lstUniqueExtensions->Sorted = true;
}
//---------------------------------------------------------------------------



void __fastcall TfrmCallBilling::Button1Click(TObject *Sender)
{
  for (int i = 0; i < lstOutput->Count; i++)
  {
	  ListBox1->Items->Add( IntToStr(user[i].getDuration()) + " : "
							+ user[i].getNumbers() +"\n"+
							 user[i].getDate());
	// displaying record
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmCallBilling::saveClick(TObject *Sender)
{
 // TStreamWriter *write = new TStreamWriter;
}
//---------------------------------------------------------------------------



