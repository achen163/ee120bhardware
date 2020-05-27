
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static int counter3 = 0;
static unsigned char max = 0;
/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
		detect_max_amp_state = DMAInit;           
	       	break;
        
        default:
		detect_max_amp_state = DMAInit;
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
		if (counter3 < 9 ) {
			if (max >= ~PINA) {
				max = ~PINA;
			}
		}
		else {
			result = result | max; 
		}
            break;
        default:
            break;
    }
}
