void ASSIGNINCREMENTS_P(){
  
  PENV = PulsarEnv[analogControls[3]>>9];

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;

  case 0:
    
    UPDATECONTROLS_FM();  
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095.0)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];
      
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];      
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).
   

    UPDATECONTROLS_FMALT();     
  
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn); 
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; //keep away from "rails"
    
    FMX_HiOffset=mixHi*FMX_HiOffsetCont;

    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0]+FMX_HiOffset;
      o3.phase_increment = inputConverterF*osc_mult[0];
      
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0]+FMX_HiOffset;
      o3.phase_increment = inputConverterF*osc_mult[0];      
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ();    
  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);    
    
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];
      
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];      
    }
break;
  case 3://ALT CZ  
  

    UPDATECONTROLS_CZALT();    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 

FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];
      lfo.phase_increment = inputConverterF*(osc_mult[1]/8.0);
    }
    else{
     FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];    
      lfo.phase_increment = inputConverter*(osc_mult[1]/2.0);
    }

    break; 
   
  }
  
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

