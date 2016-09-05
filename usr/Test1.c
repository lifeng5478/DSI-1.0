/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.28                          *
*        Compiled Jan 30 2015, 16:41:06                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "MESSAGEBOX.h"   //�õ�messagebox��������ʽ����������
#include "sim900a.h"
#include "GUI.H"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0    (GUI_ID_USER + 0x00)
#define ID_BUTTON_0    (GUI_ID_USER + 0x01)
#define ID_BUTTON_1    (GUI_ID_USER + 0x02)
#define ID_BUTTON_2    (GUI_ID_USER + 0x03)
#define ID_BUTTON_3    (GUI_ID_USER + 0x04)
#define ID_BUTTON_4    (GUI_ID_USER + 0x05)
#define ID_BUTTON_5    (GUI_ID_USER + 0x06)
#define ID_BUTTON_6    (GUI_ID_USER + 0x7)
#define ID_TEXT_0    (GUI_ID_USER + 0x08)
#define ID_TEXT_1    (GUI_ID_USER + 0x09)
#define ID_SLIDER_0    (GUI_ID_USER + 0x0A)
#define ID_SLIDER_1    (GUI_ID_USER + 0x0B)
#define ID_TEXT_2    (GUI_ID_USER + 0x0C)
#define ID_TEXT_3    (GUI_ID_USER + 0x0D)
#define ID_TEXT_4    (GUI_ID_USER + 0x0E)
#define ID_TEXT_5    (GUI_ID_USER + 0x0F)
#define ID_TEXT_6    (GUI_ID_USER + 0x10)
#define ID_TEXT_7    (GUI_ID_USER + 0x11)
#define ID_TEXT_8    (GUI_ID_USER + 0x12)
#define ID_TEXT_9    (GUI_ID_USER + 0x13)
#define ID_TEXT_10    (GUI_ID_USER + 0x14)
#define ID_IMAGE_0 (GUI_ID_USER + 0x15)
//#define ID_PROGBAR_0  (GUI_ID_USER + 0x16)
#define ID_IMAGE_0_IMAGE_0 0x00
#define ID_BUTTON_7   (GUI_ID_USER + 0x17)
#define ID_BUTTON_8   (GUI_ID_USER + 0x18)
#define ID_BUTTON_9   (GUI_ID_USER + 0x19)

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

int slider0,slider1,edit0,edit1,Text0,Text1,i,hbutton,Text9,m,Text10,Probar0;
	unsigned char ClickStart=0;
char *itoa(int value, char *string, int radix);
void OnSlider0ValueChanged(WM_MESSAGE * pMsg);
void OnSlider1ValueChanged(WM_MESSAGE * pMsg);
void OnSellectClicked(WM_MESSAGE*pMsg);
void OnStartClicked(WM_MESSAGE*pMsg);
void OnBUTTON1clicked(WM_MESSAGE*pMsg);
void StatusErro(void);
extern void _MessageBox(char * pText, char * pCaption);
extern void IMAGE_SetPNG   (IMAGE_Handle hObj, const void * pData, U32 FileSize);
void SetupsReturn(void);

extern int CCR1_Val;
extern int CCR2_Val;
char I2c_Buf_Write[1];

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "DS TEK", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button0", ID_BUTTON_0, 130, 30, 40, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button1", ID_BUTTON_1, 130, 80, 40, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button2", ID_BUTTON_2, 130, 130, 40, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button3", ID_BUTTON_3, 130, 180, 40, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button4", ID_BUTTON_4, 130, 230, 40, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Sellect", ID_BUTTON_5, 70, 321, 110, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Start", ID_BUTTON_6, 200, 321, 70, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Setup", ID_BUTTON_7, 600, 321, 70, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "1", ID_TEXT_0, 640, 220, 150, 50, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "1", ID_TEXT_1, 640, 90, 150, 50, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "SMS Status", ID_TEXT_9, 310, 360, 150, 40, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "GSM return", ID_TEXT_10, 310, 250, 150, 60, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 1000, 1000, 250, 70, 0, 0x0, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_1, 1000, 1000, 250, 70, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "FF Master", ID_TEXT_2, 480, 235, 155, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "MF Master", ID_TEXT_3, 480, 100, 155, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Status", ID_TEXT_4, 20, 30, 80, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "FF", ID_TEXT_5, 20, 180, 80, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "MF", ID_TEXT_6, 20, 130, 80, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Pump", ID_TEXT_7, 20, 80, 80, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Sensor", ID_TEXT_8, 20, 230, 80, 40, 0, 0x0, 0 },
 { IMAGE_CreateIndirect, "Image", ID_IMAGE_0, 211, -3, 356, 55, 0, 0, 0 },
 //  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 384, 186, 226, 13, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
