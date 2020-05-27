//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static int counter2 = 0;


/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            detect_eq_state = DEQInit;
            break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
		counter2++;
		if ((~PINA & 0xF8) == 0 && counter2 >  9 ) {
			result = result | 0x00;
			counter2 = 0;
		}
		else if ((~PINA & 0xF8) > 0){
			result = result | 0x02;
		}
            break;
        default:
            break;
    }
}
