#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <string>
#include <iostream>


char testString[100]= {};


void button_action_test(Fl_Widget *w, void *data);
int main(int argc, char *argv[]) {
	
	//setup window
	Fl_Window* mainWindow = new Fl_Window(640, 480);

	//box for name and version
	

	Fl_Box *logo = new Fl_Box(20,20,150,30,"DeckBox 0.1");
	//styling
	logo->box(FL_UP_BOX);
	logo->labelfont(FL_BOLD+FL_ITALIC);
	logo->labelsize(16);
	logo->labeltype(FL_SHADOW_LABEL);
	

	//main buttons
   	new Fl_Button(100, 400, 80, 30, "Power");
	new Fl_Button(200, 400, 80, 30, "Reset");
	new Fl_Button(300, 400, 160, 30, "I'm Feeling Lucky");


	//input and output fields

	Fl_Input *sampleInput = new Fl_Input(100, 360, 100, 30, "Write Stuff"); //defines an input field
	Fl_Output *sampleOutput = new Fl_Output(100, 300, 200, 30, "output"); //defines an output field
	sampleOutput->value("LLL");
	

	
//	sampleInput->value(testString);
	Fl_Button *button = new Fl_Button(220, 360, 80, 30, "Copy");
	button->callback(button_action_test, (void *)0);

	button->type(FL_NORMAL_BUTTON);











   	mainWindow->end();
   	mainWindow->show(argc, argv);
   	return Fl::run();
}







void button_action_test(Fl_Widget *w, void *data){
	Fl_Input *sampleInput = (Fl_Input *)w;
		
	Fl_Output *sampleOutput = (Fl_Output *)w;
	sampleInput->value(testString);
	sampleOutput->value(testString);
	printf("button pressed\n");
	for (int i = 0; i < 100; i++){
		printf("%c", testString[i]);
		std::cout << testString[i];
	}
	printf("\n");

}