extern unsigned char _acImage_0[5410] ;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsong40;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontnumber;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontxuanxiang24;
extern GUI_CONST_STORAGE GUI_BITMAP bmoff;
extern GUI_CONST_STORAGE GUI_BITMAP bmON;
extern GUI_CONST_STORAGE GUI_BITMAP bmBT1;
extern GUI_CONST_STORAGE GUI_BITMAP bmBT2;
extern GUI_CONST_STORAGE GUI_BITMAP bmBT3;
extern GUI_CONST_STORAGE GUI_BITMAP bmblueBT1;
extern GUI_CONST_STORAGE GUI_BITMAP bmblueBT2;
extern GUI_CONST_STORAGE GUI_BITMAP bmOK;
extern GUI_CONST_STORAGE GUI_BITMAP bmcancle;
// USER START (Optionally insert additional static code)

static const void * _GetImageById(U32 Id, U32 * pSize) {
  switch (Id) {
  case ID_IMAGE_0_IMAGE_0:
    *pSize = sizeof(_acImage_0);
    return (const void *)_acImage_0;
  }
  return NULL;
}
// USER END



/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
	U32          FileSize;
	const void * pData;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'DS TEK'
    //
    hItem = pMsg->hWin;
   // FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
  //  FRAMEWIN_SetTitleHeight(hItem, 25);
//    FRAMEWIN_SetFont(hItem, GUI_FONT_20_1);
 //   FRAMEWIN_SetTextColor(hItem, 0x000000FF);
		FRAMEWIN_SetClientColor(hItem,0X625B57);
		 FRAMEWIN_SetTitleVis(hItem, 0);
//��ʾͼ��
	   hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_0);
    pData = _GetImageById(ID_IMAGE_0_IMAGE_0, &FileSize);
    IMAGE_SetPNG(hItem, pData, FileSize);
	

		//�õ���ֵ
		slider0=WM_GetDialogItem(pMsg->hWin,ID_SLIDER_0);
		SLIDER_SetRange(slider0,0,100);
    SLIDER_SetValue(slider0,1);
    slider1=WM_GetDialogItem(pMsg->hWin,ID_SLIDER_1);
		SLIDER_SetRange(slider1,0,100);
		Text0 = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0); 
	  Text1 = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1); 
	  Text9 = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
		Text10 = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);

