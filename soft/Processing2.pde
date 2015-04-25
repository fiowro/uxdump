//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
 import processing.serial.*;
 
 PFont font;
 PrintWriter output;
 Serial myPort;                   // The serial port
 
 //sizes of windows
 int HRMtextwindow_width = 1200;
 int HRMtextwindow_height = 50;
 int GSRtextwindow_width = 290;
 int GSRMtextwindow_height = 40;
 
 //initialization of variables for calculate average value of BPM
 int[] data=new int[100000];         
 int i;
 int number_of_BPM_values;          
 int avr;
 int sum=0;
 
 //initialization of variables for calculate average value of BPM in 5 measurements
 int a;
 int count_five_measurements=0;
 int avr_five_measurements=0;
 int sum_five_measurements=0;
 
 //initialization of variables for calculate average value of BPM in 5 seconds
 int b;
 int count_five_sec=0;
 int avr_five_sec=0;
 int sum_five_sec=0;
 int measure_five_sec = 0;
 
 //initialization of variables for calculate average value of BPM in 1 minute
 int c;
 int count_one_min=0;
 int avr_one_min=0;
 int sum_one_min=0;
 long measure_one_min = 0;
 
 //time initialization for filename
 String filename;
 int day = day();
 int min = minute(); 
 int hr = hour();    
 int month = month();
 int year = year();

 int TBB=0;                       //holds the value of time between beats
 int BPM = 0;                     //holds the value of BPM
 int PTT, t1, t2;
 
 //for drawing the graphs
 float value_HRM_1;
 float value_HRM_2;
 float value_GSR;
 float prevByte_HRM_1 = 0;
 float prevByte_HRM_2 = 0;
 float prevByte_GSR = 0;
 int xPos = 1;                    // horizontal position of the graph
 int xIncrement = 3;
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void setup() 
   {
   filename="HRM_and_GSR ("+day+"_"+month+"_"+year+" "+hr+"-"+min+").csv";  
   output = createWriter(filename);
   create_header();
   font = loadFont("TimesNewRomanPSMT-36.vlw");
   textFont(font);  
   size(1200, 700);        
   println(Serial.list());         // print a list of available serial ports
   myPort = new Serial(this, Serial.list()[1], 9600);
   myPort.bufferUntil('\n');
   }
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------   
void draw() 
{    
    //background(255, 253, 248);  
    noStroke();
    fill(255, 240, 240);   
    rect(0, 0, HRMtextwindow_width, HRMtextwindow_height);                    //for HRM text    
    //rect(0, 650, GSRtextwindow_width, GSRMtextwindow_height);                   //for GSR text
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    line(xPos-xIncrement, 200-prevByte_HRM_1, xPos, 200-value_HRM_1);           //draw the line of heart rate
    line(xPos-xIncrement, 400-prevByte_HRM_2, xPos, 400-value_HRM_2);           //draw the line of heart rate_2
    stroke(25,100,0);
    strokeWeight(2);
    line(xPos-xIncrement, 600-prevByte_GSR, xPos, 600-value_GSR);               //draw the line of galvanic skin response
  
    prevByte_HRM_1 = value_HRM_1;
    prevByte_HRM_2 = value_HRM_2;  
    prevByte_GSR = value_GSR;
    
    if (xPos >= width) 
    {
          xPos = 0;
          background(255, 253, 248); 
    } 
    
    else
    {
          xPos += xIncrement;           // increment the horizontal position
    }
    fill(255,0,0);
    
    text("BPM: " + BPM, 10, 40);                               // print the BPM   
    text("PTT: " + PTT + " ms", 190, 40);                              // print the time between heartbeats in mS  
    text("Average BPM: " + avr, 390, 40);  
    
    /*
    text("BPM: " + BPM, 10, 300);                               // print the BPM   
    text("PTT: " + PTT + " ms", 300, 300);                              // print the time between heartbeats in mS  
    text("Average BPM: " + avr, 10, 340);  
    */
    
    //text("AVR BPM in 1 minute: " + avr_one_min, 10, 340);
    //text("AVR BPM in 5 mesurements: " + avr_five_measurements, 10, 380); 
    //text("AVR BPM in 5 seconds: " + avr_five_sec, 10, 380); 
    fill(25,100,0);
    //text("Signal GSR: " + value_GSR, 10, 780);
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------   
void serialEvent(Serial port)
{ 
     String inData = myPort.readStringUntil('\n'); 
     inData = trim(inData);                              // cut off white space (carriage return)

     //SIGNAL GSR
     if (inData.charAt(0) == 'G')
     {                                                   // leading 'G' for sensor data
         inData = inData.substring(1);                   // cut off the leading 'G'
         value_GSR = int(inData);                        // convert the string to usable int
         value_GSR = map(value_GSR, 0, 1023, 0, 150);
         value_GSR = int(value_GSR);
     }
     
     //SIGNAL HRM_1     
     if (inData.charAt(0) == 'S')
     {                                                   // leading 'H' for sensor data
         inData = inData.substring(1);                   // cut off the leading 'H'
         value_HRM_1 = int(inData);                        // convert the string to usable int
         value_HRM_1 = map(value_HRM_1, 0, 1023, 0, 150);
         value_HRM_1 = int(value_HRM_1);
     }
    
     //SIGNAL HRM_2 
     if (inData.charAt(0) == 'R')
      {                                      // leading 'R' for sensor data
         inData = inData.substring(1);       // cut off the leading 'R'
         value_HRM_2 = int(inData);              // convert the string to usable int
         value_HRM_2 = map(value_HRM_2, 0, 1023, 0, 150);
         value_HRM_2 = int(value_HRM_2);
      }
        
     if (inData.charAt(0) == 'B')
     {                                                   // leading 'B' for BPM data
         inData = inData.substring(1);                   // cut off the leading 'B'
         BPM = int(inData);                              // convert the string to usable int
         logging();
         
         data[a] = BPM;
         sum_five_measurements = sum_five_measurements + data[a];
         data[b] = BPM;
         sum_five_sec = sum_five_sec + data[a];
         data[c] = BPM;
         sum_one_min = sum_one_min + data[c];
         
         //calculating the average BPM value
         data[number_of_BPM_values] = BPM;
         sum = sum + data[number_of_BPM_values];       
         avr = sum/(number_of_BPM_values+1);  
         number_of_BPM_values++; 
         
         //calculating the average BPM value in 5 measurements 
         count_five_measurements++;
         if (count_five_measurements==5)
                {
                avr_five_measurements = sum_five_measurements/count_five_measurements;
                count_five_measurements=0;
                sum_five_measurements=0;
                }
         
         //calculating the average BPM value in 5 seconds
         count_five_sec++;
         if (millis() > measure_five_sec+5000)
                {  
                measure_five_sec = millis();  
                avr_five_sec = sum_five_sec/count_five_sec;
                count_five_sec=0;
                sum_five_sec=0;
                }        

         //calculate the average BPM value in 1 minute
         count_one_min++;
         if (millis()>measure_one_min+60000)
               {        
                measure_one_min = millis();  
                avr_one_min = sum_one_min/count_one_min;
                count_one_min=0;
                sum_one_min=0;
               }                              
     }
     
     if (inData.charAt(0) == 'T')
     {                                                   // leading 'T' means TBB data 
         inData = inData.substring(1);                   // cut off the leading 'T'
         TBB = int(inData);                              // convert the string to usable int
     }

    //time of the first peak in heart rate monitor
    if (inData.charAt(0) == 'A')
     {                                        // leading 'Q' means TBB data 
         inData = inData.substring(1);        // cut off the leading 'Q'
         t1 = int(inData);                   // convert the string to usable int
     }
     
    //time of the second peak in heart rate monitor
    if (inData.charAt(0) == 'C')
     {                                        // leading 'Q' means TBB data 
         inData = inData.substring(1);        // cut off the leading 'Q'
         t2 = int(inData);                   // convert the string to usable int
     }
     
     //Pulse Transit Time
     if (inData.charAt(0) == 'P')
     {                                        // leading 'Q' means TBB data 
         inData = inData.substring(1);        // cut off the leading 'Q'
         PTT = int(inData);                   // convert the string to usable int
     }



     
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------  
void logging()
{
     int mil = millis();
     int seco = second();
     int minut = minute(); 
     int hou = hour();
     int day2 = day();
     int month2 = month();
     int year2 = year();
     output.print(number_of_BPM_values+1 + ",");
     output.print(+hou+":"+minut+":"+seco+":"+mil+",");
     output.print(+day2+"/"+month2+"/"+year2+",");
     output.print(BPM + ",");
     output.print(PTT + ","); 
     output.print(value_GSR + ","); 
     output.print(avr_five_sec + ",");
     output.print(avr_one_min + ",");
     output.print(avr + ",");
     //output.print(TBB + ",");  
     output.println(avr_five_measurements + ",");
     output.flush();  
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------  
void create_header()
{
   output.print("№,");
   output.print("Time,");
   output.print("Date,");
   output.print("Beats per minute,");
   output.print("PTT,");
   output.print("Value GSR,");   
   output.print("Average value of BPM in 5 seconds,");
   output.print("Average value of BPM in 1 minute,");
   output.print("Average value of BPM,");
   //output.print("Time between beats (ms),");
   output.println("Average value of BPM in 5 measurements,");
}
