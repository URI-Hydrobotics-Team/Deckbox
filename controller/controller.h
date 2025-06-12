#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>

struct axis_state {
    	short x, y;
};

class controller_t {


	private:
		char *device;
    		int js;
    		struct js_event event;
    		size_t axis;
	

    		struct axis_state axes[3] = {0};
		
	public:


	int read_event(){
    		ssize_t bytes;

    		bytes = read(js, &event, sizeof(event));

    		if (bytes == sizeof(event))
        		return 0;

    			/* Error, could not read full event. */
    			return -1;
	}


	size_t get_axis_count(){
    		__u8 axes;

    		if (ioctl(js, JSIOCGAXES, &axes) == -1){
        		return 0;
		}
   		 return axes;
	}


	size_t get_button_count(){
    		__u8 buttons;
    		if (ioctl(js, JSIOCGBUTTONS, &buttons) == -1){
        		return 0;
		}
    		return buttons;
	}

	size_t get_axis_state(){
    		size_t axis = event.number / 2;

    		if (axis < 3){
        		if (event.number % 2 == 0)
            			axes[axis].x = event.value;
       			else{
            			axes[axis].y = event.value;
    			}
		}
    		return axis;
	}






	void setDevice(char *dev){
		device = dev;
	}

	void init(){
		/*check if device has been set */
		if (strlen(device) == NULL){
			device = DEFAULT_CONTROLLER;
			std::cout << "Using 'js0' for controller\n";
		}	
		/* open device */
		js = open(device, O_RDONLY);
		if (js == -1){
			std::cout << "failed to open " << device <<'\n';
		}else{
			std::cout << "Opened controller at " << device << '\n';
		}
		
		/* set flags */

		int flags = fcntl(js, F_GETFL, 0);
		fcntl(js, F_SETFL, flags | O_NONBLOCK);


		struct timeval timeout={0,CONTROLLER_TIMEOUT};  //tv_sec, tv_usec
		setsockopt(js, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout,sizeof(struct timeval));



	}

	void poll(){
		//std::cout << "polling\n";
		read_event(); //read event
		switch (event.type){
			/* for testing*/
            		case JS_EVENT_BUTTON:
                		printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
                		break;
            		case JS_EVENT_AXIS:
                		axis = get_axis_state();
                		if (axis < 3){
                    			printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                		}
				break;
            		default:
                		break; //ignore
        	}



	}



	void closeFD(){
		close(js);		
	}	
	
		




};
