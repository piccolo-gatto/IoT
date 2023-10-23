import time

counter_start = 0
counter_end = 0

import paho.mqtt.client as paho


broker = 'broker.emqx.io'
client = paho.Client('client-isu-242')
print('Connecting to broker', broker)
client.connect(broker)
client.loop_start()
topic = ''

while True:
    current_second = int(time.time() % 60)

    if current_second == 20 + counter_start:
        print(current_second, "sec")
        print("start", counter_start, "end", counter_end)
        print("Лампочка включена")
        time.sleep((40 - counter_end)-(20 + counter_start))

    elif current_second == 40 - counter_end:
        print(current_second, "sec")
        print("start", counter_start, "end", counter_end)
        print("Лампочка выключена")

        if counter_end % 2 == 1:
            counter_start += 1

        counter_end += 1
        if counter_end == 6:
            counter_end = 0

        if counter_start == 6:
            counter_start = 0

        time.sleep(59 - ((40 - counter_end) - (20 + counter_start)))

    else:
        time.sleep(1) 


client.disconnect()
client.loop_stop()
