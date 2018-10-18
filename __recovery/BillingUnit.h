//---------------------------------------------------------------------------
//#include callerID_h;
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#ifndef BillingUnitH
#define BillingUnitH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.StdCtrls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.StdCtrls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.StdCtrls.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "CallerID.h"

//---------------------------------------------------------------------------
class TfrmCallBilling : public TForm
{
__published:	// IDE-managed Components
	TBevel *Bevel1;
	TPanel *pnlTop;
	TImage *imgPnlTop;
	TEdit *edtStartTime;
	TEdit *edtendtime;
	TButton *btnCalcDuration;
	TListBox *lstOutput;
	TButton *btnSortExtension;
	TButton *btnTopExtension;
	TListBox *lstUniqueExtensions;
	TButton *btnUniqueExt;
	TPageControl *PgControl;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TListBox *ListBox1;
	TButton *Button1;
	TMemo *Memo1;
	TButton *save;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCalcDurationClick(TObject *Sender);
	void __fastcall btnSortExtensionClick(TObject *Sender);
	void __fastcall btnTopExtensionClick(TObject *Sender);
	void __fastcall btnUniqueExtClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall saveClick(TObject *Sender);
private:	// User declarations
	callerID user[100];
public:		// User declarations
	__fastcall TfrmCallBilling(TComponent* Owner);
	TStringList *myFileDataList;
	AnsiString ExtractField(AnsiString OneRecordLine, int FieldInd, int FieldCount);
	AnsiString HeadingData[12];
	void AddHeadings();

	float calcCost(int Duration);
	void ListData();

	// 1.1
	int calcCallDuration(AnsiString StartTime, AnsiString EndTime);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCallBilling *frmCallBilling;
//---------------------------------------------------------------------------
#endif
