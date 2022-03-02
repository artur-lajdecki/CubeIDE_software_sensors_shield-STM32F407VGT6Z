/*
 * ui_functions.c
 *
 *  Created on: May 18, 2021
 *      Author: Artur
 */

#include <menu.h>
#include <ugui.h>

static const  struct menuitem *currMenuPtr = &menu_link;    //Current menu position
static int8_t menuindex;                                    //Index of current menu position
static int8_t menufirstpos;                                 //Index of menu position displayed at the top

uint8_t Menu_GetMenuItemsNo() {
	const struct menuitem *tmpmenuitem = currMenuPtr;
	uint8_t index=0;

	while(tmpmenuitem) {
		tmpmenuitem=tmpmenuitem->next;
		index++;
	}

	return index;
}

const struct menuitem *Menu_GetMenuItem(uint8_t index) {
	const struct menuitem *tmpmenuitem=currMenuPtr;

	while((tmpmenuitem) && (index>0)) {
	 tmpmenuitem=tmpmenuitem->next;
	 index--;
	}

	return tmpmenuitem;
}

uint8_t Menu_GetMenuRows() {
	uint8_t menuRows = UG_GetYDim() / (gui1.font.font_height);
	return menuRows;
}

void Menu_Show() {
	const struct menuitem *tmpmenuitem=Menu_GetMenuItem(menufirstpos);
	uint8_t menuitemsno=Menu_GetMenuItemsNo();

	for(uint8_t i=0; i < Menu_GetMenuRows(); i++) {
		uint8_t xbox = 0, ybox = 26;

		if(menuindex == ((menufirstpos + i) % menuitemsno)) {

			UG_SetBackcolor( C_BLUE );
			UG_FillFrame(xbox, 2+(i*ybox), UG_GetXDim(), (gui1.font.char_height)+(0+(i*ybox)), C_BLUE);
			UG_PutString( 0, 2+(i*ybox), tmpmenuitem->text);
		}
		else {
			UG_SetBackcolor( C_BLACK );
			UG_FillFrame(xbox, 2+(i*ybox), UG_GetXDim(), (gui1.font.char_height)+(0+(i*ybox)), C_BLACK);
			UG_PutString( 0, 2+(i*ybox), tmpmenuitem->text);
		}

		if(tmpmenuitem->submenu) {
			UG_PutString( xbox, 2+(i*ybox), "");
		}

		tmpmenuitem = tmpmenuitem->next;

		if(tmpmenuitem == NULL)  //End of list
		{
			if(Menu_GetMenuItemsNo() > Menu_GetMenuRows()){
				tmpmenuitem=currMenuPtr;
			}
			else {
				break;   //Finish to avoid repeating elements
			}
		}
	}
}

void Menu_SelectNext() {
	uint8_t no = Menu_GetMenuItemsNo();
	menuindex++;

	if(no > Menu_GetMenuRows()){
		int8_t dist;	//Distance between first and highlighted position

		if(menuindex < menufirstpos) {
			dist = no - menufirstpos + menuindex;
		}
		else {
			dist=menuindex-menufirstpos;
		}

		if(dist >= Menu_GetMenuRows()) {
			menufirstpos++;  //End of screen, scroll
		}
	}

	menuindex %= no;
	menufirstpos %= no;
	Menu_Show();
}

void Menu_SelectPrev() {
	if(menuindex > 0)
	{
		if(menuindex == menufirstpos) menufirstpos--;
		menuindex--;
	}
	 else
	{
		if(menufirstpos == 0)
		{
			menuindex=Menu_GetMenuItemsNo()-1;
			if(Menu_GetMenuItemsNo()>Menu_GetMenuRows()) menufirstpos = menuindex;
		} else menuindex = Menu_GetMenuItemsNo()-1;
	}
	Menu_Show();
}

void Menu_Back() {
	menufirstpos = 0;
	menuindex = 0;
	currMenuPtr = currMenuPtr->parent;
}

void Menu_Click() {
  const struct menuitem *tmpmenuitem = Menu_GetMenuItem(menuindex);
  const struct menuitem *submenu = tmpmenuitem->submenu;

  menuitemfuncptr mfptr = tmpmenuitem->menuitemfunc;

  if(mfptr) {
	  (*mfptr)();
  }
  if(submenu) {
	  currMenuPtr = submenu;
	  menuindex = 0;
	  menufirstpos = 0;
   }
  UG_FillScreen( C_BLACK );
  Menu_Show();
}

void GUI_init(void) {

  /* -------------------------------------------------------------------------------- */
  /* Define µGUI structure (ST7735 128x160)                              			  */
  /* -------------------------------------------------------------------------------- */
  UG_Init(&gui1,(void(*)(UG_S16,UG_S16,UG_COLOR))ST7735_DrawPixel,ST7735_HEIGHT,ST7735_WIDTH);

  /* Clear Screen */
  UG_FillScreen( C_BLACK );
  UG_FontSelect ( &FONT_6X8 ) ;
  UG_SetBackcolor ( C_BLACK ) ;
  UG_SetForecolor ( C_CYAN ) ;
}

