# получить че нить с esp
# import time
# import paho.mqtt.client as mqtt_client
# import random
#
# broker="broker.emqx.io"
#
# def on_message(client, userdata, message):
#     time.sleep(1)
#     data = str(message.payload.decode("utf-8"))
#     print("received message =", data)
#
# client = mqtt_client.Client('isu10012300')
# # FOR new version change ABOVE line to
# #client = mqtt_client.Client(
# #    mqtt_client.CallbackAPIVersion.VERSION1,
# #    'isu10012300'
# #)
# client.on_message=on_message
#
# print("Connecting to broker",broker)
# client.connect(broker)
# client.loop_start()
# print("Subcribing")
# client.subscribe("lab/ESP8266_1B9B/strip/state")
# time.sleep(1800)
# client.disconnect()
# client.loop_stop()




# после есп чтобы посмотреть что есп получает данные
import time
import paho.mqtt.client as mqtt_client
import random

broker = "broker.emqx.io"

#client = mqtt_client.Client('isu10012300')
#FOR new version change ABOVE line to
client = mqtt_client.Client(
   mqtt_client.CallbackAPIVersion.VERSION1,
   'isu10012300'
)

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")

for i in range(10):
    state = "255000000000255000255000000000255000000000255"
    state = state[i:] + state[:i]
    print(f"state is {state}")
    client.publish("lab/ESP8266_1B9B/strip/set_leds", state)
    time.sleep(2)

client.disconnect()
client.loop_stop()





# import time
# import paho.mqtt.client as mqtt_client
# import random
#
# broker="broker.emqx.io"
#
# client = mqtt_client.Client('isu10012300')
# # FOR new version change ABOVE line to
# #client = mqtt_client.Client(
# #    mqtt_client.CallbackAPIVersion.VERSION1,
# #    'isu10012300'
# #)
#
# print("Connecting to broker",broker)
# print(client.connect(broker))
# client.loop_start()
# print("Publishing")
#
# state = "255255255"\
# "255000000"\
# "000000255"\
# "255255255"\
# "255000000"\
# "000000255"\
# "255255255"\
# "255000000"\
# "000000255"\
# "255255255"\
# "255000000"\
# "000000255"
#
# for i in range(10):
#     state = state[9:] + state[:9]
#     print(f"state is {state}")
#     client.publish("lab/ESP8266_1B9B/strip/set_leds", state)
#     time.sleep(2)
#
# client.disconnect()
# client.loop_stop()

