from RPIO import PWM

PWM.setup(1,0)
PWM.init_channel(0)

PWM.add_channel_pulse(0,17,0,100)
