

void keyPressed()
{
int sec = second();
int min = minute(); 
int hr = hour();    
int day = day();
int month = month();
int year = year();

 switch(key){
   case 's':    // pressing 's' or 'S' will take a jpg of the processing window
   case 'S':
     saveFrame("HeartBeat-" +day+"_"+month+"_"+year+" "+hr+"-"+min+"-"+sec+".jpg");    // take a shot of that!
     break;

   default:
     break;
 }
}