//	Probar0=WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
		BUTTON_SetFocussable(hItem,0);
		BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmBT1,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmBT2,0,0);
    BUTTON_SetText(hItem, "");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
		BUTTON_SetFocussable(hItem,0);
				BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmBT1,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmBT2,0,0);
    BUTTON_SetText(hItem, "");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
		BUTTON_SetFocussable(hItem,0);
				BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmBT1,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmBT2,0,0);
    BUTTON_SetText(hItem, "");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
		BUTTON_SetFocussable(hItem,0);
				BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmBT1,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmBT2,0,0);
    BUTTON_SetText(hItem, "");
    //extern GUI_CONST_STORAGE GUI_BITMAP bmblueBT2;
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
		BUTTON_SetFocussable(hItem,0);
				BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmBT1,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmBT2,0,0);
    BUTTON_SetText(hItem, "");
    //
	  // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
		BUTTON_SetFocussable(hItem,0);
    BUTTON_SetText(hItem, "");
				BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmblueBT1,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmblueBT2,0,0);
    BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
		
		// Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
		BUTTON_SetFocussable(hItem,0);
    BUTTON_SetText(hItem, "");
		//		BUTTON_SetText(hItem,"");
		BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
	BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmoff,0,0);
    BUTTON_SetFont(hItem, GUI_FONT_24B_ASCII);
    // Initialization of 'NUM'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, 0xffffff);
    TEXT_SetFont(hItem, &GUI_Fontnumber);
    //
    // Initialization of 'NUM'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, 0xffffff);
    TEXT_SetFont(hItem, &GUI_Fontnumber);
    //
    // Initialization of 'FF Master'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextColor(hItem, 0x00FF0000);
    //TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
		   TEXT_SetFont(hItem, &GUI_Fontsong40);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'MF Master'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextColor(hItem, 0x00FF0000);
    TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
		 TEXT_SetFont(hItem,& GUI_Fontsong40);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Status'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, &GUI_Fontxuanxiang24);
    //
    // Initialization of 'FF'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, &GUI_Fontxuanxiang24);
    //
    // Initialization of 'MF'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, &GUI_Fontxuanxiang24);
    //
    // Initialization of 'Pump'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, &GUI_Fontxuanxiang24);
    //
    // Initialization of 'Sensor'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, &GUI_Fontxuanxiang24);
		// Initialization of 'SMS Status'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, &GUI_Fontxuanxiang24);
		
				// Initialization of 'GSMreturn'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
							if(i==3)
              StatusErro();
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
			OnBUTTON1clicked(pMsg);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) { 	
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
				
OnSellectClicked(pMsg);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
			case ID_BUTTON_6: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
				
OnStartClicked(pMsg);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
						case ID_BUTTON_7: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
				
SetupsReturn();
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_0: // Notifications sent by 'Slider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
				OnSlider0ValueChanged(pMsg);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_1: // Notifications sent by 'Slider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
				OnSlider1ValueChanged(pMsg);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateDS TEK
*/
//WM_HWIN CreateDS TEK(void);
void MainTask(void) {
//WM_HWIN hWin;
// GUI_Init();
// 	PROGBAR_SKINFLEX_PROPS Props;
 //  WM_SetDesktopColor(GUI_BLACK);      /* Automacally update desktop window */
//		WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
	// WM_MULTIBUF_Enable(1);
	WIDGET_SetDefaultEffect_None();
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
   // FRAMEWIN_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	PROGBAR_SetDefaultSkinClassic();
	 FRAMEWIN_SetDefaultSkinClassic();
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    BUTTON_SetDefaultSkinClassic();
	GUI_UC_SetEncodeUTF8();
	
	
	
	
	
	
	
//PROGBAR_GetSkinFlexProps(&Props, 0);
//Props.ColorFrame= 0X00625B57;
//Props.ColorText = 0x00dfdfdf;
//Props.aColorLowerL[0]=0x007ac9e7;
//Props.aColorLowerL[1]=0x00289bc9;
//Props.aColorUpperL[0]=0x002796c3;
//Props.aColorUpperL[1]=0x001e77a0;
//PROGBAR_SetSkinFlexProps(&Props, 0);
//WM_InvalidateWindow(hWin);
	
	
	

	
	
	
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	  //WM_SetCreateFlags(WM_CF_MEMDEV);                       //????????????????
    //WM_EnableMemdev(WM_HBKWIN);                              //????????????
GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0); 
	    while(1)
  {
    GUI_Delay(1);
  }
//  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END



/*********************************************************************
*
*      ����仯��ֵ�Ӻ���
*
**********************************************************************/

void OnSlider0ValueChanged(WM_MESSAGE * pMsg)
{
	int a; char *Buf;const char* p;
		a=SLIDER_GetValue(slider0);
		I2c_Buf_Write[0]=tmp;
		itoa(a, Buf, 10);
	 p= (const char*)(char*)Buf;
	TEXT_SetText(Text0,p);
		I2C_EE_BufferWrite( I2c_Buf_Write, 1, 1);
	//	I2C_EE_ByteWrite(I2c_Buf_Write,1);
			if(ClickStart==1)
	{
	CCR1_Val=SLIDER_GetValue(slider0)*256/100;
	Tim3_OC_init();
	}


}

void OnSlider1ValueChanged(WM_MESSAGE * pMsg)
{
		int a;char *Buf;const char* p;

	a= SLIDER_GetValue(slider1);
		itoa(a, Buf, 10);
	p= (const char*)(char*)Buf;
	TEXT_SetText(Text1,p);
	//PROGBAR_SetValue(WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0),a);

			if(ClickStart==1)
	{
	CCR2_Val=SLIDER_GetValue(slider1)*256/100;
	Tim3_OC_init();
	}

	
}

/*********************************************************************
*
*       ѡ�񰴼���Ӧ
*
**********************************************************************/

void OnSellectClicked(WM_MESSAGE*pMsg)
{
			switch (++i)
	{
	case 1 :
	SLIDER_SetValue(slider1,25);
	tmp=25;
	break;
	case 2 :
	SLIDER_SetValue(slider1,50);
		tmp=50;
//    BUTTON_SetBkColor(WM_GetDialogItem(hbutton,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,GUI_RED);
//	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);
//    Props.aColorFrame[0] = 0x00FFFF00;
//    Props.aColorFrame[1] = 0x00FEFFBF;
//    Props.Radius = 4;
//	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);
//	WM_InvalidateWindow(hbutton);
	break;
	case 3 :
	SLIDER_SetValue(slider1,75);
		tmp=75;
_MessageBox("nimabi", "Message");
	break;
	case 4 :
	SLIDER_SetValue(slider1,100);
		tmp=100;
	break;
	case 5 :
	SLIDER_SetValue(slider1,1);
		tmp=1;
//	BUTTON_SetBkColor(WM_GetDialogItem(hbutton,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,GUI_INVALID_COLOR);
//    WM_InvalidateWindow(hbutton);
	i=0;
	break;
	}
}

/*********************************************************************
*
*     ����������Ӧ
*
**********************************************************************/
void OnStartClicked(WM_MESSAGE*pMsg)
{

			switch (++ClickStart)
			{
				case 1 :	
	//	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6), "STOP");
			BUTTON_SetBitmapEx(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6),BUTTON_CI_UNPRESSED,&bmON,0,0);
			CCR1_Val=SLIDER_GetValue(slider0);
			CCR2_Val=SLIDER_GetValue(slider1);
			//SLIDER_SetValue(slider1,I2c_Buf_Read1[0]);
	    Tim3_OC_init();
	  	GPIO_ResetBits(GPIOH,GPIO_Pin_11);
	break;
				case 2:
			CCR2_Val=0;
			CCR1_Val=0;
			SLIDER_SetValue(slider1,0);
			tmp=0;
			Tim3_OC_init();
//	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6), "START");
			BUTTON_SetBitmapEx(WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6),BUTTON_CI_UNPRESSED,&bmoff,0,0);
		  GPIO_SetBits(GPIOH,GPIO_Pin_11);
				i=0;
			ClickStart=0;
	break;
}
}

