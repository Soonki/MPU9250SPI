#include "MPU9250SPI.h"
//The setup function is called once at startup of the sketch
MPU9250SPI m_9250SPI;
int magSelect = 10;

void setup()
{
	// Add your initialization code here
	Serial.begin(115200);

	m_9250SPI = MPU9250SPI();
	m_9250SPI.init(magSelect);
	delay(200);

	m_9250SPI.setupMPU9250_MagRead();
}

// The loop function is called in an endless loop
void loop()
{
	delay(50);
	//Add your repeated code here
	//m_9250SPI.testConnectionToMPU9250();

	//Read Mag data from AK8930 by 9250 I2C Master
	digitalWrite(magSelect, LOW);
	SPI.transfer(MPU9250_REG_EXT_SENS_DATA_00|MPU9250_SPI_READ_MASK);
	byte ST1 = SPI.transfer(0xFF);
	byte X_LSB = SPI.transfer(0xFF);
	byte X_MSB = SPI.transfer(0xFF);
	byte Y_LSB = SPI.transfer(0xFF);
	byte Y_MSB = SPI.transfer(0xFF);
	byte Z_LSB = SPI.transfer(0xFF);
	byte Z_MSB = SPI.transfer(0xFF);
	byte ST2 = SPI.transfer(0xFF);
	digitalWrite(magSelect, HIGH);

	short int x = ((X_MSB << 8) | X_LSB);
	short int y = ((Y_MSB << 8) | Y_LSB);
	short int z = ((Z_MSB << 8) | Z_LSB);

	Serial.print("F East:");
	Serial.print(y);
	Serial.print("\t");

	Serial.print("F North:");
	Serial.print(x);
	Serial.print("\t");

	Serial.print("F Sky:");
	Serial.print(z);
	Serial.print("\t");

	Serial.print("ST1:");
	Serial.print(ST1, BIN);
	Serial.print("\t");

	Serial.print("ST2:");
	Serial.print(ST2, BIN);
	Serial.print("\n");
}
