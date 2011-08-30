import interfascia.*;
import processing.serial.*;
import cc.arduino.*;

GUIController c;
IFButton b1;
boolean doRun=true;
Arduino arduino;
int timer;
int refreshT; //in milliseconds

// set-up file streaming
PrintWriter output; // for streaming to file

// setup datex parameters
ArrayList params;
DatexParam hr, rr, sys, dia, mean, temp, sat, st, ir, etco2, fico2, eto2, fio2, etn2o, fin2o, etaa, fiaa, mac, ambp, ppeak, peep, pplat, tvi, tve, comp, mve, co, bt, pcwp, time;
int numParams=0;


void setup() {
  
  // configure display window
  size(250, 200);
  
  //create an empty arrayList .. will hold pointers to each param .. they assign themselves in their own constructors
  params = new ArrayList();  
  hr = new DatexParam("hr", "Heart Rate");
  sat = new DatexParam("sat", "Oxygen Saturation");
  rr = new DatexParam("rr", "Respiratory Rate");
  mean = new DatexParam("mean", "Mean Blood Pressure");
  sys = new DatexParam("sys", "Systolic Pressure");
  dia = new DatexParam("dia", "Diastolic Pressure");
  temp = new DatexParam("temp", "Temperature");
  st = new DatexParam("st", "ST Segment Length");
  ir = new DatexParam("ir", "InfraRed Amplitude");
  etco2 = new DatexParam("etco2", "End-Tidal CO2");
  fico2 = new DatexParam("fico2", "[Inspired CO2]");
  eto2 = new DatexParam("eto2", "End-Tidal O2");
  fio2 = new DatexParam("fio2", "[Insipired O2]");
  etn2o = new DatexParam("etn2o", "End-Tidal N2O");
  fin2o = new DatexParam("fin2o", "[Inspired N2O]");
  etaa = new DatexParam("etaa", "End-Tidal Agent");
  fiaa = new DatexParam("fiaa", "[Inspired Agent]");
  mac = new DatexParam("mac", "Min Alveolar Concentration");
  ambp = new DatexParam("ambp", "Ambient Pressure");
  ppeak = new DatexParam("ppeak", "Peak Airway Pressure");
  peep = new DatexParam("peep", "Positive End Expiratory Pressure");
  pplat = new DatexParam("pplat", "Plateau Pressure");
  tvi = new DatexParam("tvi", "Tidal Volume Inspiration");
  tve = new DatexParam("tve", "Tidal Volume Expiration");
  comp = new DatexParam("comp", "Compliance (cms H2O)");
  mve = new DatexParam("mve", "Minute Volume Expiration");
  co = new DatexParam("co", "Cardiac Output");
  bt = new DatexParam("bt", "Blood Temperature");
  pcwp = new DatexParam("pcwp", "Pulmonary Capillary Wedge Pressure");
  time = new DatexParam("time", "System Time");

  
  // Arial font
  PFont myFont = createFont(PFont.list()[4], 12);  // maybe hard-code Arial in here?
  textFont(myFont);
  
  // setup Arduino
  arduino = new Arduino(this, Arduino.list()[1], 57600);

  refreshT = 2000;
  timer = millis()+refreshT;
  
  // setup button
  c = new GUIController (this);
  b1 = new IFButton("Stop", 40, 120, 50);
  b1.addActionListener(this);
  c.add(b1);
}


void draw() {
  
  float newHR, newSAT, newRR, newMBP;
  float a; 
  
  background(255);
  //stroke(on); //?
  
  
  if (millis() - timer > refreshT) {  // every so often, pretend to get a packet of data
    timer = millis();
  
    // acquire analog voltages here ... convert from [0,1023] to appropriate vital sign values
    newHR =   (float)(arduino.analogRead(0))/1023 * 160;
    newSAT =  (float)(arduino.analogRead(1))/1023 * 20 +  80;
    newRR =   (float)(arduino.analogRead(2))/1023 * 50      ;
    newMBP =  (float)(arduino.analogRead(3))/1023 * 130 + 20;
    
    a=0.99; 
    
    hr.setVal  ( round( (1-a)*hr.getVal()   + a*newHR  ));
    sat.setVal ( round( (1-a)*sat.getVal()  + a*newSAT ));
    rr.setVal  ( round( (1-a)*rr.getVal()   + a*newRR  ));
    mean.setVal ( round( (1-a)*sys.getVal()  + a*newMBP ));

    
    
    // set time
    int y = year(); int m = month(); int d = day(); int h = hour(); int mi = minute(); int s = second();
    String date = new String(nf(y,4) + nf(m,2) + nf(d,2) + nf(h,2) + nf(mi,2) + nf(s,2));
    time.setLongName(date);
    
    if (doRun) {
      fileWrite();
    }
  
  }
  
      // text display and plotting
  for (int i = 3; i>=0; i--) {
    DatexParam dp = (DatexParam) params.get(i);    // assumes void; need to type-cast
    if (dp.shortName!="time") {
      text(dp.getLongName() + ": " + dp.getVal(), 10, i*20+20);
      fill(0, 0, 0, 255);
    }
  }
  
}


void actionPerformed (GUIEvent e) 
{
  if (e.getSource() ==b1)
  {
    if (doRun) {
      doRun=false;
      b1.setLabel("Run");
    }
    else {
      doRun=true;
      b1.setLabel("Stop");
    }
  } 
}

void fileWrite() {
  // output file
  
  output = createWriter("C:/Documents and Settings/cbennett4/My Documents/PTSAFE/Data/" + time.getLongName() + ".csv");
  
  for (int i = 0; i<params.size(); i++) {
    DatexParam dp = (DatexParam) params.get(i);
    output.println(dp.shortName + "," + int(dp.val) + ",");
  }
  
  output.flush(); // Write the remaining data
  output.close(); // Finish him.
  
}

void keyPressed() {
  if (key == 'x')
    exit(); // Stop the program  
  else if (key == 's')
    fileWrite();
}





class DatexParam {
  float val;
  String shortName;
  String longName;
  
  // constructor
  DatexParam (String shortName_, String longName_) {    // constructor
    val=0;
    shortName = shortName_;    // what is it called?
    longName = longName_;
    // attatch to main record
    params.add(this);
  }
  void setVal (float val_) {
    val = val_;
  }
  float getVal() {
    return val;
  }
  String getShortName() {
    return shortName;
  }
  void setLongName(String name) {
    longName = name;
  }
  String getLongName() {
    return longName;
  }
}


