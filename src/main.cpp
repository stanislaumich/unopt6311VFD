#include <Arduino.h>

/*
 PT6311_Test04_Sketch - Driver Test for PT6311 VFD Controller
 
 Copyright (c) 2014 Dmitry Pakhomenko.
 dmitryp@magictale.com
 http://magictale.com
 
 This example code is in the public domain.
 */

#include <util/delay.h>
#include <PT6311.h>

#define VFD_CS_PIN 1   //Just an example, specify your own correct pin number! This is STB in PT6311 datasheet notation.
#define VFD_CLK_PIN 2  //Just an example, specify your own correct pin number! This is CLK in PT6311 datasheet notation.
#define VFD_DATA_PIN 3 //Just an example, specify your own correct pin number! This is DIN in PT6311 datasheet notation.

#define VFD_BYTES_PER_DIGIT 3      //3
PT6311 pt6311_driver;

void write_raw(uint8_t value, uint8_t number_of_bytes) 
{
    pt6311_driver.displayMemWriteCmd(true, false);
    for (uint8_t i = 0; i < number_of_bytes; i++)
    {
        pt6311_driver.data(value, false, ((i + 1) == number_of_bytes));
    }
}

void fill_mem(uint8_t value, uint8_t number_of_bytes, uint8_t start_addr)
{
    //Set PT6311 address to point at 0x0 (the very beginning of its frame buffer)
    pt6311_driver.addrSetCmd(start_addr); 

    //And finally, switch on all segments for first three digits to make sure that display works.
    write_raw(value, number_of_bytes);
}

void setup()
{
  //Initialise pins
  pt6311_driver.init(VFD_CS_PIN, VFD_CLK_PIN, VFD_DATA_PIN);
  
  //Switch display on. Just an example, specify correct mode (number of digits and segment for your hardware)
  pt6311_driver.reset(VFD_DISP_MODE_10D18S); // good VFD_DISP_MODE_10D18S
  //If doesn't work try also VFD_DISP_MODE_9D19S, VFD_DISP_MODE_10D18S, VFD_DISP_MODE_11D17S VFD_DISP_MODE_12D16S

  for (uint8_t i = 0; i < 12; i++) //9
  {
      fill_mem(0x00, VFD_BYTES_PER_DIGIT, i * VFD_BYTES_PER_DIGIT);
      delay(10); 
      //fill_mem(0, VFD_BYTES_PER_DIGIT * 9, 0);
  }
  /*
  for (uint8_t i = 0; i < 5; i++) //9
  {
      fill_mem(0x1, VFD_BYTES_PER_DIGIT, i * VFD_BYTES_PER_DIGIT);
      delay(100); 
      //fill_mem(0, VFD_BYTES_PER_DIGIT * 9, 0);
  }
  */
 /*
  for (uint8_t i = 0; i < 28; i+=3) //9
  {
  pt6311_driver.addrSetCmd(i);
  pt6311_driver.displayMemWriteCmd(true, false);
  //pt6311_driver.data(0, false, false);
  pt6311_driver.data(255, false, false);
  pt6311_driver.data(255, false, false);
  pt6311_driver.data(0x00, false, true);
  }
  */
  pt6311_driver.addrSetCmd(3);
  pt6311_driver.displayMemWriteCmd(true, false);
  //pt6311_driver.data(0, false, false);
  pt6311_driver.data(8, false, false);
  pt6311_driver.data(132, false, false);
  pt6311_driver.data(0, false, true);
  
 //pt6311_driver.displayLEDWriteCmd(true, false);
 //pt6311_driver.data(0, false, true);
}

void loop()
{  
    //Don't do any work here - just a stub
    while (1)
    {
      //fill_mem(0x08, 1/*VFD_BYTES_PER_DIGIT*/, 3/*1 * VFD_BYTES_PER_DIGIT*/);
      //pt6311_driver.addrSetCmd(13);
      //pt6311_driver.displayMemWriteCmd(true, false);
      //pt6311_driver.data(1, false, true);
      int i=64;
      for (int j=0;j<3;j++){
      
      pt6311_driver.addrSetCmd(0);
      pt6311_driver.displayMemWriteCmd(true, false);
      pt6311_driver.data(8+i, false, false);
      pt6311_driver.data(0, false, false);
      pt6311_driver.data(0, false, true);
        i/=2;
        delay(100);
      }
      
      /*
      pt6311_driver.displayLEDWriteCmd(true, false);
      pt6311_driver.data(0, false, true);
      delay(1000); 
      pt6311_driver.displayLEDWriteCmd(true, false);
      pt6311_driver.data(255, false, true);
      delay(1000);
      */     
    }
}
