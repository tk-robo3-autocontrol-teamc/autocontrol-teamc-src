import time
import RPi.GPIO as GPIO

HCSR04_TRIG_BCM_PIN = 14
HCSR04_ECHO_BCM_PIN = 4

class HCSR04:
    def __init__(self, trig_pin=HCSR04_TRIG_BCM_PIN, echo_pin=HCSR04_ECHO_BCM_PIN):
        GPIO.setmode(GPIO.BCM)
        self.trig_bcm_pin = trig_pin
        self.echo_bcm_pin = echo_pin
        GPIO.setup(self.trig_bcm_pin, GPIO.OUT)
        GPIO.setup(self.echo_bcm_pin, GPIO.IN)

    def getEchoTime(self):
        GPIO.output(self.trig_bcm_pin, GPIO.LOW)
        time.sleep(0.001)
        GPIO.output(self.trig_bcm_pin, GPIO.HIGH)
        time.sleep(0.000_01)
        GPIO.output(self.trig_bcm_pin, GPIO.LOW)

        while GPIO.input(self.echo_bcm_pin) == GPIO.LOW:
            echo_off = time.time()

        while GPIO.input(self.echo_bcm_pin) == GPIO.HIGH:
            echo_on = time.time()

        print(echo_off)
        print(echo_on)
        echo_time = echo_on - echo_off
        print(echo_time)
        return echo_time
    
    def getDistance(self, temp=25):
        echo_time = self.getEchoTime()
        distance = (331.50 + 0.606681 * temp) * echo_time / 2.0
        return distance

if __name__ == '__main__':
    hcsr04_instance = HCSR04(HCSR04_TRIG_BCM_PIN, HCSR04_ECHO_BCM_PIN)

    while True:
        try:
            temp = 25
            distance = hcsr04_instance.getDistance(temp)
            print(f"distance: {distance * 100}cm")
            time.sleep(1)
        except KeyboardInterrupt:
            print("Control-C is detected.")
            break

    print("GPIO is now being cleaned-up.")
    GPIO.cleanup()
