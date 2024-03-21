from pydantic import BaseModel
from datetime import datetime


class TemperatureValue(BaseModel):
    value: float
    location: str
    device_id: str


class TemperatureSaved(TemperatureValue):
    id: int
    timestamp: datetime

    class Config:
        orm_mode = True