/*********************************************************************
*
*       ״̬������Ӧ
*
**********************************************************************/

void StatusErro(void)
{
	WM_HWIN hWin;
	hWin=FRAMEWIN_CreateEx(100,100,200,180,hbutton,WM_CF_SHOW,FRAMEWIN_CF_MOVEABLE|WM_CF_FGND,0,"diaobaole",0);//ֻ�м���FGND�ſ��Է�ֹ�����
	FRAMEWIN_SetTitleHeight(hWin, 30);
	FRAMEWIN_AddCloseButton(hWin,FRAMEWIN_BUTTON_RIGHT,0);
	TEXT_CreateAsChild(80, 90,60,20,hWin,0,WM_CF_SHOW,"NiuBI",TEXT_CF_HCENTER);
WM_MakeModal(hWin);
}



/*********************************************************************
*
*       ��Ϣ��ʾ��Ӧ
*
**********************************************************************/
void _MessageBox(char * pText, char * pCaption) 
{
  WM_HWIN hBox;WM_HWIN hItem;
	GUI_RECT Rect;
  hBox = MESSAGEBOX_Create(pText, pCaption, GUI_MESSAGEBOX_CF_MODAL | GUI_MESSAGEBOX_CF_MOVEABLE);  //���messagebox���ܻ�
// ������Ϣ���ڴ�С
  //
  WM_GetWindowRectEx(hBox, &Rect);
  WM_SetWindowPos(hBox, Rect.x0 - 15, 
                        Rect.y0 - 15, 
                        Rect.x1 - Rect.x0 + 1 + 50, 
                        Rect.y1 - Rect.y0 + 1 + 30);
  //
  // Change font of button widget
  //
  hItem = WM_GetDialogItem(hBox, GUI_ID_OK);
 // BUTTON_SetFont(hItem, pFont);
  //
  // ���ð����ؼ���С
  //
  WM_GetWindowRectEx(hItem, &Rect);
  WM_SetWindowPos(hItem, Rect.x0+10, 
                         Rect.y0 + 10, 
                         Rect.x1 - Rect.x0 + 1 + 30, 
                         Rect.y1 - Rect.y0 + 1 +  10);
  WM_SetStayOnTop(hBox, 1);
  WM_BringToTop(hBox);
  //GUI_ExecCreatedDialog(hBox);
}


