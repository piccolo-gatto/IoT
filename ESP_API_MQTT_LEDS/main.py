import requests
import time
import asyncio
#172.20.10.2
SERVER_URL = "http://127.0.0.1:8055"

broker = "broker.emqx.io"
TOPIC = "lab/ESP8266_1B9B/strip/set_leds"


async def get_colors(user, device):
    response = requests.post(f"{SERVER_URL}/all_leds", json={'user_id': int(user), 'device_id': int(device)})
    if response.status_code == 200:
        return response.json()
    else:
        print('get colors', response)
        return None


def send_color(device, color):
    client = mqtt_client.Client('isu10012300')
    topic = f"{TOPIC}"
    print("Connecting to broker", broker)
    print(client.connect(broker))
    client.publish(topic, color)
    time.sleep(2)
    print(f"Color {color} sent to device {device}")


async def pub():
    while True:
        user = str(input('print user id: '))
        device = str(input('print device id: '))
        data = await get_colors(user, device)
        if data:
            for row in data:
                color = row["colors_id"]
                code = requests.post(f"{SERVER_URL}/get_led", json={'color_id': color}).json()['color']
                send_color(device, code)

        await asyncio.sleep(5)

if __name__ == '__main__':
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    try:
        loop.run_until_complete(pub())
    except KeyboardInterrupt:
        pass


