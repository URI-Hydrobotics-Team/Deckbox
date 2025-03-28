#include <forms.h>
#include <stdio.h>
#include <string.h>
//external I/O definitions

float value = 0;

void updateStick(FL_OBJECT *stick){

	value += 1;

	printf("%i\n", stick);

	fl_set_slider_value(stick, value);



}



void update_button_cb(FL_OBJECT *obj, long argument);


void power_button_cb(FL_OBJECT *obj, long argument);


void reset_button_cb(FL_OBJECT *obj, long argument);


int main(int argc, char **argv){

	//external I/O definitions

	FILE *conPtr; //remoteRX online file
	char rxIsOnline[2];


	FL_FORM *form;
    	//define objects
	FL_OBJECT *power,*update, *reset, *radioGroup, *radio1, *radio2, *textOutput1, *stick1, *conOnlineIndicator;
	char textString[] = "look here look listen";
	
    	fl_initialize(&argc, argv, 0, 0, 0);

    	form = fl_bgn_form(FL_UP_BOX, 800, 600);
	//fl_add_box(FL_UP_BOX, 1, 1, 140, 20, "CONTROLS");
	fl_add_labelframe(FL_EMBOSSED_FRAME, 2, 20, 140, 500, "buttons 'n shit");
	//fl_add_box(FL_FRAME_BOX, 1, 30, 140, 500, ""); //border box around buttons
	fl_add_box (FL_OVAL_BOX, 600, 500, 150, 60, "deckBox X11");
    	reset = fl_add_button(FL_NORMAL_BUTTON, 20, 40, 100, 50, "reset");
    	power = fl_add_button(FL_NORMAL_BUTTON, 20, 110, 100, 50, "power");
	update = fl_add_button(FL_NORMAL_BUTTON, 20, 180, 100, 50, "update");
	//fl_set_object_callback(update, update_button_cb, 0);
	fl_set_object_callback(reset, reset_button_cb, 0);
	fl_set_object_callback(power, power_button_cb, 0);




	//mode ui
	fl_add_labelframe(FL_EMBOSSED_FRAME, 200, 20, 200, 150, "mode");
	radio1 = fl_add_button(FL_RADIO_BUTTON, 220, 40, 100, 20, "radio 1");
	radio2 = fl_add_button(FL_RADIO_BUTTON, 220, 80, 100, 20, "radio 2");

	radioGroup = fl_addto_group(radio1);
	radioGroup = fl_addto_group(radio2);
	

	//data output

	fl_add_labelframe(FL_EMBOSSED_FRAME, 200, 220, 300, 300, "Data Output Fields");
	textOutput1 = fl_add_text(FL_NORMAL_TEXT, 220, 260, 200, 20, textString);
	textString[1] = '@';
	//fl_redraw_object(textOutput1);
	//re define to redraw
	textOutput1 = fl_add_text(FL_NORMAL_TEXT, 220, 260, 200, 20, textString);


	//controller visual
	
	fl_add_labelframe(FL_EMBOSSED_FRAME, 420, 20, 300, 140, "Sticks");
	stick1 = fl_add_slider(FL_HOR_SLIDER, 440, 40, 200, 20, "Horizontal");	
	fl_set_slider_bounds(stick1, 0, 100);
	fl_set_slider_value(stick1, 0);
	conOnlineIndicator = fl_add_text(FL_NORMAL_TEXT, 640, 130, 70, 20, "OFFLINE");



    	fl_end_form();
 
    	fl_show_form(form, FL_PLACE_MOUSE, FL_FULLBORDER, "deckBox XForms Inerface");

	//fl_do_forms();
    	while (1){
		//fl_do_forms();

		if(fl_do_forms() == update){
			//rx is online
			rxIsOnline[0] = ' ';
			conPtr = fopen("../rx_is_online", "r");
			fgets(rxIsOnline, 2, conPtr);


			fclose(conPtr);
			printf("%c\n", rxIsOnline[0]); //print for debugging
			if (rxIsOnline[0] == '1'){
				fl_set_object_label(conOnlineIndicator, "ONLINE");
			}else{

				fl_set_object_label(conOnlineIndicator, "OFFLINE");
			}

		}

		
	}

    	//fl_hide_form(form);


    	fl_finish();
    	return 0;
}







void update_button_cb(FL_OBJECT *obj, long argument){


	//rx is online
	//fgets(rxIsOnline, 1, conPtr);
	//printf("%s\n", rxIsOnline);
	printf("test\n");
	/*
	if (rxIsOnline[1] == '1'){
		conOnlineIndicator = fl_add_text(FL_NORMAL_TEXT, 400, 260, 100, 20, "Online");			
		}else{
		conOnlineIndicator = fl_add_text(FL_NORMAL_TEXT, 400, 260, 100, 20, "Offline");			
		
	}
	*/


}

void power_button_cb(FL_OBJECT *obj, long argument){

	printf("power hit\n");
}

void reset_button_cb(FL_OBJECT *obj, long argument){

	//updateStick(stick1);
}






