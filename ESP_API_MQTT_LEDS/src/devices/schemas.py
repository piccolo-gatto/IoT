from pydantic import BaseModel
from datetime import datetime


class NewDevice(BaseModel):
    id: str
    user_id: int


class DeviceSaved(NewDevice):
    id: str
    user_id: int

    class Config:
        orm_mode = True
