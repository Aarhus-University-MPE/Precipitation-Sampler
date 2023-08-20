// Worst Case Sample Function
if(ultralyd() || millis()- lastSampleTime > SamplePeriod){
  bool ignoreTimeout = (millis()- lastSampleTime) > samplePeriod;
  sample(ignoreTimeout);
}


sample(bool ignoreTimeout){
  recalibrateLoadCell();
  if(loadCellValue > volumeMin) saveVolume();

  if(ignoreTimeout) // Contineous sampling

  if(timeout) reset();
}


