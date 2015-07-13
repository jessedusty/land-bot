#define terminator '|'
#define maxSize 8


int charToDigit(char c) {
  int ret = c - '0';
  return (ret >= 0 && ret <= 9 ? ret : -1);
}

int readIntToEnd() {
  char c;
  int retVal = 0;
  int count = 0;
  while (count < maxSize) {
    c = Serial1.read();
    if (c == '|') return (count > 0 ? retVal : -1);
    int digit = charToDigit(c); 
    if (digit != -1) { 
      retVal = (retVal * 10) + digit;
      count++;
    }
  }
}

void readSerial() {
  if (Serial1.available() != 0) { 
       char c;    
       c = Serial1.read(); 
       switch (c) {
         case 'm':
           targetHeading = readIntToEnd();
           Serial1.print("Setting target to: ");
           Serial1.println(targetHeading);
         break;
         case 'e':
           Serial1.println("Enabled");
           compassEnabled = true; 
         break;
         case 'd':
           Serial1.println("Disabled");
           compassEnabled = false;
         break;
       }
     }
}  
