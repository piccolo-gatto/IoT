import uvicorn
from fastapi import FastAPI

from database import engine, Base
from devices.router import router as devices_router
from users.router import router as users_router
from leds.router import router as leds_router

Base.metadata.create_all(bind=engine)
app = FastAPI()
app.include_router(devices_router)
app.include_router(users_router)
app.include_router(leds_router)

if __name__ == "__main__":
    uvicorn.run(app, host='localhost', port=8005)
