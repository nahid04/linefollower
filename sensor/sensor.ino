void sensorInit(){
  for(int i=0;i<NUM_SENSOR;i++){
    
    
    pinMode(sensorPin[i],INPUT);
    sensorA[i]=0;
  }
  sensorCalib1();
}
void sensorCalib1(){
  int smin[NUM_SENSOR]={10,10,10,10,10,10,10,10};
  int smax[NUM_SENSOR]={950,950,950,950,950,950,950,950};
  
  for(int i=0;i<NUM_SENSOR;i++){
    sensorMin[i]=smin[i];
    sensorMax[i]=smax[i];
  }
}
int chkPat()
{
  for(int i=0;i<NUM_SENSOR;i++){
    //sensorA[i]=analogRead(sensorPin[i]);
    if(analogRead(sensorPin[i])<400)
      chk[i]=0;
    else 
      chk[i]=1;
      
     Serial.print(chk[i]);
     Serial.print(" ");
  }
  Serial.println();
}
int sensorRead(){
  int pos = 0;
  long sum=0,avg=0;
  for(int i=0;i<NUM_SENSOR;i++){
    sensorA[i]=analogRead(sensorPin[i]);
    
    #ifdef CALIBON
    int den=sensorMax[i]-sensorMin[i];
    int x;
    if(den!=0) x=(((long)sensorA[i])-sensorMin[i])*1000/den;
    if(x<0) x=0;
    else if(x>1000) x=1000;
    sensorA[i]=x;
    #endif
    
    avg += ((long)(sensorA[i]) * (i * 1000));
    sum += sensorA[i];
    
    #ifdef SENSOR_DEBUG
    Serial.print(sensorA[i]);
    Serial.print('\t');
    //Serial.print(avg);
    //Serial.print('\t');
    #endif
  }
  pos = avg/sum;
  #ifdef SENSOR_DEBUG
  Serial.print(pos);
  //Serial.println();
  #endif
  return pos;
}