/*********************************************************************
*
*    ���ô��ڳ�ʼ��
*
**********************************************************************/
	void InitialDialog(WM_HWIN hWin)
	{
		WM_HWIN hItem;
	FRAMEWIN_SetTitleHeight(hWin, 30);
	FRAMEWIN_AddCloseButton(hWin,FRAMEWIN_BUTTON_RIGHT,0);
	TEXT_CreateAsChild(80, 90,60,20,hWin,0,WM_CF_SHOW,"NiuBI",TEXT_CF_HCENTER);
	BUTTON_CreateEx(10, 140,130,45,hWin, WM_CF_SHOW,0,ID_BUTTON_8);
	BUTTON_CreateEx(150, 140,130,45,hWin, WM_CF_SHOW,0,ID_BUTTON_9);
		hItem = WM_GetDialogItem(hWin, ID_BUTTON_8);
		BUTTON_SetFocussable(hItem,0);
		BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmOK,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmcancle,0,0);
    BUTTON_SetText(hItem, "");
				hItem = WM_GetDialogItem(hWin, ID_BUTTON_9);
		BUTTON_SetFocussable(hItem,0);
		BUTTON_SetBkColor(hItem,BUTTON_CI_PRESSED,0X625B57);
		BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,0X625B57);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_UNPRESSED,&bmcancle,0,0);
		BUTTON_SetBitmapEx(hItem,BUTTON_CI_PRESSED,&bmOK,0,0);
    BUTTON_SetText(hItem, "");
		
	}
/*********************************************************************
*
*     ���ð�����Ӧ�ص�����
*
**********************************************************************/
static void _cbFrameWin(WM_MESSAGE * pMsg) 
{
  switch (pMsg->MsgId) 
	{ 
		case WM_PAINT:
				//		GUI_SetBkColor(GUI_BLACK);
						GUI_Clear();
			break;

	 default:
    WM_DefaultProc(pMsg);
	}
}



/*********************************************************************
*
*      ���ð�����Ӧ
*
**********************************************************************/

void SetupsReturn(void)
{
	WM_HWIN hWin;
	hWin=FRAMEWIN_CreateEx(300,150,300,200,0, WM_CF_SHOW,FRAMEWIN_CF_MOVEABLE|WM_CF_FGND,0,"Setups",_cbFrameWin);//ֻ�м���FGND�ſ��Է�ֹ�����
	InitialDialog(hWin);
//		
WM_MakeModal(hWin);
}


/*********************************************************************
*
*       GSM����
*
**********************************************************************/

void OnBUTTON1clicked(WM_MESSAGE*pMsg)
{
	char *redata;
	uint16_t len;
	
	switch (++m)
	{
		case 1:
			
		if(sim900a_cmd("AT\r","OK", 100) != SIM900A_TRUE)
		{
			TEXT_SetText(Text9,"NG");
			SIM900A_CLEAN_RX();
			LED2_ON;
		}
	  if(sim900a_cmd("AT\r","OK", 100) == SIM900A_TRUE)
		{
		TEXT_SetText(Text9,"OK");
			SIM900A_CLEAN_RX();
			sim900a_cmd("AT+CGMM\r","OK", 100);
			//SIM900A_CLEAN_RX();
			redata = SIM900A_RX(len);
			TEXT_SetText(Text10,redata);
			
				LED2_ON;
		}
		break;
		case 2:
		SIM900A_CLEAN_RX();
		TEXT_SetText(Text9,"GSMStatus");
		TEXT_SetText(Text10,"GSMreturn");
		LED2_OFF;
		m=0;
		break;
	}
}
/*********************************************************************
*
*       �ַ���ת����
*
**********************************************************************/

char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*************************** End of file ****************************/