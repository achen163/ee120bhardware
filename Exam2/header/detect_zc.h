
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static int counter4 = 0;
static unsigned char first= 0;
static unsigned char second = 0;
/*complete the state machine*/

void Detect_ZC()
{
    switch(detect_zc_state)
    {
        case DZCInit:
            
	break;
        
        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit:
            if (counter4 < 1) {
		counter4++;
		first = ~PINA;
		break;
	    }
	    else if (counter4 < 2) {
		second = ~PINA;
		counter = 0;
		break;
	    }
	    if ((first + second) == 4) {
		result = result | 0x04;
		first = 0;
		second = 0;
	    }
	    if (( second - first ) == 4) {
		result = result | 0x04;
		first = 0;
		second = 0;
	    }
	    else {
		result = result | 0x00;
		first = 0;
		second = 0;
	    }

		break;
        default:
            break;
    }
}
