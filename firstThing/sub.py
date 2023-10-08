import paho.mqtt.client as paho
import serial
import time


broker = "broker.emqx.io"

port = "COM3" # COM3 for windows
connection = serial.Serial(port, timeout=1)

def send_command(cmd: str, response_len: int) -> str:
    str_resp = None
    connection.write(cmd.encode())
    if response_len != 0:
        resp = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp


def on_message(client, userdata, message):
    time.sleep(1)
    data = str(message.payload.decode("utf-8"))
    print("received message =", data)
    if data == "led on":
        resp = send_command("u", 6)
    elif data == "led off":
        resp = send_command("d", 7)


client = paho.Client("client-isu-0087")
client.on_message=on_message

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Subscribing")
client.subscribe("Katya/Alena")
time.sleep(120)
client.disconnect()
client.loop_stop()