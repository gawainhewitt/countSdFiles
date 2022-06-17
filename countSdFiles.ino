#include <SD.h>

const int chipSelect = 10;

void setup()
{

  SPI.setMOSI(11);  
  SPI.setSCK(13);  
  
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  File root = SD.open("/");
  
  countDirectory(root);
  
  Serial.println("done!");
}

void loop()
{
  // nothing happens after setup finishes.
}

void countDirectory(File dir) {
  int count_files = 0;
    while(true) {
      File entry = dir.openNextFile();
      if (! entry) {
        Serial.print("number of files = ");
        Serial.println(count_files -1);
        return count_files -1;
        break;
      }
      String file_name = entry.name();	//Get file name so that we can check 
                //if it's a duplicate
      if( file_name.indexOf('~') != 0 ) 	//Igrnore filenames with a ~. It's a mac thing.
      {					//Just don't have file names that have a ~ in them
        count_files++;
      }
    }
}

