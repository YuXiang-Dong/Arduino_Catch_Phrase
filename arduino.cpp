int PinA = 1, PinB = 2, PinC = 3, PinD = 4, PinE = 5, PinF = 6, PinG = 7;
int H = 0, K = 0, M = 0, P = 0;
int i = 0, delaytime = 1000;

void setup()
{
  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
  pinMode(PinC, OUTPUT);
  pinMode(PinD, OUTPUT);
  pinMode(PinE, OUTPUT);
  pinMode(PinF, OUTPUT);
  pinMode(PinG, OUTPUT);
}

//Involves applying HKMP format for detecting values from 0000 - 1111
//When the state of a pin is high,that means the segment is turned off.
//When the state of a pin is low, that means the segment is on

// To understand void loop
// P changes every time i increases
// M changes every time P reaches 2
// K changes every time M reaches 2
// H changes every time K reaches 2
// and if H is equal to 2, that means it's reset time!
void loop()
{
  updateDisplay(); // display 0000 first before P increases
  delay(delaytime);
  P++;
  if(P == 2)
  {
    P=0;
    M++;
  }
  if(M == 2)
  {
    M=0;
    K++;
  }
  if(K == 2)
  {
    K=0;
    H++;
  }
  if(H == 2)//if H == 2, that means it reached the end of the iteration
  {
    H=0;//it will reset HKMP to 0 and the loop starts again
    K=0;
    M=0;
    P=0;
  }
}

void updateDisplay()
{
  SegmentA();
  SegmentB();
  SegmentC();
  SegmentD();
  // Segment E is always on, so it's connected to GND. No Work!!
  SegmentF();
  SegmentG();
}

void SegmentA()
{
  // a = HP’+M’P’+H’K’M’
  if (((H == 1 && P == 0) || (M == 0 && P == 0)) || ((H == 0 && K == 0) && M == 0))
  {
    digitalWrite(PinA, HIGH);
  }
  else
  {
    digitalWrite(PinA, LOW);
  }
}

void SegmentB()
{
  // b = M’P’+K’P
  if ((M == 0 && P == 0) || (K == 0 && P ==1))
  {
    digitalWrite(PinB, HIGH);
  }
  else
  {
    digitalWrite(PinB, LOW);
  }
}

void SegmentC()
{
  // c = HM’+KMP
  if ((H == 1 && M == 0) || ((K == 1 && M == 1) && P == 1))
  {
    digitalWrite(PinC, HIGH);
  }
  else
  {
    digitalWrite(PinC, LOW);
  }
}

void SegmentD()
{
  // d = H’K’M
  if (H == 0 && (K == 0 && M == 1))
  {
    digitalWrite(PinD, HIGH);
  }
  else
  {
    digitalWrite(PinD, LOW);
  }
}

void SegmentF()
{
  // f = MP + HM
  if ((M == 1 && P == 1) || (H == 1 && M == 1))
  {
    digitalWrite(PinF, HIGH);
  }
  else
  {
    digitalWrite(PinF, LOW);
  }
}

void SegmentG()
{
  // g = K’MP + KM’P + KMP’+ HM’P’
  if (((((K == 0 && M == 1) && P == 1) || ((K == 1 && M == 0) && P == 1)) || ((K == 1 && M == 1) && P == 0)) || ((H == 1 && M == 0) && P == 0))
  {
    digitalWrite(PinG, HIGH);
  }
  else
  {
    digitalWrite(PinG, LOW);
  }
}
