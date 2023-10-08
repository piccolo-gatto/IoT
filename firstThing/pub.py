import time
import paho.mqtt.client as paho


broker = 'broker.emqx.io'
client = paho.Client('client-isu-242')
print('Connecting to broker', broker)
client.connect(broker)
client.loop_start()
print('Publishing')

for _ in range(10):
  state = str(input('Enter the command: '))
  print(f'The command {state} was send')
  client.publish('Katya/Alena', state)
  time.sleep(1)

client.disconnect()
client.loop_stop()