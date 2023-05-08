bool failed_to_setup = false;
bool freq_set_failed = false;
long randNumber;
int packetNum = 0;
float timeStep;
float a, b, c, d, e, f;
char serial_text[255] = "";
float g_x, g_y, g_z, a_x, a_y, a_z, lin_x, lin_y, lin_z;
float p_alt, internal_press, pitot_press, g_alt, pitot_vel;
float thermo_1, thermo_2, thermo_3,thermo_4,thermo_5,thermo_6,thermo_7,thermo_8;
char g_x_s[9], g_y_s[9], g_z_s[9], a_x_s[9], a_y_s[9], a_z_s[9], lin_x_s[9], lin_y_s[9], lin_z_s[9];
char p_alt_s[9], internal_press_s[9], pitot_press_s[9], g_alt_s[9], pitot_vel_s[9];
char thermo_1_s[9], thermo_2_s[9], thermo_3_s[9],thermo_4_s[9],thermo_5_s[9],thermo_6_s[9],thermo_7_s[9],thermo_8_s[9];
int rssi;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  if (random(0,20) == 1)
  {
    failed_to_setup = true;
    if (random(0,2) == 1) freq_set_failed = true;
  }
  timeStep = 0;
  a = 5;
  b = 5;
  c = 5;
  d = 5;
  e = 5;
  f = 5;
}

void loop() {
  if (failed_to_setup)
  {
    if (freq_set_failed) Serial.println("1 3");
    else Serial.println("1 2");
    return;
  }
  // put your main code here, to run repeatedly:
  randNumber = random(0, 100);
  if (randNumber == 1)
  {
    Serial.println("1,d1");
  }
  else if (randNumber < 3)
  {
    Serial.println("1 1");
  }
  else if (randNumber < 5)
  {
    Serial.println("1 0");
  }
  else
  {
    g_x = a *10 * sin(timeStep + b);
    g_y = b * 10 * cos(b*timeStep + d);
    g_z = c * 10 *  sin(timeStep + e);

    a_x = f * b * cos(e*timeStep+f);
    a_y = c * d * sin(timeStep+a);
    a_z = f * a * cos(c*timeStep+c);

    lin_x = a_x - g_x;
    lin_y = a_y - g_y;
    lin_z = a_z - g_z;

    p_alt = a *c*5 * (4+sin(a*timeStep + d));
    internal_press = e *5 * (2+sin(b*timeStep + f));
    g_alt = b *f*5 * (5+sin(a*timeStep + a));

    pitot_press = e *5*c * (2+cos(b*timeStep + f));
    pitot_vel = c *a*5 * (5+sin(f*timeStep + c));

    thermo_1 = 130 + a * cos(timeStep + c);
    thermo_2 = 120 + b * cos(a*timeStep + f);
    thermo_3 = 110 + d * cos(timeStep + d);
    thermo_4 = 100 + e * cos(d*timeStep + b);
    thermo_5 = 90 + a * cos(timeStep + a);
    thermo_6 = 80 + f * cos(timeStep + f);
    thermo_7 = 70 + a * cos(timeStep + d);
    thermo_8 = 60 + c * cos(timeStep + a);

    rssi = (1-cos(timeStep)) * 50;
    timeStep += (long)millis() / 5000.0;
    a = a * 0.95 + random(8) * .05;
    b = b * 0.95 + random(8)  * .05;
    c = c * 0.95 + random(8)  * .05;
    d = d * 0.95 + random(8)  * .05;
    e = e * 0.95 + random(8)  * .05;
    f = f * 0.95 + random(8)  * .05;
    dtostrf(g_x, 7, 3, g_x_s);
    dtostrf(g_y, 7, 3, g_y_s);
    dtostrf(g_z, 7, 3, g_z_s);
    dtostrf(a_x, 7, 3, a_x_s);
    dtostrf(a_y, 7, 3, a_y_s);
    dtostrf(a_z, 7, 3, a_z_s);
    dtostrf(lin_x, 7, 3, lin_x_s);
    dtostrf(lin_y, 7, 3, lin_y_s);
    dtostrf(lin_z, 7, 3, lin_z_s);
    dtostrf(p_alt, 8, 4, p_alt_s);
    dtostrf(internal_press, 8, 4, internal_press_s);
    dtostrf(g_alt, 8, 4, g_alt_s);
    dtostrf(pitot_press, 8, 4, pitot_press_s);

    dtostrf(pitot_vel, 8, 4, pitot_vel_s);
    dtostrf(thermo_1, 8, 4, thermo_1_s);
    dtostrf(thermo_2, 8, 4, thermo_2_s);
    dtostrf(thermo_3, 8, 4, thermo_3_s);
    dtostrf(thermo_4, 8, 4, thermo_4_s);
    dtostrf(thermo_5, 8, 4, thermo_5_s);
    dtostrf(thermo_6, 8, 4, thermo_6_s);
    dtostrf(thermo_7, 8, 4, thermo_7_s);
    dtostrf(thermo_8, 8, 4, thermo_8_s);

    sprintf(serial_text, "%d %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %i", 
                          packetNum, g_x_s, g_y_s, g_z_s, a_x_s, a_y_s, a_z_s, lin_x_s, lin_y_s, lin_z_s, p_alt_s, internal_press_s, g_alt_s, pitot_press_s, pitot_vel_s, thermo_1_s, thermo_2_s, thermo_3_s, thermo_4_s, thermo_5_s, thermo_6_s, thermo_7_s, thermo_8_s, rssi);
    Serial.println(serial_text);
    
    delay(100);
    
  }
  packetNum = (packetNum + 1) % 10;
}
