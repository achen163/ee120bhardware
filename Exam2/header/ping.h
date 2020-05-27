
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static int counter = 0;

/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit:
       		ping_state = PInit;
	break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
		if(counter < 9 ) {
			result = result | 0x00;
			counter++;
		}
		else {
			result = result|0x01;
			counter = 0;
		}
            break;
        default:
            break;
    }
}
